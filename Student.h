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
    string studentId;
    string studentName;
    double weightedScore;
    Course math = Course("math", 5);
    Course algorithm = Course("algorithm", 4.5);
    vector<Course> studentCourses;
public:
    explicit Student(string studentId = "0", string studentName = "0", vector<Course> studentCourses = {}, double weightedScore = 0);
    bool searchByStudentId(string studentId);
    bool searchByStudentName(string studentName);
    Student* searchStudentByKeyword(const string& searchKeyword);
    Course* getSingleCourse();
    double getSingleCourseScore(const string& courseName);
    void countWeightedScore();
    void display();
};

#endif //ACHIEVEMENTMANAGEMENT_STUDENT_H
