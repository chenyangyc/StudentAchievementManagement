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
    Student *student = searchByKeyword();
    Course *courseChosen = chooseCourse(student);
    cout << "Input the " << courseChosen->courseName << " score: ";
    cin >> courseChosen->score;
    getWeightedAchievements();
    cout << "After altering the score is: " << endl;
    student->display();
    store();
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
    string searchKeyword;
    map<double, pair<string, string>> scoreRanking;
    cout << "Which course do you want to query? " << endl;
    cin >> searchKeyword;
    for(const Student& student: students){
        for(Course course: student.studentCourses){
            if(course.searchByCourseName(searchKeyword)){
                scoreRanking.insert(pair<double,pair<string, string>>(course.score, pair<string,string>(student.studentId, student.studentName)));
            }
        }
    }
    cout << "All scores of " << searchKeyword << " is : " << endl;
    for(auto & iter : scoreRanking) {
        cout << iter.second.second << "\t" << iter.second.first << "\t" << iter.first << endl;
    }
}

Course *Management::chooseCourse(Student *student) {
    char choice;
    Course *courseChosen;
    cout << "Which course do you want to choose? " << endl;
    cout << "1. math" << endl;
    cout << "2. algorithm" << endl;
    cin >> choice;
    switch (choice){
        case '1':
            courseChosen = &student->studentCourses[0];
            break;
        case '2':
            courseChosen = &student->studentCourses[1];
            break;
        default:
            cout << "Check your choice!" << endl;
    }
    return courseChosen;
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

void Management::play() {
    cout << "ID" << setw(16) <<  "Name" << setw(12) <<  "Math" << setw(12) << "Algorithm"<< setw(12) << "Weighted Achievements" << setw(12) << endl;
    for (Student student: students) {
        student.display();
    }
}

void Management::getWeightedAchievements() {
    for(Student &student: students){
        double weightedScore = 0;
        double creditSum = 0;
        for(const Course& course: student.studentCourses){
            creditSum += course.credit;
        }
        for(const Course& course: student.studentCourses){
            double weights = course.credit / creditSum;
            weightedScore += course.score * weights;
        }
        student.weightedScore = weightedScore;
        student.display();
    }
    store();
}































