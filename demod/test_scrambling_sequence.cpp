#include <gtest/gtest.h>
#include <complex>
#include <vector>
#include "scram.h"


TEST(SequenceScramblingTest, BasicDemodulation) {
    // Подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 0, 1, 0, 1, 0, 1};
    double cinit = 2147418129;
    auto cinit_unit32 = uint32_t(cinit); // auto вместо uint32_t

    // Ожидаемый результат
    std::vector<int> expected_bits = {0, 1, 1, 1, 1, 1, 0, 1};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = sequenceScrambling(cinit_unit32, input_symbols);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}



// Created by morda on 08.10.2025.
