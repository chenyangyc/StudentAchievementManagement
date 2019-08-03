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
    int courseNum;
    string studentId;
    string studentName;
private:
    double weightedScore, creditsSum, Gpa;
    vector<Course> studentCourses;
public:
    explicit Student(int courseNum = 0, string studentId = "0", string studentName = "0", vector<Course> studentCourses = {}, double weightedScore = 0,
                     double creditsSum = 0);
    void setWeightedScore();
    double getWeightedScore();
    void setCreditsSum();
    double getCreditsSum();
    void setGpa();
    double getGpa();
    void addCourseToList(Course& course);
    Course* getCourseFromList(int i);
    bool searchByStudentId(string studentId);
    bool searchByStudentName(string studentName);
    Student* searchStudentByKeyword(const string& searchKeyword);
    Course* getSingleCourse();
    double getSingleCourseScore(const string& courseName);
    void display();
};

#endif //ACHIEVEMENTMANAGEMENT_STUDENT_H
