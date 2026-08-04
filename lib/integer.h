#ifndef EML_RESEARCH_INTEGER_H
#define EML_RESEARCH_INTEGER_H
#include <cstdio>
#include <vector>

namespace acc {
	/**
	 * 高精度算法。存储的数为自然数。
	 */
	class unsigned_integer : public std::vector<int> {
	public:
		unsigned_integer() : unsigned_integer(0) {
		}

		explicit unsigned_integer(const int n) {
			push_back(n);
			check();
		}

		explicit unsigned_integer(const std::string &str) {
			for (int i = static_cast<int>(str.length()) - 1; i >= 0; --i) {
				push_back(str[i] - '0');
			}
			check();
		}

		unsigned_integer &check() {
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

		[[nodiscard]] signed to_signed() const;

		[[nodiscard]] std::string to_string() const;

		[[nodiscard]] std::string to_stringE() const;
	};

	const auto integer_0 = unsigned_integer(0);
	const auto integer_1 = unsigned_integer(1);
	const auto integer_2 = unsigned_integer(2);
	const auto integer_10 = unsigned_integer(10);

	inline bool operator!=(const unsigned_integer &a, const unsigned_integer &b) {
		if (a.size() != b.size())return true;
		for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
			if (a[i] != b[i])return true;
		return false;
	}

	inline bool operator==(const unsigned_integer &a, const unsigned_integer &b) {
		return !(a != b);
	}

	inline bool operator<(const unsigned_integer &a, const unsigned_integer &b) {
		if (a.size() != b.size())return a.size() < b.size();
		for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
			if (a[i] != b[i])return a[i] < b[i];
		return false;
	}

	inline bool operator>(const unsigned_integer &a, const unsigned_integer &b) {
		return b < a;
	}

	inline bool operator<=(const unsigned_integer &a, const unsigned_integer &b) {
		return !(a > b);
	}

	inline bool operator>=(const unsigned_integer &a, const unsigned_integer &b) {
		return !(a < b);
	}

	inline unsigned_integer &operator+=(unsigned_integer &a, const unsigned_integer &b) {
		if (a.size() < b.size())a.resize(b.size());
		for (int i = 0; i != b.size(); ++i)a[i] += b[i];
		return a.check();
	}

	inline unsigned_integer operator+(unsigned_integer a, const unsigned_integer &b) {
		return a += b;
	}

	inline unsigned_integer &operator-=(unsigned_integer &a, unsigned_integer b) {
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

	inline unsigned_integer operator-(unsigned_integer a, const unsigned_integer &b) {
		return a -= b;
	}

	inline unsigned_integer operator*(const unsigned_integer &a, const unsigned_integer &b) {
		unsigned_integer n;
		n.assign(a.size() + b.size() - 1, 0);
		for (int i = 0; i != a.size(); ++i)
			for (int j = 0; j != b.size(); ++j)
				n[i + j] += a[i] * b[j];
		return n.check();
	}

	inline unsigned_integer &operator*=(unsigned_integer &a, const unsigned_integer &b) {
		return a = a * b;
	}

	inline unsigned_integer divideF(unsigned_integer &a, const unsigned_integer &b) {
		unsigned_integer ans;
		for (int t = static_cast<int>(a.size() - b.size()); a >= b; --t) {
			unsigned_integer d;
			d.assign(t + 1, 0);
			d.back() = 1;
			unsigned_integer c = b * d;
			while (a >= c) {
				a -= c;
				ans += d;
			}
		}
		return ans;
	}

	inline unsigned_integer operator/(unsigned_integer a, const unsigned_integer &b) {
		return divideF(a, b);
	}

	inline unsigned_integer &operator/=(unsigned_integer &a, const unsigned_integer &b) {
		return a = a / b;
	}

	inline unsigned_integer &operator%=(unsigned_integer &a, const unsigned_integer &b) {
		divideF(a, b);
		return a;
	}

	inline unsigned_integer operator%(unsigned_integer a, const unsigned_integer &b) {
		return a %= b;
	}

	inline unsigned_integer pow(const unsigned_integer &n, const unsigned_integer &k) {
		if (k.empty())return integer_1;
		if (k == integer_2)return n * n;
		if (k.front() % 2)return n * pow(n, k - integer_1);
		return pow(pow(n, k / integer_2), integer_2);
	}

	inline unsigned_integer mid(const unsigned_integer &a, const unsigned_integer &b) {
		return (a + b) / integer_2;
	}

	inline unsigned_integer sqrt(const unsigned_integer &n) {
		unsigned_integer left = integer_1, right = n;
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

	inline void print(const unsigned_integer &a) {
		// for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i) {
		// 	printf("%d", a[i]);
		// }

		printf("%s", a.to_string().c_str());
	}

	inline void println(const unsigned_integer &a) {
		print(a);
		printf("\n");
	}

	inline void printE(const unsigned_integer &a) {
		// if (a.size() < 8) {
		// 	print(a);
		// }
		//
		// printf("%d.%d%d%de%llu", a[a.size() - 1], a[a.size() - 2], a[a.size() - 3], a[a.size() - 4],
		// 		static_cast<unsigned long long>(a.size() - 1));

		printf("%s", a.to_stringE().c_str());
	}

	inline void printlnE(const unsigned_integer &a) {
		printE(a);
		printf("\n");
	}

	inline void unsigned_integer::print() const { acc::print(*this); }
	inline void unsigned_integer::println() const { acc::println(*this); }
	inline void unsigned_integer::printE() const { acc::printE(*this); }
	inline void unsigned_integer::printlnE() const { acc::printlnE(*this); }

	inline signed unsigned_integer::to_signed() const {
		if (*this == integer_0) {
			return 0;
		}

		return (*this)[0] + (*this / integer_10).to_signed() * 10;
	}

#define _digital(i) static_cast<char>('0' + (*this)[i])

	inline std::string unsigned_integer::to_string() const {
		if (*this == integer_0) {
			return "0";
		}

		const auto cache = (*this / integer_10);
		if (cache == integer_0) {
			return std::string() + _digital(0);
		}
		return cache.to_string() + _digital(0);
	}

	inline std::string unsigned_integer::to_stringE() const {
		if (size() < 8) {
			return to_string();
		}

		return std::string() + _digital(size() - 1) + "." + _digital(size() - 2) + _digital(size() - 3) +
				_digital(size() - 4) + "e" + unsigned_integer(static_cast<int>(size()) - 1).to_string();
	}
#undef _digital
}

#endif //EML_RESEARCH_INTEGER_H
