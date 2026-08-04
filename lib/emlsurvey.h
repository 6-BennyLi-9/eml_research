#ifndef EML_RESEARCH_EMLSURVEY_H
#define EML_RESEARCH_EMLSURVEY_H
#include "eml.h"
#include "integer.h"

namespace eml {
	class emlsurvey {
	public:
		acc::integer theta{1}, depth{1};
		int algebra = 0;

		[[nodiscard]] bool pure() const {
			return !algebra;
		}

		void println() const {
			printf("theta = ");
			theta.println();
			printf("depth = ");
			depth.println();

			if (algebra) {
				printf("containing algebra\n");
			} else {
				printf("pure expression\n");
			}
		}
	};

	inline emlsurvey survey(const eml &target) {
		emlsurvey res, temp;

		if (target.type) {
			res.algebra = target.type;
			return res;
		}

		if (target.lValue) {
			temp = survey(*target.lValue);
			res.algebra = std::max(res.algebra, temp.algebra);
			res.theta += temp.theta;
			res.depth = temp.depth;
		} else {
			res.theta += acc::integer_1;
		}

		if (target.rValue) {
			temp = survey(*target.rValue);
			res.algebra = std::max(res.algebra, temp.algebra);
			res.theta += temp.theta;

			if (res.depth < temp.depth) {
				res.depth = temp.depth;
			}
		} else {
			res.theta += acc::integer_1;
		}

		res.depth += acc::integer_1;

		return res;
	}

	inline emlexp make_exp(const eml& target, const emlsurvey& survey) {
		return {survey.algebra, target};
	}

	inline emlexp make_exp(const eml& target) {
		return make_exp(target, survey(target));
	}
}

#endif //EML_RESEARCH_EMLSURVEY_H
