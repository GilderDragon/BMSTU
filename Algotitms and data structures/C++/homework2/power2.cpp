#include <iostream>
#include <vector>

#define max_num 1000001

using namespace std;

vector<int> all_sum(int n, vector<int>& vec) {
    vector<int> ans;

    int total = 1 << n;

    for (int mask = 1; mask < total; mask++) {
        int temp = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                 temp += vec[i];
            }
        }
        ans.push_back(temp);
    }
    return ans;
}

int main() {
    int n;
    cin >> n;

    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    vector<int> powers;
    powers.push_back(1);
    while (powers.back() < max_num) {
        powers.push_back(powers.back() * 2);
    }

    int ans = 0;

    for (int i : all_sum(n, vec)) {
        bool fl = false;
        for (int j : powers) {
            if (i == j) {
                fl = true;
                break;
            }
        }
        if (fl) ans++;
    }

    cout << ans;

    return 0;
}
