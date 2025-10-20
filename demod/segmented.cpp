#include "dlsch_info.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <Eigen/Dense>

// содержит реализацию attachParitybits для матриц

//std::vector<int> segmented(std::vector<int> trblk, int F, int C, int CBZ) {
MatrixXi segmented(std::vector<int> blk, int C, int CBZ, int F) {
    int blkLen = blk.size();
    std::string crc_type = "crc24b";
    bool attach_zeros = true;

    if (C == 1) {
        // Случай 1: один блок
        // Просто добавляем filler bits к исходному вектору
        std::vector<int> resultVector = blk;
        for (int i = 0; i < F; i++) {
            resultVector.push_back(-1);
        }

        // Преобразуем вектор в матрицу с одним столбцом
        MatrixXi resultMatrix(resultVector.size(), 1);
        for (int i = 0; i < resultVector.size(); i++) {
            resultMatrix(i, 0) = resultVector[i];
        }

        return resultMatrix;

    } else {
        // Случай 2: несколько блоков

        // Вычисляем сколько нулей нужно добавить
        int totalBits = CBZ * C;
        int zeroPadding = totalBits - blkLen;

        // Создаем расширенный вектор с нулями
        std::vector<int> extendedBlk = blk;
        for (int i = 0; i < zeroPadding; i++) {
            extendedBlk.push_back(0);
        }

        // Преобразуем вектор в матрицу (reshape)
        MatrixXi cb(CBZ, C);
        for (int col = 0; col < C; col++) {
            for (int row = 0; row < CBZ; row++) {
                int index = col * CBZ + row;
                cb(row, col) = extendedBlk[index];
            }
        }

        // Применяем CRC кодирование к матрице
        MatrixXi cbCRC = attachPbitsMatrix(cb, crc_type, attach_zeros);

        // Добавляем filler bits
        MatrixXi finalResult(cbCRC.rows() + F, C);

        // Копируем данные с CRC
        for (int col = 0; col < C; col++) {
            for (int row = 0; row < cbCRC.rows(); row++) {
                finalResult(row, col) = cbCRC(row, col);
            }
        }

        // Добавляем filler bits
        for (int col = 0; col < C; col++) {
            for (int row = cbCRC.rows(); row < finalResult.rows(); row++) {
                finalResult(row, col) = -1;
            }
        }

        return finalResult;
    }
}
//
// Created by morda on 17.10.2025.
//
