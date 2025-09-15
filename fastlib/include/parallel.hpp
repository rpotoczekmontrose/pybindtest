#pragma once
#include <vector>
#include <functional>
#include <numeric>
#include "thread_pool.hpp"

namespace fastlib
{

    template <typename InIt, typename Func>
    auto parallel_map(InIt begin, InIt end, Func f, size_t num_workers = 0)
    {
        if (num_workers == 0)
            num_workers = std::thread::hardware_concurrency();
        ThreadPool pool(num_workers);
        using OutT = std::invoke_result_t<Func, decltype(*begin)>;
        std::vector<std::future<OutT>> futures;
        for (auto it = begin; it != end; ++it)
        {
            futures.emplace_back(pool.enqueue([v = *it, &f]()
                                              { return f(v); }));
        }
        std::vector<OutT> out;
        out.reserve(futures.size());
        for (auto &fu : futures)
            out.push_back(fu.get());
        return out;
    }

    template <typename InIt, typename MapF, typename ReduceT, typename ReduceOp>
    ReduceT parallel_map_reduce(InIt begin, InIt end, MapF mapf, ReduceT init, ReduceOp op, size_t num_workers = 0)
    {
        auto mapped = parallel_map(begin, end, mapf, num_workers);
        return std::accumulate(mapped.begin(), mapped.end(), init, op);
    }

} // namespace fastlib