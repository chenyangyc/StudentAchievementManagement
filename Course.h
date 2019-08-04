//
// Created by Desirelife on 2019/8/2.
//

#ifndef ACHIEVEMENTMANAGEMENT_COURSE_H
#define ACHIEVEMENTMANAGEMENT_COURSE_H

#include <string>

using namespace std;

class Course {
public:
    string courseName;
    double credit, gpaSum;  //该门课程的学分和所有学生该门课程的总绩点
    int num;        //拥有该门课的学生的数量， gpaSum和 num在计算年纪平均成绩和年级平均绩点时用到
private:
    double score;   //成绩
    double gpa;     //课程绩点
public:
    explicit Course(string courseName = "0", double credit = 0);
    /*对封装起来的变量的 set和 get操作*/
    void setGpa();
    double getGpa();
    void setScore(double score);
    double getScore();
    /*搜索课程*/
    bool searchByCourseName(const string &searchName);
    /*重载操作符使得 Course类型可以作为 map的 key或 value*/
    bool operator <(const Course& c) const;

};


#endif //ACHIEVEMENTMANAGEMENT_COURSE_H
