// main.cpp (tests + example usage)
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
    std::cout << "\n=== 25-pair color code reference ===\n";
    std::cout << TelCoColorCoder::formatColorCoding();

    return 0;
}
