#ifndef ASSIGNMENT_1_DATE_TIME_H
#define ASSIGNMENT_1_DATE_TIME_H
#include <string>
#include <chrono>
#include <iostream>
namespace SAX {
    class Date_time {
    private:
        std::tm m_date_time;
        bool m_error_flag;

        //private proxy class
        struct proxy{
            Date_time& m_owner;
            std::string m_request;
            bool plus_or_minus;
            //helper function to get the correct member from the owner
            auto getMember(const std::string& request) {
                if (request =="year") return m_owner.m_date_time.tm_year+1900;
                else if (request =="month") return m_owner.m_date_time.tm_mon;
                else if (request =="day") return m_owner.m_date_time.tm_mday;
                else if (request =="hour") return m_owner.m_date_time.tm_hour;
                else if (request =="minute") return m_owner.m_date_time.tm_min;
                else if (request =="second") return m_owner.m_date_time.tm_sec;
                else throw "Incorrect request";
            }

             operator int() {
                return getMember(m_request);
            }

            proxy& operator=(int value){

                if (m_request == "year"){
                    m_owner.m_date_time.tm_year = value - 1900;
                }
                else if (m_request == "month"){
                    m_owner.m_date_time.tm_mon = value -1 ;
                }
                else if (m_request == "hour"){
                    if(plus_or_minus) {
                        time_t time1 = m_owner.my_time_t();
                        time1 += value * 3600;
                        tm localTime = *std::localtime(&time1);
                        m_owner.m_date_time = localTime;
                    }
                    else {m_owner.m_date_time.tm_hour =value;}
                }
                else if (m_request == "minute"){
                    if(plus_or_minus) {
                        time_t time1 = m_owner.my_time_t();
                        time1 += value * 60;
                        tm localTime = *std::localtime(&time1);
                        m_owner.m_date_time = localTime;
                    }
                    else {m_owner.m_date_time.tm_min =value;}

                }
                else if (m_request == "second"){
                    if(plus_or_minus) {
                        time_t time1 = m_owner.my_time_t();
                        time1 += 1;
                        tm localTime = *std::localtime(&time1);
                        m_owner.m_date_time = localTime;
                    }
                    else {m_owner.m_date_time.tm_min =value;}
                }
                plus_or_minus =false;
                return *this;
            }

            proxy& operator+=(int value){
                *this = *this + value;
                return *this;
            }

            proxy& operator-=(int value){
                value *= -1;
                *this += value;
                return *this;
            }
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

        const int& operator[](const std::string& str)const;

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
            return proxy{*this, "year", false};
        }
        proxy month(){
            return proxy{*this, "month",false};
        }
        proxy day(){
            return proxy{*this, "day",false};
        }
        proxy hour(){
            return proxy{*this, "hour",false};
        }
        proxy minute(){
            return proxy{*this, "minute",false};
        }
        proxy second(){
            return proxy{*this, "second",false};
        }

    };
}

#endif //ASSIGNMENT_1_DATE_TIME_H
