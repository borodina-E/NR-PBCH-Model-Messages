#include <gtest/gtest.h>
#include "kron.h"

TEST(KRONTEST, kron)
{
	vector<vector<int>> Matrix1{{0, 1}, {1, 1}};
	vector<vector<int>> Matrix2{{1, 1}, {0, 0}};
	vector<vector<int>> NewMatrix  = kron(Matrix1, Matrix2);
	vector<vector<int>> RealMatrix = {{0, 0, 1, 1}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
	EXPECT_EQ(NewMatrix, RealMatrix);
}
