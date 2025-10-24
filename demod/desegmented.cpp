#include "dlsch_info.h"
#include <vector>
#include <stdexcept>
#include <Eigen/Dense>

std::vector<int> desegmented(MatrixXi cbs, int C, int blklen, int F) {
    // F - Number of filler bits in each code block
    // CBZ - Number of bits in each code block (excluding CB-CRC bits and filler bits)
    // C - Number of code block segments

    std::string crc_type = "crc24b";            //
    // Убираем filler bits (последние F строк)
    MatrixXi cbi(cbs.rows() - F, cbs.cols());
    for (int col = 0; col < cbs.cols(); col++) {
        for (int row = 0; row < cbs.rows() - F; row++) {
            cbi(row, col) = cbs(row, col);
        }
    }

    std::vector<int> blk;

    if (C == 1) {
        // Случай 1: один блок
        // Просто преобразуем матрицу в вектор
        for (int i = 0; i < cbi.rows(); i++) {
            blk.push_back(cbi(i, 0));
        }

    } else {
        // Случай 2: несколько блоков
        // Применяем CRC декодирование
        blk = verifyPbitsMatrix(cbi, crc_type);
    }

    // Обрезаем до исходной длины blklen. Так как в случае нечётного количества бит полезной нагрузки+crc, то добавится в столбец матрицы 1 лишний ноль
    if (blk.size() > blklen) {
        blk.resize(blklen);
    }

    return blk;
}


//
// Created by morda on 24.10.2025.
//
