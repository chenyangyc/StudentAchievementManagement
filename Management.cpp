//
// Created by Desirelife on 2019/7/30.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <map>
#include <algorithm>
#include <io.h>
#include "Management.h"

using namespace std;

void Management::addStudent() {
    Student s;
    Course course;
    cout << "输入您要添加的学生学号: ";
    cin >> s.studentId;
    for (Student student: students) {
        if (student.searchByStudentId(s.studentId)) {
            cout << "该学生信息已经存在！" << endl;
            return;
        }
    }
    cout << "输入学生姓名: ";
    cin >> s.studentName;
    cout << "输入学生的课程数目: ";
    cin >> s.courseNum;
    for(int i = 0; i < s.courseNum; i++) {
        cout << "依次输入课程名称，学分和成绩（以空格隔开）: ";
        double score;
        cin >> course.courseName >> course.credit >> score;
        course.setScore(score);
        s.addCourseToList(course);
        if(courses.find(course.courseName) == courses.end()){
            courses[course.courseName] = course;
            courses[course.courseName].num = 1;
            courses[course.courseName].gpaSum = course.getGpa();
        } else {
            score += courses[course.courseName].getScore();
            courses[course.courseName].setScore(score);
            courses[course.courseName].num++;
            courses[course.courseName].gpaSum += course.getGpa();
        }
    }
    s.setCreditsSum();
    s.setWeightedScore();
    s.setGpa();
    students.push_back(s);
    cout << "您添加的学生信息为: " << endl;
    s.display();
    storeFile();
}

Student *Management::searchStudentByKeyword() {
    string searchKeyword;
    cout << "输入您想查询的学生姓名或学号: ";
    cin >> searchKeyword;
    for (Student &student: students) {
        Student *studentPtr = student.searchStudentByKeyword(searchKeyword);
        if (studentPtr != nullptr) return studentPtr;
    }
    cout << "无该学生，请检查您的关键字拼写" << endl;
    return nullptr;
}

void Management::showSingleStudent() {
    Student *student = searchStudentByKeyword();
    if (student != nullptr) {
        cout << "----------您查询的学生信息---------- " << endl;
        cout << endl;
        student->display();
        storeFile();
        return;
    }
}

void Management::deleteStudent() {
    string searchKeyword;
    cout << "输入想删除的学生学号或姓名: ";
    cin >> searchKeyword;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].searchStudentByKeyword(searchKeyword)) {
            students.erase(students.begin() + i);
            cout << "成功删除!" << endl;
            storeFile();
            return;
        }
    }
    cout << "没有此学生! 检查搜索关键词!" << endl;
}

void Management::alterScore() {
    Student *student = searchStudentByKeyword();
    if(student == nullptr)  return;
    Course *courseChosen = student->getSingleCourse();
    if(courseChosen == nullptr)  return;
    cout << "输入新的" << courseChosen->courseName << "成绩: ";
    double score;
    cin >> score;
    courseChosen->setScore(score);
    courseChosen->setGpa();
    student->setWeightedScore();
    student->setGpa();
    cout << "修改后的该生信息为: " << endl;
    student->display();
    storeFile();
}

bool cmp(Student &a, Student &b) {
    double aws = a.getWeightedScore();
    double bws = b.getWeightedScore();
    return aws > bws;
}

bool singleCmp(pair<pair<string, string>, double> &a, pair<pair<string, string>, double> &b) {
    return a.second > b.second;
}

void Management::getRankingBySingleCourseScore() {
    string searchKeyword;
    cout << "输入您想查询的课程名称：";
    cin >> searchKeyword;
    map<pair<string, string>, double> scores;
    vector<pair<pair<string, string>, double>> sortedScores;
    for (Student &student: students) {
        double score = student.getSingleCourseScore(searchKeyword);
        if (score == -1)
            return;
        scores.insert(pair<pair<string, string>, double>(pair<string, string>(student.studentId, student.studentName),
                                                         score));
        sortedScores.emplace_back(pair<string, string>(student.studentId, student.studentName),
                                  score);
    }
    sort(sortedScores.begin(), sortedScores.end(), singleCmp);
    cout << "----------" << searchKeyword << "的成绩排名----------" << endl;
    cout << endl;
    cout << "学号\t" << "姓名\t" << "成绩\t" << endl;
    for (auto &iter : sortedScores) {
        cout << iter.first.first << "\t" << iter.first.second << "\t" << iter.second << endl;
    }
}

void Management::getRankingByWeightedScore() {
    vector<Student> sortedStudents;
    for (Student &student: students) {
        student.setWeightedScore();
        student.setGpa();
        sortedStudents.push_back(student);
    }
    sort(sortedStudents.begin(), sortedStudents.end(), cmp);
    cout << "----------加权成绩排名----------" << endl;
    cout << endl;
    cout << "学号\t" << "姓名\t" << "加权成绩\t" << "平均绩点" << endl;
    for (auto &student: sortedStudents) {
        cout << student.studentId << "\t" << student.studentName << "\t" << student.getWeightedScore() << "\t" << student.getGpa() << endl;
    }
    storeFile();
}

void Management::storeFile() {
    ofstream outfile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!outfile) {
        cout << "No data!" << endl;
        return;
    }
    for (int i = 0; i < students.size(); i++) {
        outfile << students[i].studentId << " " << students[i].studentName << " " << students[i].courseNum << " ";
        for(int j = 0; j < students[i].courseNum; j++){
            outfile << students[i].getCourseFromList(j)->courseName << " " << students[i].getCourseFromList(j)->credit << " " << students[i].getCourseFromList(j)->getScore() << " ";
        }
        if(i == students.size() - 1){
            outfile << students[i].getWeightedScore() << " " << students[i].getCreditsSum();
        } else{
            outfile << students[i].getWeightedScore() << " " << students[i].getCreditsSum() << endl;
        }
    }
    outfile.close();
}

void Management::loadFile() {
    Student s;
    ifstream infile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!infile.is_open()) {
        cout << "No data!" << endl;
        return;
    }
    int coursesNumbers;
    double weightedScore,creditSum;
    string studentId, studentName;
    Course course;
    vector<Course> tempCourses;

    while(!infile.eof()){
        infile >> studentId >> studentName >> coursesNumbers;
        for(int i = 0; i < coursesNumbers; i++) {
            double score;
            infile >> course.courseName >> course.credit >> score;
            course.setScore(score);
            course.setGpa();
            tempCourses.push_back(course);
            if(courses.find(course.courseName) == courses.end()){
                courses[course.courseName] = course;
                courses[course.courseName].num = 1;
                courses[course.courseName].gpaSum = course.getGpa();
            } else {
                score += courses[course.courseName].getScore();
                courses[course.courseName].setScore(score);
                courses[course.courseName].num++;
                courses[course.courseName].gpaSum += course.getGpa();
            }
        }
        infile >> weightedScore >> creditSum;
        Student student = Student(coursesNumbers, studentId, studentName, tempCourses, weightedScore, creditSum);
        students.push_back(student);
        tempCourses.clear();
    }
    infile.close();
}

void Management::showAllStudents() {
    cout << "----------所有学生成绩统计----------" << endl;
    cout << endl;
    for (Student& student: students) {
        student.setGpa();
        student.display();
    }
}

void Management::showAllCourses() {
    cout << "----------所有科目信息统计----------" << endl;
    cout << endl;
    map<string, Course>::iterator iter;
    for (iter = courses.begin(); iter != courses.end(); iter++) {
        double averageScore = iter->second.getScore() / iter->second.num;
        iter->second.setScore(averageScore);
        cout << "科目名称：" << iter->first << "\t" << "科目学分：" << iter->second.credit << endl;
        cout << "年纪平均成绩: " << averageScore << "\t";
        cout << "年级平均绩点：" << iter->second.gpaSum / iter->second.num << endl;
        cout << endl;
    }
}
