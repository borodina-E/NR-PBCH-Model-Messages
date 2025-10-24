#include <gtest/gtest.h>
#include <complex>
#include <vector>
#include "scram.h"
#include <Eigen/Dense>
#include "dlsch_info.h"

TEST(segmented_tests, SegmentedC1) {
    // Подготовка тестовых данных
    std::vector<int> bitstream = {1, 0, 1, 1, 0};
    int len_bitstream = 5;
    int C = 1;
    int CBZ = 21;
    int F = 19;
    int L = 16;

    std::vector<int> input_symbols = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Ожидаемый результат

    Eigen::VectorXi expected_bits(40);
    expected_bits.setZero();

    // Задаём конкретную битовую последовательность
    std::vector<int> initial_bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, -1, -1, -1, -1, -1,
                                     -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    // Заполняем
    for (int i = 0; i < initial_bits.size() && i < 40; ++i) {
        expected_bits(i) = initial_bits[i];
    }

    // Вызов тестируемой функции
    MatrixXi actual_bits = segmented(input_symbols, C, CBZ, F);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(segmented_tests, SegmentedC2) {
    // Подготовка тестовых данных
    std::vector<int> bitstream = {1, 0, 1, 1, 0};
    int len_bitstream = 5;
    int C = 2;      // в основном коде для подобного результата надо внутри dlsch_info помнять C на 2 при B <= Kcb
    int CBZ = 11;
    int F = 9;
    int L = 16;

    std::vector<int> input_symbols = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Ожидаемый результат

    Eigen::MatrixXi expected_bits(44, 2);
    expected_bits.setZero();

    // Задаём конкретную битовую последовательность
    std::vector<int> initial_bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0,
                                     1, 1, 0, 0, 1, 1, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 0, 1, 1,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1,
                                     0, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    for (int col = 0; col < expected_bits.cols(); col++) {
        for (int row = 0; row < expected_bits.rows(); row++) {
            int index = col * expected_bits.rows() + row;
            expected_bits(row, col) = initial_bits[index];
        }
    }

    // Вызов тестируемой функции
    MatrixXi actual_bits = segmented(input_symbols, C, CBZ, F);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(segmented_tests, DesegmentedC1) {
    // Подготовка тестовых данных
    std::vector<int> bitstream = {1, 0, 1, 1, 0};
    int len_bitstream = 5;
    int C = 1;
    int CBZ = 21;
    int F = 19;
    int L = 16;

    Eigen::MatrixXi input_symbols(40, 1);
    input_symbols.setZero();

    std::vector<int> bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1,
                             -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    // Заполняем
    for (int i = 0; i < input_symbols.size() && i < 40; ++i) {
        input_symbols(i) = bits[i];
    }

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = desegmented(input_symbols, C, len_bitstream + L, F);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(segmented_tests, DesegmentedC2) {
    // Подготовка тестовых данных
    std::vector<int> bitstream = {1, 0, 1, 1, 0};
    int len_bitstream = 5;
    int C = 2;
    int CBZ = 11;
    int F = 9;
    int L = 16;

    Eigen::MatrixXi input_symbols(44, 2);
    input_symbols.setZero();

    std::vector<int> bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0,
                             1, 1, 0, 0, 1, 1, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1,
                             0, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    for (int col = 0; col < input_symbols.cols(); col++) {
        for (int row = 0; row < input_symbols.rows(); row++) {
            int index = col * input_symbols.rows() + row;
            input_symbols(row, col) = bits[index];
        }
    }

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = desegmented(input_symbols, C, len_bitstream + L, F);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(segmented_tests, Segment2DesegmentC1) {
    // Подготовка тестовых данных
    std::vector<int> bitstream = {1, 0, 1, 1, 0};
    int len_bitstream = 5;
    int C = 1;
    int CBZ = 21;
    int F = 19;
    int L = 16;


    std::vector<int> input_symbols = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Вызов одной из тстируемых функций
    MatrixXi seg = segmented(input_symbols, C, CBZ, F);

    // Ожидаемый результат + вызов одной из тестируемых функций
    std::vector<int> expected_bits = desegmented(seg, C, len_bitstream + L, F);

    // Проверка результата
    EXPECT_EQ(input_symbols, expected_bits);
}

TEST(segmented_tests, Segment2DesegmentC2) {
    // Подготовка тестовых данных
    std::vector<int> bitstream = {1, 0, 1, 1, 0};
    int len_bitstream = 5;
    int C = 2;
    int CBZ = 21;
    int F = 19;
    int L = 16;

    std::vector<int> input_symbols = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Вызов одной из тстируемых функций
    MatrixXi seg = segmented(input_symbols, C, CBZ, F);

    // Ожидаемый результат + вызов одной из тестируемых функций
    std::vector<int> expected_bits = desegmented(seg, C, len_bitstream + L, F);

    // Проверка результата
    EXPECT_EQ(input_symbols, expected_bits);
}

//
// Created by morda on 24.10.2025.
//
