// TelCoColorCoder.cpp
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
    oss << "Pair\tMajor\tMinor\n";
    const int total = kMajorColorCount * kMinorColorCount;
    for (int i = 1; i <= total; ++i) {
        ColorPair p = getColorFromPairNumber(i);
        oss << i << "\t" << kMajorColorNames[static_cast<int>(p.major())]
            << "\t" << kMinorColorNames[static_cast<int>(p.minor())] << "\n";
    }
    return oss.str();
}

} // namespace TelCoColorCoder
