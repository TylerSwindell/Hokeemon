#pragma once

#include "./Date.hpp"

const std::string 
    Date::BOLD_WHITE_TEXT = "\033[1;97m",
    Date::BOLD_RED_TEXT = "\033[1;31m",
    Date::TEXT_RESET = "\033[0m",
    Date::BWT = BOLD_WHITE_TEXT,
    Date::BRT = BOLD_RED_TEXT,
    Date::RTF = TEXT_RESET,
    Date::PASSED = BWT + "Passed\n",
    Date::FAILED = BRT + "Failed\n";



Date::Date() { 
    setDefaultDateTime();
    month = convertMonth(dateArr[1]);
    day = stoi(dateArr[2]);
    year = stoi(dateArr[4]);
}

Date::Date(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
}

void Date::setDate(int m, int d, int y) { month = m; day = d; year = y; }
int* Date::getDate() { return dateInts; }

void Date::setDefaultDateTime() { 
    // Stores current time (in seconds) since Jan 1, 1970
    std::time_t seconds = std::time(nullptr);
    // Converts the seconds to a readable format
    std::string formattedTime = std::ctime(&seconds);

    short count = 0; 
    char iterator = '\040'; 
    char nullTerm = '\0';
    
    std::string tempStr = "";

    // Splits formattedTime string into array of strings
    for (uint i = 0; i < formattedTime.length()+1; i++) {
        char c = formattedTime[i];
        if (c == iterator || c == nullTerm) {
            // Adds each piece of the split string to the arr
            dateArr[count++] = tempStr;
            tempStr = "";
        } else tempStr += c;
    }

    // Gets last two digits off the year
    std::string year = "";
    year += dateArr[4][2];
    year += dateArr[4][3];
    dateArr[4] = year;
}

short Date::convertMonth(std::string m) {
    short date = 0;
    for (short i = 0; i < short(m.length()); i++)
        date += short(m.at(i));

    short month = 0;
    switch (date) {
        // Numerical Value of each month's chars
        case 281: month = 1; break;     // Jan
        case 269: month = 2; break;     // Feb 
        case 288: month = 3; break;     // Mar
        case 291: month = 4; break;     // Apr
        case 295: month = 5; break;     // May
        case 301: month = 6; break;     // Jun
        case 299: month = 7; break;     // Jul
        case 285: month = 8; break;     // Aug
        case 296: month = 9; break;     // Sep
        case 294: month = 10; break;    // Oct
        case 307: month = 11; break;    // Nov  
        case 268: month = 12; break;    // Dec
        default:
        break;
    }
    if (month < 1) 
        std::cout << BRT <<"Invalid Month Entered" << std::endl;

    return month;
}

std::string Date::getDateString() {
    std::string m = std::to_string(month);
    std::string d = std::to_string(day);
    std::string y = std::to_string(year);
    
    return ( m + '/' + d + '/' + y );
}

void Date::printDate() {
    std::cout << getDateString();
}

void Date::componentUnitTest() {
    Date test;
    test.setDate(3, 31, 1994);
    (test.getDateString() == "3/31/1994") 
        ? std::cout << PASSED : std::cout << FAILED;
}

void Date::passedTest() { std::cout << PASSED + RTF; }
void Date::failedTest() { std::cout << FAILED + RTF; }
void Date::testComponent(std::string condition, std::string expectedResult) {
    (condition == expectedResult) ? passedTest() : failedTest(); 
}
