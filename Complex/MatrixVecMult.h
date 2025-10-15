#ifndef MATRIXMULT_H
#define MATRIXMULT_H

#include <vector>
#include <stdint.h>
using namespace std;

template <typename T>
vector<T> MatrixVecMult(vector<T>& Vec, vector<vector<int>>& M)
{
	int m = M.size();
	int n = M[0].size();
	int p = Vec.size();
	vector<T> resultVec(m, 0);
	if(n != p) {
		cout << "Invalid size!";
		return resultVec;
	}
	else {
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				resultVec[i] += Vec[j] * M[j][i];
			}
		}
		return resultVec;
	}
}

#endif