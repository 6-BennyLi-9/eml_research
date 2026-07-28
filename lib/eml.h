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
	};

	const auto X = eml(true);
	const auto E = eml();

	inline eml ln(const eml &e) {
		// return eml(nullptr, eml(eml(nullptr, e), nullptr));
		return eml{nullptr, eml{eml{nullptr, e}, nullptr}};
	}

	inline eml exp(const eml &e) {
		return eml{e, nullptr};
	}
}
#endif //EML_RESEARCH_EML_H
