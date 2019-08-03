//
// Created by Desirelife on 2019/7/30.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <map>
#include "Management.h"

using namespace std;

void Management::addStudent() {
    Student s;
    cout << "Input the id of the student you want to add: ";
    cin >> s.studentId;
    for (Student student: students) {
        if (student.searchByStudentId(s.studentId)) {
            cout << "This has been added before!" << endl;
            return;
        }
    }
    cout << "Input the name of the student you want to add: ";
    cin >> s.studentName;
    cout << "Input the math score of the student you want to add: ";
    cin >> s.math.score;
    cout << "Input the algorithm score of the student you want to add: ";
    cin >> s.algorithm.score;
    s.studentCourses = {s.math, s.algorithm};
    students.push_back(s);
    cout << "The information of the student you added: " << endl;
    s.display();
    store();
}

Student *Management::searchStudentByKeyword() {
    string searchKeyword;
    cout << "Input the id or name of the student you want to deal with: ";
    cin >> searchKeyword;
    for (Student &student: students) {
        Student* studentPtr = student.searchStudentByKeyword(searchKeyword);
        if(studentPtr != nullptr)   return studentPtr;
    }
    return nullptr;
}

void Management::showSingleStudent() {
    Student *student = searchStudentByKeyword();
    if(student != nullptr){
        cout << "The information you are looking for is: " << endl;
        student->display();
        store();
        return;
    }
}

void Management::deleteStudent() {
    string searchKeyword;
    cout << "Input the id or name of the student you want to delete: ";
    cin >> searchKeyword;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].searchStudentByKeyword(searchKeyword)) {
            students.erase(students.begin() + i);
            cout << "Deleted Successfully!" << endl;
            store();
            return;
        }
    }
    cout << "No such student! Check your keyword!" << endl;
}

void Management::alterScore() {
    Student *student = searchStudentByKeyword();
    Course *courseChosen = student->getSingleCourse();
    cout << "Input the " << courseChosen->courseName << " score: ";
    cin >> courseChosen->score;
    getWeightedAchievements();
    cout << "After altering the score is: " << endl;
    student->display();
    store();
}

void Management::showSingleCourseScores() {
    string searchKeyword;
    cout << "Which course do you want to query? " << endl;
    cin >> searchKeyword;
    map<double, pair<string, string>> scoreRanking;
    for(Student student: students){
        double score = student.getSingleCourseScore(searchKeyword);
        scoreRanking.insert(pair<double,pair<string, string>>(score, pair<string,string>(student.studentId, student.studentName)));
    }
    cout << "All scores of " << searchKeyword << " is : " << endl;
    for(auto & iter : scoreRanking) {
        cout << iter.second.second << "\t" << iter.second.first << "\t" << iter.first << endl;
    }
}

void Management::getWeightedAchievements() {
    for(Student &student: students){
        student.countWeightedScore();
        student.display();
    }
    store();
}

void Management::store() {
    ofstream outfile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!outfile) {
        cout << "No data!" << endl;
        return;
    }
    for (Student student : students) {
        outfile << student.studentId << " " << student.studentName << " "
        << student.studentCourses[0].score << " " << student.studentCourses[1].score
        << " " << student.weightedScore <<endl;
    }
    outfile.close();
}

void Management::load() {
    Student s;
    ifstream infile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!infile.is_open()) {
        cout << "No data!" << endl;
        return;
    }
    double weightedScore;
    string studentId, studentName;
    vector<Course> courses = {s.math, s.algorithm};
    while (infile >> studentId >> studentName >> courses[0].score >> courses[1].score >> weightedScore) {
        Student student = Student(studentId, studentName, courses, weightedScore);
        students.push_back(student);
    }
    infile.close();
}

void Management::showAllStudents() {
    cout << "ID" << setw(16) <<  "Name" << setw(12) <<  "Math" << setw(12) << "Algorithm"<< setw(12) << "Weighted Achievements" << setw(12) << endl;
    for (Student student: students) {
        student.display();
    }
}

































