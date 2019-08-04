//
// Created by Desirelife on 2019/7/30.
//

#ifndef ACHIEVEMENTMANAGEMENT_STUDENT_H
#define ACHIEVEMENTMANAGEMENT_STUDENT_H

#include <string>
#include <vector>
#include "Course.h"
using namespace std;

class Student {
public:
    int courseNum;      //该学生拥有的课程数目
    string studentId;       //学号
    string studentName;
private:
    double weightedScore, creditsSum, Gpa;      //加权成绩、总学分和平均绩点
    vector<Course> studentCourses;      // 拥有的课程的列表
public:
    explicit Student(int courseNum = 0, string studentId = "0", string studentName = "0", vector<Course> studentCourses = {}, double weightedScore = 0,
                     double creditsSum = 0);
    /* 对封装起来的成员变量的 set和 get操作*/
    void setWeightedScore();
    double getWeightedScore();
    void setCreditsSum();
    double getCreditsSum();
    void setGpa();
    double getGpa();
    void addCourseToList(Course& course);
    Course* getCourseFromList(int i);
    /*对学生和课程的查找*/
    bool searchByStudentId(string studentId);
    bool searchByStudentName(string studentName);
    Student* searchStudentByKeyword(const string& searchKeyword);
    Course* getSingleCourse();
    double getSingleCourseScore(const string& courseName);
    /*展示所有学生的信息*/
    void display();
};

#endif //ACHIEVEMENTMANAGEMENT_STUDENT_H
