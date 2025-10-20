//
// Created by morda on 06.10.2025.
//

#ifndef QPSK_DEMODULATE_SCRAM_H
#define QPSK_DEMODULATE_SCRAM_H

#include <vector>
#include <complex>
#include <cstdint>


std::vector<int> scrambling(std::vector<int> codeword);

std::vector<int> sequenceScrambling(uint32_t cinit, std::vector<int> codeword);

std::vector<int> qpskDemodulator(std::vector<std::complex<double>> symbols);

std::vector<int> attachParityBits(std::vector<int> bitstream, std::string crc_type, bool attach_zeros);

std::vector<int> verifyParityBits(std::vector<int> bits, std::string crc_type);

//std::vector<int> qpsk_demodulate(const std::vector<std::complex<double>>& symbols);



#endif //QPSK_DEMODULATE_SCRAM_H


