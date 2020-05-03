#include "HugeInteger.h"
#include <string.h>
#include <math.h>

// Class HugeInteger

const int MAX_SIZE = 100;

std::ostream& operator<< (std::ostream& o, const HugeInteger& h) {
	for (int i = h.m_size - 1; i >= 0; --i) {
		std::cout << h.m_number[i];
	}
	return o;
}

std::istream& operator >> (std::istream& i, HugeInteger& h) {
	return i;
}

HugeInteger::HugeInteger()
	: m_number(0)
	, m_size(0)
	, m_maxsize(MAX_SIZE)
{
	m_number = new char[m_maxsize];
}

HugeInteger::HugeInteger(int x)
	: m_number(0)
	, m_size(sizeofint(x))
	, m_maxsize(MAX_SIZE)
{
	m_number = new char[m_maxsize];
	for (int i = 0; i < m_size; ++i) {
		m_number[i] = x % 10 + '0';
		x /= 10;
	}
}

HugeInteger::HugeInteger(const char* c)
	: m_number(0)
	, m_size(strlen(c))
	, m_maxsize((MAX_SIZE > strlen(c)) ? MAX_SIZE : strlen(c))
{
	m_number = new char[m_maxsize];
	for (int i = 0; i < m_size; ++i) {
		m_number[i] = c[m_size - 1 - i];
	}
}

HugeInteger::HugeInteger(const HugeInteger& h)
	: m_number(0)
	, m_size(h.m_size)
	, m_maxsize(h.m_maxsize)
{
	delete[] m_number;
	m_number = new char[m_maxsize];
	for (int i = 0; i < m_size; ++i) {
		m_number[i] = h.m_number[i];
	}
}

HugeInteger& HugeInteger::operator=(const HugeInteger& h) {
	if (this != &h) {
		m_size = h.m_size;
		m_maxsize = h.m_maxsize;
		delete[] m_number;
		for (int i = 0; i < m_size; ++i) {
			m_number[i] = h.m_number[i];
		}
	}
	return *this;
}

HugeInteger::~HugeInteger() {
	delete[] m_number;
}

bool HugeInteger::operator==(const HugeInteger& h) const {
	if (m_size > h.m_size) {
		return true;
	}
	if (m_size < h.m_size) {
		return false;
	}
	for (int i = 0; i < m_size; ++i) {
		if (m_number[i] != h.m_number[i]) {
			return false;
		}
	}
	return true;
}

bool HugeInteger::operator>(const HugeInteger& h) const {
	if (m_size > h.m_size) {
		return true;
	}
	if (m_size < h.m_size) {
		return false;
	}
	for (int i = m_size - 1; i > 0; --i) {
		if (m_number[i] > h.m_number[i]) {
			return true;
		}
	}
	return false;
}

HugeInteger& HugeInteger::operator+=(const HugeInteger& h) {
	int in_mind = 0;
	if (m_size > h.m_size) {
		for (int i = 0; i < h.m_size; ++i) {
			int trans = m_number[i] + h.m_number[i] - 2 * '0';
			m_number[i] = (trans + '0' + in_mind) % 10;
			in_mind = trans / 10;
		}
		if (in_mind == 1) {
			for (int i = h.m_size; i < m_size; ++i) {
				int trans = m_number[i] - '0' + in_mind;
				m_number[i] = trans % 10 + '0';
				in_mind = trans / 10;
				if (i == h.m_size - 1) {
					m_number[i] = in_mind + trans % 10 + '0';
				}
			}
		}
	}
	else {
		if (h.m_size < m_maxsize) {
			for (int i = 0; i < m_size; ++i) {
				int trans = m_number[i] + h.m_number[i] - 2 * '0' + in_mind;
				m_number[i] = trans % 10 + '0';
				in_mind = trans / 10;
			}
			for (int i = m_size; i < h.m_size; ++i) {
				int trans = h.m_number[i] - '0' + in_mind;
				m_number[i] = trans % 10 + '0';
				in_mind = trans / 10;
				if (i == h.m_size - 1 && in_mind == 1) {
					m_number[i] = in_mind + trans % 10 + '0';
				}
			}
			m_size = h.m_size;
		}
		else {
			m_maxsize = h.m_size * 2;
			char* tmp = new char[m_maxsize];
			for (int i = 0; i < m_size; ++i) {
				tmp[i] = m_number[i];
			}
			delete[] m_number;
			m_number = tmp;
			for (int i = 0; i < m_size; ++i) {
				int trans = m_number[i] + h.m_number[i] - 2 * '0' + in_mind;
				m_number[i] = trans % 10 + '0';
				in_mind = trans / 10;
			}
			for (int i = m_size; i < h.m_size; ++i) {
				int trans = h.m_number[i] - '0' + in_mind;
				m_number[i] = trans % 10 + '0';
				in_mind = trans / 10;
				if (i == h.m_size - 1 && in_mind == 1) {
					m_number[i] = in_mind + trans % 10 + '0';
				}
			}
			m_size = h.m_size;
		}
	}
	return *this;
}

HugeInteger& HugeInteger::operator-=(const HugeInteger& h) {
	return *this;
}

HugeInteger& HugeInteger::operator*=(const HugeInteger& h) {
	m_maxsize = m_size * h.m_size * 2;
	char* tmp = new char[m_maxsize];
	for (int i = 0; i < m_size; ++i) {
		tmp[i] = m_number[i];
	}
	delete[] m_number;
	m_number = tmp;
	return *this;
}

HugeInteger& HugeInteger::operator/=(const HugeInteger&) {
	return *this;
}

HugeInteger& HugeInteger::operator%=(const HugeInteger&) {
	return *this;
}

HugeInteger& HugeInteger::operator++() {
	if (m_number[0] - '0' < 9) {
		++m_number[0];
	}
	else {
		*this += 1;
	}
	return *this;
}

HugeInteger& HugeInteger::operator--() {
	if (m_number[0] > 0) {
		--m_number[0];
	}
	else {
		*this -= 1;
	}
	return *this;
}

HugeInteger HugeInteger::operator++(int) {
	HugeInteger tmp(*this);
	++tmp;
	return tmp;
}

HugeInteger HugeInteger::operator--(int) {
	HugeInteger tmp(*this);
	--tmp;
	return tmp;
}
//End of class HugeInteger

//HugeInteger functions

bool operator<=(const HugeInteger& h1, const HugeInteger& h2) {
	return !(h1 > h2);
}

bool operator>=(const HugeInteger& h1, const HugeInteger& h2) {
	return !(h1 < h2);
}

bool operator<(const HugeInteger& h1, const HugeInteger& h2) {
	return ((h1 != h2) && !(h1 > h2));
}

bool operator!=(const HugeInteger& h1, const HugeInteger& h2) {
	return !(h1 == h2);
}

HugeInteger operator+(HugeInteger h1, const HugeInteger& h2) {
	return h1 += h2;
}

HugeInteger& operator-(HugeInteger, const HugeInteger&);
HugeInteger& operator*(HugeInteger, const HugeInteger&);
HugeInteger& operator%(HugeInteger, const HugeInteger&);
HugeInteger& operator/=(HugeInteger, const HugeInteger&);
//End of HugeInteger functions

int sizeofint(int x) {
	int size = 0;
	while (x != 0) {
		x /= 10;
		++size;
	}
	return size;
}