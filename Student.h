//
// Created by Desirelife on 2019/7/30.
//

#ifndef ACHIEVEMENTMANAGEMENT_STUDENT_H
#define ACHIEVEMENTMANAGEMENT_STUDENT_H

#include <string>
using namespace std;

class Student {
public:
    string studentId;
    string studentName;
    string mathScore;
public:
    explicit Student(string studentId = "0", string studentName = "0", string mathScore = "0");
    void setStudent(string studentId, string studentName, string mathScore);
    void setMath(string mathScore)  {this->mathScore = mathScore;}
    bool searchByStudentId(string studentId){return this->studentId == studentId;}
    bool searchByStudentName(string studentName){return this->studentName == studentName;}
    void display();
};


#endif //ACHIEVEMENTMANAGEMENT_STUDENT_H
