// nfn.cpp : Defines the entry point for the Natural Finite Numbers.
// copyright ulfarf

#include "stdafx.h"
#include <iostream>

class nfn {
	size_t size;
	unsigned long long *ptr;
	const unsigned long long MAXx64 = (unsigned long long) - 1;
	const unsigned long long ZEROx64 = (unsigned long long)0;
	const int x64 = 64;
public:
	nfn() {
		size = (size_t)1;
		ptr = new unsigned long long[size];
		ptr[0] = ZEROx64;
	}
	nfn(size_t sizet) {
		size = sizet;
		ptr = new unsigned long long[size];
		for (unsigned long long i = ZEROx64; i < size; i++) {
			ptr[i] = ZEROx64;
		}
	}
	void operator delete(void* ptr);
	//prefix 
	void operator++() {

		unsigned long long i = (unsigned long long)0;
		while (ptr[i] == MAXx64 && i < size) {
			ptr[i++] = ZEROx64;
		}
		++ptr[i];
	}
	//postfix
	void operator++(int) {
		unsigned long long i = ZEROx64;
		while (ptr[i] == MAXx64 && i < size) {
			ptr[i++] = ZEROx64;
		}
		ptr[i]++;
	}
		nfn& operator+=(const nfn& in) {
		unsigned long long i = ZEROx64;
		while (i < size) {
			ptr[i] += (in.size >i)?in.ptr[i]:ZEROx64;
			if (ptr[i]<in.ptr[i]&&!i== size) ptr[i + 1]++;
			i++;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const nfn& in);

	// left shift(int) 
	nfn operator<<(const unsigned long long &in) const {
		size_t i = ZEROx64;
		size_t moduli = (size_t)in % x64;
		div_t divli = div(in, x64);
		while (i < size - divli.quot)
		{
			ptr[size - i - 1] = (ptr[size - i - 1 - divli.quot]);
			i++;
		}
		i = ZEROx64;
		while (i < divli.quot)
		{
			(ptr[i]) = ZEROx64;
			i++;
		}
		i = ZEROx64;
		while (i < size)
		{
			unsigned long long right = (ptr[size - i - 1]) >> x64 - divli.rem;
			(ptr[size - i - 1]) <<= divli.rem;
			(ptr[size - i + divli.quot]) += right;
			i++;
		}
		return this[ZEROx64];
	}
};

std::ostream& operator<<(std::ostream& os, const nfn& in)
{
	size_t i = (unsigned long long)0;
	while (i < in.size)
	{
		os << (unsigned long long)(in.ptr[in.size - i++ - 1]);  if (in.size == i) os << " "; else os << ".";
	}
	return os;
}

void nfn::operator delete(void* ptr) {
	//		delete  ptr;
}

int main()
{
	nfn B(5),c(6);
	++B;
	//B++;
	std::cout << "\n" << B << "\n";
	B << (unsigned long long)63;
	std::cout << "\n" << B << "\n";
	B << (unsigned long long)2;
	++B;
	std::cout << "\n" << B << "\n";
	B << (unsigned long long)63;
	std::cout << "\n" << B << "\n";
	std::cout << "\n" << c << "\n";
	c += B;
	c++;
	c += B;
	c += c;
	std::cout << "\n" << c << "\n";
	delete &B;
	char i[256];
	std::cin.getline(i,256);
	return 0;
}

