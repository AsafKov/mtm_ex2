#include "examDetails.h"

namespace mtm {
    ExamDetails::ExamDetails(int courseId, int examMonth, int examDay, double examHour, int duration,
                                  string zoomLink) {
        isValidDate(examMonth, examDay);
        isValidTime(examHour);
        isValidArgs(courseId);
        this->courseId = courseId;
        this->examDay = examDay;
        this->examHour = examHour;
        this->duration = duration;
        this->examMonth = examMonth;
        this->zoomLink = std::move(zoomLink);
    }

    string ExamDetails::getLink() const {
        return this->zoomLink;
    }

    void ExamDetails::setLink(const string& link) {
        this->zoomLink = link;
    }

    double ExamDetails::operator-(const ExamDetails &exam) const {
        int exam1_days_total = this->examMonth * MONTH_LENGTH + this->examDay;
        int exam2_days_total = exam.examMonth * MONTH_LENGTH + exam.examDay;
        if(exam1_days_total == exam2_days_total){
            return (this->examHour - exam.examHour);
        }
        return exam1_days_total - exam2_days_total;
    }

    bool ExamDetails::operator<(const ExamDetails &exam) const {
        double diff = *this - exam;
        if(diff < 0){
            return true;
        }
        if(diff == 0){
            return courseId > exam.courseId;
        }
        return false;
    }

    ExamDetails& ExamDetails::operator=(const ExamDetails &exam) {
        if (this == &exam) {
            return *this;
        }
        this->courseId = exam.courseId;
        this->examDay = exam.examDay;
        this->examMonth = exam.examMonth;
        this->duration = exam.duration;
        this->zoomLink = exam.zoomLink;
        return *this;
    }

    ExamDetails::ExamDetails(const ExamDetails &exam) {
        this->courseId = exam.courseId;
        this->examDay = exam.examDay;
        this->examMonth = exam.examMonth;
        this->examHour = exam.examHour;
        this->duration = exam.duration;
        this->zoomLink = exam.zoomLink;
    }

    ExamDetails ExamDetails::makeMatamExam() {
        return ExamDetails(MATAM_COURSE_NUMBER, MATAM_EXAM_MONTH, MATAM_EXAM_DAY, MATAM_EXAM_HOUR,
                           MATAM_EXAM_DURATION, mtm::MATAM_ZOOM_LINK);
    }

    ostream &operator<<(ostream &os, const ExamDetails &exam) {
        return os << "Course Number: " << exam.courseId << std::endl << "Time: " << exam.examDay << "."
                  << exam.examMonth << " at "
                  << (int) exam.examHour << ":"
                  << ((exam.examHour - (int) exam.examHour <= ExamDetails::ACCEPTED_NUMERIC_ERROR) ? "00" : "30")
                  << std::endl << "Duration: "
                  << exam.duration << ":00" << std::endl << "Zoom Link: " << exam.zoomLink << std::endl;
    }

    void ExamDetails::isValidDate(double examMonth, double examDay) {
        if (examMonth < 1 || examMonth > YEAR_LENGTH || examDay < 1 || examDay > MONTH_LENGTH) {
            throw InvalidDateException();
        }
    }

    void ExamDetails::isValidTime(double examHour) {
        double decimal_diff = (examHour - (int) examHour);
        if ((decimal_diff > ACCEPTED_NUMERIC_ERROR && decimal_diff != 0.5) || examHour < 0 || examHour > 23.5) {
            throw InvalidTimeException();
        }
    }

    void ExamDetails::isValidArgs(double courseNumber) {
        double decimal_diff = courseNumber - (int) courseNumber;
        if (decimal_diff != 0 || courseNumber < 0) {
            throw InvalidArgsException();
        }
    }
}

