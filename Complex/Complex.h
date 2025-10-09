// Complex.h
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Complex {
	T re; // real part
	T im; // imaginary part
public:
	Complex(T a, T b) : re{a}, im{b}
	{}
	Complex(const Complex& copy)
	{
		re = copy.re;
		im = copy.im;
	}
	T getRe() const
	{
		return re;
	};
	T getIm() const
	{
		return im;
	};
	T abs()
	{
		return sqrt(pow(re, 2) + pow(im, 2));
	};
	T abs2()
	{
		return pow(re, 2) + pow(im, 2);
	};
	T argRad()
	{
		return atan2(im, re);
	};
	T argDeg()
	{
		return atan2(im, re) * 180 / M_PI;
	};
	Complex conj()
	{
		T newIm = -im;
		Complex conjNum(re, newIm);
		return conjNum;
	};
	void print() const
	{
		cout << re;
		if(im > 0) {
			cout << " + i*" << im << endl;
		}
		else if(im < 0)
			cout << " - i*" << -im << endl;
		else
			cout << endl;
	}
	template <typename U>
	auto operator+(const Complex<U>& numb) const
	{
		using ResultType = decltype(T() + U());
		return Complex<ResultType>{static_cast<ResultType>(re) + static_cast<ResultType>(numb.getRe()),
		                           static_cast<ResultType>(im) + static_cast<ResultType>(numb.getIm())};
	}
	template <typename U>
	auto operator-(const Complex<U>& numb) const
	{
		using ResultType = decltype(T() - U());
		return Complex<ResultType>{static_cast<ResultType>(re) - static_cast<ResultType>(numb.getRe()),
		                           static_cast<ResultType>(im) - static_cast<ResultType>(numb.getIm())};
	}
	template <typename U>
	auto operator/(const Complex<U>& numb) const
	{
		using ResultType       = decltype(T() / U());
		auto c                 = static_cast<ResultType>(numb.getRe());
		auto d                 = static_cast<ResultType>(numb.getIm());
		ResultType denominator = static_cast<ResultType>(pow(c, 2)) + static_cast<ResultType>(pow(d, 2));
		return Complex<ResultType>{(static_cast<ResultType>(re) * c + static_cast<ResultType>(im) * d) / denominator,
		                           (static_cast<ResultType>(im) * c - static_cast<ResultType>(re) * d) / denominator};
	}
	template <typename U>
	auto operator*(const Complex<U>& numb) const
	{
		using ResultType = decltype(T() * U());
		return Complex<ResultType>(static_cast<ResultType>(re) * static_cast<ResultType>(numb.getRe()) -
		                               static_cast<ResultType>(im) * static_cast<ResultType>(numb.getIm()),
		                           static_cast<ResultType>(im) * static_cast<ResultType>(numb.getRe()) +
		                               static_cast<ResultType>(re) * static_cast<ResultType>(numb.getIm()));
	}

	template <typename U>
	bool operator==(const Complex<U>& numb) const
	{
		using ResultType = decltype(T() / U());
		return (static_cast<ResultType>(re) == static_cast<ResultType>(numb.getRe())) &&
		       (static_cast<ResultType>(im) == static_cast<ResultType>(numb.getIm()));
	}
};
#endif // COMPLEX_H