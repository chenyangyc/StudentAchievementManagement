//
// Created by Desirelife on 2019/8/4.
// 使用builder设计模式
//

#ifndef ACHIEVEMENTMANAGEMENT_COURSEBUILDER_H
#define ACHIEVEMENTMANAGEMENT_COURSEBUILDER_H

#include "Course.h"

class CourseBuilder {
private:
    Course course;
public:
    CourseBuilder courseName(string courseName);
    CourseBuilder credit(double credit);
    CourseBuilder score(double score);
    CourseBuilder gpa();
    Course build();
};


#endif //ACHIEVEMENTMANAGEMENT_COURSEBUILDER_H
