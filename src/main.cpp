#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class Student {
    public:
        Student() {
            id = 0;
            name = "";
        }
        Student(int a, string b) {
            id = a;
            name = b;
        }
        int id;
        string name;

};

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
    private:
        float calculateFinalGrade(float a, float b, float c, float f) {
            float grade = 0.0;
            grade = (a * 0.2) + (b * 0.2) + (c * 0.2) + (f * 0.4);
            return grade;
        }
};


vector<Course> loadCourses(string filepath) {
    ifstream courseFile(filepath);
    vector<Course> courses;
    string txt;
    while (getline(courseFile, txt)) {
        //cout << txt << "\n";
        char * cstr = new char [txt.length()+1];
        string c_code;
        int s_id;
        float t1; float t2; float t3; float f;
        std::strcpy (cstr, txt.c_str());

        char * tok = strtok(cstr, ",");
        s_id = atoi(tok);
        tok = strtok(NULL, ",");
        c_code = tok;
        tok = strtok(NULL, ",");
        t1 = atof(tok);
        tok = strtok(NULL, ",");
        t2 = atof(tok);
        tok = strtok(NULL, ",");
        t3 = atof(tok);
        tok = strtok(NULL, ",");
        f = atof(tok);
        Course course(t1, t2, t3, f, c_code, s_id);
        //cout << student.id << " " << student.name << "\n";
        courses.push_back(course);
        delete[] cstr;
    }
    return courses;
}

vector<Student> loadStudents(string filepath) {
    ifstream nameFile(filepath);
    string txt;
    vector<Student> students;
    while (getline(nameFile, txt)) {
        //cout << txt << "\n";
        char * cstr = new char [txt.length()+1];
        string s_name;
        int id;
        std::strcpy (cstr, txt.c_str());

        char * tok = strtok(cstr, ",");
        id = atoi(tok);
        tok = strtok(NULL, ",");
        s_name = tok;
        Student student(id, s_name);
        //cout << student.id << " " << student.name << "\n";
        students.push_back(student);
        delete[] cstr;
    }
    return students;
}



int main() {
    string namePath = "../build/NameFile.txt";
    string coursePath = "../build/CourseFile.txt";
    string txt;
    vector<Student> students = loadStudents(namePath);
    for (int i = 0; i < students.size() - 1; i++) {
        cout << students.at(i).id << " " << students.at(i).name << "\n";
    }

    vector<Course> courses = loadCourses(coursePath);


    for (int i = 0; i < courses.size() - 1; i++) {
        cout << courses.at(i).s_id << " " << courses.at(i).code << " " << courses.at(i).avg << "\n";
    }

    return 0;
}

