#include <bits/stdc++.h>

int dot(std::pair<int, int> v1, std::pair<int, int> v2) { return v1.first * v2.first + v1.second * v2.second; }
std::pair<int, int> add(std::pair<int, int> v1, std::pair<int, int> v2) { return {v1.first + v2.first, v1.second + v2.second}; }

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a(n);
    std::vector<std::string> strs(n);
    std::map<std::string, int> id;
    for(int i = 0; i < n; i++) {
        std::cin >> strs[i] >> a[i].first >> a[i].second;
        id[strs[i]] = i;
    }
    int m;
    std::cin >> m;
    std::map<std::vector<std::string>, std::pair<int, int>> info;
    {
        std::vector<std::string> txt(m);
        for(int i = 0; i < m; i++) {
            std::cin >> txt[i];
        }
        for(int i = 0; i < m; i++) {
            std::vector<std::string> cur;
            for(int j = i+1; j-i <= 5 && j < m; j++) {
                cur.push_back(txt[j-1]);
                info[cur] = add(info[cur], a[id[txt[j]]]);
            }
        }
    }
    int q, k;
    std::cin >> q >> k;
    while(q--) {
        std::cin >> m;
        std::vector<std::string> txt(m);
        for(int i = 0; i < m; i++) {
            std::cin >> txt[i];
        }
        std::string token = "*";
        for(int i = std::min(m, k); i >= 1; i--) {
            std::vector<std::string> cur(txt.end() - i, txt.end());
            if(info.count(cur) == 0) continue;
            auto vec = info[cur];
            std::pair<int, int> best(-1e9, -1e9);
            for(int j = 0; j < n; j++) {
                best = std::max(best, {dot(a[j], vec), -j});
            }
            token = strs[-best.second];
            break;
        }
        for(int i = 0; i < m; i++) {
            std::cout << txt[i] << ' ';
        }
        std::cout << token << '\n';
    }
}
