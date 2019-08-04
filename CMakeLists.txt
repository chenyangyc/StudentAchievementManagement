cmake_minimum_required(VERSION 3.14)
project(AchievementManagement)

set(CMAKE_CXX_STANDARD 14)

add_executable(AchievementManagement main.cpp
        Student.cpp Student.h
        Management.cpp Management.h
        Course.cpp Course.h
        ManageStudentMethods.h
        ManageFileMethods.h)