#ifndef COURSELIST_H
#define COURSELIST_H
#include "course.h"
#include<fstream>

class CourseList {
private:
    Course* head;      // 链表头指针

public:
    CourseList() : head(nullptr) {}
    ~CourseList();

    // 从文件加载
    void loadFromFile(const string& filename);

    // 保存到文件
    void saveToFile(const string& filename);

    // 添加课程
    void add(Course& c);

    // 删除课程（按课程编号）
    bool remove(const string& id);

    // 修改课程信息（按课程编号）
    bool modify(const string& id);

    // 查找课程（按课程编号精确查找）
    Course* findById(const string& id);

    // 模糊查找课程
    void fuzzySearch(int field, const string& keyword) const;

    // 按学分范围查询
    void searchByCredits(float minCredits, float maxCredits) const;

    // 浏览所有课程
    void displayAll() const;

    // 排序显示
    void sortByField(int field);

    // 获取头指针
    Course* getHead() const { return head; }
};

#endif
