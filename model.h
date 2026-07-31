#ifndef EML_RESEARCH_MODEL_H
#define EML_RESEARCH_MODEL_H
#include <vector>

namespace model {
	typedef void (*runnable)();

	struct model_sample {
		std::string name;
		std::string description;
		runnable runner;

		model_sample(const char * name, const char * description, runnable runner):
			name(name), description(description), runner(runner)
		{}
	};
	typedef std::vector<model_sample> model;
}
#endif //EML_RESEARCH_MODEL_H
