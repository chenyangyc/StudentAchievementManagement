//
// Created by Desirelife on 2019/7/30.
//
#include <iostream>
#include <iomanip>
#include "Student.h"
using namespace std;

Student::Student(string studentId, string studentName, string mathScore) {
    this->studentId = studentId;
    this->studentName = studentName;
    this->mathScore = mathScore;
}

void Student::setStudent(string studentId, string studentName, string mathScore) {
    this->studentId = studentId;
    this->studentName = studentName;
    this->mathScore = mathScore;
}

void Student::display() {
    cout << studentId << setw(8) << studentName << setw(8) << mathScore << endl;
}
