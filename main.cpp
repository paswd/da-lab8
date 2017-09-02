#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long double TDouble;

const size_t MAX_NUM = 51;
const TDouble EPS = 1.084202172485504434007453e-18;

class TBag {
public:
	size_t Supple[MAX_NUM];
	size_t InitIndex;
	size_t Length;
	size_t Cost;

	TBag(void) {
		this->Cost = 0;
	}

	void Get(void) {
		for (size_t i = 0; i < this->Length; i++) {
			cin >> this->Supple[i];
		}
		cin >> this->Cost;
	}
};

/* TArr {
public:
	size_t Arr[MAX_NUM];
	size_t Length;

	TArr(void) {
		this->Length = 0;
	}
	TArr(size_t num) {
		this->Length = num;
	}
};*/

/*bool NextStep(TArr *orig, size_t m) {
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
}*/

void MatrixToTriangle(TDouble map[MAX_NUM][MAX_NUM], int m, int n) {
	vector <int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; col++) {
		int sel = row;
		for (int i = row; i < n; i++)
			if (abs(map[i][col]) > abs(map[sel][col])) {
				sel = i;
			}
		if (abs(map[sel][col]) < EPS) {
			continue;
		}
		for (int i = col; i <= m; i++) {
			swap(map[sel][i], map[row][i]);
		}
		where[col] = row;

		for (int i = 0; i < n; i++) {
			if (i != row) {
				TDouble c = map[i][col] / map[row][col];
				for (int j = col; j <= m; j++) {
					map[i][j] -= map[row][j] * c;
				}
			}
		}
		row++;
	}

	/*for (size_t i = 0; i < (size_t) m; i++) {
		for (size_t j = 0; j < (size_t) n; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	/*
	vector <TDouble> ans;

	ans.assign(m, 0);
	for (int i = 0; i < m; i++) {
		if (where[i] != -1) {
			ans[i] = map[where[i]][m] / map[where[i]][i];
		}
	}
	for (int i = 0; i < n; i++) {
		TDouble sum = 0;
		for (int j=0; j<m; ++j) {
			sum += ans[j] * map[i][j];
		}
		if (abs (sum - map[i][m]) > EPS) {
			return 0;
		}
	}

	for (int i=0; i<m; ++i) {
		if (where[i] == -1) {
			return false;
		}
	}
	return true;
	*/
}

bool IsRowZero(TDouble *arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (arr[i] != 0) {
			return false;
		}
	}
	return true;
}

bool IsLinearIndependent(TBag *base, size_t size, size_t current_indepentent) {
	/*TBag current_base[MAX_NUM];
	for (size_t i = 0; i < current_index->Length; i++) {
		current_base[i] = base[current_index->Arr[i]];
	}

	MatrixToTriangle(current_base, current_index->Length);

	for (size_t i = 0; i < current_index->Length; i++) {
		if (current_base[i].Supple[i] == 0) {
			return false;
		}
	}

	return true;*/

	TDouble matrix[MAX_NUM][MAX_NUM];

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < base[i].Length; j++) {
			matrix[i][j] = (TDouble) base[i].Supple[j];
		}
	}

	MatrixToTriangle(matrix, (int) size, (int) base[0].Length);

	size_t new_independent = 0;
	for (size_t i = 0; i < size; i++) {
		if (!IsRowZero(matrix[i], base[i].Length)) {
			new_independent++;
		}
	}
	//cout << "new_independent = " << new_independent << endl;
	//cout << "current_indepentent = " << current_indepentent << endl;
	if (new_independent > current_indepentent) {
		return true;
	}
	return false;
}

int main(void) {
	size_t m, n;
	cin >> m >> n;

	TBag base[MAX_NUM];

	for (size_t i = 0; i < m; i++) {
		base[i].Length = n;
		base[i].Get();
		base[i].InitIndex = i;
	}

	for (size_t i = m; i > 0; i--) {
		bool change = false;
		for (size_t j = 1; j < i; j++) {
			if (base[j - 1].Cost > base[j].Cost) {
				TBag tmp = base[j - 1];
				base[j - 1] = base[j];
				base[j] = tmp;
				change = true;
			}
		}
		if (!change) {
			break;
		}
	}

	/*TArr current_index(n);
	//TArr max_index(n);
	bool current_index_using[MAX_NUM];
	for (size_t i = 0; i < m; i++) {
		if (i < n) {
			current_index_using[i] = true;
		} else {
			current_index_using[i] = false;
		}
	}
	//size_t diff = m - n;
	for (size_t i = 0; i < n; i++) {
		current_index.Arr[i] = i;
		//max_index[i] = i + diff;
	}

	bool is_correct_answer = false;
	do {
		if (IsLinearIndependent(base, &current_index, m, n)) {
			is_correct_answer = true;
			for (size_t i = 0; i < current_index.Length; i++) {
				cout << current_index.Arr[i] + 1 << " ";
			}
			cout << endl;
			break;
		}
	} while (NextStep(&current_index, m));

	if (!is_correct_answer) {
		cout << -1 << endl;
	}*/




	vector <size_t> res(0);

	size_t current = 0;

	for (size_t i = 0; i < m && current < n; i++) {
		if (IsLinearIndependent(base, i + 1, current)) {
			size_t pos = res.size();
			res.resize(res.size() + 1);
			res[pos] = base[i].InitIndex;
			current++;
		}
	}

	if (res.size() < n) {
		cout << "-1" << endl;
		return 0;
	}

	sort(res.begin(), res.end());

	for (size_t i = 0; i < res.size(); i++) {
		cout << res[i] + 1 << " ";
	}
	cout << endl;

	return 0;
}
