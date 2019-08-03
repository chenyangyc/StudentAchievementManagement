//
// Created by Desirelife on 2019/7/30.
//
#include <iostream>
#include <iomanip>
#include "Student.h"
#include "Course.h"

#define ERROR -1;
using namespace std;

Student::Student(int courseNum, string studentId, string studentName, vector<Course> studentCourses,
                 double weightedScore,
                 double creditsSum) {
    this->courseNum = courseNum;
    this->studentId = studentId;
    this->studentName = studentName;
    this->studentCourses = studentCourses;
    this->weightedScore = weightedScore;
    this->creditsSum = creditsSum;
}

void Student::setWeightedScore() {
    double countingScore = 0;
    for (Course &course: studentCourses) {
        double weight = course.credit / creditsSum;
        countingScore += course.getScore() * weight;
    }
    this->weightedScore = countingScore;
}

double Student::getWeightedScore() {
    return this->weightedScore;
}

void Student::setCreditsSum() {
    double creditSum = 0;
    for (const Course &course: studentCourses) {
        creditSum += course.credit;
    }
    this->creditsSum = creditSum;
}

double Student::getCreditsSum() {
    return this->creditsSum;
}

void Student::setGpa() {
    this->Gpa = 0;
    for (int i = 0; i < studentCourses.size(); i++) {
        this->Gpa += studentCourses[i].getGpa() * studentCourses[i].credit / creditsSum;
    }
}

double Student::getGpa() {
    return this->Gpa;
}

void Student::addCourseToList(Course &course) {
    course.setGpa();
    this->studentCourses.push_back(course);
}

Course *Student::getCourseFromList(int i) {
    if (i >= 0 && i < studentCourses.size())
        return &studentCourses[i];
    return nullptr;
}

double Student::getSingleCourseScore(const string &courseName) {
    for (Course course: studentCourses) {
        if (course.searchByCourseName(courseName)) {
            return course.getScore();
        }
    }
    cout << "没有这门课程，请检查您的关键字拼写" << endl;
    return ERROR
}

bool Student::searchByStudentId(string studentId) {
    return this->studentId == studentId;
}

bool Student::searchByStudentName(string studentName) {
    return this->studentName == studentName;
}

Student *Student::searchStudentByKeyword(const string &searchKeyword) {
    if (searchByStudentId(searchKeyword) || searchByStudentName(searchKeyword)) {
        Student *studentPtr = this;
        return studentPtr;
    }
    return nullptr;
}

Course *Student::getSingleCourse() {
    int choice;
    Course *courseChosen = nullptr;
    cout << "您想要选择哪门课程? " << endl;
    for (int i = 0; i < studentCourses.size(); i++) {
        cout << i + 1 << "." << studentCourses[i].courseName << endl;
    }
    cin >> choice;
    if (choice < 1 || choice > studentCourses.size()) return nullptr;
    courseChosen = &studentCourses[choice - 1];
    return courseChosen;
}

void Student::display() {
    cout << "学生姓名：" << studentName << "\t";
    cout << "学号：" << studentId << endl;
    cout << " 科目" << setw(8) << "学分" << setw(8) << "成绩" << setw(8) << "绩点" << endl;
    for (Course &course: studentCourses) {
        cout << course.courseName << setw(8) << course.credit << setw(8) << course.getScore() << setw(8)
             << course.getGpa() << setw(8) << endl;
    }
    cout << "加权成绩：" << weightedScore << "\t" << "总绩点：" << Gpa << "\t" << "总学分: " << creditsSum << endl;
    cout << endl;
}
