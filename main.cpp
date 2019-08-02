#include <iostream>
#include "Student.h"
#include "Management.h"
using namespace std;

int main()
{
    //TODO: quite a lot of work
    Management management;
    management.load();
    int n = 1000;
    char choice;
    string mathScore;
    while(n--){
        cout << "1. Add students" << endl;
        cout << "2. Show All Students' Information" << endl;
        cout << "3. Search Students by Id or Name" << endl;
        cout << "4. Delete Students by Id or Name" << endl;
        cout << "5. Alter Scores" << endl;
        cout << "6. Single Course Ranking" << endl;
        cout << "7. Get Weighted Scores" << endl;
        cout << "0. Exit" << endl;
        cout << "Input your choice: ";
        choice = getchar();
        switch (choice){
            case '1':
                management.addStudent();
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
            case '6':
                management.searchSingleCourseScores();
                break;
            case '7':
                management.getWeightedAchievements();
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
