#include <gtest/gtest.h>
#include "Complex.h"
#include "qpskModulator.h"
#include <vector>
#include <cmath>

TEST(qpskModulatorTest, Modulation)
{
	vector<uint8_t> data{1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1};
	vector<Complex<double>> outputData;
	outputData = qpskModulator(data, outputData);

	const double res = 1.0 / sqrt(2);
	for(size_t i = 0, elem = 0; i < data.size() / 2; i += 2, elem += 1) {
		if((data[i] == 0) && (data[i + 1]) == 0) {
			EXPECT_NEAR(outputData[elem].getRe(), res, 1e-10);
			EXPECT_NEAR(outputData[elem].getIm(), res, 1e-10);
		}
		else if((data[i] == 1) && (data[i + 1]) == 0) {
			EXPECT_NEAR(outputData[elem].getRe(), -res, 1e-10);
			EXPECT_NEAR(outputData[elem].getIm(), res, 1e-10);
		}
		else if((data[i] == 1) && (data[i + 1]) == 1) {
			EXPECT_NEAR(outputData[elem].getRe(), -res, 1e-10);
			EXPECT_NEAR(outputData[elem].getIm(), -res, 1e-10);
		}
		else if((data[i] == 0) && (data[i + 1]) == 1) {
			EXPECT_NEAR(outputData[elem].getRe(), res, 1e-10);
			EXPECT_NEAR(outputData[elem].getIm(), -res, 1e-10);
		}
	}
}