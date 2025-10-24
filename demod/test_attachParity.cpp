#include "gtest/gtest.h"
#include <vector>
#include <cmath>
#include <cstdint>
#include "scram.h"


TEST(attachParityTest, crc16) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc16";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(attachParityTest, crc24c) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc24c";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0,
                                      0, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(attachParityTest, crc24a) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc24a";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1,0,1,1,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,1,0,0,1,0,1};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(attachParityTest, crc24b) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc24b";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1,
                                      0, 1};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(attachParityTest, crc6) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc6";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(attachParityTest, crc11) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc11";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0};

    // Вызов тестируемой функции
    std::vector<int> actual_bits = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

TEST(attachParityTest, verifytest) {
    // подготовка тестовых данных
    std::vector<int> input_symbols = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    std::string crc_type = "crc16";
    bool attach_zeros = true;

    // Ожидаемый результат
    std::vector<int> expected_bits = {1, 0, 1, 1, 0};

    // Вызов тестируемой функции 1
    std::vector<int> bits_with_crc = attachParityBits(input_symbols, crc_type, attach_zeros);

    // Вызов тестируемой функции 2
    std::vector<int> actual_bits = verifyParityBits(bits_with_crc, crc_type);

    // Проверка результата
    EXPECT_EQ(actual_bits, expected_bits);
}

//
// Created by morda on 12.10.2025.
//
