#ifndef QPSKMODULATOR_H
#define QPSKMODULATOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Complex.h"

using namespace std;

template <typename T>
vector<Complex<T>> qpskModulator(vector<uint8_t>& input, vector<Complex<T>>& output)
{
	if(input.size() % 2 != 0) {
		throw invalid_argument("Input size must be even");
	}
	for(auto& n: input) {
		if((n != 0) && (n != 1)) {
			throw invalid_argument("Input must contain 0 or 1)");
		}
	}
	output.clear();
	for(size_t i = 0; i < input.size() / 2; i += 1) {
		T re = (1 - 2 * input[2 * i]) / sqrt(2.0);
		T im = (1 - 2 * input[(2 * i) + 1]) / sqrt(2.0);
		Complex<T> elem(re, im); // комплексное число Complex<T> elem(re, im);
		output.push_back(elem);  // добавление комплексного числа в вектор состоящий из Complex
	}
	return output;
}

#endif