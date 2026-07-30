#ifndef EML_RESEARCH_INTEGER_H
#define EML_RESEARCH_INTEGER_H
#include <cstdio>
#include <vector>
namespace acc {
	/**
	 * 高精度算法。存储的数为自然数。
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

		void print() const;

		void println() const;

		void printE() const;

		void printlnE() const;

		[[nodiscard]] signed toSigned() const ;
	};

	const auto integer_0 = acc_integer(0);
	const auto integer_1 = acc_integer(1);
	const auto integer_2 = acc_integer(2);
	const auto integer_10 = acc_integer(10);

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
		if (a < b) {
#ifdef DEBUG
			printf("[WARNING] Minus Operation Has Reversed, with a:");
			a.print();
			printf(", b:");
			b.println();
#endif
			swap(a, b);
		}
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

	inline acc_integer pow(const acc_integer &n, const acc_integer &k) {
		if (k.empty())return integer_1;
		if (k == integer_2)return n * n;
		if (k.front() % 2)return n * pow(n, k - integer_1);
		return pow(pow(n, k / integer_2), integer_2);
	}

	inline acc_integer mid(const acc_integer &a, const acc_integer &b) {
		return (a + b) / integer_2;
	}

	inline acc_integer sqrt(const acc_integer &n) {
		acc_integer left = integer_1, right = n;
		while (right > left + integer_1) {
			if (mid(left, right) * mid(left, right) < n) {
				left = mid(left, right);
			} else {
				right = mid(left, right);
			}
		}
		if (right * right <= n) {
			return right;
		}
		return left;
	}

	inline void print(const acc_integer &a) {
		for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
			printf("%d", a[i]);
		}
	}

	inline void println(const acc_integer &a) {
		print(a);
		printf("\n");
	}

	inline void printE(const acc_integer &a) {
		if (a.size() < 8) {
			print(a);
		}

		printf("%d.%d%d%de%llu", a[a.size() - 1], a[a.size() - 2], a[a.size() - 3], a[a.size() - 4], a.size() - 1);
	}

	inline void printlnE(const acc_integer &a) {
		printE(a);
		printf("\n");
	}

	inline void acc_integer::print() const { acc::print(*this); }
	inline void acc_integer::println() const { acc::println(*this); }
	inline void acc_integer::printE() const { acc::printE(*this); }
	inline void acc_integer::printlnE() const { acc::printlnE(*this); }

	inline signed acc_integer::toSigned() const {
		if (*this == integer_0) {
			return 0;
		}

		return (*this)[0] + (*this / integer_10).toSigned() * 10;
	}
}

#endif //EML_RESEARCH_INTEGER_H
