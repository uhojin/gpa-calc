#include <iostream>
#include <list>
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

    int getCourseID() {
        return courseID;
    }

    int getCredits() {
        return courseCredit;
    }

    float getGrade() {
        return grade;
    }

};

class Student {
private:
    string name;
    list<Course> courses;

public:
    Student(string n) {
        name = n;
    }

    void addCourse(Course courseItem) {
        courses.push_back(courseItem);
    }

    void deleteCourse(int courseId) {
        for (auto it = courses.begin(); it != courses.end(); it++) {
            if (it -> getCourseID() == courseId) {
                courses.erase(it);
                break;
            }
        }
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
