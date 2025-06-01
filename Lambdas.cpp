#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <sstream>
using namespace std;

int leastIntervals(const vector<char>& tasks, int n) {
    unordered_map<char, int> freq;
    for (char task : tasks) {
        freq[task]++;
    }

    priority_queue<int> maxHeap;
    for (auto& p : freq) {
        maxHeap.push(p.second);
    }

    int time = 0;

    while (!maxHeap.empty()) {
        int cycle = n + 1;
        vector<int> temp;

        for (int i = 0; i < cycle; ++i) {
            if (!maxHeap.empty()) {
                int current = maxHeap.top();
                maxHeap.pop();
                if (current > 1) {
                    temp.push_back(current - 1);
                }
            }
            time++;

            if (maxHeap.empty() && temp.empty()) {
                break;
            }
        }

        for (int count : temp) {
            maxHeap.push(count);
        }
    }

    return time;
}

// Helper function to parse input like: ["A","A","B","B"]
vector<char> parseInput(const string& s) {
    vector<char> result;
    for (size_t i = 0; i < s.size(); ++i) {
        if (isalpha(s[i])) {
            result.push_back(s[i]);
        }
    }
    return result;
}

int main() {
    string input;
    getline(cin, input);

    vector<char> rounds = parseInput(input);

    int n;
    cin >> n;

    int result = leastIntervals(rounds, n);
    cout << result << endl;

    return 0;
}
