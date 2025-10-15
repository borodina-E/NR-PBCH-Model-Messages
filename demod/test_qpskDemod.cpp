#include <gtest/gtest.h>
#include <complex>
#include <vector>
#include "scram.h"

TEST(QPSKDemodulationTest, BasicDemodulation) {
    // Подготовка тестовых данных
    std::vector<std::complex<double>> input_symbols = {
            {-0.7071, -0.7071},  // Ожидается: 1, 1
            {-0.7071, 0.7071},  // Ожидается: 1, 0
            {0.7071,  -0.7071},  // Ожидается: 0, 1
            {0.7071,  0.7071}   // Ожидается: 0, 0
    };

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 1, 1, 0, 0, 1, 0, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = qpskDemodulator(input_symbols);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(QPSKDemodulationTest, SingleSymbol) {
    std::vector<std::complex<double>> input_symbols = {{-0.7071, 0.7071}};
    std::vector<int> expected_bits = {1, 0};

    auto result = qpskDemodulator(input_symbols);

    EXPECT_EQ(result, expected_bits);
}

TEST(QPSKDemodulationTest, EmptyInput) {
    std::vector<std::complex<double>> input_symbols;
    std::vector<int> expected_bits;

    auto result = qpskDemodulator(input_symbols);

    EXPECT_EQ(result, expected_bits);
}

TEST(QPSKDemodulationTest, BoundaryValues) {
    // Тестирование граничных значений
    std::vector<std::complex<double>> input_symbols = {
            {0.0,     -0.7071},  // Реальная часть = 0
            {-0.7071, 0.0}   // Мнимая часть = 0
    };

    // Ожидаемое поведение при нулевых значениях
    std::vector<int> expected_bits = {0, 1, 1, 0};

    auto result = qpskDemodulator(input_symbols);

    EXPECT_EQ(result, expected_bits);
}