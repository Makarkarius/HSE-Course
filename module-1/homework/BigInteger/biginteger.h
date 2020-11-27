#pragma once

#include <vector>
#include <string>

#define BASE 10

using namespace std;


class BigInteger {
public:
	BigInteger();
	BigInteger(int);
	BigInteger(string);
	BigInteger(vector<long long>);
	explicit operator bool() const;
	string toString() const;
	friend std::ostream &operator<<(ostream&, const BigInteger&);
	friend std::istream &operator>>(istream&, BigInteger&);
	
	BigInteger operator++(int);
	BigInteger operator--(int);
	BigInteger& operator++();
	BigInteger& operator--();
	const BigInteger operator-() const;
	
	friend const BigInteger operator*(BigInteger, BigInteger);
	friend const BigInteger operator/(BigInteger, const BigInteger&);
	friend const BigInteger operator%(BigInteger, const BigInteger&);
	friend const BigInteger operator+(BigInteger, const BigInteger&);
	friend const BigInteger operator-(BigInteger, const BigInteger&);
	
	
	bool operator>(const BigInteger&) const;
	bool operator>=(const BigInteger&) const;
	bool operator<(const BigInteger&) const;
	bool operator<=(const BigInteger&) const;
	bool operator==(const BigInteger&) const;
	bool operator!=(const BigInteger&) const;

	BigInteger& operator=(const BigInteger&);
	BigInteger& operator=(int);
	BigInteger& operator=(const string &str);
	BigInteger& operator+=(const BigInteger&);
	BigInteger& operator-=(const BigInteger&);
	BigInteger& operator*=(const BigInteger&);
	BigInteger& operator/=(const BigInteger&);
	BigInteger& operator%=(const BigInteger&);


private:
	vector<long long int> parts;
	bool is_negative;
	void remove_zeros() {
		while (this->parts.size() > 1 && this->parts.back() == 0) {
			this->parts.pop_back();
		}
		if (this->parts.size() == 1 && this->parts[0] == 0)
			this->is_negative = 0;
	}

	void normalize() {
		for (long long i = 0; i < this->parts.size() - 1; ++i) {
			this->parts[i + 1] += this->parts[i] / BASE;
			this->parts[i] %= BASE;
		}
		this->remove_zeros();
	}
};
