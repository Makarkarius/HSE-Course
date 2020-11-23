#include <iostream>
#include <vector>
#include <string>
#include "biginteger.h"

using namespace std;

int max(const long long& a, const long long& b) {
	return (a < b) ? b : a;
}

BigInteger::BigInteger() {
	this->parts = {};
	this->is_negative = 0;
}

BigInteger::BigInteger(int num) {
	if (num == 0) {
		this->is_negative = 0;
		this->parts.push_back(0);
	}
	if (num < 0)
		this->is_negative = 1;
	else
		this->is_negative = 0;
	num = abs(num);
	while (num != 0) {
		this->parts.push_back(num % 10);
		num /= BASE;
	}
}

BigInteger::BigInteger(string str) {
	if (str.length() == 0) {
		this->parts.push_back(0);
		this->is_negative = false;
	} else {
		if (str[0] == '-') {
			str = str.substr(1);
			this->is_negative = true;
		} else {
			this->is_negative = false;
		}
		for (long long i = str.size() - 1; i >= 0; i--) {
			this->parts.push_back(str[i] - '0');
		}
		this->remove_zeros();
	}
}

BigInteger::BigInteger(vector<long long> arr) {
	this->is_negative = 0;
	this->parts = arr;
}

string BigInteger::toString() const {
	string res;
	if (this->is_negative)
		res.push_back('-');
	for (long long i = this->parts.size() - 1; i >= 0; i--) {
		res.push_back(this->parts[i] + '0');
	}
	return res;
}

istream& operator>>(istream& is, BigInteger& num) {
	string str;
	is >> str;
	num = str;
	return is;
}

ostream& operator<<(ostream& os, const BigInteger& num) {
	if(num.is_negative)
		os << "-";
	for(long long i = num.parts.size() - 1; i >= 0; i--) {
		os << num.parts[i];
	}
	return os;
}

BigInteger BigInteger::operator++(int) {
	BigInteger copy = *this;
	*this += 1;
	return copy;
}

BigInteger BigInteger::operator--(int) {
	BigInteger copy = *this;
	*this -= 1;
	return copy;
}

BigInteger& BigInteger::operator++() {
	*this += 1;
	return *this;
}

BigInteger& BigInteger::operator--() {
	*this -= 1;
	return *this;
}

BigInteger::operator bool() const {
	if (*this == 0)
		return 0;
	return 1;
}

const BigInteger BigInteger::operator-() const {
	BigInteger copy = *this;
	copy.is_negative ^= 1;
	return copy;
}


vector<long long> naive_mul(const vector<long long>& x, const vector<long long>& y) {
	long long len = x.size();
	vector<long long> res(2 * len, 0);

	for (long long i = 0; i < len; ++i) {
		for (long long j = 0; j < len; ++j) {
			res[i + j] += x[i] * y[j];
		}
	}

	return res;
}
vector<long long> mul(const vector<long long>& x, const vector<long long>& y) {
	long long len = x.size();
	vector<long long> res(2 * len);

	if (len <= 4) return naive_mul(x, y);

	long long k = len / 2;

	vector<long long> Xr{ x.begin(), x.begin() + k };
	vector<long long> Xl{ x.begin() + k, x.end() };
	vector<long long> Yr{ y.begin(), y.begin() + k };
	vector<long long> Yl{ y.begin() + k, y.end() };
	vector<long long> P1 = mul(Xl, Yl);
	vector<long long> P2 = mul(Xr, Yr);
	vector<long long> Xlr(k);
	vector<long long> Ylr(k);

	for (long long i = 0; i < k; ++i) {
		Xlr[i] = Xl[i] + Xr[i];
		Ylr[i] = Yl[i] + Yr[i];
	}
	vector<long long> P3 = mul(Xlr, Ylr);
	for (size_t i = 0; i < len; ++i) {
		P3[i] -= P2[i] + P1[i];
	}
	for (size_t i = 0; i < len; ++i) {
		res[i] = P2[i];
	}
	for (long long i = len; i < 2 * len; ++i) {
		res[i] = P1[i - len];
	}
	for (long long i = k; i < len + k; ++i) {
		res[i] += P3[i - k];
	}

	return res;
}
const BigInteger operator*(BigInteger a, BigInteger b) {
	while (a.parts.size() < b.parts.size()) {
		a.parts.push_back(0);
	}
	while (b.parts.size() < a.parts.size()) {
		b.parts.push_back(0);
	}
	if (a.parts.size() % 2 != 0) {
		a.parts.push_back(0);
		b.parts.push_back(0);
	}
	a.parts = mul(a.parts, b.parts);
	a.normalize();
	a.is_negative = (a.is_negative == b.is_negative ? 0 : 1);
	if (a.parts.size() == 1 && a.parts[0] == 0)
		a.is_negative = 0;
	return a;
}

const BigInteger operator/(BigInteger lhs, const BigInteger& rhs) {
	if (rhs == 0) throw "div by zero";
	BigInteger b = rhs;
	b.is_negative = 0;
	BigInteger current;
	for (long long i = lhs.parts.size() - 1; i >= 0; --i) {
		if (current.parts.size() == 0) {
			current.parts.push_back(0);
		} else {
			current.parts.push_back(current.parts[current.parts.size() - 1]);
			for (long long i = current.parts.size() - 2; i > 0; --i) {
				current.parts[i] = current.parts[i - 1];
			}
			current.parts[0] = 0;
		}
		current.parts[0] = lhs.parts[i];
		current.remove_zeros();
		long long x = 0, lt = 0, rt = BASE;
		while (lt <= rt) {
			long long mt = (lt + rt) / 2;
			BigInteger t = b * mt;
			if (t <= current) {
				x = mt;
				lt = mt + 1;
			}
			else rt = mt - 1;
		}
		lhs.parts[i] = x;
		current = current - b * x;
	}
	lhs.is_negative ^= rhs.is_negative;
	lhs.remove_zeros();
	return lhs;
}

const BigInteger operator%(BigInteger lhs, const BigInteger& rhs) {
	lhs -= (lhs / rhs) * rhs;
	if (lhs.is_negative)
		lhs += rhs;
	return lhs;
}

const BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
	if (lhs.is_negative) {
		if (rhs.is_negative) {
			return -(-lhs + (-rhs));
		}
		else {
			return rhs - (-lhs);
		}
	}
	else if (rhs.is_negative) {
		return lhs - (-rhs);
	}
	int add = 0;
	for (long long i = 0; i < max(lhs.parts.size(), rhs.parts.size()) || add != 0; i++) {
		if (i == lhs.parts.size())
			lhs.parts.push_back(0);
		lhs.parts[i] += add + (i < rhs.parts.size() ? rhs.parts[i] : 0);
		add = lhs.parts[i] >= BASE;
		if (add != 0)
			lhs.parts[i] -= BASE;
	}
	lhs.remove_zeros();
	return lhs;
}

const BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
	if (rhs.is_negative) {
		return lhs + (-rhs);
	}
	else if (lhs.is_negative) {
		return -(-lhs + rhs);
	}
	else if (lhs < rhs) {
		return -(rhs - lhs);
	}
	int add = 0;
	for (long long i = 0; i < rhs.parts.size() || add != 0; ++i) {
		lhs.parts[i] -= add + (i < rhs.parts.size() ? rhs.parts[i] : 0);
		add = lhs.parts[i] < 0;
		if (add != 0)
			lhs.parts[i] += BASE;
	}
	lhs.remove_zeros();
	return lhs;
}


bool BigInteger::operator<(const BigInteger& rhs) const {
	if (*this == rhs) return false;
	if (this->is_negative) {
		if (rhs.is_negative) return ((-rhs) < (-*this));
		else return true;
	} else if (rhs.is_negative) {
		return false;
	} else {
		if (this->parts.size() != rhs.parts.size()) {
			return this->parts.size() < rhs.parts.size();
		} else {
			for (long long i = this->parts.size() - 1; i >= 0; --i) {
				if (this->parts[i] != rhs.parts[i]) return this->parts[i] < rhs.parts[i];
			}

			return false;
		}
	}
}

bool BigInteger::operator<=(const BigInteger& rhs) const {
	return (*this < rhs || *this == rhs);
}

bool BigInteger::operator>(const BigInteger& rhs) const {
	return !(*this <= rhs);
}

bool BigInteger::operator>=(const BigInteger& rhs) const {
	return !(*this < rhs);
}

bool BigInteger::operator==(const BigInteger& rhs) const {
	return (this->parts == rhs.parts && this->is_negative == rhs.is_negative);
}

bool BigInteger::operator!=(const BigInteger& rhs) const {
	return !(*this == rhs);
}


BigInteger& BigInteger::operator=(const string& str) {
	*this = BigInteger(str);
	return *this;
}

BigInteger& BigInteger::operator=(int num) {
	*this = BigInteger(num);
	return *this;
}

BigInteger& BigInteger::operator=(const BigInteger& num) = default;

BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
	return *this = *this * rhs;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
	*this = *this / rhs;
	return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& rhs) {
	*this = *this % rhs;
	return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& rhs) {
	*this = *this + rhs;
	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
	*this = *this - rhs;
	return *this;
}
