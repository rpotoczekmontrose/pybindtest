#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>
#include <atomic>

namespace fastlib
{

    class ThreadPool
    {
    public:
        explicit ThreadPool(size_t threads = std::thread::hardware_concurrency())
        {
            stop_.store(false);
            for (size_t i = 0; i < threads; i++)
                workers_.emplace_back([this]
                                      { this->worker_loop(); });
        }
        ~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lock(m_);
                stop_.store(true);
            }
            cv_.notify_all();
            for (auto &t : workers_)
                if (t.joinable())
                    t.join();
        }

        template <typename F, typename... Args>
        auto enqueue(F &&f, Args &&...args) -> std::future<std::invoke_result_t<F, Args...>>
        {
            using Ret = std::invoke_result_t<F, Args...>;
            auto task = std::make_shared<std::packaged_task<Ret()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            std::future<Ret> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(m_);
                tasks_.emplace([task]()
                               { (*task)(); });
            }
            cv_.notify_one();
            return res;
        }

    private:
        void worker_loop()
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(m_);
                    cv_.wait(lock, [this]
                             { return stop_.load() || !tasks_.empty(); });
                    if (stop_.load() && tasks_.empty())
                        return;
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
                task();
            }
        }

        std::vector<std::thread> workers_;
        std::queue<std::function<void()>> tasks_;
        std::mutex m_;
        std::condition_variable cv_;
        std::atomic<bool> stop_{false};
    };

} // namespace fastlib