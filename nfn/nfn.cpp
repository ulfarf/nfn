// nfn.cpp : Defines the entry point for the Natural Finite Numbers.
// copyright ulfarf

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
		if (prev < ptr[at]) {
			std::cout << "carryon";
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
			if (prev != ptr[at+i]) {
				std::cout << "carryon2";
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
	//by patent o(n^1)multiplier with a bug
	nfn& operator*=(const nfn& in) {
		nfn a(size);
		nfn tmp(2);
		a += *this;
		zero();
		if (this == &in) {
			//std::cout << "this and in are the same \n";
			unsigned long long i = ZEROx64, j = ZEROx64;
			while (i < size) {
				
				while (i+j < size) {
					//std::cout << (a.ptr[i] & (MAXx64 >> 32))*(a.ptr[j] & (MAXx64 >> 32)) << " \n";
					tmp.zero();
					fullmult(a.ptr[i], a.ptr[j], tmp);
					std::cout <<" tmp = "<< tmp;

					addat(i+j, tmp);
					/*std::cout << "ptr[" << i << "] " << ptr[i] << "["<< j <<"] p " << p << "\n";
					if (ptr[i] < p&&i < size - 1) {
						ptr[i + 1] += 1;
						std::cout << "ptr[" << i << " + 1] " << ptr[i + 1] << "\n";
						p--;
					}*/
					j++;
				}
				//std::cout << tmp <<" a "<< a << "\n";
				//addat(i, tmp);
				//ptr[i] = p;
				i++;
			}
				
			
		}
		else {
		/*	std::cout << "else \n";
			unsigned long long i = ZEROx64, j = ZEROx64;
			while (i < size) {
				while (j < size) {
					unsigned long long p, p0, p1, p2, p3;
					p = ptr[i + j];
					std::cout << (a.ptr[i] & (MAXx64 >> 32))*(in.ptr[j] & (MAXx64 >> 32)) << " \n";
					ptr[i + j] += (a.ptr[i] & (MAXx64 >> 32))*(in.ptr[j] & (MAXx64 >> 32)) + ((a.ptr[i] & (MAXx64 << 32)))*((in.ptr[j] & (MAXx64 << 32)));

					ptr[i + j + 1] += ((a.ptr[i] & (MAXx64 << 32)) >> 32)*((a.ptr[j] & (MAXx64 << 32)) >> 32);
					ptr[i + j + 1] += ((a.ptr[i] & (MAXx64 >> 32)))*((a.ptr[j] & (MAXx64 << 32)) >> 32);
					ptr[i + j + 1] += ((a.ptr[i] & (MAXx64 << 32)) >> 32)*((a.ptr[j] & (MAXx64 >> 32)));
					std::cout << "ptr[" << i << "] " << ptr[i] << "["<< j <<"] p " << p << "\n";
					if (ptr[i] < p&&i < size - 1) {
					ptr[i + 1] += 1;
					std::cout << "ptr[" << i << " + 1] " << ptr[i + 1] << "\n";
					p--;
					}
					j++;
				}
				//ptr[i] = p;
				i++;
			}

*/
		}

		//addat(pp ,0);
		
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
	nfn B(10),c(10);
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
	c++;
	c *= c;

	std::cout << "\n" << c << "\n";
	c *= c;
	std::cout << "\n" << c << "\n";
	c *= c;
	/*c *= c;
	c *= c;
	c *= c;
	c *= c;	*/




	std::cout << "\n" << c << "\n";

	delete &B;
	//nfn d(1024*1024*128),e(1024 * 1024 * 128);
	//d++; d << 256; d += d; e += d; d++; e += d; //d *= e;
	//unsigned long long size = d.getsize();
	//std::cout << "\n" << size*8 << " bytes\n";
	//std::cout << "\n" << d << "\n";
	char i[256];
	std::cin.getline(i, 256);
	return 0;

}

