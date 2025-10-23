#ifndef QPSK_DEMODULATE_DLSCH_INFO_H
#define QPSK_DEMODULATE_DLSCH_INFO_H

#include<string>
#include<vector>
#include <Eigen/Dense>

// Структура для информации о базовом графе
struct BgInfo {
    std::string CRC;        // crc
    int L;                  // pow crc
    int BGN;                // base graph number
    int B;                  // length of transport block after CRC attachment
};

// Структура для информации о сегментации входных данных
struct CbInfo {
    int C;                  // Number of code block segments
    int cbz;                // Number of bits in each code block (excluding CB-CRC bits and filler bits)
    int Lcb;                // Number of parity bits in each code block
    int F;                  // Number of filler bits in each code block = K - Kd
    int K;                  // Number of bits in each code block (including CB-CRC bits and filler bits)
    int Zc;                 // Selected lifting size
    std::vector<int> Z;     // Full lifting size set
};

// Основная структура информации DLSCH
struct DlschInfo {
    std::string CRC;
    int L;
    int BGN;
    int C;
    int Lcb;
    int F;
    int Zc;
    int K;
    int N;
    int CBZ;
};

// Основные функции
BgInfo getBgnInfo(int A, double R);

CbInfo getCbsInfo(int B, int bgn);

DlschInfo dlsch_info(int tbs, double R);


// segmented
// MatrixXi - матрица целых чисел (динамического размера)
typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> MatrixXi;

MatrixXi attachPbitsMatrix(MatrixXi cb, std::string crc_type, bool attach_zeros);

MatrixXi segmented(std::vector<int> blk, int C, int CBZ, int F);
//MatrixXi segmented(std::vector<int> blk, DlschInfo info);

#endif //QPSK_DEMODULATE_DLSCH_INFO_H

