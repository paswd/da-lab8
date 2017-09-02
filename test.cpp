#include <iostream>

using namespace std;

const size_t MAX_NUM = 51;

class TArr {
public:
	size_t Arr[MAX_NUM];
	size_t Length;

	TArr(void) {
		this->Length = 0;
	}
	TArr(size_t num) {
		this->Length = num;
	}
};

bool NextStep(TArr *orig, size_t m) {
	for (size_t j = orig->Length; j > 0; j--) {
		size_t i = j - 1;
		if (orig->Arr[i] < m - orig->Length + i + 1) {
			orig->Arr[i]++;
			for (size_t k = j; k < orig->Length; k++) {
				orig->Arr[k] = orig->Arr[k - 1] + 1;
			}
			return true;
		}
	}
	return false;
}

int main(void) {
	TArr arr(4);
	for (size_t i = 0; i < 4; i++) {
		arr.Arr[i] = i;
	}
	do {
		for (size_t i = 0; i < 4; i++) {
			cout << arr.Arr[i] << " ";
		}
		cout << endl;
	} while (NextStep(&arr, 6));
	return 0;
}
