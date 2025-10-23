#include <iostream>
#include <cmath>
#include <vector>
#include "RateMatchingInterleavingPattern.h"

using namespace std;

vector<uint8_t> RateMatching(vector<uint8_t>& input)
{
	int N = 512;
	vector<int> J(N, 0);
	vector<int> IP = RMIP;
	vector<uint8_t> seq(N, 0);
	vector<int> I(N, 0);
	/*	for(int n = 0; n < N; n++) {
	        I[n] = 32 * n / N;
	    }*/
	for(int n = 0; n < N; n++) {
		int i  = 32 * n / N;
		J[n]   = IP[i] * (N / 32) + (n % (N / 32));
		seq[n] = input[J[n]];
	}
	N     = static_cast<int>(seq.size());
	int E = 864;
	int K = 512;
	vector<uint8_t> output(E, 0);
	if(E >= N) {
		for(int i = 0; i < E; i++) {
			if(1 < E - N)
				output[i] = seq[i % N];
		}
	}
	else if(static_cast<double>(K) / E <= 7.0 / 16.0) {
		for(int i = 0, j = 0; i < E, j < N; i++, j++) {
			output[i] = seq[j];
		}
	}
	else {
		for(int i = 0; i < E; i++) {
			output[i] = seq[i];
		}
	}
	return output;
};
/*int main()
{
    vector<uint8_t> codeword(512, 0);
    for(int i = 0; i < 512; i++) {
        codeword[i] = rand() % 2;
    }
    vector<uint8_t> outputCodeword = RateMatching(codeword);
    *//*for(auto n: outputCodeword) {
	    cout << static_cast<int>(n);
	}*//*
}*/
