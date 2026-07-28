#pragma once
#ifndef EML_RESEARCH_INTEGER_H
#include <cstdio>
#include <vector>
/**
 * 高精度算法。存储的数仅为自然数。
 */
class acc_integer : public std::vector<int> {
public:
	acc_integer() : acc_integer(0) {
	}

	explicit acc_integer(const int n) {
		push_back(n);
		check();
	}

	acc_integer &check() {
		while (!empty() && !back())pop_back();
		if (empty())return *this;
		for (int i = 1; i < size(); ++i) {
			(*this)[i] += (*this)[i - 1] / 10;
			(*this)[i - 1] %= 10;
		}
		while (back() >= 10) {
			push_back(back() / 10);
			(*this)[size() - 2] %= 10;
		}
		return *this;
	}
};

const auto integer_0 = acc_integer(0);
const auto integer_1 = acc_integer(1);
const auto integer_2 = acc_integer(2);

inline bool operator!=(const acc_integer &a, const acc_integer &b) {
	if (a.size() != b.size())return true;
	for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
		if (a[i] != b[i])return true;
	return false;
}

inline bool operator==(const acc_integer &a, const acc_integer &b) {
	return !(a != b);
}

inline bool operator<(const acc_integer &a, const acc_integer &b) {
	if (a.size() != b.size())return a.size() < b.size();
	for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
		if (a[i] != b[i])return a[i] < b[i];
	return false;
}

inline bool operator>(const acc_integer &a, const acc_integer &b) {
	return b < a;
}

inline bool operator<=(const acc_integer &a, const acc_integer &b) {
	return !(a > b);
}

inline bool operator>=(const acc_integer &a, const acc_integer &b) {
	return !(a < b);
}

inline acc_integer &operator+=(acc_integer &a, const acc_integer &b) {
	if (a.size() < b.size())a.resize(b.size());
	for (int i = 0; i != b.size(); ++i)a[i] += b[i];
	return a.check();
}

inline acc_integer operator+(acc_integer a, const acc_integer &b) {
	return a += b;
}

inline acc_integer &operator-=(acc_integer &a, acc_integer b) {
	if (a < b)swap(a, b);
	for (int i = 0; i != b.size(); a[i] -= b[i], ++i)
		if (a[i] < b[i]) {
			int j = i + 1;
			while (!a[j])++j;
			while (j > i) {
				--a[j];
				a[--j] += 10;
			}
		}
	return a.check();
}

inline acc_integer operator-(acc_integer a, const acc_integer &b) {
	return a -= b;
}

inline acc_integer operator*(const acc_integer &a, const acc_integer &b) {
	acc_integer n;
	n.assign(a.size() + b.size() - 1, 0);
	for (int i = 0; i != a.size(); ++i)
		for (int j = 0; j != b.size(); ++j)
			n[i + j] += a[i] * b[j];
	return n.check();
}

inline acc_integer &operator*=(acc_integer &a, const acc_integer &b) {
	return a = a * b;
}

inline acc_integer divideF(acc_integer &a, const acc_integer &b) {
	acc_integer ans;
	for (int t = static_cast<int>(a.size() - b.size()); a >= b; --t) {
		acc_integer d;
		d.assign(t + 1, 0);
		d.back() = 1;
		acc_integer c = b * d;
		while (a >= c) {
			a -= c;
			ans += d;
		}
	}
	return ans;
}

inline acc_integer operator/(acc_integer a, const acc_integer &b) {
	return divideF(a, b);
}

inline acc_integer &operator/=(acc_integer &a, const acc_integer &b) {
	return a = a / b;
}

inline acc_integer &operator%=(acc_integer &a, const acc_integer &b) {
	divideF(a, b);
	return a;
}

inline acc_integer operator%(acc_integer a, const acc_integer &b) {
	return a %= b;
}

inline acc_integer sqrt(const acc_integer &n) {
	acc_integer res = integer_1;
	while (res * res <= n) {
		res += integer_1;
	}
	if (res > integer_1) {
		res -= integer_1;
	}
	return res;
}

inline acc_integer pow(const acc_integer &n, const acc_integer &k) {
	if (k.empty())return integer_1;
	if (k == integer_2)return n * n;
	if (k.front() % 2)return n * pow(n, k - integer_1);
	return pow(pow(n, k / integer_2), integer_2);
}

inline void print_acc(const acc_integer &a) {
	for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
		printf("%d", a[i]);
	}
}

inline void println_acc(const acc_integer &a) {
	print_acc(a);
	printf("\n");
}

#define EML_RESEARCH_INTEGER_H

#endif //EML_RESEARCH_INTEGER_H
