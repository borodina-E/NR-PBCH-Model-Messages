#include <vector>
#include "scram.h"
#include <bitset>
#include <numeric>

std::vector<int> verifyParityBits(std::vector<int> bits, std::string crc_type) {
    // poly initializing

    int L;                  // number of parity bits

    if (crc_type == "crc6") {
        L = 6;
    } else if (crc_type == "crc11") {
        L = 11;
    } else if (crc_type == "crc16") {
        L = 16;
    } else if (crc_type == "crc24a") {
        L = 24;
    } else if (crc_type == "crc24b") {
        L = 24;
    } else if (crc_type == "crc24c") {
        L = 24;
    }
    bool attach_zeros = false;
    std::vector<int> check_seq = attachParityBits(bits, crc_type, attach_zeros);

    // если он последовательности с crc взять ещё раз то часть с crc станет равна нулю

    std::vector<int> calculated_crc(check_seq.end() - L, check_seq.end());
    int sum = std::accumulate(calculated_crc.begin(), calculated_crc.end(), 0);

    // же операцию, будут везде нули
    if (sum == 0) {
        int len = bits.size();
        bits.resize(len - L);
    }

    return bits;
}



//
// Created by morda on 15.10.2025.
//
