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
	T getRe()
	{
		return re;
	};
	T getIm()
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
	Complex operator+(const Complex& numb) const
	{
		return Complex{re + numb.re, im + numb.im};
	}
	Complex operator-(const Complex& numb) const
	{
		return Complex{re - numb.re, im - numb.im};
	}
	Complex operator/(const Complex& numb) const
	{
		return Complex{(re * numb.re + im * numb.im) / (pow(numb.re, 2) + (pow(numb.im, 2))),
		               (im * numb.re - re * numb.im) / (pow(numb.re, 2) + (pow(numb.im, 2)))};
	}
	Complex operator*(const Complex& numb) const
	{
		return Complex(re * numb.re - im * numb.im, im * numb.re + re * numb.im);
	}
	bool operator==(const Complex& numb) const
	{
		return (re == numb.re) && (im == numb.im);
	}
};

int main()
{
	Complex<double> z(1, 5.8);
	Complex<double> n(0.6, 7.516);
	cout << "Модуль комплексного числа: " << z.abs() << endl;
	cout << "Квадрат модуля комплексного числа: " << z.abs2() << endl;
	cout << "Аргумент комплексного числа: " << z.argRad() << " радиан, " << z.argDeg() << " градусов" << endl;
	cout << "Комплексное число: ";
	z.print();
	Complex zConj = z.conj();
	cout << "Сопряженное комплексное число: ";
	zConj.print();
	Complex c = z + n;
	cout << "Сложение: ";
	c.print();
	c = z - n;
	cout << "Вычитание: ";
	c.print();
	c = z / n;
	cout << "Деление: ";
	c.print();
	c = z * n;
	cout << "Умножение: ";
	c.print();
	bool isequal = (z == n);
	cout << "Сравнение: " << isequal << endl;
	Complex zCopy = z;
	zCopy.print();
	cout << z.getRe() << endl;
	cout << z.getIm() << endl;
	return 0;
}