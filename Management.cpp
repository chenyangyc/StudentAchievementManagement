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

Student* judgeReaptedName(vector<Student*> searchResults);

void Management::addStudent() {
    int courseNum;
    string studentId,studentName;
    vector<Course> addCourses;
    cout << "输入您要添加的学生学号: ";
    cin >> studentId;
    for (Student student: students) {
        if (student.searchByStudentId(studentId)) {
            cout << "该学生信息已经存在！" << endl;
            return;
        }
    }
    cout << "输入学生姓名: ";
    cin >> studentName;
    cout << "输入学生的课程数目: ";
    cin >> courseNum;
    for(int i = 0; i < courseNum; i++) {
        cout << "依次输入课程名称，学分和成绩（以空格隔开）: ";
        string courseName;
        double score, credit;
        cin >> courseName >> credit >> score;
        //使用builder设计模式实例化 Course类的对象
        Course course = CourseBuilder()
                .courseName(courseName)
                .credit(credit)
                .score(score)
                .gpa()
                .build();
        addCourses.push_back(course);
        countCourses(course, score);    //统计新加入的课程信息，用以更新该课程年级平均成绩
    }
    //使用builder设计模式实例化 Student类的对象
    Student student = StudentBuilder()
            .courseNum(courseNum)
            .studentId(studentId)
            .studentName(studentName)
            .studentCourses(addCourses)
            .creditsSum()
            .weightedScore()
            .gpa()
            .build();
    students.push_back(student);
    cout << "您添加的学生信息为: " << endl;
    student.display();
    storeFile();        //存储信息
}

/*使用vector来做到学生重名时课展示所有查询结果*/
vector<Student*> Management::searchStudentByKeyword() {
    string searchKeyword;
    cout << "输入您想查询的学生姓名或学号: ";
    cin >> searchKeyword;
    vector<Student*> searchResults;
    for (Student &student: students) {
        Student *studentPtr = student.searchStudentByKeyword(searchKeyword);    //调用Student类的方法进行查询
        if (studentPtr != nullptr) {
            searchResults.push_back(studentPtr);
        }
    }
    if(searchResults.empty()){
        cout << "无该学生，请检查您的关键字拼写" << endl;
    }
    return searchResults;
}

void Management::showSingleStudent() {
    vector<Student*> student = searchStudentByKeyword();        //调用Student类的 searchStudentByKeyword方法进行查询
    if (! student.empty()) {
        cout << "----------您查询的学生信息---------- " << endl;
        cout << endl;
        for(int i = 0; i < student.size(); i++){
            student[i]->display();
        }
        storeFile();
        return;
    }
}

void Management::deleteStudent() {
    string searchKeyword;
    cout << "输入想删除的学生学号或姓名: ";
    cin >> searchKeyword;
    /*此处代码逻辑和searchStudentByKeyword很相似，但由于交互不同不可直接调用*/
    vector<Student*> searchResults;
    Student* studentPtr = nullptr;
    for (Student &student: students) {
        studentPtr = student.searchStudentByKeyword(searchKeyword);    //调用Student类的方法进行查询
        if (studentPtr != nullptr) {
            searchResults.push_back(studentPtr);
        }
    }
    if(searchResults.empty()) {
        cout << "无该学生，请检查您的关键字拼写" << endl;
        return;
    }
    /*对重名做判断*/
    studentPtr = judgeReaptedName(searchResults);
    if(studentPtr == nullptr)   return;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].searchStudentByKeyword(studentPtr->studentId)) {
            students.erase(students.begin() + i);
            cout << "成功删除!" << endl;
            storeFile();
            return;
        }
    }
}

void Management::alterScore() {
    /*调用Student类的 searchStudentByKeyword和 getSingleCourse方法确定要修改的学生和课程*/
    vector<Student*> searchResults = searchStudentByKeyword();
    if(searchResults.empty()) return;

    /*判断学生重名的情况*/
    Student* studentPtr = judgeReaptedName(searchResults);
    if(studentPtr == nullptr)   return;
    /*选中学生后对课程的操作*/
    Course *courseChosen = studentPtr->getSingleCourse();
    if(courseChosen == nullptr)  return;
    cout << "输入新的" << courseChosen->courseName << "成绩: ";
    double score;
    cin >> score;
    /*对课程设置成绩和绩点， 对学生计算加权和绩点*/
    courseChosen->setScore(score);
    courseChosen->setGpa();
    studentPtr->setWeightedScore();
    studentPtr->setGpa();
    cout << "--------修改后的该生信息为----------- " << endl;
    cout << endl;
    studentPtr->display();
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
        if (score == 0)
            continue;
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

void Management::showAllStudents() {
    cout << "----------所有学生成绩统计----------" << endl;
    cout << endl;
    for (Student& student: students) {
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

void Management::storeFile() {
    ofstream outfile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!outfile) {
        cout << "No data!" << endl;
        return;
    }
    for (int i = 0; i < students.size(); i++) {
        outfile << students[i].studentId << " " << students[i].studentName << " " << students[i].courseNum << endl;
        for(int j = 0; j < students[i].courseNum; j++){     //格式化存储格式
            if(i == students.size() - 1){
                if(j == students[i].courseNum - 1){
                    outfile << students[i].getCourseFromList(j)->courseName << " " << students[i].getCourseFromList(j)->credit << " " << students[i].getCourseFromList(j)->getScore();
                }else{
                    outfile << students[i].getCourseFromList(j)->courseName << " " << students[i].getCourseFromList(j)->credit << " " << students[i].getCourseFromList(j)->getScore() << endl;
                }
            } else{
                outfile << students[i].getCourseFromList(j)->courseName << " " << students[i].getCourseFromList(j)->credit << " " << students[i].getCourseFromList(j)->getScore() << endl;
            }
        }

    }
    outfile.close();
}

void Management::loadFile() {
    ifstream infile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!infile.is_open()) {
        cout << "No data!" << endl;
        return;
    }
    int coursesNumbers;
    string studentId, studentName;
    vector<Course> tempCourses;
    courses.clear();
    while(!infile.eof()){
        infile >> studentId >> studentName >> coursesNumbers;
        for(int i = 0; i < coursesNumbers; i++) {
            string courseName;
            double score, credit;
            infile >> courseName >> credit >> score;
            Course course = CourseBuilder()
                    .courseName(courseName)
                    .credit(credit)
                    .score(score)
                    .gpa()
                    .build();
            tempCourses.push_back(course);
            countCourses(course, score);        //统计课程信息用以计算年级平均成绩
        }
        Student student = StudentBuilder()
                .courseNum(coursesNumbers)
                .studentId(studentId)
                .studentName(studentName)
                .studentCourses(tempCourses)
                .creditsSum()
                .weightedScore()
                .gpa()
                .build();
        students.push_back(student);
        tempCourses.clear();
    }
    infile.close();
}

/*对重名的情况根据学号二次判断*/
Student* judgeReaptedName(vector<Student*> searchResults){
    Student* studentPtr;
    if(searchResults.size() > 1){     //判断是否有学生重名
        int choice;
        cout << "您想要选择的学生是？" << endl;
        for(int i = 0; i < searchResults.size(); i++){
            cout << i + 1 << "." << searchResults[i]->studentId << " " << searchResults[i]->studentName << endl;
        }
        cout << "输入您的选择：" ;
        cin >> choice;
        if (choice < 1 || choice > searchResults.size()){     //处理可能出现的输入错误情况，避免数组溢出的报错
            cout << "请检查您的选择是否有误" << endl;
            return nullptr;
        }
        studentPtr = searchResults[choice - 1];      //确定所选择的学生
    } else{
        studentPtr = searchResults[0];
    }
    return studentPtr;
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


