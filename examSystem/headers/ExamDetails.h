#ifndef MTM_EX2_EXAMDETAILS_H
#include <string>
#include <iostream>
#include <ostream>
using std::string;
using std::ostream;
using std::cout;
using std::endl;
#define MTM_EX2_EXAMDETAILS_H

class ExamDetails {
    int courseId;
    int examMonth;
    int examDay;
    double examHour;
    int duration;
    string zoomLink;


public:
    ExamDetails(double courseId, double examMonth, double examDay, double examHour, double examLength, string zoomLink="");
    string getLink() const;
    void setLink(string link);
    int operator-(const ExamDetails &exam) const;
    bool operator<(const ExamDetails &exam) const;
    ExamDetails& operator=(const ExamDetails &exam);
    ExamDetails(const ExamDetails &exam);
    friend ostream& operator<<(ostream &os, const ExamDetails &exam);
    static ExamDetails makeMatamExam();
    class InvalidDateException{};
    class InvalidTimeException{};
    class InvalidArgsException{};

private:
    static void isValidTime(double hour);
    static void isValidDate(double month, double day);
    static void isValidArgs(double courseNumber);
};

ostream& operator<<(ostream &os, const ExamDetails &exam);

#endif //MTM_EX2_EXAMDETAILS_H
