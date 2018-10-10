#ifndef ASSIGNMENT_1_DATE_TIME_H
#define ASSIGNMENT_1_DATE_TIME_H
#include <string>
#include <chrono>
namespace SAX {
    class Date_time {
    public:
        explicit Date_time();
        Date_time(const int& year, const int& month,const int& day);
        explicit Date_time(const std::time_t& time);
        Date_time& operator=(const std::time_t& time);
        Date_time(const Date_time& o);
        Date_time& operator=(const Date_time& o);
        Date_time& operator=(const std::tm& time);

        std::string str();
        std::string str(std::string fmt);

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

    private:
        std::tm m_date_time;
        bool m_error_flag;
    };
}

#endif //ASSIGNMENT_1_DATE_TIME_H
