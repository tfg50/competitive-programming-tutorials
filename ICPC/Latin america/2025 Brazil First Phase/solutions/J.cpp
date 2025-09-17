#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    std::set<int> st;
    for(int i = 0; i < 10; i++) {
        int x;
        std::cin >> x;
        st.insert(x);
    }
    std::cout << 4 - (int) st.size() << '\n';
}
