#ifndef TELCO_COLOR_CODER_H_
#define TELCO_COLOR_CODER_H_

#include <functional>
#include <string>

namespace TelCoColorCoder {
enum class MajorColor : int { White = 0, Red, Black, Yellow, Violet };
enum class MinorColor : int { Blue = 0, Orange, Green, Brown, Slate };

constexpr int kMajorColorCount = 5;
constexpr int kMinorColorCount = 5;
constexpr int kTotalPairCount = kMajorColorCount * kMinorColorCount;

class ColorPair {
public:
    constexpr ColorPair(MajorColor maj, MinorColor min) noexcept
        : major_{maj}, minor_{min} {}
    constexpr MajorColor major() const noexcept { return major_; }
    constexpr MinorColor minor() const noexcept { return minor_; }
    std::string toString() const;

private:
    MajorColor major_;
    MinorColor minor_;
};

ColorPair getColorFromPairNumber(int pairNumber); // throws std::out_of_range if invalid
int getPairNumberFromColor(MajorColor major, MinorColor minor) noexcept;

void forEachPair(const std::function<void(int, MajorColor, MinorColor)>& callback) noexcept;
std::string formatColorCoding();            // returns a multi-line printable string
void printColorCoding(std::ostream& out);   // stream directly to an ostream
std::string majorToString(MajorColor m);
std::string minorToString(MinorColor m);

}

#endif // TELCO_COLOR_CODER_H_
