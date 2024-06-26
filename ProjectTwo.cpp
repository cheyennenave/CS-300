// ProjectTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//CS-300
//Professor Ling
//Cheyenne Nave
//June 19th, 2024


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

class Course { 
public: //declare house keeping variables
    Course() {}
    Course(string id, string name, vector<string> prereq) : id(id), name(name), prereq(prereq) {}
    string id;
    string name;
    vector<string> prereq;
};

void readFile(vector<string>& lines, string fileName) { //function to open and read file
    ifstream infile;
    infile.open(fileName.c_str()); //converts to c-string
    if (!infile.is_open()) { //error-handling
        cout << "Error while opening " << fileName << endl;
        return;
    }
    lines.clear(); // clear lines vector before reading new file
    string line;
    while (getline(infile, line)) {
        lines.push_back(line); //adds data
    }
    infile.close();
}

void validateFile(vector<string>& lines, vector<Course>& courses) { //function to get and store data
    for (const string& line : lines) { //declare variables
        stringstream ss(line);
        string id, name, prereqStr;
        vector<string> prereq;

        getline(ss, id, ','); //gets data for id and stops at comma
        if (id.empty()) {
            cout << "Error: Missing course ID" << endl; //error handling
            continue;
        }
        getline(ss, name, ',');//gets data for name and stops at comma
        if (name.empty()) {
            cout << "Error: Missing course name" << endl;//error handling
            continue;
        }
        while (getline(ss, prereqStr, ',')) {
            prereq.push_back(prereqStr);//adds prerequisites to prereq vector
        }
        courses.emplace_back(id, name, prereq);
    }
}

void printCourseInfo(const Course& course) { //function to print individual course info
    cout << "Course ID: " << course.id << endl;
    cout << "Course Name: " << course.name << endl;
    cout << "Prerequisites: ";
    if (course.prereq.empty()) {
        cout << "None";
    }
    else {
        for (size_t i = 0; i < course.prereq.size(); ++i) { //parses and prints for correct prerequisite
            cout << course.prereq[i];
            if (i < course.prereq.size() - 1) {
                cout << "; ";
            }
        }
    }
    cout << endl;
}

void printInfo(const vector<Course>& courseInfo, const string& courseId) { //function to use in menu to call printCourseInfo
    for (const auto& course : courseInfo) {
        if (courseId == course.id) {
            printCourseInfo(course);
            return;
        }
    }
    cout << "Invalid Entry" << endl;
}

void printSorts(vector<Course>& courseInfo) { //function to print all courses alphanumerically
    sort(courseInfo.begin(), courseInfo.end(), [](const Course& a, const Course& b) {
        return a.id < b.id; //sorts
        });
    for (const auto& course : courseInfo) {
        cout << course.id << ": " << course.name << endl;
    }
}

int main() {
    string fileName = "input_file.csv"; //house keeping variables
    int menu = 1;
    string courseId;
    string temp;
    vector<string> lines; //vector for lines
    vector<Course> courseInfo; //vector for file

    readFile(lines, fileName);
    validateFile(lines, courseInfo);

    cout << "Welcome to the ABCU Course Planner" << endl;
    cout << "Please select an option below." << endl;

    while (menu != 9) { //creates menu options
        cout << "1. Load Course" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Individual Course" << endl;
        cout << "9. Exit" << endl;
        cin >> menu;
        getline(cin, courseId);

        switch (menu) {
        case 1: //loads courses
            cout << "Case 1: Load Course" << endl;
            readFile(lines, fileName);
            validateFile(lines, courseInfo);
            break;
        case 2: //prints sorted courses
            cout << "Here is a sample schedule: " << endl;
            printSorts(courseInfo);
            break;
        case 3: //prints individual course info
            cout << "Which course would you like to know more about?" << endl;
            getline(cin, courseId);
            printInfo(courseInfo, courseId);
            break;
        case 9: //exits program
            cout << "Thank you for using our service. Goodbye." << endl;
            break;
        default:
            cout << "Invalid Entry. Please enter 1, 2, 3, or 9." << endl;
        }
    }
    return 0;
}


