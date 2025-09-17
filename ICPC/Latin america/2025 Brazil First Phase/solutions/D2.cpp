#include <bits/stdc++.h>

using namespace std;

const int MAX = 205;

set<set<int>> order[MAX];

int N;
vector<int> a, b;
vector<int> f;
map<set<set<int>>, int> all_states;
int transition[MAX][100];
bool terminal[MAX];

int curr_step = 0;
int memo[25][1 << 6][MAX], step[25][1 << 6][MAX];

int get_index(int a, int b) {
    return 7 * a + b;
}

set<set<int>> next_state(set<set<int>> state, int da, int db) {
    set<set<int>> new_state = state;
    set<int> da_set, db_set;

    for (set<int> cset: state) {
        if (cset.count(da)) da_set = cset;
        if (cset.count(db)) db_set = cset;
    }

    if (da_set != db_set) {
        new_state.erase(da_set);
        new_state.erase(db_set);

        for (int v: db_set)
            da_set.insert(v);

        new_state.insert(da_set);
    }

    return new_state;
}

void get_all_states() {
    set<set<int>> initial_state;
    for (int i = 0; i < 6; i++) {
        set<int> i_set;
        i_set.insert(i);
        initial_state.insert(i_set);
    }

    queue<set<set<int>>> q;
    q.push(initial_state);

    int curr_state = 0;
    while (!q.empty()) {
        set<set<int>> v = q.front(); q.pop();
        if (all_states.count(v)) continue;
        order[curr_state] = v;
        all_states[v] = curr_state++;
        for (int a = 0; a < 6; a++)
            for (int b = 0; b < 6; b++) {
                set<set<int>> nxt = next_state(v, a, b);
                q.push(nxt);
            }
    }
}

bool is_terminal(set<set<int>> state) {
    int cnt_singles = 0;
    for (set<int> cset: state)
        if ((int) cset.size() > 1)
            cnt_singles++;

    return cnt_singles <= 1;
}

int count(int i = 0, int mask = 0, int state = 0) {
    int &ans = memo[i][mask][state];
    if (step[i][mask][state] == curr_step) return ans;

    step[i][mask][state] = curr_step;

    if (i >= N) {
        if(__builtin_popcount(mask) > 2 || !terminal[state]) return ans = 0;
        ans = 1;
        std::set<int> st;
        for(auto group : order[state]) {
            if(group.size() > 1) st = group;
        }
        if(st.empty()) {
            for(int j = 0; j < 6; j++) {
                ans += (1 << f[j]) - 1;
            }
        } else {
            for(auto x : st) {
                ans <<= f[x];
            }
        }
        return ans;
    }

    return ans = count(i + 1, mask, state) + count(i + 1, mask ^ (1 << a[i]) ^ (1 << b[i]), transition[state][get_index(a[i], b[i])]);
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);

    get_all_states();

    int num_states = all_states.size();
    for (auto [state, idx]: all_states) {
        for (int a = 0; a < 6; a++) {
            for (int b = 0; b < 6; b++) {
                set<set<int>> nxt = next_state(state, a, b);
                transition[idx][get_index(a, b)] = all_states[nxt];
            }
        }
    }

    for (auto [state, idx]: all_states)
        terminal[idx] = is_terminal(state);

    int T; cin >> T;
    while (T--) {
        cin >> N;
        curr_step++;

        a.resize(N), b.resize(N);
        f.assign(7, 0);
        for (int i = 0; i < N; i++) {
            cin >> a[i] >> b[i];
            a[i]--, b[i]--;
            if(a[i] == b[i]) {
                N--;
                f[a[i]]++;
                i--;
            }
        }

        int ans = count();
        cout << ans-1 << "\n";
    }
}
