#ifndef STUDENT_H
#define STUDENT_H
#include<string>
#include<iostream>
using namespace std;

class Student {
private:
    string id;
    string name;
    string gender;
    string major;
    string className;
public:
    Student* next;
    Student(string id = "", string name = "", string gender = "", 
            string major = "", string className = "")
        : id(id), name(name), gender(gender), major(major), 
          className(className), next(nullptr) {}
    string getId() const { return id; }
    string getName() const { return name; }
    string getGender() const { return gender; }
    string getMajor() const { return major; }
    string getClassName() const { return className; }
    void setName(const string& n) { name = n; }
    void setGender(const string& g) { gender = g; }
    void setMajor(const string& m) { major = m; }
    void setClassName(const string& c) { className = c; }
    bool operator==(const Student& s) const { return id == s.id; }
    void display() const;
    void input();
    bool isEmpty() const { return id.empty(); }
};
#endif
