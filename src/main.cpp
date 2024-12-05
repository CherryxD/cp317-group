#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <map>

using namespace std;

int validate_id(int id) {
    int status = 0;
    // Check that student id is strictly 9 digits 
    if (id / 100000000 >= 10 || id / 100000000 <= 0) {
        cout << "Student ID: " << id << endl;
        status = 1;
    }
    return status;
}

// string tokenizer
vector<string> split(string s, string delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        if (pos != 0) {
            token = s.substr(0, pos);
            tokens.push_back(token);
        }
        s.erase(0, (pos + delimiter.length()));
    }
    tokens.push_back(s);

    return tokens;
}

class Course {
    public:
        Course() { // default constructor if any null values are attempted to be loaded;
            test1 = 0.0;
            test2 = 0.0;
            test3 = 0.0;
            exam = 0.0;
            code = "";
            s_id = 0;
            avg = 0.0;
        }
        Course(float x, float y, float z, float f, string c, int i) { // actual constructor
            test1 = x;
            test2 = y;
            test3 = z;
            exam = f;
            code = c;
            s_id = i;
            avg = calculateFinalGrade(x, y, z, f);
        }
        float avg;
        string code;
        int s_id;
	// show error number if invalid data is given
        int validate() {
	    int status = validate_id(s_id);
            if (isdigit(code.at(2)) == 0) {
                // print erroneous course code
                cout << "Course Code was: " << code << endl;
                status = 2;
            }
            else if (test1 < 0 || test2 < 0 || test3 < 0 || exam < 0) {
                // print possibly erroneous grades
                cout << "Marks: Test 1 " << test1 << ", Test 2 " << test2 << ", Test 3" << test3 << ", Final Exam " << exam << endl;
                status = 3;
            }
            return status;
        }
    private:
        // these don't need to be interacted with once loaded
        float test1;
        float test2;
        float test3;
        float exam;
        float calculateFinalGrade(float a, float b, float c, float f) {
            float grade = 0.0;
            grade = (a * 0.2) + (b * 0.2) + (c * 0.2) + (f * 0.4);
            return grade;
        }
};

// Print error depending on error code is given
string errorHandling(int code) {
    string msg;
    /* 
    1 - invalid id;
    2 - invalid course code;
    3 - invalid grades;
    4 - invalid name;
    */
    switch(code) {
        case 1:
        msg = "There was an invalid ID loaded";
        break;
        case 2:
        msg = "There was an invalid course code loaded";
        break;
        case 3:
        msg = "There was an invalid grade loaded";
        break;
        case 4:
        msg = "There was an invalid student name loaded";
        break;
        case 5:
        msg = "There was an invalid number of inputs loaded";
        break;
    }
    return msg;
}

// Compare student ids from within course object
bool compareSID(Course c1, Course c2) {
    return (c1.s_id < c2.s_id);
}

// Load courses from file
vector<Course> loadCourses(string filepath) {
    ifstream courseFile(filepath);
    vector<Course> courses;
    string txt;
    while (getline(courseFile, txt)) {
        int status;
        string c_code;
        int s_id;
        float t1; float t2; float t3; float f;
        vector<string> tokens = split(txt, ", ");
        if (tokens.size() == 6) {
            s_id = stoi(tokens.at(0));
            c_code = tokens.at(1);
            t1 = stof(tokens.at(2));
            t2 = stof(tokens.at(3));
            t3 = stof(tokens.at(4));
            f = stof(tokens.at(5));
            // Load data from line into object
            Course course(t1, t2, t3, f, c_code, s_id);
            // Validate course has correct information
            status = course.validate();
            if (status != 0) {
                cout << errorHandling(status) << endl;
            }
            else { // If course info is valid, add to list of courses
                courses.push_back(course);
            }
        }
        else {
            // print error about invalid number of inputs
            cout << tokens.size() << " inputs were loaded, expected 6" << endl;
            cout << errorHandling(5) << endl;
        }
    }
    courseFile.close(); // close courseFile
    return courses;
}

map<int, string> loadStudents(string filepath) {
    ifstream nameFile(filepath);
    string txt;
    map<int, string> students;
    while (getline(nameFile, txt)) {
        //cout << txt << endl;
        string s_name;
        int id;
        vector<string> tokens = split(txt, ", ");
        if (tokens.size() == 2) {
            id = stoi(tokens.at(0));
            s_name = tokens.at(1);
            int status = validate_id(id);
            if (status != 0) { // Print error according to error code
                cout << errorHandling(status) << endl;
            }
            else { // Add student to map if data is valid
                students.insert(pair<int, string>(id, s_name));
            }
        }
        else {
            // print error about invalid number of inputs
            cout << tokens.size() << " inputs were loaded, expected 2" << endl;
            cout << errorHandling(5) << endl;
        }
    }
    nameFile.close();
    return students;
}

int main(int argc, char *argv[]) {
    string namePath;
    string coursePath;
    string outputPath;
    string txt;

    if (argc < 4) { // Verify the user has provided file paths
	cout << "Please enter a course file, name file, and output file" << endl;
    }
    else { // Get user-given paths
        coursePath = argv[1];
        namePath = argv[2];
	    outputPath = argv[3];
    }
    ofstream outfile; // create header for output file
    outfile.open(outputPath); // link to output file 
  
    // Load student ids and names from file
    map<int, string> students = loadStudents(namePath);

    // Load course information and sort
    vector<Course> courses = loadCourses(coursePath);
    sort(courses.begin(), courses.end(), compareSID);

    // Print all student info
    for (map<int, string>::iterator it = students.begin(); it != students.end(); ++it) { 
      cout << it->first << " " << it->second << endl;
    }
    /*
    // Print all course information
    for (int i = 0; i < courses.size(); i++) {
        cout << courses.at(i).s_id << " " << courses.at(i).code << " " << courses.at(i).avg << endl;
    }
    */
    // Print to output in dicated format
    for (long unsigned int i = 0; i < courses.size(); i++) {
        auto studentID = students.find(courses.at(i).s_id);
        outfile << courses.at(i).s_id << ", " << studentID->second << ", " << courses.at(i).code << ", " << fixed << setprecision(1) << courses.at(i).avg << endl;
    }
    outfile.close(); // close output file
    return 0;
}

