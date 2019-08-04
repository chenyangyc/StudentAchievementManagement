//
// Created by Desirelife on 2019/8/4.
// 使用builder设计模式
//

#ifndef ACHIEVEMENTMANAGEMENT_STUDENTBUILDER_H
#define ACHIEVEMENTMANAGEMENT_STUDENTBUILDER_H

#include "Student.h"

class StudentBuilder {
private:
    Student student;
public:
    StudentBuilder courseNum(int courseNum);
    StudentBuilder studentId(string studentId);
    StudentBuilder studentName(string studentName);
    StudentBuilder studentCourses(vector<Course> studentCourses);
    StudentBuilder creditsSum();
    StudentBuilder weightedScore();
    StudentBuilder gpa();
    Student build();
};


#endif //ACHIEVEMENTMANAGEMENT_STUDENTBUILDER_H
