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

bool Course::searchByCourseName(const string &searchName) {
    return this->courseName == searchName;
}
