#include "ExamDetails.h"

ExamDetails::ExamDetails(int courseId, int examMonth, int examDay, double examHour, int examLength, string zoomLink) {
    this->courseId = courseId;
    this->examDay = examDay;
    this->examHour = examHour;
    this->examLength = examLength;
    this->examMonth = examMonth;
    this->zoomLink = zoomLink;
}

string ExamDetails::getLink() const{
    return this->zoomLink;
}

void ExamDetails::setLink(const string link) {
    this->zoomLink = link;
}

int ExamDetails::operator-(const ExamDetails &exam) const {
    int exam1_days_total = this->examMonth*30 + this->examDay;
    int exam2_days_total = exam.examMonth*30 + exam.examDay;

    return exam1_days_total-exam2_days_total;
}

bool ExamDetails::operator<(const ExamDetails &exam) const{
    return this - &exam < 0;
}

//TODO: validate string handling method
ExamDetails& ExamDetails::operator=(const ExamDetails &exam) {
    if(this == &exam){
        return *this;
    }
    this->courseId = exam.courseId;
    this->examDay = exam.examDay;
    this->examMonth = exam.examMonth;
    this->examLength = exam.examLength;
    this->zoomLink = exam.zoomLink;
    return *this;
}

ExamDetails::ExamDetails(const ExamDetails &exam) {
    this->courseId = exam.courseId;
    this->examDay = exam.examDay;
    this->examMonth = exam.examMonth;
    this->examHour = exam.examHour;
    this->examLength = exam.examLength;
    this->zoomLink = exam.zoomLink;
}

ExamDetails ExamDetails::makeMatamExam() {
    return ExamDetails(1, 2, 3, 4, 5, "DEFAULT_ZOOM_LINK");
}

void ExamDetails::operator<<(const ExamDetails &exam) {
    cout <<
}
