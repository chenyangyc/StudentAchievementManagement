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
    double credit, gpaSum;
    int num;
private:
    double score;
    double gpa;
public:
    explicit Course(string courseName = "0", double credit = 0);
    void setGpa();
    double getGpa();
    void setScore(double score);
    double getScore();
    bool searchByCourseName(const string &searchName);
    bool operator <(const Course& c) const;

};


#endif //ACHIEVEMENTMANAGEMENT_COURSE_H
