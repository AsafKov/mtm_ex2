#ifndef MTM_EX2_EXAMDETAILS_H
#include <string>
#include <iostream>
using std::string;
#define MTM_EX2_EXAMDETAILS_H

class ExamDetails {
    int courseId;
    int examMonth;
    int examDay;
    double examHour;
    int examLength;
    string zoomLink;

public:
    ExamDetails(int courseId, int examMonth, int examDay, double examHour, int examLength, string zoomLink="");
    string getLink() const;
    void setLink(string link);
    int operator-(const ExamDetails &exam) const;
    bool operator<(const ExamDetails &exam) const;
    ExamDetails& operator=(const ExamDetails &exam);
    ExamDetails(const ExamDetails &exam);
    static ExamDetails makeMatamExam();
};

#endif //MTM_EX2_EXAMDETAILS_H
