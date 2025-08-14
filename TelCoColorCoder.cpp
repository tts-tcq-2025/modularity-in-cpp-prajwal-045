// TelCoColorCoder.cpp
// Implementation for TelCoColorCoder.h

#include "TelCoColorCoder.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace TelCoColorCoder {

// Definitions of the color name tables.
const std::array<std::string, kMajorColorCount> kMajorColorNames = {
    "White", "Red", "Black", "Yellow", "Violet"
};

const std::array<std::string, kMinorColorCount> kMinorColorNames = {
    "Blue", "Orange", "Green", "Brown", "Slate"
};

// ColorPair implementation
ColorPair::ColorPair(MajorColor major, MinorColor minor) noexcept
    : major_(major), minor_(minor) {}

MajorColor ColorPair::major() const noexcept { return major_; }
MinorColor ColorPair::minor() const noexcept { return minor_; }

std::string ColorPair::toString() const {
    const std::size_t majorIndex = static_cast<std::size_t>(major_);
    const std::size_t minorIndex = static_cast<std::size_t>(minor_);
    return kMajorColorNames[majorIndex] + " " + kMinorColorNames[minorIndex];
}

// Convert pair number (1..25) -> ColorPair
ColorPair getColorFromPairNumber(int pairNumber) {
    const int total = static_cast<int>(kTotalPairCount);
    if (pairNumber < 1 || pairNumber > total) {
        throw std::out_of_range("pairNumber must be in range 1..25");
    }
    const int zeroBased = pairNumber - 1;
    const std::size_t majorIndex = static_cast<std::size_t>(zeroBased / static_cast<int>(kMinorColorCount));
    const std::size_t minorIndex = static_cast<std::size_t>(zeroBased % static_cast<int>(kMinorColorCount));
    return ColorPair(static_cast<MajorColor>(static_cast<int>(majorIndex)),
                     static_cast<MinorColor>(static_cast<int>(minorIndex)));
}

// Convert (major, minor) -> pair number (1..25)
int getPairNumberFromColor(MajorColor major, MinorColor minor) {
    const int majorIndex = static_cast<int>(major);
    const int minorIndex = static_cast<int>(minor);
    return majorIndex * static_cast<int>(kMinorColorCount) + minorIndex + 1;
}

// Produce a nicely aligned multi-line string for printing.
std::string formatColorCoding() {
    std::ostringstream oss;
    // Header
    oss << std::left << std::setw(6) << "Pair" << std::setw(12) << "Major" << std::setw(12) << "Minor" << '\n';
    const int total = static_cast<int>(kTotalPairCount);
    for (int i = 1; i <= total; ++i) {
        ColorPair p = getColorFromPairNumber(i);
        oss << std::left << std::setw(6) << i
            << std::setw(12) << kMajorColorNames[static_cast<std::size_t>(p.major())]
            << std::setw(12) << kMinorColorNames[static_cast<std::size_t>(p.minor())]
            << '\n';
    }
    return oss.str();
}

// Stream directly to output (useful to avoid creating large temporary strings).
void printColorCoding(std::ostream& out) {
    out << formatColorCoding();
}

} // namespace TelCoColorCoder
