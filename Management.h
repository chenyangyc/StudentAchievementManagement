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
    void addStudent();
    Student* searchStudentByKeyword();
    void showSingleStudent();
    void deleteStudent();
    void alterScore();
    void showSingleCourseScores();
    void getWeightedAchievements();
    void getRankingByWeightedScore();
    void storeFile();
    void loadFile();
    void showAllStudents();
};

#endif //ACHIEVEMENTMANAGEMENT_MANAGEMENT_H
