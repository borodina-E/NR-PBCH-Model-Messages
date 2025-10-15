#include <iostream>
#include <cmath>
#include <vector>
#include "PolarCodingInterleaverPattern.h"
#include "PolarSequenceReliability.h"
#include "kron.h"
#include "MatrixVecMult.h"

using namespace std;

vector<uint8_t> polarCoding(vector<uint8_t>& input)
{
	int K = static_cast<int>(input.size());
	int N = 512;
	vector<uint8_t> output;
	output.reserve(K);
	vector<int> IP = P;
	for(size_t m = 0, k = 0; m < 164; m++) {
		if(IP[m] >= 164 - K) {
			IP[k] = IP[m] - (164 - K);
			k++;
		}
	}
	for(int i = 0; i < K; i++) {
		output.push_back(input[IP[i]]);
	}

	vector<int> Q_0_Nmax = PolSeqRel;
	vector<int> Q_0_N;
	for(int i = 0; i < 1023; i++) {
		if(Q_0_N.size() > N)
			break;
		if(Q_0_Nmax[i] < N) {
			Q_0_N.push_back(Q_0_Nmax[i]);
		}
	}

	vector<int> Q_I_N;
	for(size_t j = Q_0_N.size() - K; j < Q_0_N.size(); j++) {
		Q_I_N.push_back(Q_0_N[j]);
	}

	vector<vector<int>> G_2(2, vector<int>(2, 1));
	G_2[0][1]               = 0;
	vector<vector<int>> G_N = G_2;
	for(int i = 0; i < 8; i++) {
		G_N = kron(G_2, G_N);
	}
	vector<uint8_t> u(N, 0);
	for(int n = 0, k = 0; n < N; n++) {
		auto result{find(Q_I_N.begin(), Q_I_N.end(), n)};
		if(result != Q_I_N.end()) {
			u[n] = output[k];
			k++;
		}
		else {
			u[n] = 0;
		}
	}
	output.clear();
	vector<uint8_t> Mult = MatrixVecMult(u, G_N);

	for(int n: Mult) {
		output.push_back(n % 2);
	}
	return output;
};
int main()
{
	vector<uint8_t> codeword{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	                         0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1};
	vector<uint8_t> outputCodeword = polarCoding(codeword);
	for(auto n: outputCodeword) {
		cout << static_cast<int>(n);
	}
}
