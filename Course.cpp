#include <utility>

//
// Created by Desirelife on 2019/8/2.
//

#include "Course.h"
#include <iostream>
#include <iomanip>

using namespace std;


Course::Course(string courseName, double credit) {
    this->courseName = std::move(courseName);
    this->credit = credit;
}

void Course::setGpa() {
    if (score >= 90) {
        this->gpa = 4.0;
    } else if (score >= 85) {
        this->gpa = 3.7;
    } else if (score >= 82) {
        this->gpa = 3.3;
    } else if (score >= 78) {
        this->gpa = 3.0;
    } else if (score >= 75) {
        this->gpa = 2.7;
    } else if (score >= 72) {
        this->gpa = 2.3;
    } else if (score >= 68) {
        this->gpa = 2.0;
    } else if (score >= 64) {
        this->gpa = 1.5;
    } else if (score >= 60) {
        this->gpa = 1.0;
    } else {
        this->gpa = 0;
    }
}

double Course::getGpa() {
    return this->gpa;
}

void Course::setScore(double score) {
    this->score = score;
}

double Course::getScore() {
    return this->score;
}

bool Course::searchByCourseName(const string &searchName) {
    return this->courseName == searchName;
}

bool Course::operator <(const Course& c) const {
    return this->score > c.score;
}

