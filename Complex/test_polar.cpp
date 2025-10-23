#include <gtest/gtest.h>
#include <vector>
#include "polarCoding.h"
#include "polarDecoding.h"

using namespace std;
TEST(PolarCodingTest, PolarRecoveryTest)
{
	vector<uint8_t> codeword(63, 0);
	for(int i = 0; i < 63; i++) {
		codeword[i] = rand() % 2;
	}
	vector<uint8_t> outputCodeword = polarCoding(codeword);
	vector<uint8_t> Codeword       = polarDecoding(outputCodeword);
	EXPECT_EQ(codeword, Codeword);
};