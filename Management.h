//
// Created by Desirelife on 2019/7/30.
//

#ifndef ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
#define ACHIEVEMENTMANAGEMENT_MANAGEMENT_H

#include <vector>
#include "Student.h"

class Management {
protected:
    vector<Student> students;
public:
    Management()= default;
    void addStudent(Student &s);
    void deleteStudents();
    void seek();
    void alter();
    void store();
    void load();
    void play();
};

#endif //ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
