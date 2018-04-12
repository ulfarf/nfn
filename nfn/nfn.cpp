// nfn.cpp : Defines the entry point for the Natural Finite Numbers.
// copyright ulfarf 2018

#include "stdafx.h"
#include <iostream>

class nfn {
	unsigned long long size;
	unsigned long long *ptr;
	const unsigned long long MAXx64 = (unsigned long long) - 1;
	const unsigned long long ZEROx64 = (unsigned long long)0;
	const unsigned long long x64 = 64;
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
	unsigned long long getsize() {
		return size;
	}
	void zero() {
		unsigned long long i = ZEROx64;
		while(i<size)ptr[i++] = ZEROx64;
	}
	void fullmult(unsigned long long a, unsigned long long b, nfn &o) {
		o.addat(0, (((a & (MAXx64 << 32)))*((b & (MAXx64 << 32)))));
		o.addat(0, (a & (MAXx64 >> 32))*(b & (MAXx64 >> 32)));
		o.addat(1, ((a & (MAXx64 << 32)) >> 32)*((b & (MAXx64 << 32)) >> 32));
		o.addat(1, ((a & (MAXx64 >> 32)))*((b & (MAXx64 << 32)) >> 32));
		o.addat(1, ((a & (MAXx64 << 32)) >> 32)*((b & (MAXx64 >> 32))));
		o.addat(1, ((a & (MAXx64 << 32)) >> 32)*((b & (MAXx64 << 32))));
	}
	void addat(unsigned long long at, unsigned long long a) {
		unsigned long long prev = ptr[at];
		ptr[at] += a;
		if (prev > ptr[at]) {
			unsigned long long i = at ;
			while (ptr[i] == MAXx64 && i < size) { std::cout << "while"; ptr[i] = ZEROx64; i++; }
			ptr[i]++;
			ptr[at]--;
		}
	}
	void addat(unsigned long long at, nfn& a) {
		unsigned long long prev = ZEROx64;
		unsigned long long i = ZEROx64;
		while (i<a.size&&(at+i)<size)
		{
			prev = ptr[at + i];
			ptr[at+i] += a.ptr[i];
			if (prev > ptr[at+i]) {
				unsigned long long j = at+i;
				while (ptr[ j] == MAXx64 && j < size) { std::cout << "while2"; ptr[ j] = ZEROx64; j++; }
				ptr[j]++;
				ptr[at + i]--;
			}
			i++;
		}
	}
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
		unsigned long long j = ZEROx64;

		while (i < size) {
			j = ptr[i];
			
			ptr[i] += (in.size >i) ? in.ptr[i] : ZEROx64;
			if (ptr[i] < j) ptr[i + 1]++;
			i++;
		}
		return *this;
	}
	//by patent o((1/4096)n^1) multiplier this shows naive schoolbook multiplyer o((1/4096)n^2)
	nfn& operator*=(const nfn& in) {
		nfn a(size);
		nfn tmp(2);
		a += *this;
		zero();
		if (this == &in) {
			unsigned long long i = ZEROx64, j = ZEROx64;
			while (i < size) {
				
				while (i+j < size) {
					tmp.zero();
					fullmult(a.ptr[i], a.ptr[j], tmp);
				//	std::cout <<" tmp = "<< tmp;
					addat(i+j, tmp);
					j++;
				}
				j = ZEROx64;
				i++;
			}
		}
		else {
			//std::cout << "this and in are the different \n";
			unsigned long long i = ZEROx64, j = ZEROx64;
			while (i < size) {
				while (i + j < size) {
					tmp.zero();
					fullmult(a.ptr[i], in.ptr[j], tmp);
				//	std::cout << " tmp = " << tmp;
					addat(i + j, tmp);
					j++;
				}
				j = ZEROx64;
				i++;
			}
		}
			return *this;
	}
	

	friend std::ostream& operator<<(std::ostream& os, const nfn& in);

	// left shift(int) 
	nfn operator<<(const unsigned long long &in) const {
		unsigned long long i = ZEROx64;
		unsigned long long rem = (unsigned long long)in % x64;
		unsigned long long quot = (unsigned long long)in / x64;

		while (i < size - quot)
		{
			ptr[size - i - 1] = (ptr[size - i - 1 - quot]);
			i++;
		}
		i = ZEROx64;
		while (i < quot)
		{
			(ptr[i]) = ZEROx64;
			i++;
		}
		i = ZEROx64;
		while (i < size)
		{
			unsigned long long right = (ptr[(size - i) - (unsigned long long)1]) >> (x64 - rem);
			(ptr[size - i - 1]) <<= rem;
			(ptr[size - i + quot]) += right;
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
	nfn B(10),c(100);
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
	//c += B;
	std::cout << "\n" << c << "\n";
	c++;
	c++;
	std::cout << "\n" << c << "\n";
	c *= c;
	std::cout << "\n" << c << "\n";
	c *= c;
	std::cout << "\n" << c << "\n";
	c *= c;
	std::cout << "\n" << c << "\n";
	c *= c;
	std::cout << "\n" << c << "\n";
	c *= c;

	std::cout << "\n" << c << "\n";
	//c++;
	c *= c;

	std::cout << "\n" << c << "\n";
	c *= c;
	std::cout << "\n" << c << "\n";
	c *= c;
	c *= c;std::cout << "\n" << c << "\n";
	c *= c;
	c *= c;std::cout << "\n" << c << "\n";
	



	

	delete &B;
	nfn d(8*1024),e(8* 1024);
	//o(n)=o(524188)
	d++; d << 256; d += c; e += d; d++; e += d; d *= e; d *= d; d *= d; d *= d; d *= d; d *= d;
	std::cout << "\n d" << d << "\n";
	//unsigned long long size = d.getsize();
	//std::cout << "\n" << size*8 << " bytes\n";
	//std::cout << "\n" << d << "\n";
	char i[256];
	std::cin.getline(i, 256);
	return 0;

}

