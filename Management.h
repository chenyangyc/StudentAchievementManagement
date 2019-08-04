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
    Student* searchStudentByKeyword();      //根据姓名或学号搜索学生信息
    /* 将每门出现的课程信息加入到统计所有课程信息的 map中*/
    void countCourses(Course course, double score);
    /*以下均为继承接口后重写的方法*/
    void addStudent() override ;
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
