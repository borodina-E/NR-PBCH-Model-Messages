#include <gtest/gtest.h>
#include <vector>
#include "RateMatching.h"
#include "RateRecovery.h"

using namespace std;
TEST(RateMatchingTest, RateRecovery)
{
	for(int i = 0; i < 100; i++) {
		vector<uint8_t> codeword(512, 0);
		for(int j = 0; j < 512; j++) {
			codeword[j] = rand() % 2;
		}
		vector<uint8_t> outputCodeword = RateMatching(codeword);
		vector<uint8_t> Codeword       = RateRecovery(outputCodeword);
		EXPECT_EQ(codeword, Codeword);
	}
};