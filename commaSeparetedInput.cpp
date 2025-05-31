#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string input;
    cout << "Enter comma separated integers: ";
    getline(cin, input);

    vector<int> numbers;
    stringstream ss(input);
    string token;

    while (getline(ss, token, ',')) {
        // Optional: remove spaces around the token
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start != string::npos && end != string::npos)
            token = token.substr(start, end - start + 1);

        numbers.push_back(stoi(token));
    }

    // Print the vector
    cout << "You entered:\n";
    for (int num : numbers)
        cout << num << " ";
    cout << "\n";

    return 0;
}
