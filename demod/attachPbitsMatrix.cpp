#include "dlsch_info.h"
#include "scram.h"
#include <vector>
#include <stdexcept>
#include <Eigen/Dense>

// Вспомогательная функция для CRC кодирования матрицы

MatrixXi attachPbitsMatrix(MatrixXi cb, std::string crc_type, bool attach_zeros) {
    int rows = cb.rows();
    int cols = cb.cols();

    // Создаем матрицу для результата (добавляем 24 строки для CRC24B)
    MatrixXi result(rows + 24, cols);

    // Обрабатываем каждый столбец матрицы
    for (int col = 0; col < cols; col++) {

        // Преобразуем столбец матрицы в std::vector<int>
        std::vector<int> columnBits;
        for (int row = 0; row < rows; row++) {
            columnBits.push_back(cb(row, col));
        }

        // Применяем существующую функцию attachParityBits
        std::vector<int> crcEncoded = attachParityBits(columnBits, crc_type, true);

        // Преобразуем результат обратно в столбец матрицы
        for (int row = 0; row < crcEncoded.size(); row++) {
            result(row, col) = crcEncoded[row];
        }
    }
    return result;
}


//
// Created by morda on 20.10.2025.
//
