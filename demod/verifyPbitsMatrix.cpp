#include "dlsch_info.h"
#include "scram.h"
#include <vector>
#include <stdexcept>
#include <Eigen/Dense>

// Вспомогательная функция для CRC декодирования матрицы

std::vector<int> verifyPbitsMatrix(MatrixXi cb, std::string crc_type) {
    int rows = cb.rows();
    int cols = cb.cols();
    std::vector<int> crcEncoded;
    std::vector<int> result;


    // Обрабатываем каждый столбец матрицы
    for (int col = 0; col < cols; col++) {

        // Преобразуем столбец матрицы в std::vector<int>
        std::vector<int> columnBits;
        for (int row = 0; row < rows; row++) {
            columnBits.push_back(cb(row, col));
        }

        // Применяем существующую функцию verifyParityBits для проверки ошибок
        crcEncoded = verifyParityBits(columnBits, crc_type);

        result.insert(result.end(), crcEncoded.begin(), crcEncoded.end());


    }
    return result; // на выходе вместо матрицы имеем вектор
}

//
// Created by morda on 24.10.2025.
//
