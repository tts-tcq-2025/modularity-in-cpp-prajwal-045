#include "TelCoColorCoder.h"
#include <array>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>
namespace TelCoColorCoder {
static const std::array<const char*, kMajorColorCount> kMajorNames = {
    "White", "Red", "Black", "Yellow", "Violet"
};
static const std::array<const char*, kMinorColorCount> kMinorNames = {
    "Blue", "Orange", "Green", "Brown", "Slate"
};

std::string majorToString(MajorColor m) {
    const int idx = static_cast<int>(m);
    return std::string(kMajorNames[idx]);
}
std::string minorToString(MinorColor m) {
    const int idx = static_cast<int>(m);
    return std::string(kMinorNames[idx]);
}

std::string ColorPair::toString() const {
    return majorToString(major_) + " " + minorToString(minor_);
}

ColorPair getColorFromPairNumber(int pairNumber) {
    if (pairNumber < 1 || pairNumber > kTotalPairCount)
        throw std::out_of_range("pairNumber must be in range 1..25");
    const int zero = pairNumber - 1;
    const MajorColor maj = static_cast<MajorColor>(zero / kMinorColorCount);
    const MinorColor min = static_cast<MinorColor>(zero % kMinorColorCount);
    return ColorPair(maj, min);
}

int getPairNumberFromColor(MajorColor major, MinorColor minor) noexcept {
    return static_cast<int>(major) * kMinorColorCount + static_cast<int>(minor) + 1;
}

void forEachPair(const std::function<void(int, MajorColor, MinorColor)>& cb) noexcept {
    int pairNum = 1;
    for (int m = 0; m < kMajorColorCount; ++m) {
        for (int n = 0; n < kMinorColorCount; ++n) {
            cb(pairNum, static_cast<MajorColor>(m), static_cast<MinorColor>(n));
            ++pairNum;
        }
    }
}
std::string formatColorCoding() {
    std::ostringstream oss;
    oss << std::left << std::setw(6) << "Pair" << std::setw(12) << "Major" << std::setw(12) << "Minor" << '\n';
    forEachPair([&oss](int pair, MajorColor maj, MinorColor min) {
        oss << std::left << std::setw(6) << pair
            << std::setw(12) << kMajorNames[static_cast<int>(maj)]
            << std::setw(12) << kMinorNames[static_cast<int>(min)]
            << '\n';
    });
    return oss.str();
}
void printColorCoding(std::ostream& out) {
    out << formatColorCoding();
}
}
