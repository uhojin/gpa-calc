#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#define MAX_CHAR 20
#define RMN(str) str[strcspn(str,"\n")]=0

using namespace std;

class Course {
private:
    int courseID;
    int courseCredit;
    int grade;

public:
    Course(int id, int credit, int grade) {
        courseID = id;
        courseCredit = credit;
        this->grade = grade;
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
    explicit Student(string sName) {
        name = std::move(sName);
        cout << setprecision(1) << fixed;
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

    static bool compareCourseID(Course &a, Course &b) {
        return a.getCourseID() < b.getCourseID();
    }

    void sortCourses() {
        courses.sort(compareCourseID);
    }

    void displayCourses() {
        cout << "Courses taken by " << name << ":" << endl;
        for (auto& course : courses) {
            cout << "Course ID: " << course.getCourseID()
                 << " Credit: " << course.getCredit()
                 << " Grade: " << course.getGrade()
                 << endl;
        }
    }

    double calculateGPA() {
        double totalWeightedGrade = 0;
        double totalCredit = 0;
        for (auto& course : courses) {
            int grade = course.getGrade();
            int credit = course.getCredit();
            totalWeightedGrade += convertGradeToPoints(grade) * credit;
            totalCredit += credit;
        }
        return totalWeightedGrade / totalCredit;
    }

    static double convertGradeToPoints(int grade) {
        if (grade <= 100 && grade >= 0) {
            if (grade <= 49) {
                return 0.0;
            }
            if (grade <= 54) {
                return 1.0;
            }
            if (grade <= 59) {
                return 1.5;
            }
            if (grade <= 64) {
                return 2.0;
            }
            if (grade <= 69) {
                return 2.5;
            }
            if (grade <= 74) {
                return 3.0;
            }
            if (grade <= 79) {
                return 3.3;
            }
            if (grade <= 84) {
                return 3.6;
            }
            if (grade <= 89) {
                return 3.8;
            }
            return 4.0;
        }
        cout << "Invalid grade. Grades are between 0 and 100" << endl;
        return 0;
    }

    // File 'grades.txt' must exist in the same directory as the program.
    // Each line of the file should contain the course id, grade and credit separated by spaces.
    // Method invoked by student.loadGradesFromFile("grades.txt");
    void loadGradesFromFile(const string &fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Failed to open file " << fileName << endl;
            return;
        }
        while (!file.eof()) {
            int courseId, grade, credit;
            file >> courseId >> grade >> credit;
            Course courseItem(courseId, credit, grade);
            courses.push_back(courseItem);
        }
        file.close();
        cout << "\nGrades loaded." << endl;
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
        double totalGPA = calculateGPA();
        file << setprecision(1) << fixed;
        file << "Cumulative GPA: " << totalGPA << endl;
        file.close();
        cout << "Grades have been saved to GPA.txt" << endl;
    }

    void menu() {
        int choice;
        int index = 0;
        do {
            cout << endl << "---------------------------------";
            cout << endl << "-- GPA Calculation Application --";
            cout << endl << "---------------------------------" << endl;
            cout << ++index << ". Add a course" << endl;
            cout << ++index << ". Delete a course" << endl;
            cout << ++index << ". Modify a course grade" << endl;
            cout << ++index << ". Sort course list" << endl;
            cout << ++index << ". Display courses" << endl;
            cout << ++index << ". Calculate GPA" << endl;
            cout << ++index << ". Load grades from grades.txt" << endl;
            cout << ++index << ". Save student data to GPA.txt" << endl;
            cout << ++index << ". Exit" << endl;
            cout << "Enter your choice : ";
            cin >> choice;
            index = 0;

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
                    sortCourses();
                    break;
                }
                case 5: {
                    displayCourses();
                    break;
                }
                case 6: {
                    double gpa = calculateGPA();
                    cout << "GPA: " << gpa << endl;
                    break;
                }
                case 7: {
                    loadGradesFromFile("grades.txt");
                    break;
                }
                case 8: {
                    saveToFile("GPA.txt");
                    break;
                }
                case 9: {
                    break;
                }
                default: {
                    cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
                    break;
                }
            }
        } while (choice != 9);
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
