#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include "scram.h"

// ?? как быть с unit32_t ?? размер для x1 и x2 31 или len + 1600?

std::vector<int> scrambling(std::vector<int> codeword) {
    // зададим необходимые параметры n_RNTI и nID
    double n_RNTI = 65535;
    double nID = 17;
    auto len = std::size(codeword); // длина входной последовательности // auto вместо int

    // инициализируюшая последовательность cinit
    double left = (n_RNTI * pow(2, 16) + nID);
    double right = pow(2, 31);
    double cinit = fmod(left, right); // остаток от деление (mod 2) для типа double из <cmath>
    auto cinit_unit32 = uint32_t(cinit); // auto вместо uint32_t
    //uint32_t cinit = (n_RNTI << 16) + nID; // Более эффективно через битовый сдвиг


    std::vector<int> sequence = sequenceScrambling(cinit_unit32, codeword);

    // Применение скремблирования к входным данным
    std::vector<int> result(len, 0);
    for (int i = 0; i < len; i++) {
        result[i] = (codeword[i] + sequence[i]) % 2;
    }

    return result;
}