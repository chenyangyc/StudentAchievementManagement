//
// Created by Desirelife on 2019/7/30.
//

#ifndef ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
#define ACHIEVEMENTMANAGEMENT_MANAGEMENT_H

#include <vector>
#include <map>
#include "StudentBuilder.h"
#include "CourseBuilder.h"
#include "ManageMethods.h"

class Management : public ManageMethods {
protected:
    vector<Student> students;
    map<string, Course> courses;
public:
    Management() = default;

    vector<Student*> searchStudentByKeyword();      //根据姓名或学号搜索学生信息
    /* 将每门出现的课程信息加入到统计所有课程信息的 map中*/
    void countCourses(Course course, double score);

    /*以下均为继承接口后重写的方法*/
    void addStudent() override;      //添加学生信息
    void showSingleStudent() override;     //展示单个学生信息
    void deleteStudent() override;      //删除学生信息
    void alterScore() override;    //修改成绩
    void getRankingBySingleCourseScore() override;   //按照单门课程成绩进行排序
    void getRankingByWeightedScore() override;       //按照加权成绩进行排序
    void showAllStudents() override;    //展示所有学生信息
    void showAllCourses() override;      //展示所有课程信息
    void storeFile() override;   //向文件写入信息并存储
    void loadFile() override;    //从文件读出信息
};

#endif //ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
