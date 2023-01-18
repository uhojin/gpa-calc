#include <iostream>
#include <list>
#include <fstream>
#define MAX_CHAR 99

using namespace std;

class Course {
private:
    int courseID;
    int courseCredit;
    int grade;

public:
    Course(int id, int credit, int g) {
        courseID = id;
        courseCredit = credit;
        grade = g;
    }

    int getCourseID() {
        return courseID;
    }

    int getCredit() {
        return courseCredit;
    }

    int getGrade() {
        return grade;
    }

    void setCourseID(int id) {
        courseID = id;
    }

    void setCourseCredit(int credit) {
        courseCredit = credit;
    }

    void setGrade(int g) {
        grade = g;
    }

};

class Student {
private:
    string name;
    list<Course> courses;

public:
    Student(string sName) {
        name = std::move(sName);
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

    void updateCourseGrade(int courseId, int newGrade) {
        for (auto &course : courses) {
            if (course.getCourseID() == courseId) {
                course.setGrade(newGrade);
                break;
            }
        }
    }

    void sortCourses() {
        courses.sort([](Course &a, Course &b) {
            return a.getCourseID() < b.getCourseID();
        });
    }

    void displayCourses() {
        cout << "Courses taken by " << name << ":" << endl;
        for (auto& course : courses) {
            cout << "Course ID: " << course.getCourseID()
                 << "Credit: " << course.getCredit()
                 << "Grade: " << course.getGrade()
                 << endl;
        }
    }

    double calculateGPA() {
        int totalWeightedGrade = 0;
        double totalCredit = 0;
        for (auto& course : courses) {
            int grade = course.getGrade();
            int credit = course.getCredit();
            totalWeightedGrade += grade * credit;
            totalCredit += credit;
        }
        return totalWeightedGrade / totalCredit;
    }

    void loadGradesFromFile(string &fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Failed to open file" << fileName << endl;
            return;
        }
        while (!file.eof()) {
            int courseId, grade, credit;
            file >> courseId >> grade >> credit;
            Course courseItem(courseId, credit, grade);
            courses.push_back(courseItem);
        }
        file.close();
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
