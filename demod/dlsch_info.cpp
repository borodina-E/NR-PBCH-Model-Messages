#include "dlsch_info.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

DlschInfo dlsch_info(int tbs, double R) {
    DlschInfo info;
    // Get base graph information
    BgInfo bginfo = getBgnInfo(tbs, R);

    // Get code block segment information
    CbInfo cbinfo = getCbsInfo(bginfo.B, bginfo.BGN);

    // Get number of bits after LDPC encoding
    int N;
    if (bginfo.BGN == 1) {
        N = 66 * cbinfo.Zc;
    } else {
        N = 50 * cbinfo.Zc;
    }

    // Combine information into the output structure
    info.CRC = bginfo.CRC;
    info.L = bginfo.L;
    info.BGN = bginfo.BGN;
    info.C = cbinfo.C;
    info.Lcb = cbinfo.Lcb;
    info.F = cbinfo.F;
    info.Zc = cbinfo.Zc;
    info.K = cbinfo.K;
    info.N = N;
    info.CBZ = cbinfo.cbz;

    return info;
}

BgInfo getBgnInfo(int tbs, double R) {
    BgInfo info;
    // Cast A to double, to make all the output fields have same data type
    double A = static_cast<double>(tbs);

    // LDPC base graph selection
    if (A <= 292 || (A <= 3824 && R < 0.67) || R <= 0.25) {
        info.BGN = 2;
    } else {
        info.BGN = 1;
    }

    // Get transport block size after CRC attachment according to 38.212
    // 6.2.1 and 7.2.1, and assign CRC polynomial to CRC field of output
    // structure info

    std::string crc;
    if (A > 3824) {
        info.L = 24;
        info.CRC = "24A";
    } else {
        info.L = 16;
        info.CRC = "crc16";
    }

    // Get the length of transport block after CRC attachment
    info.B = tbs + info.L;

    return info;
}

CbInfo getCbsInfo(int B, int bgn) {
    CbInfo info;

    // Cast B to double, to make all the output fields have same data type
    double A = static_cast<double>(B);

    // Get the maximum code block size
    int Kcb;
    if (bgn == 1) {
        Kcb = 8448;
    } else {
        Kcb = 3840;
    }

    // Get number of code blocks and length of CB-CRC coded block
    int L; // for crc
    int C;
    int Bd;

    if (B <= Kcb) {
        L = 0;
        C = 2;
        Bd = B;
    } else {
        L = 24;                 // Length of the CRC bits attached to each code block
        //C = static_cast<int>(std::ceil(B / static_cast<double>(Kcb - L)));
        C = int(std::ceil(B / (Kcb - L)));
        Bd = B + C * L;
    }

    // Obtain the number of bits per code block (excluding CB-CRC bits)
    int cbz = static_cast<int>(std::ceil(static_cast<double>(B) / C));
    //int cbz = std::ceil(B / C);

    // Get number of bits in each code block (excluding filler bits);
    int Kd = static_cast<int>(std::ceil(static_cast<double>(Bd) / C));
    //int Kd = std::ceil(Bd / C);

    // Find the minimum value of Z in all sets of lifting sizes in 38.212
    // Table 5.3.2-1, denoted as Zc, such that Kb*Zc>=Kd

    int Kb;
    if (bgn == 1) {
        Kb = 22;
    } else {
        if (B > 640) {
            Kb = 10;
        } else if (B > 560) {
            Kb = 9;
        } else if (B > 192) {
            Kb = 8;
        } else {
            Kb = 6;
        }
    }

    // Lifting sizes from 38.212 Table 5.3.2-1
    std::vector<int> Zlist;

    for (int i = 2; i <= 16; i++) Zlist.push_back(i);
    for (int i = 18; i <= 32; i += 2) Zlist.push_back(i);
    for (int i = 36; i <= 64; i += 4) Zlist.push_back(i);
    for (int i = 72; i <= 128; i += 8) Zlist.push_back(i);
    for (int i = 144; i <= 256; i += 16) Zlist.push_back(i);
    for (int i = 288; i <= 384; i += 32) Zlist.push_back(i);

    // Find minimum Z such that Kb * Z >= Kd
    int Zc = 384; // start with maximum
    for (int Z: Zlist) {
        if (Kb * Z >= Kd && Z < Zc) {
            Zc = Z;
        }
    }

    // Get number of bits (including filler bits) for LDPC encoder
    int K;
    if (bgn == 1) {
        K = 22 * Zc;
    } else {
        K = 10 * Zc;
    }

    info.C = C;
    info.cbz = cbz;
    info.Lcb = L;
    info.F = K - Kd;
    info.K = K;
    info.Zc = Zc;
    info.Z = Zlist;

    return info;

}

//
// Created by morda on 17.10.2025.
//
