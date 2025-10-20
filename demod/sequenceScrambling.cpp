#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

// ?? как быть с unit32_t ?? размер для x1 и x2 31 или len + 1600?

std::vector<int> sequenceScrambling(uint32_t cinit_unit32, std::vector<int> codeword) {
    // зададим необходимые параметры n_RNTI и nID
    double n_RNTI = 65535;
    double nID = 17;
    //auto cinit_unit32 = uint32_t(cinit); // auto вместо uint32_t

    // get scramble sequence 38.211 5.2.1 + 7.3.2.3
    auto len = std::size(codeword); // длина входной последовательности // auto вместо int

    std::vector<int> x1(31, 0); // массив нулей х1
    x1[0] = 1;

    std::vector<int> x2(31, 0); // массив нулей х2

    for (int i = 0;
         i < 31; i++) {              // перевод cinit в биты??   Нужны: bitand - побитовое и and bitshift - сдвиг
        x2[i] = (cinit_unit32 >> i) & 1; // ?? х[i]
    }

    // ?? увеличили размеры векторов для генерации последовательности
    auto total_length = len + 1600; // вместо int записал auto -> выдало size_t
    x1.resize(total_length, 0);
    x2.resize(total_length, 0);

    // Генерация последовательности с начальным сдвигом Nc
    for (int n = 0; n < len + 1600 - 31; n++) {             // тут с 0 тк c++ убрал +1 в крайнем значении
        x1[n + 31] = (x1[n + 3] + x1[n]) % 2;               // ранее делал через fmod()
        x2[n + 31] = (x2[n + 3] + x2[n + 2] + x2[n + 1] + x2[n]) % 2;
    }

    std::vector<int> sequence(len + 1600, 0); // длина последовательности с учётом сдвига

    // Комбинируем последовательность
    for (int n = 0; n < len; n++) { // убрал +1
        // sequence[n] = fmod(x1[n + 1600] + x2[n + 1600], 2);
        sequence[n] = (x1[n + 1600] + x2[n + 1600]) % 2;
    }

    sequence.resize(len); // убираем мусорные биты

    return sequence;
}


// Created by morda on 08.10.2025.

