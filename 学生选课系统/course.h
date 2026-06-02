#ifndef COURSE_H
#define COURSE_H
#include<string>
#include<iostream>
using namespace std;

class Course {
private:
    string id;
    string name;
    string type;
    int totalHours;
    int lectureHours;
    int labHours;
    float credits;
    string semester;
public:
    Course* next;
    Course(string id = "", string name = "", string type = "",
           int totalHours = 0, int lectureHours = 0, int labHours = 0,
           float credits = 0, string semester = "")
        : id(id), name(name), type(type), totalHours(totalHours),
          lectureHours(lectureHours), labHours(labHours),
          credits(credits), semester(semester), next(nullptr) {}
    string getId() const { return id; }
    string getName() const { return name; }
    string getType() const { return type; }
    int getTotalHours() const { return totalHours; }
    int getLectureHours() const { return lectureHours; }
    int getLabHours() const { return labHours; }
    float getCredits() const { return credits; }
    string getSemester() const { return semester; }
    void setName(const string& n) { name = n; }
    void setType(const string& t) { type = t; }
    void setTotalHours(int h) { totalHours = h; }
    void setLectureHours(int h) { lectureHours = h; }
    void setLabHours(int h) { labHours = h; }
    void setCredits(float c) { credits = c; }
    void setSemester(const string& s) { semester = s; }
    bool operator==(const Course& c) const { return id == c.id; }
    void display() const;
    void input();
    bool isEmpty() const { return id.empty(); }
};
#endif