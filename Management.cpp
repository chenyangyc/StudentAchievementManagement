//
// Created by Desirelife on 2019/7/30.
//

#include <iostream>
#include <fstream>
#include <cstring>
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
    cin >> s.studentCourses[0].score;
    cout << "Input the algorithm score of the student you want to add: ";
    cin >> s.studentCourses[1].score;
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
}

void Management::alter() {
    char choice;
    Student *student = searchByKeyword();
    if (student != nullptr) {
        cout << "Which course do you want to alter? " << endl;
        cout << "1. math" << endl;
        cout << "2. algorithm" << endl;
        cin >> choice;
        switch (choice){
            case '1':
                cout << "Input the math score: ";
                cin >> student->studentCourses[0].score;
                break;
            case '2':
                cout << "Input the alrorithm score: ";
                cin >> student->studentCourses[1].score;
                break;
            default:
                cout << "Check your choice!" << endl;
        }
        cout << "After altering the score is: " << endl;
        student->display();
        store();
        return;
    }
}

void Management::store() {
    ofstream outfile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!outfile) {
        cout << "No data!" << endl;
        return;
    }
    for (Student student : students) {
        outfile << student.studentId << " " << student.studentName << " " << student.studentCourses[0].score << " " << student.studentCourses[1].score << endl;
    }
    outfile.close();
}

void Management::load() {
    ifstream infile(R"(F:\CLion\CLionProjects\AchievementManagement\StudentsInfo.txt)");
    if (!infile.is_open()) {
        cout << "No data!" << endl;
        return;
    }
    string studentId, studentName;
    Course math, algorithm;
    vector<Course> courses = {math, algorithm};
    while (infile >> studentId >> studentName >> courses[0].score >> courses[1].score) {
        Student student = Student(studentId, studentName, courses);
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

void Management::searchSingleCourseScores() {

}
































