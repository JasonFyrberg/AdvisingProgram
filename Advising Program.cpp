// Jason Fyrberg
// CS300 Project Two: Course Planner

#include <iostream> 
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// define class Course with its details
class Course {
public:
    string courseNumber;
    string courseTitle;
    vector<string> prereqs;
};

// print course info
void printCourse(const vector<Course> &courses, const string &courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&courseNumber](const Course &course) {
        return course.courseNumber == courseNumber;
    });

    if (it != courses.end()) {
        cout << "Course Title: " << it->courseTitle << endl;
        cout << "Course Number: " << it->courseNumber << endl;
        cout << "Prerequisites: ";
        for (const auto &prereq : it->prereqs) {
            cout << prereq << " ";
        }
        cout << endl;
    } else {

        cout << "Course not in directory." << endl;
    }
}

// sort courses in alphanumerical order
bool sortCourses(const Course &a, const Course &b) {
    string courseNumA = a.courseNumber;
    string courseNumB = b.courseNumber;

    return courseNumA < courseNumB;
}

// print course list 
void printCourseList(const vector<Course> &courses) {
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), sortCourses);

    cout << "Course List:" << endl;
    for (const auto &course : sortedCourses) {
        cout << course.courseNumber << " : " << course.courseTitle << endl;
    }
}

// load data from file into data structure
void LoadDataStruct(const string &fileName, vector<Course> &courses) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file!" << endl;
        return;

    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string courseNumber, courseTitle, prereq;
        getline(iss, courseNumber, ',');
        getline(iss, courseTitle, ',');
        
        Course newCourse;
        newCourse.courseNumber = courseNumber;
        newCourse.courseTitle = courseTitle;

        while (getline(iss, prereq, ',')) {
            newCourse.prereqs.push_back(prereq);
            
        }

        courses.push_back(newCourse);
    }

    file.close();
}

// main function
int main() {
    vector<Course> courses;
    string fileName;
    int menu_choice = 0;

    while (menu_choice != 4) {
        cout << "How can I help you? " << endl;
        cout << "1.) Load Data Structure" << endl;
        cout << "2.) Print Course List" << endl;
        cout << "3.) Print Course" << endl;

        // Exit is option 9 to allow for growth of program

        cout << "9.) Exit" << endl;
        cin >> menu_choice;

        switch (menu_choice) {

            case 1: {
                cout << "Enter name of file: ";
                cin >> fileName;
                LoadDataStruct(fileName, courses);
                break;
            }

            case 2: {
                printCourseList(courses);
                break;
            }

            case 3: {
                string courseNumber;
                cout << "Enter the course number: ";
                cin >> courseNumber;
                printCourse(courses, courseNumber);
                break;
            }

            case 9: {
                cout << "Thank you for using the course planner!" << endl;
                return 0;

            }

            default: {

                cout << menu_choice << " is not a valid option. \n" << endl;

            }
        }
    }

    return 0;
}
