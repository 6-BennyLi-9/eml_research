#ifndef EML_RESEARCH_TABLE_H
#define EML_RESEARCH_TABLE_H
#include <cassert>
#include <string>
#include <vector>

namespace lazy {
	class table {
		std::vector<std::pmr::vector<std::string>> mem;
		int xLen = 0;
	public:
		void wrap() {
			assert(!mem.empty());

			if (mem.size() > 1) {
				if ((mem.front().size() == mem.back().size())) {
					mem.emplace_back();
				}
			} else {
				mem.emplace_back();
			}
		}

		void put(const std::string &next) {
			if (!mem.empty()) {
				mem.back().push_back(next);
			} else {
				mem.push_back({next});
			}

			if (mem.size() > 1 && mem.back().size() == mem.front().size()) {
				wrap();
			}

			xLen = std::max(xLen, static_cast<int>(next.size()));
		}

		void print() const {
			for (int i = 0; i < (xLen + 2) * mem.front().size() + 2; ++i) {
				printf("=");
			}

			for (const auto& line: mem) {
				if (line.size() != mem.front().size()) {
					continue;
				}

				printf("\n||");
				for (const auto& item: line) {
					printf("%s", item.c_str());
					for (int i = 1; i <= xLen - item.length(); ++i) {
						printf(" ");
					}

					printf("||");
				}
			}
			printf("\n");
			for (int i = 0; i < (xLen + 2) * mem.front().size() + 2; ++i) {
				printf("=");
			}
			printf("\n");
		}
	};
}
#endif //EML_RESEARCH_TABLE_H
