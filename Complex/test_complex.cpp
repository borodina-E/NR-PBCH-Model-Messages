#include <gtest/gtest.h>
#include "Complex.h"

// конструкторы
TEST(ComplexConstructorTest, DefaultValues)
{
	Complex<double> c(3.0, 4.0);
	EXPECT_DOUBLE_EQ(c.getRe(), 3.0);
	EXPECT_DOUBLE_EQ(c.getIm(), 4.0);
}
TEST(ComplexConstructorTest, NegativeValues)
{
	Complex<double> c(-2.5, -1.5);
	EXPECT_DOUBLE_EQ(c.getRe(), -2.5);
	EXPECT_DOUBLE_EQ(c.getIm(), -1.5);
}
TEST(ComplexConstructorTest, CopyConstructor)
{
	Complex<double> original(5.0, -3.0);
	Complex<double> copy(original);

	EXPECT_DOUBLE_EQ(copy.getRe(), 5.0);
	EXPECT_DOUBLE_EQ(copy.getIm(), -3.0);
	EXPECT_TRUE(original == copy);
}
// математика
TEST(ComplexMathTest, Addition)
{
	Complex<int> a(4, 5);
	Complex<double> b(-5.0, 7.0);
	Complex<double> result = a + b;
	EXPECT_DOUBLE_EQ(result.getRe(), -1.0);
	EXPECT_DOUBLE_EQ(result.getIm(), 12.0);
}
TEST(ComplexMathTest, Subtraction)
{
	Complex<int> a(4.0, 5.0);
	Complex<float> b(-5.0, 7.0);
	Complex<float> result = a - b;
	EXPECT_FLOAT_EQ(result.getRe(), 9);
	EXPECT_FLOAT_EQ(result.getIm(), -2);
}
TEST(ComplexMathTest, Multiplication)
{
	Complex<float> a(4.0, 5.0);
	Complex<double> b(-5.0, 7.0);
	Complex<double> result = a * b;
	EXPECT_DOUBLE_EQ(result.getRe(), -55);
	EXPECT_DOUBLE_EQ(result.getIm(), 3);
}
TEST(ComplexMathTest, Division)
{
	Complex<double> a(4.0, 0.0);
	Complex<float> b(2.0, 0.0);
	Complex<double> result = a / b;

	EXPECT_DOUBLE_EQ(result.getRe(), 2.0);
	EXPECT_DOUBLE_EQ(result.getIm(), 0.0);
}
TEST(ComplexMathTest, Equality)
{
	Complex<double> a(4.0, 5.0);
	Complex<double> b(-5.0, 7.0);
	Complex<double> c(-5.0, 7.0);
	bool result1 = a == b;
	bool result2 = c == b;
	EXPECT_EQ(result1, false);
	EXPECT_EQ(result2, true);
}
// функции
TEST(ComplexFunctionTest, AbsoluteValue)
{
	Complex<double> c(3.0, 4.0);
	EXPECT_DOUBLE_EQ(c.abs(), 5.0);
}
TEST(ComplexFunctionTest, AbsoluteValue2)
{
	Complex<double> c(-3.0, 4.0);
	EXPECT_DOUBLE_EQ(c.abs2(), 25.0);
}
TEST(ComplexFunctionTest, Conjugate)
{
	Complex<float> c(-3.0, 4.0);
	Complex<float> conjugate = c.conj();
	EXPECT_DOUBLE_EQ(conjugate.getRe(), -3.0);
	EXPECT_DOUBLE_EQ(conjugate.getIm(), -4.0);
}
TEST(ComplexFunctionTest, ArgRad)
{
	Complex<double> a(1.0, 0.0);
	Complex<double> b(0.0, 1.0);
	Complex<double> c(-1.0, 0.0);
	Complex<double> d(1.0, 1.0);
	EXPECT_DOUBLE_EQ(a.argRad(), 0.0);
	EXPECT_DOUBLE_EQ(b.argRad(), M_PI / 2);
	EXPECT_DOUBLE_EQ(c.argRad(), M_PI);
	EXPECT_NEAR(d.argRad(), M_PI / 4, 1e-10);
}
TEST(ComplexFunctionTest, ArgDeg)
{
	Complex<double> c(1.0, 1.0);
	EXPECT_NEAR(c.argDeg(), 45.0, 1e-10);
}
// нулевые значения
TEST(ComplexZeroCaseTest, ZeroValues)
{
	Complex<double> c(0.0, 0.0);
	EXPECT_DOUBLE_EQ(c.getRe(), 0.0);
	EXPECT_DOUBLE_EQ(c.getIm(), 0.0);
	EXPECT_DOUBLE_EQ(c.abs(), 0.0);
	EXPECT_DOUBLE_EQ(c.argRad(), 0.0); // По определению
}
