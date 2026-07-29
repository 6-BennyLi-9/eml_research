//
// Created by QuSX on 2026/7/29.
//

#ifndef EML_RESEARCH_MODEL_H
#define EML_RESEARCH_MODEL_H
#include <vector>

namespace model {
	typedef void (*model_sample_runner)();

	struct model_sample {
		const char* name;
		const char* description;
		model_sample_runner runner;

		model_sample(const char * name, const char * description, model_sample_runner runner):
			name(name), description(description), runner(runner)
		{}
	};
	typedef std::vector<model_sample> model;
}
#endif //EML_RESEARCH_MODEL_H
