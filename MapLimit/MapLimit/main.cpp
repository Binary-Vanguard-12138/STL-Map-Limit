#include <string>
#include "LimitMap.h"


int main() {
	LimitMap<std::string, int> ml(12);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++) {
			char szKey[16] = {};
			sprintf_s(szKey, _countof(szKey) - 1, "key%d", j);
			std::string key = szKey;
			if (ml.has(key)) {
				printf("%s %d\n", key.c_str(), ml.get(key));
			}
			else {
				ml.set(key, j);
			}
		}
	}
	printf("%d\n", ml.size());
	return 0;
}