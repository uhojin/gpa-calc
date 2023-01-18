#include <iostream>
#define MAX_CHAR 99

using namespace std;

class Course {
private:
    int courseID;
    int courseCredit;
    float grade;

public:
    Course(int id, int credit, float g) {
        courseID = id;
        courseCredit = credit;
        grade = g;
    }

    int getCredits() {
        return courseCredit;
    }

    float getGrade() {
        return grade;
    }

};


int main(int argc, char** argv) {
    char str[MAX_CHAR];
    cout << "Enter Student Name: ";
    fgets(str, MAX_CHAR, stdin);
    RMN(str);
    cout << str << endl;
    Student *s = new Student(str);
    s -> menu();
    delete s;
    return 0;
}
