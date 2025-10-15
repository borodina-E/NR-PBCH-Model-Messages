#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <typename T>
vector<vector<T>> kron(vector<vector<T>>& M1, vector<vector<T>>& M2)
{
	int m = M1.size();
	int n = M1[0].size();
	int p = M2.size();
	int q = M2[0].size();
	vector<vector<T>> KronMatrix(m * p, vector<T>(n * q));
	for(int rowsM1 = 0; rowsM1 < m; rowsM1++) {
		for(int colsM1 = 0; colsM1 < n; colsM1++) {
			for(int rowsM2 = 0; rowsM2 < p; rowsM2++) {
				for(int colsM2 = 0; colsM2 < q; colsM2++) {
					KronMatrix[rowsM1 * p + rowsM2][colsM1 * q + colsM2] = M1[rowsM1][colsM1] * M2[rowsM2][colsM2];
				}
			}
		}
	}
	return KronMatrix;
}