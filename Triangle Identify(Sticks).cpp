//Acute, Right, Obtuse Triangle Identification C++ Mini O(n2logn)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n; 
    cin >> n;
    vector<int> sticks(n);
    for (int i = 0; i < n; i++) cin >> sticks[i];

    sort(sticks.begin(), sticks.end());

    vector<long long> sq(n);
    for (int i = 0; i < n; i++) sq[i] = 1LL * sticks[i] * sticks[i];

    int acute = 0, right = 0, obtuse = 0;

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            long long sum_squares = sq[i] + sq[j];
            int left = j + 1, right_idx = n - 1;

            // Find max k with sticks[i] + sticks[j] > sticks[k]
            // triangle inequality binary search
            int valid_max = j;
            while (left <= right_idx) {
                int mid = (left + right_idx) / 2;
                if ((long long)sticks[i] + sticks[j] > sticks[mid]) {
                    valid_max = mid;
                    left = mid + 1;
                } else {
                    right_idx = mid - 1;
                }
            }
            if (valid_max == j) continue; // no valid c

            // Binary search for right triangle c^2 == sum_squares
            int low = j + 1, high = valid_max, right_pos = -1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (sq[mid] == sum_squares) {
                    right_pos = mid;
                    break;
                } else if (sq[mid] < sum_squares) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            if (right_pos != -1) right++;

            // Binary search for obtuse triangles: find first c where c^2 > sum_squares
            low = j + 1; high = valid_max;
            int obtuse_start = valid_max + 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (sq[mid] > sum_squares) {
                    obtuse_start = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            int obtuse_count = max(0, valid_max - obtuse_start + 1);
            obtuse += obtuse_count;

            // Acute count = total valid - right - obtuse
            int total_valid = valid_max - (j + 1) + 1;
            int acute_count = total_valid - (right_pos != -1 ? 1 : 0) - obtuse_count;
            if (acute_count > 0) acute += acute_count;
        }
    }

    cout << acute << " " << right << " " << obtuse << "\n";

    return 0;
}