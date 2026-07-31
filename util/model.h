#ifndef EML_RESEARCH_MODEL_H
#define EML_RESEARCH_MODEL_H
#include <vector>
#include <chrono>
#define current_time std::chrono::high_resolution_clock::now()

namespace lazy {
	typedef void (*runnable)();

	struct model_sample {
		std::string name;
		std::string description;
		runnable runner;

		model_sample(const char *name, const char *description, runnable runner) : name(name), description(description),
			runner(runner) {
		}

		[[nodiscard]] auto run() const {
			const auto start = current_time;
			runner();
			const auto end = current_time;

			return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		}
	};

	typedef std::vector<model_sample> model;
}
#endif //EML_RESEARCH_MODEL_H
