#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long double TNumber;

const size_t MAX_NUM = 51;
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

bool IsRowZero(TNumber *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != 0) {
            return false;
        }
    }
    return true;
}

size_t GetRank(TNumber map[MAX_NUM][MAX_NUM], size_t m, size_t n) {
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

    size_t rank = 0;

    for (size_t i = 0; i < m; i++) {
        if (!IsRowZero(map[i], n)) {
            rank++;
        }
    }
    return rank;
}

bool IsLinearIndependent(TBag *base, size_t size, size_t current_independent) {
    TNumber matrix[MAX_NUM][MAX_NUM];

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < base[i].Length; j++) {
            matrix[i][j] = (TNumber) base[i].Supple[j];
        }
    }

    size_t rank = GetRank(matrix, size, base[0].Length);
    
    if (rank > current_independent) {
        return true;
    }
    return false;
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
    
    if (current < n) {
        cout << "-1" << endl;
        return 0;
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
