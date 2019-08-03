//
// Created by Desirelife on 2019/7/30.
//
#include <iostream>
#include <iomanip>
#include "Student.h"
#include "Course.h"

#define ERROR -1;
using namespace std;

Student::Student(string studentId, string studentName, vector<Course> studentCourses, double weightedScore) {
    this->studentId = studentId;
    this->studentName = studentName;
    this->studentCourses = studentCourses;
    this->weightedScore = weightedScore;
}

double Student::getSingleCourseScore(const string &courseName) {
    for (Course course: studentCourses) {
        if (course.searchByCourseName(courseName)) {
            return course.score;
        }
    }
    cout << "No such course. Please check your spelling." << endl;
    return ERROR
}

void Student::countWeightedScore() {
    double creditSum = 0;
    double countingScore = 0;
    for (const Course &course: studentCourses) {
        creditSum += course.credit;
    }
    for (const Course &course: studentCourses) {
        double weight = course.credit / creditSum;
        countingScore += course.score * weight;
        this->weightedScore = countingScore;
    }
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

void Student::display() {
    cout << studentId << setw(8) << studentName << setw(8);
    for (const Course &course: studentCourses) {
        cout << course.score << setw(8);
    }
    cout << weightedScore << setw(8);
    cout << endl;
}

Course *Student::getSingleCourse() {
    int choice;
    Course *courseChosen = nullptr;
    cout << "Which course do you want to choose? " << endl;
    for(int i = 0; i < studentCourses.size(); i++){
        cout << i + 1 << "." << studentCourses[i].courseName << endl;
    }
    cin >> choice;
    switch (choice){
        case 1:
            courseChosen = &studentCourses[0];
            break;
        case 2:
            courseChosen = &studentCourses[1];
            break;
        default:
            cout << "Check your choice!" << endl;
    }
    return courseChosen;
}


