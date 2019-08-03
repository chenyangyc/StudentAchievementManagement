//
// Created by Desirelife on 2019/7/30.
//

#ifndef ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
#define ACHIEVEMENTMANAGEMENT_MANAGEMENT_H

#include <vector>
#include <map>
#include "Student.h"

class Management {
protected:
    vector<Student> students;
    map<string, int> coursesNum;
    map<string, Course> courses;
public:
    Management()= default;
    void addStudent();
    Student* searchStudentByKeyword();
    void showSingleStudent();
    void deleteStudent();
    void alterScore();
    void getRankingBySingleCourseScore();
    void getRankingByWeightedScore();
    void storeFile();
    void loadFile();
    void showAllStudents();
    void showAllCourses();
};

#endif //ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
