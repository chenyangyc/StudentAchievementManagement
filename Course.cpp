//
// Created by Desirelife on 2019/8/2.
//

#include "Course.h"
#include <iostream>
#include <iomanip>

using namespace std;

Course::Course(string courseName, double credit) {
    this->courseName = courseName;
    this->credit = credit;
}


void Course::setScore(string score) {
    this->score = score;
}
