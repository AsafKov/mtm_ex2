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
private:
    const static int MONTH_LENGTH = 30;
    const static int YEAR_LENGTH = 12;
    const static int MATAM_COURSE_NUMBER = 234124;
    const static int MATAM_EXAM_MONTH = 7;
    const static int MATAM_EXAM_DAY = 28;
    const static int MATAM_EXAM_HOUR = 13;
    const static int MATAM_EXAM_LENGTH = 3;

    int courseId;
    int examMonth;
    int examDay;
    double examHour;
    int duration;
    string zoomLink;
    static void isValidTime(double hour);
    static void isValidDate(double month, double day);
    static void isValidArgs(double courseNumber);

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
};

ostream& operator<<(ostream &os, const ExamDetails &exam);

#endif //MTM_EX2_EXAMDETAILS_H
