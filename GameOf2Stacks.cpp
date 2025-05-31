int twoStacks(int maxSum, vector<int> a, vector<int> b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<long long> prefixA(n + 1, 0), prefixB(m + 1, 0);

    for (int i = 0; i < n; i++) prefixA[i + 1] = prefixA[i] + a[i];
    for (int i = 0; i < m; i++) prefixB[i + 1] = prefixB[i] + b[i];

    int maxCount = 0;
    int j = m;

    // Try taking elements from a, then from b
    for (int i = 0; i <= n; i++) {
        if (prefixA[i] > maxSum) break;
        while (j > 0 && prefixA[i] + prefixB[j] > maxSum) {
            j--;
        }
        if (j >= 0)
            maxCount = max(maxCount, i + j);
    }

    // Try taking elements from b, then from a
    j = n;
    for (int i = 0; i <= m; i++) {
        if (prefixB[i] > maxSum) break;
        while (j > 0 && prefixB[i] + prefixA[j] > maxSum) {
            j--;
        }
        if (j >= 0)
            maxCount = max(maxCount, i + j);
    }

    return maxCount;
}