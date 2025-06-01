#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int G, n;
    cin >> G >> n;

    vector<int> g(n), x(n), y(n), z(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i] >> x[i] >> y[i] >> z[i];
    }

    vector<int> dp(G + 1, 0);

    // For each stuffing type
    for (int i = 0; i < n; i++) {
        vector<int> newDp = dp;

        int maxBunsByStuffing = g[i] / x[i];
        int maxBunsByFlour = G / y[i];
        int maxBuns = min(maxBunsByStuffing, maxBunsByFlour);

        for (int buns = 1; buns <= maxBuns; buns++) {
            int totalFlour = buns * y[i];
            int totalProfit = buns * z[i];

            // classic knapsack update (go backward to avoid reuse in same iteration)
            for (int flourUsed = G - totalFlour; flourUsed >= 0; flourUsed--) {
                if (dp[flourUsed] + totalProfit > newDp[flourUsed + totalFlour]) {
                    newDp[flourUsed + totalFlour] = dp[flourUsed] + totalProfit;
                }
            }
        }

        dp = move(newDp);
    }

    cout << *max_element(dp.begin(), dp.end()) << "\n";

    return 0;
}
