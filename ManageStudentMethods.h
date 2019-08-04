//
// Created by Desirelife on 2019/8/4.
// 对学生的操作
//

#ifndef ACHIEVEMENTMANAGEMENT_MANAGESTUDENTMETHODS_H
#define ACHIEVEMENTMANAGEMENT_MANAGESTUDENTMETHODS_H


class ManageStudentMethods {
    virtual void addStudent() = 0;      //添加学生信息
    virtual void showSingleStudent() = 0;      //展示单个学生信息
    virtual void deleteStudent() = 0;       //删除学生信息
    virtual void alterScore() = 0;      //修改成绩
    virtual void getRankingBySingleCourseScore() = 0;   //按照单门课程成绩进行排序
    virtual void getRankingByWeightedScore() = 0;       //按照加权成绩进行排序
    virtual void showAllStudents() = 0;     //展示所有学生信息
    virtual void showAllCourses() = 0;      //展示所有课程信息
};


#endif //ACHIEVEMENTMANAGEMENT_MANAGESTUDENTMETHODS_H
