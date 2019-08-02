//
// Created by Desirelife on 2019/7/30.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include "Management.h"

using namespace std;

void Management::addStudent(Student &s) {
    cout << "Input the id of the student you want to add: ";
    cin >> s.studentId;
    cout << "heha" << endl;
    for (Student student: students) {
        if (student.searchByStudentId(s.studentId)) {
            cout << "This has been added before!" << endl;
            return;
        }
    }
    cout << "Input the name of the student you want to add: ";
    cin >> s.studentName;
    cout << "Input the math score of the student you want to add: ";
    cin >> s.mathScore;
    students.push_back(s);
    cout << "The information of the student you added: " << endl;
    s.display();
    store();
}

void Management::deleteStudents() {
    string mathScore;
    string searchKeyword;
    cout << "Input the id or name of the student you want to delete: ";
    cin >> searchKeyword;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].searchByStudentId(searchKeyword) || students[i].searchByStudentName(searchKeyword)) {
            students.erase(students.begin() + i);
            cout << "Deleted Successfully!" << endl;
            store();
            return;
        }
    }
    cout << "No such student! Check your keyword!" << endl;
}


void Management::searchStudents() {
    string mathScore;
    Student *student = searchByKeyword();
    if(student != nullptr){
        cout << "The information you are looking for is: " << endl;
        student->display();
        store();
        return;
    }
//    string searchKeyword;
//    cout << "Input the id or name you want to search: ";
//    cin >> searchKeyword;
//    for (Student &student: students) {
//        if (student.searchByStudentId(searchKeyword) || student.searchByStudentName(searchKeyword)) {
//            cout << "The information you are looking for is: " << endl;
//            student.display();
//            store();
//            return;
//        }
//    }
//    cout << "No such student! Check your keyword!" << endl;
}

void Management::alter() {
    string mathScore;
    Student *student = searchByKeyword();
    if (student != nullptr) {
        cout << "Input the math score: ";
        cin >> mathScore;
        student->mathScore = mathScore;
        cout << "After altering the score is: " << endl;
        student->display();
        store();
        return;
    }
//    string searchKeyword;
//    cout << "Input the id or name of the student you want to alter: ";
//    cin >> searchKeyword;
//    for(Student& student: students) {
//        if (student.searchByStudentId(searchKeyword) || student.searchByStudentName(searchKeyword)) {
//            cout << "Input the math score: ";
//            cin >> mathScore;
//            student.mathScore = mathScore;
//            cout << "After altering the score is: " << endl;
//            student.display();
//            store();
//            return;
//        }
//    }
//    cout << "No such student! Check your keyword!" << endl;
}

void Management::store() {
    ofstream outfile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!outfile) {
        cout << "No data!" << endl;
        return;
    }
    for (Student student : students) {
        outfile << student.studentId << " " << student.studentName << " " << student.mathScore << endl;
    }
    outfile.close();
}

void Management::load() {
    ifstream infile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!infile.is_open()) {
        cout << "No data!" << endl;
        return;
    }
    string studentId, studentName, mathScore;
    while (infile >> studentId >> studentName >> mathScore) {
        Student student = Student(studentId, studentName, mathScore);
        students.push_back(student);
    }
    infile.close();
}

void Management::play() {
    cout << "ID\t\t Name\t\t Math" << endl;
    for (Student student: students) {
        student.display();
    }
}

Student *Management::searchByKeyword() {
    string searchKeyword;
    cout << "Input the id or name of the student you want to deal with: ";
    cin >> searchKeyword;
    for (Student &student: students) {
        if (student.searchByStudentId(searchKeyword) || student.searchByStudentName(searchKeyword)) {
            Student *studentPtr = &student;
            return studentPtr;
        }
    }
    cout << "No such student! Check your keyword!" << endl;
    return nullptr;
}
































