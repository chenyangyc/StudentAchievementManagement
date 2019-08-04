//
// Created by Desirelife on 2019/8/4.
// 对文件的读写操作
//

#ifndef ACHIEVEMENTMANAGEMENT_GENERALMETHODS_H
#define ACHIEVEMENTMANAGEMENT_GENERALMETHODS_H

#include "Student.h"

class ManageFileMethods {
private:
    virtual void storeFile() = 0;   //向文件写入信息并存储
    virtual void loadFile() = 0;    //从文件读出信息
};


#endif //ACHIEVEMENTMANAGEMENT_GENERALMETHODS_H
