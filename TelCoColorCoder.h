// TelCoColorCoder.h
// Split header for 25-pair telco color coding utilities.
// Provides conversion between pair number <-> (major, minor) colors
// and functions to produce a printable reference manual.

#ifndef TELCO_COLOR_CODER_H_
#define TELCO_COLOR_CODER_H_

#include <array>
#include <cstddef>
#include <iosfwd>
#include <string>

namespace TelCoColorCoder {

// Enumerations are scoped to avoid polluting the global namespace.
enum class MajorColor : int { White = 0, Red, Black, Yellow, Violet };
enum class MinorColor : int { Blue = 0, Orange, Green, Brown, Slate };

// Count constants for compile-time usage.
constexpr std::size_t kMajorColorCount = 5u;
constexpr std::size_t kMinorColorCount = 5u;
constexpr std::size_t kTotalPairCount = kMajorColorCount * kMinorColorCount;

// Name tables (defined in the .cpp file).
extern const std::array<std::string, kMajorColorCount> kMajorColorNames;
extern const std::array<std::string, kMinorColorCount> kMinorColorNames;

// Represents a pair of (major, minor) colors.
class ColorPair {
public:
    ColorPair(MajorColor major, MinorColor minor) noexcept;

    MajorColor major() const noexcept;
    MinorColor minor() const noexcept;

    // Produce a human-readable "Major Minor" string, e.g. "White Brown".
    std::string toString() const;

private:
    MajorColor major_;
    MinorColor minor_;
};

// Convert a 1-based pair number (1..25) into a ColorPair.
// Throws std::out_of_range if pairNumber is outside [1, kTotalPairCount].
ColorPair getColorFromPairNumber(int pairNumber);

// Convert a ColorPair (major, minor) into the 1-based pair number (1..25).
int getPairNumberFromColor(MajorColor major, MinorColor minor);

// Return a multi-line string suitable for printing as a reference/manual.
// Each line maps: PairNumber <tab> Major <tab> Minor
std::string formatColorCoding();

// Write the formatted color coding to the supplied output stream.
// This avoids extra copies if the caller wants to stream directly to a file.
void printColorCoding(std::ostream& out);

} // namespace TelCoColorCoder

#endif // TELCO_COLOR_CODER_H_
