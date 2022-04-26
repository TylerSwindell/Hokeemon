#pragma once

#include "UnitTest.hpp"

const std::string 
// Foreground Colors
// Bold Text
    UnitTest::B_W = "\033[1;97m",   // Bold White
    UnitTest::B_R = "\033[1;31m",   // Bold Red
    UnitTest::B_G = "\033[1;32m",   // Bold Green
    UnitTest::B_BL = "\033[1;30m",  // Bold Black
    UnitTest::B_BG = "\033[1;92m",  // Bold Bright Green

// Background Colors
    UnitTest::BG_BL = "\033[0;40m", // Black BG
    UnitTest::BG_R = "\033[0;41m",  // Red BG
    UnitTest::BG_G = "\033[0;42m",  // Green BG
    UnitTest::BG_BG = "\033[0;102m",// Bright Green BG

// Resets all styling attributes
    UnitTest::R_T = "\033[0m",

// Labels
    UnitTest::TESTING = "Testing:",
    UnitTest::PASSED = "Passed",
    UnitTest::FAILED = "Failed";

UnitTest::UnitTest() { 
    screenSize = 50;
    padding = 1;
    testCount = 0;
    if (!testCount) 
        std::cout << '\n' << B_W << TESTING << R_T << '\n';
}

UnitTest::UnitTest(bool test) { 
    screenSize = 50;
    padding = 1;
    testCount = 0;
    if (!testCount) 
        std::cout << '\n' << B_W << TESTING << R_T << '\n';

    if (test) 
        this->componentUnitTest();
}

void UnitTest::setScreensize(size_t ss) { UnitTest::screenSize = ss; }
size_t UnitTest::getScreensize() { return UnitTest::screenSize; }

void UnitTest::setPadding(size_t p) { padding = p; }
size_t UnitTest::getPadding() { return padding; }

void UnitTest::setTestCount(size_t count) { testCount = count; }
size_t UnitTest::getTestCount() { return testCount; }

/****************************************************************************************
 * const std::string test => value to be tested
 * const std::string expected => expected result
 ***************************************************************************************/
template<typename T>
bool UnitTest::testComponent(const T test, const T expected, std::string testDesc) {
    testCount++;

    int perimeterPadding = (this->padding * 2) + 2;

    bool result = (test == expected);
    std::string status = result ? PASSED : FAILED;
    std::string INPUT = "\nInput:";
    std::string OUTPUT = "Output:";

    // Text Lengths for each line of output
    size_t lineOneTextLen = status.length() + TESTING.length();

    // Sets status color
    std::string statusTextColor = result ?  B_BG : B_R;
    std::string statusBGColor = result ?  BG_BG : BG_R;

    // Length of all o
    int loadingLength = this->screenSize - perimeterPadding - lineOneTextLen;

    std::cout << B_W << "Test #" << std::to_string(testCount) << statusTextColor << borderChar;
    for (size_t i = 0; i < this->padding; i++) 
        std::cout << R_T << loadingChar;

    std::cout << statusBGColor;
    for (int i = 0; i < loadingLength; i++)
         std::cout << loadingChar;

    for (size_t i = 0; i < this->padding; i++) 
        std::cout << R_T << loadingChar;

    std::cout 
        << statusTextColor << borderChar << status
        << INPUT << loadingChar << expected << '\040' << borderChar << '\040'
        << OUTPUT << loadingChar << test << B_W << '\n';
        
        // Checks if testDesc is longer than the screen size
        if (testDesc.length() > screenSize) {

            // Keeps tracks of which char is being printed next
            for (size_t i = 0; i < testDesc.length()+1; i++) {
                
                // Keeps track of where the current position on the screen is
                for (size_t j = 1; j < screenSize; j++) std::cout << testDesc[i++];
                
                // New line after the screensize width is met
                std::cout << '\n';

                // Checks if the first char of the next line is 
                // a blank char if so moves to next char to avoid
                // blank chars in the first space of each line
                if (testDesc[i+1] == '\040') i++;
            
            }
            std::cout << std::endl;
        // if the length of the description is less than one line the testDesc is printed in full
        } else std::cout << testDesc << '\n';

    for (size_t i = 1; i < screenSize; i++) std::cout << ('-'); 
    std::cout << R_T << std::endl;
        
    return result;
}

// Testing Entry Point
void UnitTest::componentUnitTest() { 
    
    std::string testValueStr;
    int testValueNum;

    testValueStr = "tyler";
    testComponent<std::string>(testValueStr, "tyler");

    char testValueChar = 'c';
    testComponent<char>(testValueChar, 'c');

    testValueNum = 50;
    testComponent<size_t>(getScreensize(), testValueNum);

    testValueStr = "50";
    testComponent<std::string>(std::to_string(getScreensize()), testValueStr);

}