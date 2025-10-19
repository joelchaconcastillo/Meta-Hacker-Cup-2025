#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N;
    cin >> N;
    vector<long long> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];

    unordered_map<long long,long long> freq;
    freq.reserve(N * 2 + 10);
    freq.max_load_factor(0.7);

    long long px = 0;
    freq[px] = 1;
    for(int i = 0; i < N; i++) {
        px ^= A[i];
        freq[px]++;
    }

    long long sumLen = (long long)N * (N + 1) * (N + 2) / 6;
    long long total_g_zero = 0;
    for(auto &p : freq) {
        long long k = p.second;
        if(k < 2) continue;
        long long S1 = k * (k - 1) / 2;
        long long S2 = (k - 1) * k * (2 * k - 1) / 6;
        long long contrib = (S2 + S1) / 2;
        total_g_zero += contrib;
    }

    cout << sumLen - total_g_zero << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}

