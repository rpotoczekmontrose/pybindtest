#include <gtest/gtest.h>
#include "../fastlib/include/matrix.hpp"
#include "../fastlib/include/transformer.hpp"
#include "../fastlib/include/computations.hpp"
#include "../fastlib/include/math_utils.hpp"
#include "../fastlib/include/static_matrix.hpp"

using namespace fastlib;

TEST(MatrixTest, InitAndGetSet) {
    Matrix<double> m(2, 2, 3.0);
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            EXPECT_EQ(m.get(i, j), 3.0);
            m.set(i, j, 5.0);
            EXPECT_EQ(m.get(i, j), 5.0);
        }
    }
}

TEST(TransformerTest, ScaleTransformer) {
    Matrix<double> m(2, 2, 2.0);
    ScaleTransformer<double> scale(3.0);
    Matrix<double> result = scale.apply(m);

    for (size_t i = 0; i < result.rows(); i++) {
        for (size_t j = 0; j < result.cols(); j++) {
            EXPECT_EQ(result.get(i, j), 6.0);
        }
    }

    EXPECT_EQ(scale.name(), "Scale");
}

TEST(MatrixTest, Repr) {
    Matrix<double> m(2, 2, 1.0);
    auto r = m.repr();
    EXPECT_NE(r.find("Matrix"), std::string::npos);
}

TEST(ComputationsTest, RowNorms) {
    Matrix<double> m(3, 3, 0.0);
    m.set(0, 0, 3.0);
    m.set(0, 1, 4.0);
    m.set(1, 1, 5.0);
    m.set(2, 2, 12.0);

    auto norms = row_norms(m);
    ASSERT_EQ(norms.size(), 3);
    EXPECT_DOUBLE_EQ(norms[0], 5.0);   // sqrt(3^2 + 4^2)
    EXPECT_DOUBLE_EQ(norms[1], 5.0);   // sqrt(5^2)
    EXPECT_DOUBLE_EQ(norms[2], 12.0);  // sqrt(12^2)
}

TEST(ComputationsTest, Identity) {
    auto I = identity(4);
    EXPECT_EQ(I.rows(), 4);
    EXPECT_EQ(I.cols(), 4);
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (i == j) {
                EXPECT_EQ(I.get(i, j), 1.0);
            } else {
                EXPECT_EQ(I.get(i, j), 0.0);
            }
        }
    }
}

TEST(TransformerTest, ScaleTransformerOnIdentity) {
    ScaleTransformer<double> t(2.5);
    auto I = identity(3);
    auto result = t.apply(I);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (i == j) {
                EXPECT_EQ(result.get(i, j), 2.5);
            } else {
                EXPECT_EQ(result.get(i, j), 0.0);
            }
        }
    }
}

TEST(MathUtilsTest, SafeDivideInt) {
    EXPECT_EQ(safe_divide(10, 3), 3);
    EXPECT_EQ(safe_divide(9, 3), 3);
}

TEST(MathUtilsTest, SafeDivideDouble) {
    EXPECT_DOUBLE_EQ(safe_divide(10.0, 2.0), 5.0);
    EXPECT_DOUBLE_EQ(safe_divide(9.0, 3.0), 3.0);
}

TEST(MathUtilsTest, SafeDivideIntZero) {
    EXPECT_THROW(safe_divide(5, 0), std::runtime_error);
}

TEST(StaticMatrixTest, StaticMatrix2dIdentityAndAccess) {
    auto I2 = StaticMatrix<double, 2>::identity();
    EXPECT_EQ(I2.get(0, 0), 1.0);
    EXPECT_EQ(I2.get(0, 1), 0.0);

    I2.set(0, 1, 5.0);
    EXPECT_EQ(I2.get(0, 1), 5.0);

    EXPECT_TRUE(I2.repr().find("StaticMatrix") == 0);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}