#include <iostream>
#include <vector>
#include <cmath>
#include "Complex.h"
using namespace std;

template <typename T>
vector<Complex<T>>& qpskModulator(vector<uint8_t>& input, vector<Complex<T>>& output)
{
	bool validInput = true;
	if(input.size() % 2 != 0) {
		validInput = false;
	}
	for(auto& n: input) {
		if((n != 0) && (n != 1)) {
			validInput = false;
		}
	}
	if(validInput == 1) {
		output.clear();
		for(size_t i = 0; i < input.size() / 2; i += 1) {
			T re = (1 - 2 * input[2 * i]) / sqrt(2.0);
			T im = (1 - 2 * input[(2 * i) + 1]) / sqrt(2.0);
			Complex<T> elem(re, im); // комплексное число Complex<T> elem(re, im);
			output.push_back(elem);  // добавление комплексного числа в вектор состоящий из Complex
		}
	}
	else
		cout << "Invalid input";
	return output;
}

/*int main()
{
    vector<uint8_t> data{1, 0, 1, 1, 1, 0, 0, 0, 0, 1};
    vector<Complex<double>> outputData;
    outputData = qpskModulator(data, outputData);
    for(auto& n: outputData)
        n.print();
    cout << endl;
    return 0;
}*/
