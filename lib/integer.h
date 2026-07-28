#pragma once
#ifndef EML_RESEARCH_INTEGER_H
#include <cstdio>
#include <cstring>
/**
 * 高精度算法。目前 acc_integer 存储的数仅为自然数。
 */
class acc_integer {
	const short max_length = 2e5 + 5;
	char *head = new char[max_length], *end = head + 1;
public:
	acc_integer() : acc_integer(0) {
	}

	explicit acc_integer(int x) {
		write(x);
	}

	short len() const {
		return end - head;
	}

	void print() const {
		for (short i = len() - 1; i >= 0; --i) {
			printf("%c", head[i] + '0');
		}
	}

	void write(int x) {
		memset(head, 0, sizeof(head)); //wtf clang???
		if (x) {
			int n = 0;
			while (x) {
				head[n] = x % 10;
				x /= 10;
				++ n;
			}
			end = head + n;
		} else {
			head[0] = 0;
			end = head + 1;
		}
	}
private:
	acc_integer friend operator+(const acc_integer &, const acc_integer &);
	acc_integer friend operator-(const acc_integer &, const acc_integer &);
	acc_integer friend operator*(const acc_integer &, const acc_integer &);
	acc_integer friend operator/(const acc_integer &, const int &);
};

const auto integer_0 = acc_integer(0);
const auto integer_1 = acc_integer(1);

inline acc_integer operator+(const acc_integer &a, const acc_integer &b) {
	if (b.len() > a.len()) {
		return b + a;
	}
	acc_integer result;
	int n = 0;

	for (int i = 0; i < a.len(); ++i) {
		result.head[i] += a.head[i] + b.head[i];
		result.head[i + 1] += result.head[i] / 10;
		result.head[i] %= 10;
		++ n;
	}
	for (int i = a.len(); i < b.len(); ++i) {
		result.head[i] += b.head[i];
		result.head[i + 1] += result.head[i] / 10;
		result.head[i] %= 10;
		++ n;
	}
	if (result.head[n]) {
		++n;
	}

	result.end = result.head + n;
	return result;
}

inline acc_integer operator-(const acc_integer &a, const acc_integer &b) {
	throw "未实现";
}

inline acc_integer operator*(const acc_integer &a, const acc_integer &b) {
}

inline acc_integer operator/(const acc_integer &a, const acc_integer &b) {
}


#define EML_RESEARCH_INTEGER_H

#endif //EML_RESEARCH_INTEGER_H
