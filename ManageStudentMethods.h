//
// Created by Desirelife on 2019/8/4.
//

#ifndef ACHIEVEMENTMANAGEMENT_MANAGESTUDENTMETHODS_H
#define ACHIEVEMENTMANAGEMENT_MANAGESTUDENTMETHODS_H


class ManageStudentMethods {
    virtual void addStudent() = 0;
    virtual void showSingleStudent() = 0;
    virtual void deleteStudent() = 0;
    virtual void alterScore() = 0;
    virtual void getRankingBySingleCourseScore() = 0;
    virtual void getRankingByWeightedScore() = 0;
    virtual void showAllStudents() = 0;
    virtual void showAllCourses() = 0;
};


#endif //ACHIEVEMENTMANAGEMENT_MANAGESTUDENTMETHODS_H
