//
// Created by Desirelife on 2019/8/4.
//

#ifndef ACHIEVEMENTMANAGEMENT_GENERALMETHODS_H
#define ACHIEVEMENTMANAGEMENT_GENERALMETHODS_H

#include "Student.h"

class ManageFileMethods {
private:
    virtual void storeFile() = 0;
    virtual void loadFile() = 0;
};


#endif //ACHIEVEMENTMANAGEMENT_GENERALMETHODS_H
