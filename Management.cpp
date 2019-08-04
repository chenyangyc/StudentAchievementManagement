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
        countCourses(course, score);
//        if(courses.find(course.courseName) == courses.end()){
//            courses[course.courseName] = course;
//            courses[course.courseName].num = 1;
//            courses[course.courseName].gpaSum = course.getGpa();
//        } else {
//            score += courses[course.courseName].getScore();
//            courses[course.courseName].setScore(score);
//            courses[course.courseName].num++;
//            courses[course.courseName].gpaSum += course.getGpa();
//        }
    }
    s.setCreditsSum();      //计算总学分
    s.setWeightedScore();       //计算加权成绩
    s.setGpa();         //计算平均绩点
    students.push_back(s);
    cout << "您添加的学生信息为: " << endl;
    s.display();
    storeFile();        //存储信息
}

Student *Management::searchStudentByKeyword() {
    string searchKeyword;
    cout << "输入您想查询的学生姓名或学号: ";
    cin >> searchKeyword;
    for (Student &student: students) {
        Student *studentPtr = student.searchStudentByKeyword(searchKeyword);    //调用Student类的方法进行查询
        if (studentPtr != nullptr) return studentPtr;
    }
    cout << "无该学生，请检查您的关键字拼写" << endl;
    return nullptr;
}

void Management::showSingleStudent() {
    Student *student = searchStudentByKeyword();        //调用Student类的 searchStudentByKeyword方法进行查询
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
    /*调用Student类的 searchStudentByKeyword和 getSingleCourse方法确定要修改的学生和课程*/
    Student *student = searchStudentByKeyword();
    if(student == nullptr)  return;
    Course *courseChosen = student->getSingleCourse();
    if(courseChosen == nullptr)  return;
    cout << "输入新的" << courseChosen->courseName << "成绩: ";
    double score;
    cin >> score;
    /*对课程设置成绩和绩点， 对学生计算加权和绩点*/
    courseChosen->setScore(score);
    courseChosen->setGpa();
    student->setWeightedScore();
    student->setGpa();
    cout << "修改后的该生信息为: " << endl;
    student->display();
    storeFile();
}

/**
 * cmp 和 singleCmp为对成绩排序时的辅助方法，用来重写 sort函数，由于不需要访问成员变量，未在.h中声明
 */
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
    map<pair<string, string>, double> scores;       //利用map和pair实现三元组存储课程和学生信息
    vector<pair<pair<string, string>, double>> sortedScores;    //利用vector并重写sort函数进行排序
    /*遍历学生列表获取成绩信息*/
    for (Student &student: students) {
        double score = student.getSingleCourseScore(searchKeyword);
        if (score == -1)
            return;
        scores.insert(pair<pair<string, string>, double>(pair<string, string>(student.studentId, student.studentName),
                                                         score));
        sortedScores.emplace_back(pair<string, string>(student.studentId, student.studentName),
                                  score);
    }
    sort(sortedScores.begin(), sortedScores.end(), singleCmp);      //sort进行排序
    //输出排序结果
    cout << "----------" << searchKeyword << "的成绩排名----------" << endl;
    cout << endl;
    cout << "学号\t" << "姓名\t" << "成绩\t" << endl;
    for (auto &iter : sortedScores) {       //利用迭代器进行遍历
        cout << iter.first.first << "\t" << iter.first.second << "\t" << iter.second << endl;
    }
}

void Management::getRankingByWeightedScore() {
    vector<Student> sortedStudents;
    for (Student &student: students) {      //遍历获取成绩信息
        student.setWeightedScore();
        student.setGpa();
        sortedStudents.push_back(student);
    }
    sort(sortedStudents.begin(), sortedStudents.end(), cmp);        //重写sort进行排序
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
            countCourses(course, score);
//            if(courses.find(course.courseName) == courses.end()){
//                courses[course.courseName] = course;
//                courses[course.courseName].num = 1;
//                courses[course.courseName].gpaSum = course.getGpa();
//            } else {
//                score += courses[course.courseName].getScore();
//                courses[course.courseName].setScore(score);
//                courses[course.courseName].num++;
//                courses[course.courseName].gpaSum += course.getGpa();
//            }
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

/*将每门出现的课程信息加入到统计所有课程信息的 map中*/
void Management::countCourses(Course course, double score){
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


