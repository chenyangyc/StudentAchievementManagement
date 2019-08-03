//
// Created by Desirelife on 2019/7/30.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <map>
#include <algorithm>
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
    s.studentCourses.push_back(s.math);
    s.studentCourses.push_back(s.algorithm);
    s.countWeightedScore();
    students.push_back(s);
    cout << "The information of the student you added: " << endl;
    s.display();
    storeFile();
}

Student *Management::searchStudentByKeyword() {
    string searchKeyword;
    cout << "Input the id or name of the student you want to deal with: ";
    cin >> searchKeyword;
    for (Student &student: students) {
        Student *studentPtr = student.searchStudentByKeyword(searchKeyword);
        if (studentPtr != nullptr) return studentPtr;
    }
    cout << "No result. Please check your keyword spelling." << endl;
    return nullptr;
}

void Management::showSingleStudent() {
    Student *student = searchStudentByKeyword();
    if (student != nullptr) {
        cout << "The information you are looking for is: " << endl;
        student->display();
        storeFile();
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
            storeFile();
            return;
        }
    }
    cout << "No such student! Check your keyword!" << endl;
}

void Management::alterScore() {
    Student *student = searchStudentByKeyword();
    if(student == nullptr)  return;
    Course *courseChosen = student->getSingleCourse();
    if(courseChosen == nullptr)  return;
    cout << "Input the " << courseChosen->courseName << " score: ";
    cin >> courseChosen->score;
    student->countWeightedScore();
    cout << "After altering the score is: " << endl;
    student->display();
    storeFile();
}

bool cmp(const Student &a, const Student &b) {
    return a.weightedScore > b.weightedScore;
}

bool singleCmp(pair<pair<string, string>, double> &a, pair<pair<string, string>, double> &b) {
    return a.second > b.second;
}

void Management::getRankingBySingleCourseScore() {
    string searchKeyword;
    cout << "Which course do you want to enqury?" << endl;
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
    cout << "All scores of " << searchKeyword << " is : " << endl;
    for (auto &iter : sortedScores) {
        cout << iter.first.first << "\t" << iter.first.second << "\t" << iter.second << endl;
    }
}

void Management::getRankingByWeightedScore() {
    vector<Student> sortedStudents;
    for (const Student &student: students) {
        sortedStudents.push_back(student);
    }
    sort(sortedStudents.begin(), sortedStudents.end(), cmp);
    for (auto &student: sortedStudents) {
        cout << student.studentId << "\t" << student.studentName << "\t" << student.weightedScore << endl;
    }
}


void Management::storeFile() {
    ofstream outfile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!outfile) {
        cout << "No data!" << endl;
        return;
    }
    for (Student student : students) {
        outfile << student.studentId << " " << student.studentName << " "
                << student.studentCourses[0].score << " " << student.studentCourses[1].score
                << " " << student.weightedScore << endl;
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
    cout << "ID" << setw(12) << "Name" << setw(8) << "Math" << setw(10) << "Algorithm" << setw(8) << "Weighted Achievements" << setw(30) << endl;
    for (Student student: students) {
        student.display();
    }
}


