#include <iostream>
#pragma once

class HugeInteger {
	friend std::ostream& operator<< (std::ostream&, const HugeInteger&);
	friend std::istream& operator>> (std::istream&, HugeInteger&);
public:
	HugeInteger();
	HugeInteger(int);
	HugeInteger(const char*);
	HugeInteger(const HugeInteger&);
	HugeInteger& operator=(const HugeInteger&);
	~HugeInteger();

	bool operator==(const HugeInteger&) const;
	bool operator>(const HugeInteger&) const;
	HugeInteger& operator+=(const HugeInteger&);
	HugeInteger& operator-=(const HugeInteger&);
	HugeInteger& operator*=(const HugeInteger&);
	HugeInteger& operator/=(const HugeInteger&);
	HugeInteger& operator%=(const HugeInteger&);
	HugeInteger& operator++();
	HugeInteger& operator--();
	HugeInteger operator++(int);
	HugeInteger operator--(int);
private:
	char* m_number;
	int m_size;
	int m_maxsize;
};

bool operator<=(const HugeInteger&, const HugeInteger&);
bool operator>=(const HugeInteger&, const HugeInteger&);
bool operator<(const HugeInteger&, const HugeInteger&);
bool operator!=(const HugeInteger&, const HugeInteger&);
HugeInteger operator+(HugeInteger, const HugeInteger&);
HugeInteger& operator-(HugeInteger, const HugeInteger&);
HugeInteger& operator*(HugeInteger, const HugeInteger&);
HugeInteger& operator%(HugeInteger, const HugeInteger&);
HugeInteger& operator/=(HugeInteger, const HugeInteger&);

int sizeofint(int);