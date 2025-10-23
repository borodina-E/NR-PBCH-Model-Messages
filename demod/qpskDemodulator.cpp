#include <iostream>
#include <complex>
#include <vector>
#include "scram.h"

std::vector<int> qpskDemodulator(std::vector<std::complex<double>> comp_ampl) {

    // способ задания комплексного числа с помощью встроенной библиотеки
    std::complex<double> num1(-0.7071, -0.7071);
    std::complex<double> num2(-0.7071, 0.7071);
    std::complex<double> num3(-0.7071, 0.7071);
    std::complex<double> num4(0.7071, 0.7071);

    // попытка 1: простой пример: на входе 4 qpsk символа

    //std::complex<double> comp_ampl[]{num1, num2, num3, num4};

    // длина входной последовательности
    int size_of_sequence = std::size(comp_ampl);
    int len = size_of_sequence;

    // Использование std::vector (ранее был динамический массив, но отказался от него)
    std::vector<int> bits_vec(len * 2, 0); // заполняется нулями

    // цикл перебора входящего комплексного числа из массива comp_ampl и получения выходной последовательности
    // кодированных бит, число которых в два раза больше длины входной последовательности.
    for (int i = 0; i < len; i++) {
        if (std::real(comp_ampl[i]) > 0) {
            bits_vec[2 * i] = (1 - 1) / 2;
        }
        if (std::real(comp_ampl[i]) < 0) {
            bits_vec[2 * i] = (1 - (-1)) / 2;
        }
        if (std::imag(comp_ampl[i]) > 0) {
            bits_vec[2 * i + 1] = (1 - 1) / 2;
        }
        if (std::imag(comp_ampl[i]) < 0) {
            bits_vec[2 * i + 1] = (1 - (-1)) / 2;
        }
    }

    // auto sequence = scrambling();
    return bits_vec;
}

// Created by morda on 08.10.2025.

