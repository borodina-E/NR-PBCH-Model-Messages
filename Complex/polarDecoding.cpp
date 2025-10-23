#include <iostream>
#include <cmath>
#include <vector>
#include "PolarCodingInterleaverPattern.h"
#include "PolarSequenceReliability.h"
#include "kron.h"
#include <Eigen/Dense>
#include "convertToEigenVector.h"
#include "convertToEigenMatrix.h"
#include "convertRowVectorToUint8.h"

using namespace Eigen;
using namespace std;

vector<uint8_t> polarDecoding(vector<uint8_t>& input)
{
	int N                = static_cast<int>(input.size());
	int K                = 63;
	vector<int> Q_0_Nmax = PolSeqRel;
	vector<int> Q_0_N;
	for(int i = 0; i < 1024; i++) {
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
	int Power               = log2(N);
	for(int i = 0; i < Power - 1; i++) {
		G_N = kron(G_2, G_N);
	}
	RowVectorXd eigen_input = convertToEigenVector(input);
	MatrixXd eigen_G_N      = convertToEigenMatrix(G_N);
	MatrixXd G_N_inv;

	if(eigen_G_N.determinant() != 0) {
		G_N_inv = eigen_G_N.inverse(); // Находим обратную матрицу
	}
	else {
		cout << "Матрица не имеет обратной." << endl;
	}
	RowVectorXd eigen_Mult = eigen_input * G_N_inv;
	vector<uint8_t> Mult   = convertRowVectorToUint8(eigen_Mult);
	vector<uint8_t> u;
	for(int n: Mult) {
		u.push_back(n % 2);
	}
	vector<uint8_t> output;
	output.reserve(56);
	for(int n = 0, k = 0; n < N; n++) {
		auto result{find(Q_I_N.begin(), Q_I_N.end(), n)};
		if(result != Q_I_N.end()) {
			output.push_back(u[n]);
			k++;
			if(k > K)
				break;
		}
	}
	// интерливинг
	int kInt = static_cast<int>(output.size());
	vector<uint8_t> IntOutput(kInt, 0);
	vector<int> IP = PCIP;
	for(size_t m = 0, k = 0; m < 164; m++) {
		if(IP[m] >= 164 - K) {
			IP[k] = IP[m] - (164 - K);
			k++;
		}
	}
	for(int i = 0; i < K; i++) {
		IntOutput[IP[i]] = output[i];
	}
	return IntOutput;
};
