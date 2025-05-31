#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */

#include <bits/stdc++.h>
using namespace std;

//Calculating the minimum number of operations needed
int cookies(int k, vector<int> A) {
    // Min-Heap to keep the smallest elements at the top
    priority_queue<int, vector<int>, greater<int>> minHeap(A.begin(), A.end());
    
    int operations = 0;

    // Keep mixing the two least sweet cookies until all are at least k
    while (minHeap.size() > 1 && minHeap.top() < k) {
        int leastSweet = minHeap.top(); 
        minHeap.pop(); // Removing the least sweet cookie

        int secondLeastSweet = minHeap.top();
        minHeap.pop(); // Removing the second least sweet cookie

        int newCookie = leastSweet + 2 * secondLeastSweet; // Mix them
        minHeap.push(newCookie); // Adding new cookie to heap

        operations++; // Count the operation
    }

    // If the smallest remaining cookie is still less than k, return -1
    return (minHeap.top() >= k) ? operations : -1;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string A_temp_temp;
    getline(cin, A_temp_temp);

    vector<string> A_temp = split(rtrim(A_temp_temp));

    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        int A_item = stoi(A_temp[i]);

        A[i] = A_item;
    }

    int result = cookies(k, A);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
