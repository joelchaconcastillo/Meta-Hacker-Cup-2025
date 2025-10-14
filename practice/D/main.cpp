#include <bits/stdc++.h>
using namespace std;

int n, m;

// Compute total score
pair<long long, string> compute_score(const vector<int> &color, const vector<vector<int>> &nodes) {
    vector<unordered_map<int, int>> days(2);
    string path;
    for (int i = 0; i < m; i++) {
        path += (color[i] == 0 ? '1' : '2');
        days[color[i]][nodes[i][0]]++;
        days[color[i]][nodes[i][1]]++;
    }
    long long score = 0;
    for (auto &maps : days)
        for (auto &[coder, count] : maps)
            score += 1LL * count * count;
    return {score, path};
}

struct ComponentInfo {
    int a = 0; // count of color 0
    int b = 0; // count of color 1
    vector<int> nodes; // indices
};

// DP memo key: (idx, delta)
struct Key {
    int idx;
    int delta;
    bool operator==(const Key &o) const noexcept {
        return idx == o.idx && delta == o.delta;
    }
};

struct KeyHash {
    size_t operator()(const Key &k) const noexcept {
        return hash<long long>()(((long long)k.idx << 32) ^ (k.delta + 50000));
    }
};

unordered_map<Key, long long, KeyHash> memo;
unordered_map<Key, bool, KeyHash> choice;

long long dfsDP(int idx, int delta, const vector<ComponentInfo> &comps) {
    if (idx == (int)comps.size())
        return llabs(delta);

    Key key{idx, delta};
    if (memo.count(key)) return memo[key];

    auto [a, b, _] = comps[idx];
    long long keep = dfsDP(idx + 1, delta + (a - b), comps);
    long long flip = dfsDP(idx + 1, delta + (b - a), comps);

    bool takeFlip = flip < keep;
    choice[key] = takeFlip;
    return memo[key] = min(keep, flip);
}

// reconstruct flip choices
void reconstruct(int idx, int delta, const vector<ComponentInfo> &comps, vector<int> &color) {
    if (idx == (int)comps.size()) return;
    Key key{idx, delta};
    bool flip = choice[key];
    if (flip) {
        for (int node : comps[idx].nodes) color[node] ^= 1;
        reconstruct(idx + 1, delta + (comps[idx].b - comps[idx].a), comps, color);
    } else {
        reconstruct(idx + 1, delta + (comps[idx].a - comps[idx].b), comps, color);
    }
}

void solve() {
    cin >> n >> m;
    vector<vector<int>> nodes(m, vector<int>(2));
    vector<vector<int>> coder2node(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> nodes[i][0] >> nodes[i][1];
        coder2node[nodes[i][0]].push_back(i);
        coder2node[nodes[i][1]].push_back(i);
    }

    vector<int> color(m, -1);
    queue<int> q;
    vector<ComponentInfo> comps;

    for (int i = 0; i < m; i++) {
        if (color[i] != -1) continue;

        color[i] = 0;
        q.push(i);
        vector<bool> markedCoder(n + 1, false);
        ComponentInfo comp;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            comp.nodes.push_back(node);
            if (color[node] == 0) comp.a++;
            else comp.b++;

            int c1 = nodes[node][0], c2 = nodes[node][1];
            for (int coder : {c1, c2}) {
                if (markedCoder[coder]) continue;
                for (int next : coder2node[coder]) {
                    if (next == node) continue;
                    if (color[next] == -1) {
                        color[next] = color[node] ^ 1;
                        q.push(next);
                    }
                }
                markedCoder[coder] = true;
            }
        }
        comps.push_back(comp);
    }

    memo.clear();
    choice.clear();
    dfsDP(0, 0, comps);

    reconstruct(0, 0, comps, color);

    auto [score, path] = compute_score(color, nodes);
    cout << score << " " << path << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}

