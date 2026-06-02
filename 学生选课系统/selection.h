#ifndef SELECTION_H
#define SELECTION_H
#include<string>
#include<iostream>
using namespace std;

// 选课记录类：关联学生和课程
class Selection {
private:
    string studentId;   // 学号
    string courseId;    // 课程编号

public:
    Selection* next;    // 链表指针

    // 构造函数
    Selection(string sid = "", string cid = "")
        : studentId(sid), courseId(cid), next(nullptr) {}

    // 获取函数
    string getStudentId() const { return studentId; }
    string getCourseId() const { return courseId; }

    // 设置函数
    void setStudentId(const string& id) { studentId = id; }
    void setCourseId(const string& id) { courseId = id; }

    // 显示选课记录
    void display() const;

    // 判断是否为空
    bool isEmpty() const { return studentId.empty(); }
};

#endif
