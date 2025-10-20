#include <iostream>
#include <complex>
#include <vector>
#include "scram.h"

int main() {

    // попытка 1: простой пример: на входе 4 qpsk символа

    std::vector<std::complex<double>> comp_ampl = {
            {-0.7071, -0.7071},
            {-0.7071, 0.7071},
            {-0.7071, 0.7071},
            {0.7071,  0.7071}
    };

    // из матлаба обрезанная последовательность
    std::vector<int> codeword = {1, 0, 0, 1, 0, 1, 0, 1};
    std::string crc_type = "crc16"; // crc24c
    //std::vector<int> bitstream = {1, 1, 0, 1, 1}; // из матлаба sib1 crc 16
    std::vector<int> bitstream = {1, 0, 1, 1, 0}; // из матлаба sib1 crc 16
    bool attach_zeros = true;
    std::vector<int> bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0}; // for crc16


    std::vector<int> parity_bits = attachParityBits(bitstream, crc_type, attach_zeros);
    std::vector<int> symbols = qpskDemodulator(comp_ampl);
    std::vector<int> scrambling_bits = scrambling(codeword);
    std::vector<int> data = verifyParityBits(parity_bits, crc_type);

    return 0;
}