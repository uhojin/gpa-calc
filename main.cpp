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

    // File 'grades.txt' must exist in the same directory as the program.
    // Each line of the file should contain the course id, grade and credit separated by spaces.
    // Method invoked by student.loadGradesFromFile("grades.txt");
    void loadGradesFromFile(const string &fileName) {
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

    void saveToFile(const string& fileName) {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "Failed to open file" << fileName << endl;
            return;
        }
        file << "Name: " << name << endl;
        file << "Courses: " << endl;
        for (auto& course: courses) {
            file << "Course ID: " << course.getCourseID()
                 << " Credit: " << course.getCredit()
                 << " Grade: " << course.getGrade()
                 << endl;
        }
        double totalGPA = this->calculateGPA();
        file << "Cumulative GPA: " << totalGPA << endl;
        file.close();
    }

    void menu() {
        int choice;
        do {
            cout << endl << "---------------------------------" << endl;
            cout << endl << "-- GPA Calculation Application --" << endl;
            cout << endl << "---------------------------------" << endl;
            cout << "1. Add a course" << endl;
            cout << "2. Delete a course" << endl;
            cout << "3. Modify a course grade" << endl;
            cout << "4. Display courses" << endl;
            cout << "5. Calculate GPA" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice : ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int courseId, grade, credit;
                    cout << "Enter course ID: ";
                    cin >> courseId;
                    cout << "Enter course credit: ";
                    cin >> credit;
                    cout << "Enter course grade: ";
                    cin >> grade;
                    addCourse(Course(courseId, credit, grade));
                    break;
                }
                case 2: {
                    int courseId;
                    cout << "Enter course ID: ";
                    cin >> courseId;
                    deleteCourse(courseId);
                    break;
                }
                case 3: {
                    int courseId, newGrade;
                    cout << "Enter course ID: ";
                    cin >> courseId;
                    cout << "Enter new grade: ";
                    cin >> newGrade;
                    updateCourseGrade(courseId, newGrade);
                    break;
                }
                case 4: {
                    displayCourses();
                    break;
                }
                case 5: {
                    double gpa = calculateGPA();
                    cout << "GPA: " << gpa << endl;
                    break;
                }
                case 6: {
                    break;
                }
                default: {
                    cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                    break;
                }
            }
        } while (choice != 6);
    }
};


int main(int argc, char** argv) {
    char str[MAX_CHAR];
    cout << "Enter Student Name: ";
    fgets(str, MAX_CHAR, stdin);
    //RMN(str);
    cout << str << endl;
    Student *s = new Student(str);
    s -> menu();
    delete s;
    return 0;
}
