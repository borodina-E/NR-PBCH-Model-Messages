#include <vector>
#include "scram.h"
#include <bitset>

std::vector<int> attachParityBits(std::vector<int> bitstream, std::string crc_type, bool attach_zeros) {

    // poly initializing
    std::vector<int> Dpos;   // degree (pow )generation polynomials
    int L;                  // number of parity bits

    if (crc_type == "crc6") {
        Dpos = {5, 0};
        L = 6;

    } else if (crc_type == "crc11") {
        Dpos = {10, 9, 5, 0};
        L = 11;

    } else if (crc_type == "crc16") {
        Dpos = {12, 5, 0};
        L = 16;

    } else if (crc_type == "crc24a") {
        Dpos = {23, 18, 17, 14, 11, 10, 7, 6, 5, 4, 3, 1, 0};
        L = 24;

    } else if (crc_type == "crc24b") {
        Dpos = {23, 6, 5, 1, 0};
        L = 24;

    } else if (crc_type == "crc24c") {
        Dpos = {23, 21, 20, 17, 15, 13, 12, 8, 4, 2, 1, 0};
        L = 24;
    }

    int len_dpos = Dpos.size(); // количество

    // Пока не понял почему, но при crc24abc степени увеличиваются на один порядок +1
    if (crc_type == "crc24a" || crc_type == "crc24b" || crc_type == "crc24c") {
        for (int i = 0; i < len_dpos; i++) {
            Dpos[i] = Dpos[i] + 1;
        }
    }

    // reverse of the indexes (indexes are in the least significant order, but bits are in the most significant order).
    int dpos_0 = Dpos[0] + 1;
    for (int i = 0; i < len_dpos; i++) {
        Dpos[i] = dpos_0 - Dpos[i];
    }

    int len_bits = bitstream.size();   // length bitstream

    if (attach_zeros) {
        bitstream.insert(bitstream.end(), L, 0); // позволяет вставлять элементы по позициям. добавляем L нулей
    } else {
        len_bits = len_bits - L;
    }

    // shift registers word
    std::vector<int> crc(bitstream.begin(), bitstream.begin() + L);

    for (int n = 0; n < len_bits; n++) {
        int pulled_bit = crc[0];
        //shifting the word
        for (int i = 0; i < L - 1; i++) {
            crc[i] = crc[i + 1];
        }
        crc[L - 1] = bitstream[n + L];

        // subtraction (using XOR)
        if (pulled_bit) {
            for (int pos: Dpos) {
                crc[pos - 1] = crc[pos - 1] ^ 1;
            }
        }
    }

    // get result

    std::vector<int> data_with_crc;
    data_with_crc.reserve(len_bits + L); // указываем сколько будет храниться элементов, резервируем место

    // Добавляем данные (первые L бит) тк входная последовательность была изменена
    for (int i = 0; i < len_bits; i++) {
        data_with_crc.push_back(bitstream[i]);
    }

    // Добавляем CRC
    data_with_crc.insert(data_with_crc.end(), crc.begin(), crc.end());

    return data_with_crc;
}
//
// Created by morda on 12.10.2025.
//  в матлабе Circshift круглое смещение элементов массива на заданное количество позиций
// Bitshift - возвращает значение аргумента, сдвинутое на определённое количество бит
