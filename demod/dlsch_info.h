#ifndef QPSK_DEMODULATE_DLSCH_INFO_H
#define QPSK_DEMODULATE_DLSCH_INFO_H

include<string>;
include<vector>;

// Структура для информации о базовом графе
struct BgInfo {
    std::string CRC;        // crc
    int L;                  // pow crc
    ing BGN;                // base graph number
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
};

// Основные функции
BgInfo getBgnInfo(int tbs, double R);

CbInfo getCbsInfo(int tbs, double R);

DlschInfo dlsch_info(int B, int bgn);

std::vector<int> segmented(std::vector<int> data, int F, int C)


#endif //QPSK_DEMODULATE_DLSCH_INFO_H

