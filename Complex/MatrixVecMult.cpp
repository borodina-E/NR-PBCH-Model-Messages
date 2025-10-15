#include <iostream>
#include <cmath>
#include <vector>

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
/*
int main()
    {
        vector<uint8_t> u       = {1, 1, 0, 1};
        vector<vector<int>> G_N = {
            {1, 0, 0, 0}, // строка 0
            {1, 1, 0, 0}, // строка 1
            {1, 0, 1, 0}, // строка 2
            {1, 1, 1, 1}  // строка 3
        };
        auto result = MatrixVecMult(u, G_N);
        for(auto n: result) {
            cout << static_cast<int>(n);
        }
    }
*/
