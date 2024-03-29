#ifndef ASSIGNMENT_1_DATE_TIME_H
#define ASSIGNMENT_1_DATE_TIME_H
#include <string>
#include <chrono>

namespace SAX {
    class Date_time {
    private:
        std::tm m_date_time;
        bool m_error_flag {false};

        //private proxy class
        struct proxy{
            Date_time& m_owner;
            std::string m_request;
            bool check ;
            auto getMember(const std::string& request);
            operator int();
            proxy& operator=(int value);
            proxy& operator+=(int value);
            proxy& operator-=(int value);
            bool isValid(const int &value, const std::string &request);
        };


    public:
        explicit Date_time();
        Date_time(const int& year, const int& month,const int& day);
        explicit Date_time(const std::time_t& time);
        Date_time& operator=(const std::time_t& time);
        Date_time(const Date_time& o);
        Date_time& operator=(const Date_time& o);
        Date_time& operator=(std::tm time);

        Date_time& operator+(const std::chrono::seconds& time);
        Date_time& operator+=(const std::chrono::seconds& time);
        Date_time& operator-(const std::chrono::seconds& time);
        Date_time& operator-=(const std::chrono::seconds& time);

        bool operator<(Date_time& date_time);
        bool operator>(Date_time& date_time);
        bool operator<=(Date_time& rhsDate_time);
        bool operator>=(Date_time& date_time);
        bool operator==(Date_time& rhsDate_time);

        explicit operator std::time_t();
        explicit operator bool() const;

        friend Date_time& operator++(Date_time& dt,int);
        friend Date_time& operator--(Date_time &dt, int);
        friend Date_time& operator++(Date_time &dt);
        friend Date_time& operator--(Date_time &dt);

        int operator[](const std::string& str)const;

        std::time_t my_time_t();

        std::string str();
        std::string str(std::string fmt);

        friend std::ostream& operator<<(std::ostream &os, const Date_time &dt);
        friend std::istream& operator>>(std::istream &is, Date_time &dt);

        void parse(std::string str);
        void parse(std::string str, std::string fmt);

        void advance(const std::chrono::seconds& interval);
        void step_back(const std::chrono::seconds& interval);

        void setYear (const int& year);
        int  getYear()const;

        void setMonth (const int& month);
        int  getMonth()const;

        void setDay (const int& day);
        int  getDay()const;

        void setHour (const int& hour);
        int  getHour()const;

        void setMinute (const int& minute);
        int  getMinute()const;

        void setSecond (const int& second);
        int  getSecond()const;

        // returning a proxy
        proxy year(){
            return proxy{*this, "year"};
        }
        proxy month(){
            return proxy{*this, "month"};
        }
        proxy day(){
            return proxy{*this, "day"};
        }
        proxy hour(){
            return proxy{*this, "hour"};
        }
        proxy minute(){
            return proxy{*this, "minute"};
        }
        proxy second(){
            return proxy{*this, "second"};
        }
    };
}

#endif //ASSIGNMENT_1_DATE_TIME_H
