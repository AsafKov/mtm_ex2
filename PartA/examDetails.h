#ifndef MTM_EX2_EXAMDETAILS_H
#include <string>
#include <iostream>
#include <ostream>
using std::string;
using std::ostream;
using std::cout;
using std::endl;
#define MTM_EX2_EXAMDETAILS_H

namespace mtm {
    const static string MATAM_ZOOM_LINK = "https://tinyurl.com/59hzps6m";
    class ExamDetails {
    private:
        constexpr const static float ACCEPTED_NUMERIC_ERROR = 1e-6;
        const static int MONTH_LENGTH = 30;
        const static int YEAR_LENGTH = 12;
        const static int MATAM_COURSE_NUMBER = 234124;
        const static int MATAM_EXAM_MONTH = 7;
        const static int MATAM_EXAM_DAY = 28;
        const static int MATAM_EXAM_HOUR = 13;
        const static int MATAM_EXAM_DURATION = 3;

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
        ExamDetails(int courseId, int examMonth, int examDay, double examHour, int duration,
                    string zoomLink = "");

        string getLink() const;

        void setLink(const string& link);

        double operator-(const ExamDetails &exam) const;

        bool operator<(const ExamDetails &exam) const;

        ExamDetails &operator=(const ExamDetails &exam);

        ExamDetails(const ExamDetails &exam);

        friend ostream &operator<<(ostream &os, const ExamDetails &exam);

        static ExamDetails makeMatamExam();

    class InvalidDateException : public std::exception {
        };

        class InvalidTimeException : public std::exception {
        };

        class InvalidArgsException : public std::exception {
        };
    };
}
#endif //MTM_EX2_EXAMDETAILS_H
