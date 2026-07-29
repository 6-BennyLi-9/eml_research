//
// Created by QuSX on 2026/7/29.
//

#ifndef EML_RESEARCH_MODEL_H
#define EML_RESEARCH_MODEL_H
#include <vector>

namespace model {
	typedef void (*model_sample_runner)();

	struct model_sample {
		const char* name_cn;
		const char* description_cn;
		const char* name_en;
		const char* description_en;
		model_sample_runner runner;

		model_sample(const char * name_cn, const char * description_cn, const char * name_en, const char * description_en, model_sample_runner runner):
			name_cn(name_cn), description_cn(description_cn), name_en(name_en), description_en(description_en),runner(runner)
		{}
	};
	typedef std::vector<model_sample> model;
}
#endif //EML_RESEARCH_MODEL_H
