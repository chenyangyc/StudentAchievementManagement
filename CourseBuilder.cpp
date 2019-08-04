//
// Created by Desirelife on 2019/8/4.
//

#include "CourseBuilder.h"

CourseBuilder CourseBuilder::courseName(string courseName) {
    course.courseName = courseName;
    return *this;
}

CourseBuilder CourseBuilder::credit(double credit) {
    course.credit = credit;
    return *this;
}

CourseBuilder CourseBuilder::score(double score) {
    course.setScore(score);
    return *this;
}

CourseBuilder CourseBuilder::gpa() {
    course.setGpa();
    return *this;
}

Course CourseBuilder::build() {
    return course;
}
