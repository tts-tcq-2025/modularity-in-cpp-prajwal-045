// main.cpp - simple smoke test
#include <iostream>
#include "TelCoColorCoder.h"

int main() {
    try {
        std::cout << TelCoColorCoder::formatColorCoding();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
