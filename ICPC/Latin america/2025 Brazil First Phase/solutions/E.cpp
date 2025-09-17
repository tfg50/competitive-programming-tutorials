#include <bits/stdc++.h>

std::vector<std::pair<int, int>> bfs(const std::vector<std::vector<int>> &edges, int root) {
    int n = (int) edges.size();
    std::vector<std::pair<int, int>> dist(n, {-1, -1}); // {distance, number of minimum paths taking min with 2}
    dist[root] = {0, 1};
    std::queue<int> q;
    q.push(root);
    while(!q.empty()) {
        int on = q.front();
        q.pop();
        for(auto to : edges[on]) {
            if(dist[to].first == -1) {
                dist[to] = {dist[on].first + 1, dist[on].second};
                q.push(to);
            } else if(dist[to].first == dist[on].first + 1) {
                dist[to].second = 2;
            }
        }
    }
    return dist;
}

std::vector<std::vector<int>> gen(std::vector<std::vector<int>> &edges, int m) {
    auto ans = edges;
    m++;
    for(int i = 0; i < (int) edges.size(); i++) {
        for(int j = 0; j < (int) edges[i].size(); j++) {
            for(int k = 0; k < j; k++) {
                int u = edges[i][j], v = edges[i][k];
                m--;
                ans[u].push_back(v);
                ans[v].push_back(u);
                if(m < 0) {
                    return ans;
                }
            }
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> edges(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int toAll = 0;
    for(int i = 0; i < n; i++) {
        if((int) edges[i].size() + 1 == n) {
            toAll++;
        }
    }
    if(toAll == n) {
        // diameter is 3
        for(int i = 2; i <= n; i++) {
            std::cout << "1 " << i << '\n';
        }
        return 0;
    }
    if(toAll == 2) {
        // diameter is 4
        std::vector<int> centers;
        std::map<std::vector<int>, std::vector<int>> mp;
        for(int i = 0; i < n; i++) {
            edges[i].push_back(i);
            std::sort(edges[i].begin(), edges[i].end());
            if((int) edges[i].size() == n) {
                centers.push_back(i);
            } else {
                mp[edges[i]].push_back(i);
            }
        }
        if((int) mp.size() != 2 || (int) centers.size() != 2) {
            std::cout << "*\n";
            return 0;
        }
        std::cout << centers[0]+1 << ' ' << centers[1]+1 << '\n';
        int cnt = 0;
        for(auto [adj, ids] : mp) {
            for(auto i : ids) {
                std::cout << i+1 << ' ' << centers[cnt]+1 << '\n';
            }
            cnt++;
        }
        return 0;
    }
    // now the tree has diameter of size at least 5 vertices
    int u = 0;
    while(u < n && (int) edges[u].size() + 1 == n) u++;
    {
        auto dists = bfs(edges, u);
        std::pair<int, int> best(-1, -1);
        for(int i = 0; i < n; i++) {
            if(dists[i].first >= 2) {
                best = std::max(best, std::pair<int, int>(dists[i].first * 2 - (dists[i].second == 1 ? 0 : 1), i));
            }
        }
        if(best.first == -1) {
            std::cout << "*\n";
            return 0;
        }
        u = best.second;
    }
    int v;
    {
        auto dists = bfs(edges, u);
        std::pair<int, int> best(-1, -1);
        for(int i = 0; i < n; i++) {
            if(dists[i].first >= 2) {
                best = std::max(best, std::pair<int, int>(dists[i].first * 2 - (dists[i].second == 1 ? 0 : 1), i));
            }
        }
        if(best.first == -1) {
            std::cout << "*\n";
            return 0;
        }
        v = best.second;
    }
    auto dists1 = bfs(edges, u), dists2 = bfs(edges, v);
    std::vector<int> col(n, -1);
    col[u] = 0;
    col[v] = dists1[v].second == 1 ? 0 : 1;
    for(int i = 0; i < n; i++) if(col[i] == -1) {
        col[i] = dists1[i].first >= 2 ? (dists1[i].second == 1 ? 0 : 1) : (dists2[i].second == 1 ? col[v] : (1^col[v])); // luckily this works for the center of a tree with diameter 5
    }
    int ed = 0;
    std::vector<std::vector<int>> ans(n);
    for(int i = 0; i < n; i++) if(col[i] == 0) {
        for(auto j : edges[i]) if(col[j] == 1) {
            ed++;
            ans[i].push_back(j);
            ans[j].push_back(i);
        }
    }
    if(ed != n-1) {
        std::cout << "*\n";
        return 0;
    }
    auto other = gen(ans, m);
    for(int i = 0; i < n; i++) {
        std::sort(edges[i].begin(), edges[i].end());
        std::sort(other[i].begin(), other[i].end());
        if(edges[i] != other[i]) {
            std::cout << "*\n";
            return 0;
        }
    }
    for(int i = 0; i < n; i++) if(col[i] == 0) {
        for(auto j : edges[i]) if(col[j] == 1) {
            std::cout << i+1 << ' ' << j+1 << '\n';
        }
    }
}
