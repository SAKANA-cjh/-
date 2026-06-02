#ifndef STUDENTLIST_H
#define STUDENTLIST_H
#include "student.h"
#include<fstream>

class StudentList {
private:
    Student* head;     // 链表头指针

public:
    StudentList() : head(nullptr) {}
    ~StudentList();

    // 从文件加载
    void loadFromFile(const string& filename);

    // 保存到文件
    void saveToFile(const string& filename);

    // 添加学生（尾插法）
    void add(Student& s);

    // 删除学生（按学号）
    bool remove(const string& id);

    // 修改学生信息（按学号）
    bool modify(const string& id);

    // 查找学生（按学号精确查找）
    Student* findById(const string& id);

    // 模糊查找学生
    void fuzzySearch(int field, const string& keyword) const;

    // 浏览所有学生
    void displayAll() const;

    // 按专业统计学生人数
    void statisticsByMajor() const;

    // 按班级统计学生人数
    void statisticsByClass() const;

    // 按性别统计学生人数
    void statisticsByGender() const;

    // 排序显示
    void sortByField(int field);

    // 获取头指针
    Student* getHead() const { return head; }
};

#endif
