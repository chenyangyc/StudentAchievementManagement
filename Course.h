//
// Created by Desirelife on 2019/8/2.
//

#ifndef ACHIEVEMENTMANAGEMENT_COURSE_H
#define ACHIEVEMENTMANAGEMENT_COURSE_H
#include <string>
using namespace std;

class Course {
public:
    string courseName;
    double credit;
    string score;
public:
    Course(string courseName = "0", double credit = 0);
    bool searchByCourseName(string courseName){return this->courseName == courseName;}
    void setScore(string myScore);
};


#endif //ACHIEVEMENTMANAGEMENT_COURSE_H
