//
// Created by Desirelife on 2019/7/30.
//

#ifndef ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
#define ACHIEVEMENTMANAGEMENT_MANAGEMENT_H

#include <vector>
#include <map>
#include "ManageStudentMethods.h"
#include "ManageFileMethods.h"

class Management : public ManageStudentMethods, public ManageFileMethods {
protected:
    vector<Student> students;
    map<string, Course> courses;
public:
    Management()= default;
    Student* searchStudentByKeyword();
    void addStudent() override ;
    static bool cmp(Student &a, Student &b);
    static bool singleCmp(pair<pair<string, string>, double> &a, pair<pair<string, string>, double> &b);
    void showSingleStudent() override;
    void deleteStudent() override;
    void alterScore() override;
    void getRankingBySingleCourseScore() override;
    void getRankingByWeightedScore() override;
    void storeFile() override;
    void loadFile() override;
    void showAllStudents() override;
    void showAllCourses() override;
};

#endif //ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
