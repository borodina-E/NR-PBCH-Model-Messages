#include <iostream>
#include <complex>
#include <vector>
#include "scram.h"
#include <Eigen/Dense>
#include "dlsch_info.h"

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
    double R = 0.5137;


    std::vector<int> parity_bits = attachParityBits(bitstream, crc_type, attach_zeros);
    std::vector<int> symbols = qpskDemodulator(comp_ampl);
    std::vector<int> scrambling_bits = scrambling(codeword);
    std::vector<int> data = verifyParityBits(parity_bits, crc_type);
    int len_data = data.size();

    DlschInfo info_ldpc;
    info_ldpc = dlsch_info(len_data, R);
    //info_ldpc.C = 2;
    // стоит ли передавать целую структуру в виде парометра или так хорошо?
    MatrixXi segment_bits = segmented(data, info_ldpc.C, info_ldpc.CBZ, info_ldpc.F);


    // нужно desegmentation. После можно сделать юнит тесты? Какие? Потом ldpc
    return 0;
}