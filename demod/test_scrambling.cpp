#include <gtest/gtest.h>
#include <complex>
#include <vector>
#include "scram.h"

TEST(ScramblingDemodulationTest, BasicDemodulation) {
    // Подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 0, 1, 0, 1, 0, 1};

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 1, 1, 0, 1, 0, 0, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = scrambling(input_symbols);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}



// Created by morda on 08.10.2025.

