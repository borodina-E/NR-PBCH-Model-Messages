#include "perEncoder.h"
#include "perDecoder.h"
#include "polarCoding.h"
#include "polarDecoding.h"
#include "RateMatching.h"
#include "RateRecovery.h"
#include <iostream>
#include <vector>
#include "kron.h"

using namespace Eigen;
using namespace std;
/*
int main()
{
    vector<uint8_t> codeword(512, 0);
    for(int i = 0; i < 512; i++) {
        codeword[i] = rand() % 2;
    }
    for(auto n: codeword) {
        cout << static_cast<int>(n);
    }
    cout << endl;
    vector<uint8_t> outputCodeword = RateMatching(codeword);
    vector<uint8_t> Codeword       = RateRecovery(outputCodeword);
    for(auto n: Codeword) {
        cout << static_cast<int>(n);
    }
}*/
