#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long double TNumber;

const size_t MAX_NUM = 51;
//const TNumber EPS = 1.084202172485504434007453e-18;
const TNumber EPS = numeric_limits<TNumber>::epsilon();

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

size_t gcd(size_t a, size_t b) {
	while (a > 0 && b > 0) {
		if (a > b) {
			a %= b;
		} else {
			b %= a;
		}
	}
	return a + b;
}

size_t gcda(size_t *arr, size_t size) {
	size_t res = 0;
	for (size_t i = 0; i < size; i++) {
		res = gcd(res, arr[i]);
	}
	if (res == 0) {
		res = 1;
	}
	return res;
}

//void MatrixToTriangleOLD(TNumber map[MAX_NUM][MAX_NUM], int m, int n) {
	/*vector <int> where(m, -1);
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
				TNumber c = map[i][col] / map[row][col];
				for (int j = col; j <= m; j++) {
					map[i][j] -= map[row][j] * c;
				}
			}
		}
		row++;
	}

	for (size_t i = 0; i < (size_t) m; i++) {
		for (size_t j = 0; j < (size_t) n; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	/*
	vector <TNumber> ans;

	ans.assign(m, 0);
	for (int i = 0; i < m; i++) {
		if (where[i] != -1) {
			ans[i] = map[where[i]][m] / map[where[i]][i];
		}
	}
	for (int i = 0; i < n; i++) {
		TNumber sum = 0;
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
//}

/*size_t GetRank(TNumber map[MAX_NUM][MAX_NUM], size_t m, size_t n) {
	size_t rank = max(n, m);
	vector <char> line_used(n);
	for (size_t i = 0; i < m; i++) {
		size_t j;
		for (j = 0; j < n; j++) {
			if (!line_used[j] && fabs(map[j][i] > EPS)) {
				break;
			}
		}
		if (j == n) {
			rank--;
		} else {
			line_used[j] = 1;
			for (size_t k = i + 1; k < m; k++) {
				map[j][k] /= map[j][i];
			}
			for (size_t k = 0; k < n; k++) {
				if (k != j && fabs(map[k][i]) > EPS) {
					for (size_t l = i + 1; l < m; l++) {
						map[k][l] -= map[j][l] * map[k][i];
					}
				}
			}
		}
	}

	return rank; 
}*/

bool IsRowZero(TNumber *arr, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (arr[i] != 0) {
			return false;
		}
	}
	return true;
}

bool IsEqualMatrix(TNumber map[MAX_NUM][MAX_NUM], size_t m, size_t n) {
	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << "===" << endl;
	vector <int> where(n, -1);
	for (size_t col = 0, row = 0; col < n && row < m; col++) {
		size_t sel = row;
		for (size_t i = row; i < m; i++) {
			if (fabs(map[i][col]) > fabs(map[sel][col])) {
				sel = i;
			}
		}
		if (fabs(map[sel][col]) < EPS) {
			continue;
		}
		for (size_t i = col; i <= n; i++) {
			swap(map[sel][i], map[row][i]);
		}
		where[col] = row;
		for (size_t i = 0; i < m; i++) {
			if (i != row) {
				TNumber tmp = map[i][col] / map[row][col];
				for (size_t j = col; j <= n; j++) {
					map[i][j] -= map[row][j] * tmp;
				}
			}
		}
		row++;
	}
	vector <TNumber> ans(n, 0);
	for (size_t i = 0; i < n; i++) {
		if (where[i] != -1) {
			ans[i] = map[where[i]][n] / map[where[i]][i];
		}
	}
	for (size_t i = 0; i < m; i++) {
		TNumber summ = 0;
		for (size_t j = 0; j < n; j++) {
			summ += ans[j] * map[i][j];
		}
		if (fabs(summ - map[i][n]) > EPS) {
			cout << "Res: 0" << endl;
			return false;
		}
	}
	for (size_t i = 0; i < n; i++) {
		if (where[i] == -1) {
			cout << "Res: INF" << endl;
			return false;
		}
	}
	cout << "Res: 1" << endl;
	return true;
}

bool IsLinearIndependent(TBag *base, size_t size) {
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

	TNumber matrix[MAX_NUM][MAX_NUM];

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < base[i].Length; j++) {
			matrix[i][j] = (TNumber) base[i].Supple[j];
		}
	}

	//MatrixToTriangle(matrix, (int) size, (int) base[0].Length);
	//size_t rank = GetRank(matrix, size, base[0].Length);
	return IsEqualMatrix(matrix, size, base[0].Length);

	/*size_t new_independent = 0;
	for (size_t i = 0; i < size; i++) {
		if (!IsRowZero(matrix[i], base[i].Length)) {
			new_independent++;
		}
	}*/
	//cout << "new_independent = " << new_independent << endl;
	//cout << "current_indepentent = " << current_indepentent << endl;
	/*if (rank > current_indepentent) {
		return true;
	}
	return false;*/
}

int main(void) {
	size_t m, n;
	cin >> m >> n;

	TBag base[MAX_NUM];

	for (size_t i = 0; i < m; i++) { //Getting values
		base[i].Length = n;
		base[i].Get();
		base[i].InitIndex = i;

		size_t current_gcd = gcda(base[i].Supple, base[i].Length);
		for (size_t j = 0; j < base[i].Length; j++) {
			base[i].Supple[j] /= current_gcd;
		}
	}

	for (size_t i = m; i > 0; i--) { //Bubble sort
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

	//size_t current = 0;

	/*for (size_t i = 0; i < m && current < n; i++) {
		if (IsLinearIndependent(base, i + 1, current)) {
			size_t pos = res.size();
			res.resize(res.size() + 1);
			res[pos] = base[i].InitIndex;
			current++;
		}
	}*/
	size_t cnt;
	bool found = false;
	for (cnt = 0; cnt < m; cnt++) {
		if (IsLinearIndependent(base, cnt + 1)) {
			found = true;
			cnt++;
			break;
		}
	}

	if (!found) {
		cout << "-1" << endl;
		return 0;
	}
	for (size_t i = 0; i < cnt; i++) {
		res.push_back(base[i].InitIndex);
	}

	sort(res.begin(), res.end());

	bool first = true;
	for (size_t i = 0; i < res.size(); i++) {
		if (!first) {
			cout << " ";
		} else {
			first = false;
		}
		cout << res[i] + 1;
	}
	cout << endl;

	return 0;
}
