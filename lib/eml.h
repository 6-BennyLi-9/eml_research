#ifndef EML_RESEARCH_EML_H
#define EML_RESEARCH_EML_H
#include <cstdio>
#include <memory>
#include <utility>

namespace eml {
	class eml {
	public:
		std::shared_ptr<eml> leftValue, rightValue;
		int isX;

		eml(const std::shared_ptr<eml> &leftValue, const std::shared_ptr<eml> &rightValue):
			leftValue(leftValue), rightValue(rightValue), isX(false)
		{}
		eml() : eml(nullptr, nullptr) {}

		explicit eml(const bool isX) :
			leftValue(nullptr), rightValue(nullptr), isX(isX)
		{}

		eml(const eml &leftValue, const eml &rightValue):
			eml(std::make_shared<eml>(leftValue), std::make_shared<eml>(rightValue))
		{}
		eml(const std::shared_ptr<eml> &leftValue, const eml &rightValue):
			eml(leftValue, std::make_shared<eml>(rightValue))
		{}
		eml(const eml &leftValue, const std::shared_ptr<eml> &rightValue):
			eml(std::make_shared<eml>(leftValue), rightValue)
		{}

		void print() const {
			if (isX) {
				printf("x");
				return;
			}
			if (leftValue) {
				printf("e^(");
				leftValue->print();
				printf(")");
			} else {
				printf("e");
			}

			if (rightValue) {
				printf(" - ln(");
				rightValue->print();
				printf(")");
			}
		}

		void println() const {
			print();
			printf("\n");
		}

		void print0() const {
			printf("eml(");
			if (leftValue) {
				leftValue->print0();
			} else {
				printf("1");
			}
			printf(", ");
			if (rightValue) {
				rightValue->print0();
			} else {
				printf("1");
			}
			printf(")");
		}

		void println0() const {
			print0();
			printf("\n");
		}
	};

#define eml_constance(name, value...) inline eml name() {return value;}

	// const auto X = eml(true);
	// const auto E = eml();

	eml_constance(X, eml(true))
	eml_constance(E, eml())

	inline eml ln(const eml &e) {
		// return eml(nullptr, eml(eml(nullptr, e), nullptr));
		return eml{nullptr, eml{eml{nullptr, e}, nullptr}};
	}

	inline eml exp(const eml &e) {
		return eml{e, nullptr};
	}

	eml_constance(ZERO,eml{nullptr,eml{eml{nullptr,nullptr},nullptr}})

	/**
	 * @param a a != 0
	 * @param b
	 */
	inline eml unsafe_minus(const eml &a, const eml &b) {
		return eml{ln(a), exp(b)};
	}

	eml_constance(NEGATIVE_ONE, unsafe_minus(eml{ln(E()), E()}, E()))
}
#endif //EML_RESEARCH_EML_H
