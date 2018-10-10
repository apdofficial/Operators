#include <iostream>
#include <iomanip>
#include <sstream>
#include "Date_time.h"

int main() {
    std::chrono::seconds interval {20}, interval2 {10}, interval3 {200};
    auto year{2015}, month{1}, day{22};
    try {
        SAX::Date_time date_time;
        SAX::Date_time date_time_ownDate (year,month, day);

        std::cout << "\n""---Default constructor----" << "\n";
        std::cout << date_time.str() << "\n\n";

        std::cout << "---Year,month,day taken as argument (2015 Feb 2) by constructor----" << "\n";
        std::cout << date_time_ownDate.str() << "\n\n";

        std::cout << "---Date & time provided as a string using own formatting '%d-%b-%Y %H:%M:%S'----" << "\n";
        std::cout << date_time_ownDate.str("%d-%b-%Y %H:%M:%S") << "\n\n";

        std::cout << "---Date & time (2011-February-18 23:12:34) provided as a string----" << "\n";
        date_time.parse("2011-Feb-18 23:12:34");
        std::cout << date_time.str() << "\n\n";

        std::cout << "---Date & time (18-Jan-2011 11:11:11) provided as a string using own formatting(%Y-%b-%d %H:%M:%S)----" << "\n";
        date_time.parse("2222-Oct-22 02:15:35","%Y-%b-%d %H:%M:%S");
        std::cout << date_time.str() << "\n\n";

        std::cout << "---Year has been changed to ""1999""----" << "\n";
        date_time.setYear(1999);
        std::cout << date_time.str() << "\n\n";

        std::cout << "---Day has been changed to ""22""----" << "\n";
        date_time.setDay(22);
        std::cout << date_time.str() << "\n\n";

        std::cout << "---Asked to get year ----" << "\n";
        std::cout << date_time.getYear() << "\n\n";

        std::cout << "---Asked to get minute ----" << "\n";
        std::cout << date_time.getMinute() << "\n\n";

        std::cout << "---advanced by ""20"" seconds ----" << "\n";
        date_time.advance(interval);
        std::cout << date_time.str() << "\n\n";

        std::cout << "---stepped_back by ""10"" seconds----" << "\n";
        date_time.step_back(interval2);
        std::cout << date_time.str() << "\n\n";

//        /*wrong input*/
//        std::cout << "---Year has been changed to ""3010""----" << "\n";
//        date_time.setYear(3010);
//        std::cout << date_time.str() << "\n\n";
//
//        /*wrong input*/
//        std::cout << "---Month has been changed to ""13""----" << "\n";
//        date_time.setMonth(13);
//        std::cout << date_time.str() << "\n\n";
//
//        /*wrong input*/
//        std::cout << "---Day has been changed to ""-1""----" << "\n";
//        date_time.setDay(-1);
//        std::cout << date_time.str() << "\n\n";
//
//        /*wrong input*/
//        std::cout << "---advanced by ""200"" seconds ----" << "\n";
//        date_time.advance(interval3);
//        std::cout << date_time.str() << "\n\n";
    }
    catch(const char * str){
        std::cout<<"Exception: "<<str<<"\n";
    }
    return 0;
}
