#include <bits/stdc++.h>

long long modinverse(long long a, long long b, long long s0 = 1, long long s1 = 0) { return b == 0 ? s0 : modinverse(b, a % b, s1, s0 - s1 * (a / b)); }
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long mul(long long a, long long b, long long m) {
    long long q = (long double) a * (long double) b / (long double) m;
    long long r = a * b - q * m;
    return (r + m) % m;
}

struct Equation {
    Equation(long long a, long long m) { mod = m, ans = (a % m + m) % m, valid = true; }
    Equation() { valid = false; }
    Equation(Equation a, Equation b) {
        if(!a.valid || !b.valid) {
            valid = false;
            return;
        }
        long long g = gcd(a.mod, b.mod);
        if((a.ans - b.ans) % g != 0) {
            valid = false;
            return;
        }
        valid = true;
        mod = a.mod * (b.mod / g);
        ans = a.ans +
              mul(
                    mul(a.mod, modinverse(a.mod, b.mod), mod),
                    (b.ans - a.ans) / g
              , mod);
        ans = (ans % mod + mod) % mod;
    }
    long long mod, ans;
    bool valid;
};

// credits to FMota/UFCG

template <class T>
struct ZFunc {
    std::vector<int> z;
    ZFunc(const T &v) : z(v.size()) {
        int n = (int) v.size(), a = 0, b = 0;
        if (!z.empty()) z[0] = n;
        for (int i = 1; i < n; i++) {
            int end = i; if (i < b) end = std::min(i + z[i - a], b);
            while(end < n && v[end] == v[end - i]) ++end;
            z[i] = end - i; if(end > b) a = i, b = end;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n), p(n);
    for(int i = 0; i < n; i++) std::cin >> a[i];
    for(int i = 0; i < n; i++) std::cin >> b[i];
    for(int i = 0; i < n; i++) std::cin >> p[i];
    for(int i = 0; i < n; i++) p[i]--;
    std::vector<int> v(n+1, -1);
    for(int i = 0; i < n; i++) if(p[i] != -1) {
        std::vector<int> cyc;
        for(int j = i; p[j] != -1; ) {
            int nxt = p[j];
            p[j] = -1;
            cyc.push_back(j);
            j = nxt;
        }
        std::vector<int> vec;
        for(auto pos : cyc) vec.push_back(a[pos]);
        vec.push_back(-1);
        for(auto pos : cyc) vec.push_back(b[pos]);
        for(auto pos : cyc) vec.push_back(b[pos]);
        ZFunc z(vec);
        std::vector<int> good;
        for(int j = 0; j < (int) cyc.size(); j++) {
            if(z.z[(int) cyc.size() + 1 + j] >= (int) cyc.size()) {
                good.push_back(j);
            }
        }
        if(good.empty()) {
            std::cout << "IMPOSSIVEL\n";
            return 0;
        }
        int first = good[0];
        int m = (int) cyc.size() / (int) good.size();
        for(int j = 1; j <= m; j++) if(m % j == 0) {
            if(v[j] == -1) {
                v[j] = first % j;
            } else if(first % j != v[j]) {
                std::cout << "IMPOSSIVEL\n";
                return 0;
            }
        }
    }
    Equation eq(0, 1);
    for(int i = 1; i <= n; i++) if(v[i] != -1) {
        if(eq.mod >= (int) 2e9) {
            if(eq.ans % i != v[i]) {
                std::cout << "DEMAIS\n";
                return 0;
            }
        } else {
            eq = Equation(eq, Equation(v[i], i));
        }
    }
    if(eq.ans > (int) 1e9) {
        std::cout << "DEMAIS\n";
    } else {
        std::cout << eq.ans << '\n';
    }
}
