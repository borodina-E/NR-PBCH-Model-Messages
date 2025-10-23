#include <iostream>
#include <cmath>
#include <vector>
#include "RateMatchingInterleavingPattern.h"

using namespace std;

vector<uint8_t> RateRecovery(vector<uint8_t>& input)
{
	int E = 864;
	int N = 512;
	int K = 63;
	vector<uint8_t> outseq(N, 0);
	if(E >= N) {
		for(int i = 0; i < E; i++) {
			if(i < 512)
				outseq[i % N] = input[i];
		}
	}
	else if(static_cast<double>(K) / E <= 7.0 / 16.0) {
		for(int i = 0, j = 0; i < E, j < N; i++, j++) {
			outseq[j] = input[i];
		}
	}
	else {
		for(int i = 0; i < E; i++) {
			outseq[i] = input[i];
		}
	}
	vector<int> J(N, 0);
	vector<uint8_t> output(N, 0);
	vector<int> IP = RMIP;
	for(int n = 0; n < N; n++) {
		int i        = 32 * n / N;
		J[n]         = IP[i] * N / 32 + (n % (N / 32));
		output[J[n]] = outseq[n];
	}
	return output;
}
/*int main()
{
    vector<uint8_t> codeword(864, 0);
    for(int i = 0; i < 864; i++) {
        codeword[i] = rand() % 2;
    }
    vector<uint8_t> Codeword = RateRecovery(codeword);
    for(auto n: Codeword) {
        cout << static_cast<int>(n);
    }
}*/
