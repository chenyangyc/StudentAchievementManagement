//
// Created by Desirelife on 2019/7/30.
//
#include <iostream>
#include <iomanip>
#include "Student.h"
#include "Course.h"

#define ERROR -1;
using namespace std;

Student::Student() {
    //使用builder设计模式来构建对象，因此构造函数不需要具体内容
}

void Student::setWeightedScore() {
    double countingScore = 0;
    for (Course &course: studentCourses) {  //对所有拥有课程进行遍历，得到成绩的对应的学分进行计算
        double weight = course.credit / creditsSum;
        countingScore += course.getScore() * weight;
    }
    this->weightedScore = countingScore;
}

double Student::getWeightedScore() {
    return this->weightedScore;
}

void Student::setCreditsSum() {
    double creditSum = 0;
    for (const Course &course: studentCourses) {    //对所有拥有课程进行遍历，得到对应的学分
        creditSum += course.credit;
    }
    this->creditsSum = creditSum;
}

double Student::getCreditsSum() {
    return this->creditsSum;
}

void Student::setGpa() {
    this->Gpa = 0;
    for (int i = 0; i < studentCourses.size(); i++) {   //对所有拥有课程进行遍历，调用getGpa得到每门课的绩点
        this->Gpa += studentCourses[i].getGpa() * studentCourses[i].credit / creditsSum;    //因为封装了gpa变量，所以调用getGpa
    }
}

double Student::getGpa() {
    return this->Gpa;
}

void Student::addCourseToList(Course &course) {     //向课程列表添加课程
    course.setGpa();
    this->studentCourses.push_back(course);
}

Course *Student::getCourseFromList(int i) {     //从课程列表得到课程
    if (i >= 0 && i < studentCourses.size())
        return &studentCourses[i];
    return nullptr;
}

double Student::getSingleCourseScore(const string &courseName) {    //查询单门课程成绩
    for (Course course: studentCourses) {
        if (course.searchByCourseName(courseName)) {    //searchByCourseName是 Course类的方法
            return course.getScore();
        }
    }
    cout << "没有这门课程，请检查您的关键字拼写" << endl;
    return ERROR
}

bool Student::searchByStudentId(string studentId) {
    return this->studentId == studentId;
}

bool Student::searchByStudentName(string studentName) {
    return this->studentName == studentName;
}

Student *Student::searchStudentByKeyword(const string &searchKeyword) {
    if (searchByStudentId(searchKeyword) || searchByStudentName(searchKeyword)) {
        Student *studentPtr = this;
        return studentPtr;
    }
    return nullptr;
}

Course *Student::getSingleCourse() {        //搜索单门课程并返回指向它的指针
    int choice;
    Course *courseChosen = nullptr;
    cout << "您想要选择哪门课程? " << endl;
    for (int i = 0; i < studentCourses.size(); i++) {
        cout << i + 1 << "." << studentCourses[i].courseName << endl;
    }
    cin >> choice;
    if (choice < 1 || choice > studentCourses.size()) {
        cout << "请检查您的选择" << endl;
        return nullptr;
    }
    courseChosen = &studentCourses[choice - 1];
    return courseChosen;
}

void Student::display() {
    cout << "学生姓名：" << studentName << "\t";
    cout << "学号：" << studentId << endl;
    cout << " 科目" << setw(8) << "学分" << setw(8) << "成绩" << setw(8) << "绩点" << endl;
    for (Course &course: studentCourses) {
        cout << course.courseName << setw(8) << course.credit << setw(8) << course.getScore() << setw(8)
             << course.getGpa() << setw(8) << endl;
    }
    cout << "加权成绩：" << weightedScore << "\t" << "总绩点：" << Gpa << "\t" << "总学分: " << creditsSum << endl;
    cout << endl;
}

void Student::setCourseList(vector<Course> studentCourses) {
    this->studentCourses = studentCourses;
}

vector<Course> Student::getCourseList() {
    return this->studentCourses;
}
