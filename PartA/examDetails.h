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
        constexpr const static double LATEST_STARTING_HOUR = 23.5;
        constexpr const static double DECIMAL_DIFF_HOUR = 0.5;

        int courseId;
        int examMonth;
        int examDay;
        double examHour;
        int duration;
        string zoomLink;

        /**
         * Checks if starting hour is valid: HH:30/HH:00 and
         * @param hour - Exam stating hour
         * @throws InvalidTimeException
         */
        static void isValidTime(double hour);

        /**
         * Checks if the date and month inserted are valid
         * @param month
         * @param day
         * @throws InvalidDateException
         */
        static void isValidDate(double month, double day);

        /**
         * Checks for general input errors
         * @param courseNumber
         * @throws InvalidArgsException
         */
        static void isValidArgs(double courseNumber);

    public:
        /**
         * Constructs an ExamDetails objects with the given parameters after checking their validity
         * @param courseId
         * @param examMonth
         * @param examDay
         * @param examHour
         * @param duration
         * @param zoomLink
         */
        ExamDetails(int courseId, int examMonth, int examDay, double examHour, int duration,
                    string zoomLink = "");

        /**
         * @return Get zoom link of the exam
         */
        inline string getLink() const {
            return zoomLink;
        };

        /**
         * Set zoom link of the exam
         * @param link
         */
        inline void setLink(const string &link) {
            this->zoomLink = link;
        };

        /**
         * @param exam
         * @return the time difference between the exam it's being called on and a given exam.
         *         If the day in year is the same, returns the difference in terms of starting hour.
         */
        double operator-(const ExamDetails &exam) const;

        /**
         * @param exam
         * @return Whether the exam it's operating on starts before the given exam
         */
        bool operator<(const ExamDetails &exam) const;

        /**
         * Copies the contents of a given exam to an existing exam
         * @param exam
         * @return - Reference to the changed exam
         */
        ExamDetails &operator=(const ExamDetails &exam);

        /**
         * Constructs a new exam by copying the contents of a given exam
         * @param exam
         */
        ExamDetails(const ExamDetails &exam);

        /**
         * Formats the exam information into a ostream the can be printed
         * @param os
         * @param exam
         * @return ostream with the print format of the exam details
         */
        friend ostream &operator<<(ostream &os, const ExamDetails &exam);

        /**
         * Creates a pre-defined Matam exam
         * @return - ExamDetails objects with the information of MatamExam
         */
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
