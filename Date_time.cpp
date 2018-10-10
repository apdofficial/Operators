#include "Date_time.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <sstream>

namespace SAX {

    //default constructor constructs class with actual date & time
    Date_time::Date_time() {
        auto date_time = std::chrono::system_clock::now(); //current date & time
        std::time_t c_date_time = std::chrono::system_clock::to_time_t(date_time); //convert to time_t
        m_date_time = *std::localtime(&c_date_time); //convert to local calendar representation
    };

    // this is constructor that takes year, month and day and assigns 0 to every other member
    Date_time::Date_time(const int& year,const int& month,const int& day) {
        if(year > 3000 || year < 1900) throw "Setting years failed. [Outside of the boundaries 1900<year<3000]";
        else if(month > 11 || month < 0) throw "Setting months failed. [Outside of the boundaries 0=<month<=12]";
        else if(day < 0 || day>31) throw "Setting days failed. [Outside of the boundaries 0<day<32]";
        else {
            m_date_time.tm_year = year-1900;
            m_date_time.tm_mon  = month;
            m_date_time.tm_mday = day;
            m_date_time.tm_hour = 0;
            m_date_time.tm_min  = 0;
            m_date_time.tm_sec  = 0;
        }
    };

    // this is constructor that takes time of type time_t and checks it and if it is valid constructs class with it
    Date_time::Date_time(const std::time_t& time) {
        tm localTime = *std::localtime(&time);
        if(localTime.tm_year > 3000 || localTime.tm_year < 1900)
            throw "Setting years failed. [Outside of the boundaries 1900<year<3000]";
        else if(localTime.tm_mon > 11 || localTime.tm_mon < 0)
            throw "Setting months failed. [Outside of the boundaries 0=<month<=12]";
        else if(localTime.tm_mday < 0 || localTime.tm_mday>31)
            throw "Setting days failed. [Outside of the boundaries 0<day<32]";
        else { m_date_time =localTime;}
    };

    //copy assignment operator, copies another time_t into m_date_time
    Date_time& Date_time::operator=(const std::time_t& time){
        tm localTime = *std::localtime(&time);
        m_date_time = localTime;

        return *this;
    }

    //copy constructor, initializes a class from another instance
    Date_time::Date_time(const Date_time &o) {
        m_date_time = o.m_date_time;
        std::ostringstream os;
        os << std::put_time(&m_date_time, "%Y-%b-%d %H:%M:%S");
        std::cout<<"date_time::operator=(const date_time&)["<<os.str()<<"]called\n";
    };

    //copy assignment operator, copies another object Date_time o.m_date_time into m_date_time
    Date_time& Date_time::operator=(const Date_time& o){
        if(this != &o){
            m_date_time = o.m_date_time;
            std::ostringstream os;
            os << std::put_time(&m_date_time, "%Y-%b-%d %H:%M:%S");
            std::cout<<"date_time::operator=(const date_time&)["<<os.str()<<"]called\n";
        }
        return *this;
    }

    //copy assignment operator, copies another object of type std::tm into m_date_time
    Date_time& Date_time::operator=(const std::tm& time){
        m_date_time = time;
        return *this;
    }

    // this function is returning Date & time as a string from tm m_date_time
    std::string Date_time::str() {
        std::ostringstream os;
        os << std::put_time(&m_date_time, "%Y-%b-%d %H:%M:%S");
        if(os.fail()) throw "Returning string failed.";
        auto time_as_string{os.str()};
        return time_as_string;
    }

    // this function is returning Date & time as a string from tm m_date_time using own formatting
    std::string Date_time::str(std::string fmt) {
        std::ostringstream os;
        os << std::put_time( &m_date_time,fmt.c_str());
        if(os.fail()) throw "Returning string using own formatting failed.";
        auto time_as_string{ os.str()};
        return time_as_string;
    }

    // this function is parsing string according en standards("en_US.utf-8") and putting it into tm m_date_time
    void Date_time::parse(std::string str){
        std::tm t = {};
        std::istringstream ss (str);
        ss.imbue(std::locale("en_US.UTF-8"));
        ss >> std::get_time(&t,"%Y-%b-%d %H:%M:%S");
        if(!ss.fail())m_date_time = t;
        else throw "Parsing failed.";
    }

    // this function is parsing string according en standards("en_US.utf-8") and putting it into tm m_date_time
    // using own string formatting
    void Date_time::parse(std::string str, std::string fmt){
        std::tm t = {};
        std::istringstream ss (str);
        ss.imbue(std::locale("en_US.UTF-8"));
        ss >> std::get_time(&t,fmt.c_str());
        if(!ss.fail())m_date_time = t;
        else throw "Parsing using own formatting failed.";
    }

    // this function is adding seconds to m_date_time
    void Date_time::advance(const std::chrono::seconds& interval){
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(interval).count();
        if(seconds<60 && seconds >=0)m_date_time.tm_sec += seconds;
        else throw "Setting advanced failed. [Outside of the boundaries 0=<seconds<=59]";
    }

    // this function is subtracting seconds form m_date_time
    void Date_time::step_back(const std::chrono::seconds& interval){
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(interval).count();
        if(seconds<60 && seconds >=0) m_date_time.tm_sec -= seconds;
        else throw "Setting step_back failed. [Outside of the boundaries 0=<seconds<=59]";
    }

    void Date_time::setYear (const int& year ){
        if(year>=1900 && year<=3000)m_date_time.tm_year = year-1900;
        else throw "Setting years failed. [Outside of the boundaries 1900<year<3000]";
    };

    int Date_time::getYear()const { return m_date_time.tm_year +1900; }

    void Date_time::setMonth (const int& month){
        if(month >0 && month <= 12)m_date_time.tm_mon = month+1;
        else throw "Setting months failed. [Outside of the boundaries 1=<month<=12]";
    };

    int Date_time::getMonth()const { return m_date_time.tm_mon; };

    void Date_time::setDay (const int& day){
        if(day>0 && day<=31)m_date_time.tm_mday = day;
        else throw "Setting days failed. [Outside of the boundaries 1=<day<=31]";
    };

    int Date_time::getDay() const{ return m_date_time.tm_mday;};

    void Date_time::setHour (const int& hour){
        if(hour>=0 && hour <=24)m_date_time.tm_hour = hour;
        else throw "Setting hours failed. [Outside of the boundaries 0=<hour<=24]";
    };

    int Date_time::getHour()const { return m_date_time.tm_hour; };

    void Date_time::setMinute (const int& minute){
        if(minute>=0 && minute <=59)m_date_time.tm_min = minute;
        else throw "Setting minutes failed. [Outside of the boundaries 0=<seconds<=59]";
    };

    int Date_time::getMinute()const { return m_date_time.tm_min; };

    void Date_time::setSecond (const int& second){
        if(second>=0 && second<=59)m_date_time.tm_sec = second;
        else throw "Setting minutes failed. [Outside of the boundaries 0=<second<=59]";
    };

    int Date_time::getSecond() const{ return m_date_time.tm_sec; }
}
