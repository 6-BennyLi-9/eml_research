#ifndef EML_RESEARCH_EMLSURVEY_H
#define EML_RESEARCH_EMLSURVEY_H
#include "eml.h"
#include "integer.h"

namespace eml {
	class emlsurvey {
	public:
		acc::integer theta{};
		bool algebra = false;

		[[nodiscard]] bool pure() const {
			return !algebra;
		}

		void println() const {
			printf("theta = ");
			theta.println();

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
			res.algebra = true;
			return res;
		}

		if (target.lValue) {
			temp = survey(*target.lValue);
			res.algebra |= temp.algebra;
			res.theta += temp.theta;
		}

		if (target.rValue) {
			temp = survey(*target.rValue);
			res.algebra |= temp.algebra;
			res.theta += temp.theta;
		}

		res.theta += acc::integer_1;

		return res;
	}
}

#endif //EML_RESEARCH_EMLSURVEY_H
