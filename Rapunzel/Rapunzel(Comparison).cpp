//Binary Search For COmparison (Rapunzel)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t; cin >> t;

    while (t-- > 0) {
        int n; cin >> n;
        vector<int> soldiers(n);
        for (int i = 0; i < n; i++) {
            cin >> soldiers[i];
        }

        // Create a sorted copy for searching
        vector<int> sortedSoldiers = soldiers;
        sort(sortedSoldiers.begin(), sortedSoldiers.end());

        for (int i = 0; i < n; i++) {
            int val = soldiers[i];
            int target = val * 2;

            // Binary search to find upper bound <= target
            // upper_bound returns iterator to first element > target,
            // so we decrement it to get <= target
            auto it = upper_bound(sortedSoldiers.begin(), sortedSoldiers.end(), target);
            if (it == sortedSoldiers.begin()) {
                // No element <= target
                cout << -1 << " ";
                continue;
            }
            it--;

            // If this element equals val itself, need to exclude it:
            if (*it == val) {
                // Move iterator one step back if possible
                if (it != sortedSoldiers.begin()) {
                    it--;
                    cout << *it << " ";
                } else {
                    cout << -1 << " ";
                }
            } else {
                cout << *it << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}