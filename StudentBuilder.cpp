//
// Created by Desirelife on 2019/8/4.
//

#include "StudentBuilder.h"

StudentBuilder StudentBuilder::courseNum(int courseNum) {
    student.courseNum = courseNum;
    return *this;
}

StudentBuilder StudentBuilder::studentId(string studentId) {
    student.studentId = studentId;
    return *this;
}

StudentBuilder StudentBuilder::studentName(string studentName) {
    student.studentName = studentName;
    return *this;
}

StudentBuilder StudentBuilder::studentCourses(vector<Course> studentCourses) {
    student.setCourseList(studentCourses);
    return *this;
}

StudentBuilder StudentBuilder::weightedScore() {
    student.setWeightedScore();
    return *this;
}

StudentBuilder StudentBuilder::creditsSum() {
    student.setCreditsSum();
    return *this;
}

StudentBuilder StudentBuilder::gpa() {
    student.setGpa();
    return *this;
}

Student StudentBuilder::build() {
    return student;
}






