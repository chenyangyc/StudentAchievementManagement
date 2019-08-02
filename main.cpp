#include <iostream>
#include "Student.h"
#include "Management.h"
using namespace std;

int main()
{
    //TODO: quite a lot of work
    Student student;
    Management management;
    management.load();
    int n = 1000;
    char choice;
    string mathScore;
    while(n--){
        cout << "1. Add students" << endl;
        cout << "2. Show Information" << endl;
        cout << "3. Search Students by Id or Name" << endl;
        cout << "4. Delete according to the id" << endl;
        cout << "5. Alter according to the id" << endl;
        cout << "0. Exit" << endl;
        cout << "Input your choice: ";
        choice = getchar();
        switch (choice){
            case '1':
                management.addStudent(student);
                break;
            case '2':
                management.play();
                break;
            case '3':
                management.searchStudents();
                break;
            case '4':
                management.deleteStudents();
                break;
            case '5':
                management.alter();
                break;
            case '0':
                management.store();
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
