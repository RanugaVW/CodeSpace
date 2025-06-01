#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {10, 20, 30, 40, 30, 50};
    int target = 30;

    auto it = std::find(vec.begin(), vec.end(), target);

    if (it != vec.end()) {
        int index = std::distance(vec.begin(), it);
        std::cout << target << " found at index: " << index << std::endl;
    } else {
        std::cout << target << " not found in the vector." << std::endl;
    }

    return 0;
}
