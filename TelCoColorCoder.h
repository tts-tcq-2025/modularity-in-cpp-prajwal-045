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
