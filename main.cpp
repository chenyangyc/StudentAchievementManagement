#include <iostream>
#include "Student.h"
#include "Management.h"
using namespace std;

int main()
{
    //TODO: quite a lot of work
    Management management;
    management.loadFile();
    int n = 1000;
    char choice;
    string mathScore;
    while(n--){
        cout << "1. 添加学生" << endl;
        cout << "2. 展示所有学生的信息" << endl;
        cout << "3. 通过姓名或学号查询学生信息" << endl;
        cout << "4. 通过姓名或学号删除学生信息" << endl;
        cout << "5. 修改某学生成绩" << endl;
        cout << "6. 单科成绩排名" << endl;
        cout << "7. 加权成绩排名" << endl;
        cout << "0. 安全退出" << endl;
        cout << "请输入您的选择: ";
        choice = getchar();
        switch (choice){
            case '1':
                management.addStudent();
                break;
            case '2':
                management.showAllStudents();
                break;
            case '3':
                management.showSingleStudent();
                break;
            case '4':
                management.deleteStudent();
                break;
            case '5':
                management.alterScore();
                break;
            case '6':
                management.getRankingBySingleCourseScore();
                break;
            case '7':
                management.getRankingByWeightedScore();
                break;
            case '0':
                management.storeFile();
                return 0;
            default:
                continue;
        }
        cout << endl;
        cout << "----------Press Enter to Continue----------" << endl;
        getchar();
    }
    return 0;
}
