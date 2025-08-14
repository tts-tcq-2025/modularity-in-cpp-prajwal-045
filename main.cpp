// File: TelCoColorCoder.h
#pragma once

#include <string>
#include <array>

namespace TelCoColorCoder {

enum class MajorColor { White = 0, Red, Black, Yellow, Violet };
enum class MinorColor { Blue = 0, Orange, Green, Brown, Slate };

constexpr int kMajorColorCount = 5;
constexpr int kMinorColorCount = 5;

extern const std::array<std::string, kMajorColorCount> kMajorColorNames;
extern const std::array<std::string, kMinorColorCount> kMinorColorNames;

class ColorPair {
private:
    MajorColor major_;
    MinorColor minor_;
public:
    ColorPair(MajorColor major, MinorColor minor) noexcept;
    MajorColor major() const noexcept;
    MinorColor minor() const noexcept;
    std::string toString() const;
};

ColorPair getColorFromPairNumber(int pairNumber);
int getPairNumberFromColor(MajorColor major, MinorColor minor);

// Returns a multiline string suitable for printing as a reference manual.
std::string formatColorCoding();

} // namespace TelCoColorCoder


// File: TelCoColorCoder.cpp
#include "TelCoColorCoder.h"

#include <cassert>
#include <sstream>

namespace TelCoColorCoder {

const std::array<std::string, kMajorColorCount> kMajorColorNames = {
    "White", "Red", "Black", "Yellow", "Violet"
};

const std::array<std::string, kMinorColorCount> kMinorColorNames = {
    "Blue", "Orange", "Green", "Brown", "Slate"
};

ColorPair::ColorPair(MajorColor major, MinorColor minor) noexcept
    : major_(major), minor_(minor) {}

MajorColor ColorPair::major() const noexcept { return major_; }
MinorColor ColorPair::minor() const noexcept { return minor_; }

std::string ColorPair::toString() const {
    return kMajorColorNames[static_cast<int>(major_)] + " " +
           kMinorColorNames[static_cast<int>(minor_)];
}

ColorPair getColorFromPairNumber(int pairNumber) {
    assert(pairNumber >= 1 && pairNumber <= kMajorColorCount * kMinorColorCount);
    const int zeroBased = pairNumber - 1;
    MajorColor major = static_cast<MajorColor>(zeroBased / kMinorColorCount);
    MinorColor minor = static_cast<MinorColor>(zeroBased % kMinorColorCount);
    return ColorPair(major, minor);
}

int getPairNumberFromColor(MajorColor major, MinorColor minor) {
    return static_cast<int>(major) * kMinorColorCount + static_cast<int>(minor) + 1;
}

std::string formatColorCoding() {
    std::ostringstream oss;
    oss << "Pair	Major	Minor
";
    const int total = kMajorColorCount * kMinorColorCount;
    for (int i = 1; i <= total; ++i) {
        ColorPair p = getColorFromPairNumber(i);
        oss << i << "	" << kMajorColorNames[static_cast<int>(p.major())]
            << "	" << kMinorColorNames[static_cast<int>(p.minor())] << "
";
    }
    return oss.str();
}

} // namespace TelCoColorCoder


// File: main.cpp (tests + example usage)
#include <iostream>
#include <cassert>

#include "TelCoColorCoder.h"

using TelCoColorCoder::MajorColor;
using TelCoColorCoder::MinorColor;

void testNumberToPair(int pairNumber,
    MajorColor expectedMajor,
    MinorColor expectedMinor)
{
    TelCoColorCoder::ColorPair colorPair =
        TelCoColorCoder::getColorFromPairNumber(pairNumber);
    std::cout << "Got pair " << colorPair.toString() << std::endl;
    assert(colorPair.major() == expectedMajor);
    assert(colorPair.minor() == expectedMinor);
}

void testPairToNumber(
    MajorColor major,
    MinorColor minor,
    int expectedPairNumber)
{
    int pairNumber = TelCoColorCoder::getPairNumberFromColor(major, minor);
    std::cout << "Got pair number " << pairNumber << std::endl;
    assert(pairNumber == expectedPairNumber);
}

int main() {
    // Unit tests (same expectations as original single-file version)
    testNumberToPair(4, MajorColor::White, MinorColor::Brown);
    testNumberToPair(5, MajorColor::White, MinorColor::Slate);

    testPairToNumber(MajorColor::Black, MinorColor::Orange, 12);
    testPairToNumber(MajorColor::Violet, MinorColor::Slate, 25);

    // New feature: print reference manual
    std::cout << "
=== 25-pair color code reference ===
";
    std::cout << TelCoColorCoder::formatColorCoding();

    return 0;
}
