#include <utility>

#include "Date_time.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <sstream>

namespace SAX {

    //default constructor constructs class with actual date & time
    Date_time::Date_time():
    m_error_flag{false}
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t c_date_time = std::chrono::system_clock::to_time_t(date_time);
        m_date_time = *std::localtime(&c_date_time);
    }

    // this is constructor that takes year, month and day and assigns 0 to every other member
    Date_time::Date_time(const int& year,const int& month,const int& day) :
    m_error_flag{false}
    {
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
    }

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
    }

    //copy assignment operator, copies another time_t into m_date_time
    Date_time& Date_time::operator=(const std::time_t& time){
        tm localTime = *std::localtime(&time);
        m_date_time = localTime;
        return *this;
    }

    //copy constructor, initializes a class from another instance
    Date_time::Date_time(const Date_time &o) :
        m_date_time{o.m_date_time},
        m_error_flag{o.m_error_flag}
    {}

    //copy assignment operator, copies another object Date_time o.m_date_time into m_date_time
    Date_time& Date_time::operator=(const Date_time& o){
        if(this != &o){
            m_date_time = o.m_date_time;
            m_error_flag = o.m_error_flag;
        }
        return *this;
    }

    //copy assignment operator, copies another object of type std::tm into m_date_time
    Date_time& Date_time::operator=(std::tm time){
        m_date_time = std::move(time);
        return *this;
    }

    //addition assignment operator
    Date_time& Date_time::operator+(const std::chrono::seconds& seconds){
        m_date_time.tm_sec += seconds.count();
        return *this;
    }

    //compound addition assignment operator
    Date_time& Date_time::operator+=(const std::chrono::seconds& seconds){
        m_date_time.tm_sec += seconds.count();
        return *this;
    }

    //compound subtraction  assignment operator
    Date_time& Date_time::operator-=(const std::chrono::seconds& seconds){
        m_date_time.tm_sec -= seconds.count();
        return *this;
    }

    //subtraction  assignment operator
    Date_time& Date_time::operator-(const std::chrono::seconds& seconds){
        m_date_time.tm_sec -= seconds.count();
        return *this;
    }

    bool Date_time::operator<(Date_time& rhsDate_time) {
        return rhsDate_time.my_time_t() == this->my_time_t();
    }

    bool Date_time::operator<=(Date_time& rhsDate_time){
        return rhsDate_time.my_time_t() <= this->my_time_t();
    }

    bool Date_time::operator==(Date_time& rhsDate_time){
        return rhsDate_time.my_time_t() == this->my_time_t();
    }

    bool Date_time::operator>=(Date_time& date_time){
        return date_time <= *this;
    }

    bool Date_time::operator>(Date_time& date_time){
        return date_time < *this;
    }

    Date_time::operator std::time_t() {
        return mktime(&m_date_time);
    }

    std::time_t Date_time::my_time_t(){
        return mktime(&m_date_time);
    }

    Date_time::operator bool() const{
        return m_error_flag;
    };

    std::ostream& operator<<(std::ostream &os, const Date_time &dt) {
        return os << std::put_time( &dt.m_date_time,"%Y-%b-%d %H:%M:%S")<<"\n";
    }

    std::istream& operator>>(std::istream &is, Date_time &dt) {
        is.imbue(std::locale("en_US.UTF-8"));
        is >> std::get_time(&dt.m_date_time,"%Y-%b-%d %H:%M:%S");
        return is;
    }

    //post increment
    Date_time& operator++(Date_time &dt, int) {
        dt.m_date_time.tm_sec++;
        return dt;
    }

    //post decrement
    Date_time& operator--(Date_time &dt, int) {
        dt.m_date_time.tm_sec--;
        return dt;
    }

    //pre increment
    Date_time& operator++(Date_time &dt) {
        ++dt.m_date_time.tm_sec;
        return dt;
    }

    //pre decrement
    Date_time& operator--(Date_time &dt) {
        --dt.m_date_time.tm_sec;
        return dt;
    }

    const int& Date_time::operator[](const std::string& str) const {
       if (str =="year") return m_date_time.tm_year + 1900;
       else if (str =="month") return m_date_time.tm_mon + 1;
       else if (str =="day") return m_date_time.tm_mday;
       else if (str =="hour") return m_date_time.tm_hour;
       else if (str =="minute") return m_date_time.tm_min;
       else if (str =="second") return m_date_time.tm_sec;
       else throw "Incorrect request";
    }

    // this function is returning Date & time as a string from tm m_date_time
    std::string Date_time::str(){
        return str("%Y-%b-%d %H:%M:%S");
    }

    // this function is returning Date & time as a string from tm m_date_time using own formatting
    std::string Date_time::str(std::string fmt){
        std::ostringstream os;
        os << std::put_time( &m_date_time,fmt.c_str());
        os.fail() ? (m_error_flag = true) : (m_error_flag = false);
        if(os.fail()) throw "Returning string failed.";
        auto time_as_string{ os.str()};
        return time_as_string;
    }

    // this function is parsing string according en standards("en_US.utf-8") and putting it into tm m_date_time
    void Date_time::parse(std::string str){
        parse(std::move(str),"%Y-%b-%d %H:%M:%S");
    }

    // this function is parsing string according en standards("en_US.utf-8") and putting it into tm m_date_time
    // using own string formatting
    void Date_time::parse(std::string str, std::string fmt){
        std::tm t = {};
        std::istringstream ss (str);
        ss.imbue(std::locale("en_US.UTF-8"));
        ss >> std::get_time(&t,fmt.c_str());
        ss.fail() ? (m_error_flag = true) : (m_error_flag = false);
        if(!ss.fail())m_date_time = t;
        else throw "Parsing failed.";
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


    auto Date_time::proxy::getMember(const std::string& request) {
        if (request =="year") return m_owner.m_date_time.tm_year+1900;
        else if (request =="month") return m_owner.m_date_time.tm_mon+1;
        else if (request =="day") return m_owner.m_date_time.tm_mday;
        else if (request =="hour") return m_owner.m_date_time.tm_hour;
        else if (request =="minute") return m_owner.m_date_time.tm_min;
        else if (request =="second") return m_owner.m_date_time.tm_sec;
        else throw "Incorrect request";
    }

    Date_time::proxy::operator int(){
        return getMember(m_request);
    }

    Date_time::proxy &Date_time::proxy::operator=(int value) {
        if (m_request == "year"&& isValid(value, m_request)){
            m_owner.m_date_time.tm_year = value - 1900;
        }

        else if (m_request == "month" && isValid(value, m_request)){
            m_owner.m_date_time.tm_mon = value-1;
        }

        else if (m_request == "day" && isValid(value, m_request)){
            m_owner.m_date_time.tm_mday = value;
        }

        else if (m_request == "hour"&& isValid(value, m_request)){
            m_owner.m_date_time.tm_hour = value;
        }

        else if (m_request == "minute"&& isValid(value, m_request) ){
             m_owner.m_date_time.tm_min = value;
        }

        else if (m_request == "second"&& isValid(value, m_request)){
            m_owner.m_date_time.tm_sec = value;
        }

        else throw "incorrect value";
        return *this;
    }

    Date_time::proxy &Date_time::proxy::operator-=(int value) {
        value *= -1;
        *this += value;
        return *this;
    }

    Date_time::proxy &Date_time::proxy::operator+=(int value) {
        if (m_request == "year"){
            m_owner.m_date_time.tm_year += value;
        }

        else if (m_request == "month"){
                time_t time1 = m_owner.my_time_t();
                time1 = m_owner.my_time_t();
                time1 += value * 2592000;
                tm localTime = *std::localtime(&time1);
                m_owner.m_date_time = localTime;

        }

        else if (m_request == "day" ){
                time_t time1 = m_owner.my_time_t();
                time1 += value * 86400;
                tm localTime = *std::localtime(&time1);
                m_owner.m_date_time = localTime;
        }

        else if (m_request == "hour"){
                time_t time1 = m_owner.my_time_t();
                time1 += value * 3600;
                tm localTime = *std::localtime(&time1);
                m_owner.m_date_time = localTime;
        }

        else if (m_request == "minute" ){
                time_t time1 = m_owner.my_time_t();
                time1 += value * 60;
                tm localTime = *std::localtime(&time1);
                m_owner.m_date_time = localTime;
        }

        else if (m_request == "second"){
                time_t time1 = m_owner.my_time_t();
                time1 += value;
                tm localTime = *std::localtime(&time1);
                m_owner.m_date_time = localTime;
            }

        else throw "incorrect value";
        return *this;

    }
}
