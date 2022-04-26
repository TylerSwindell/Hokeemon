#pragma once

#include <iostream>

/******************************************************************************
 * Date Class 
******************************************************************************/
// Specification B1 - Date class
class Date {
    private:
        int month = 0, day = 0, year = 0000;
        int dateInts[3] = {month, day, year};
        std::string dateArr[5];

        static const std::string    
            BOLD_WHITE_TEXT,
            BOLD_RED_TEXT,
            TEXT_RESET,
            BRT, BWT, RTF, 
            PASSED,
            FAILED;

        void passedTest();
        void failedTest();

    public:
        Date();
        Date(int m, int d, int y);
        void setDate(int, int, int);
        int* getDate();
        void setDefaultDateTime();
        short convertMonth(std::string month);
        std::string getDateString();
        void printDate();

        // Specification B2 - ComponentTest
        void componentUnitTest();
        void testComponent(std::string, std::string);
};