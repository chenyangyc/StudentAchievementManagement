//
// Created by Desirelife on 2019/7/30.
//

#include <iostream>
#include <fstream>
#include "Management.h"
using namespace std;

void Management::addStudent(Student &s) {
    cout << "Input the id of the student you want to add: ";
    cin >> s.studentId;
    for(Student student: students){
        if(student.search(s.studentId)){
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
}

void Management::deleteStudents() {
    string studentId;
    cout << "Input the id of the student you want to delete: ";
    cin >> studentId;
    for(int i = 0; i < students.size(); i++ ){
        if(students[i].search(studentId)){
            students.erase(students.begin() + i);
        }
    }
    cout << "Deleted Successfully!" << endl;
    store();
}

void Management::seek() {
    string studentId;
    cout << "Input the id you want to search: ";
    cin >> studentId;
    for(Student student: students){
        if(student.search(studentId)){
            cout << "The information you are looking for is: " << endl;
            student.display();
            break;
        }
    }
    cout << "No such id." << endl;
}

void Management::alter() {
    string studentId;
    string mathScore;
    cout << "Input the id of the student who needs altering: ";
    cin >> studentId;
    for(Student student: students){
        if(student.search(studentId)){
            cout << "Input the math score: ";
            cin >> mathScore;
            student.mathScore = mathScore;
            cout << "After altering the score is: " << endl;
            student.display();
        }
    }
}

void Management::store() {
    ofstream outfile("StudentsInfo.txt");
    if(! outfile){
        cout << "No data!" << endl;
        return;
    }
    for(Student student : students){
        outfile << student.studentId << " " << student.studentName << " " << student.mathScore << endl;
    }
    outfile.close();
}

void Management::load() {
    ifstream infile("StudentsInfo.txt");
    if(!infile){
        cout << "No data!" << endl;
        return;
    }
    string studentId, studentName, mathScore;
    while(infile >> studentId >> studentName >> mathScore){
        Student student = Student(studentId, studentName, mathScore);
        students.push_back(student);
    }
    infile.close();
}

void Management::play() {
    cout << "ID\t Name\t Math" << endl;
    for(Student student: students){
        student.display();
    }
}
