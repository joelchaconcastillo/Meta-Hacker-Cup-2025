#include <bits/stdc++.h>
using namespace std;

void solve() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        string S;
        cin >> N >> S;

        deque<int> A_pos, B_pos;
        for (int i = 0; i < N; ++i) {
            if (S[i] == 'A') A_pos.push_back(i);
            else B_pos.push_back(i);
        }

        int left = 0, right = N - 1;
        bool alice_turn = true;
        int last_eater = -1;

        while (left <= right) {
            if (alice_turn) {
                while (!A_pos.empty() && (A_pos.front() < left || A_pos.front() > right))
                    A_pos.pop_front();
                if (!A_pos.empty()) {
                    int idx = A_pos.front();
                    left = idx + 1;
                    last_eater = 0;
                }
            } else {
                while (!B_pos.empty() && (B_pos.back() < left || B_pos.back() > right))
                    B_pos.pop_back();
                if (!B_pos.empty()) {
                    int idx = B_pos.back();
                    right = idx - 1;
                    last_eater = 1;
                }
            }
            alice_turn = !alice_turn;
        }

        cout << "Case #" << t << ": " << (last_eater == 0 ? "Alice" : "Bob") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}

