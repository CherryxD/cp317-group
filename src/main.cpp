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
        status = 1;
    }
    return status;
}

class Course {
    public:
        Course() {
            test1 = 0.0;
            test2 = 0.0;
            test3 = 0.0;
            exam = 0.0;
            code = "";
            s_id = 0;
            avg = 0.0;
        }
        Course(float x, float y, float z, float f, string c, int i) {
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
        float test1;
        float test2;
        float test3;
        float exam;

	// show error number if invalid data is given
        int validate() {
	    int status = validate_id(s_id);
            if (isdigit(code.at(2)) == 0) {
                cout << code;
                status = 2;
            }
            else if (test1 < 0 || test2 < 0 || test3 < 0 || exam < 0) {
                cout << test1 << test2 << test3 << exam << endl;
                status = 3;
            }
            return status;
        }
    private:
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
    */
    switch(code) {
        case 1:
        msg = "There was an invalid ID loaded ->";
        break;
        case 2:
        msg = "There was an invalid course code loaded";
        break;
        case 3:
        msg = "There was an invalid grade loaded";
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
        char * cstr = new char [txt.length()+1];
        string c_code;
        int s_id;
        float t1; float t2; float t3; float f;
        std::strcpy (cstr, txt.c_str());

	// Extract data from between commas in line of text
        char * tok = strtok(cstr, ", ");
        s_id = atoi(tok);
        tok = strtok(NULL, ", ");
        c_code = tok;
        tok = strtok(NULL, ", ");
        t1 = atof(tok);
        tok = strtok(NULL, ", ");
        t2 = atof(tok);
        tok = strtok(NULL, ", ");
        t3 = atof(tok);
        tok = strtok(NULL, ", ");
        f = atof(tok);

	// Load data from line into object
        Course course(t1, t2, t3, f, c_code, s_id);

	// Validate course has correct information
        int status = course.validate();
        if (status != 0) {
            cout << errorHandling(status) << endl;
        }
        else { // If course info is valid, add to list of courses
            courses.push_back(course);
        }
        delete[] cstr; // Remove allocated memory from cstr
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
        char * cstr = new char [txt.length()+1];
        string s_name;
        int id;
        std::strcpy (cstr, txt.c_str());

	    // Extract info from file line
        char * tok = strtok(cstr, ",");
        id = atoi(tok);
        tok = strtok(NULL, ",");
        s_name = tok;
        int status = validate_id(id);
        if (status != 0) { // Print error according to error code
            cout << errorHandling(status) << endl;
        }
        else { // Add student to map if data is valid
	        students.insert(pair<int, string>(id, s_name));
        }
        delete[] cstr; // Free memory allocated for cstr
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
    /*
    // Print all student info
    for (map<int, string>::iterator it = students.begin(); it != students.end(); ++it) { 
      cout << it-> first << it->second << endl;
    }
    // Print all course information
    for (int i = 0; i < courses.size(); i++) {
        cout << courses.at(i).s_id << " " << courses.at(i).code << " " << courses.at(i).avg << endl;
    }
    */
    // Print to output in dicated format
    for (long unsigned int i = 0; i < courses.size(); i++) {
        auto studentID = students.find(courses.at(i).s_id);
        outfile << courses.at(i).s_id << "," << studentID-> second << ", " << courses.at(i).code << ", " << courses.at(i).avg << endl;
    }
    outfile.close(); // close output file
    return 0;
}

