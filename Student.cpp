//
// Created by Desirelife on 2019/7/30.
//
#include <iostream>
#include <iomanip>
#include "Student.h"
#include "Course.h"
using namespace std;

Student::Student(string studentId, string studentName, vector<Course> studentCourses, double weightedScore) {
    this->studentId = studentId;
    this->studentName = studentName;
    this->studentCourses = studentCourses;
    this->weightedScore = weightedScore;
}

void Student::setStudent(string studentId, string studentName) {
    this->studentId = studentId;
    this->studentName = studentName;
    initCourses();
}

void Student::display() {
    cout << studentId << setw(8) << studentName << setw(8);
    for(const Course& course: studentCourses) {
        cout << course.score << setw(8);
    }
    cout << weightedScore << setw(8);
    cout << endl;
}

void Student::initCourses() {
    this->studentCourses.push_back(this->math);
    this->studentCourses.push_back(this->algorithm);
}
