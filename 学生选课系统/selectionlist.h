#ifndef SELECTIONLIST_H
#define SELECTIONLIST_H
#include "selection.h"
#include "studentlist.h"
#include "courselist.h"
#include<fstream>

class SelectionList {
private:
    Selection* head;   // 链表头指针

public:
    SelectionList() : head(nullptr) {}
    ~SelectionList();

    // 从文件加载
    void loadFromFile(const string& filename);

    // 保存到文件
    void saveToFile(const string& filename);

    // 添加选课记录
    bool addSelection(const string& studentId, const string& courseId,
                      StudentList& slist, CourseList& clist);

    // 删除选课记录
    bool removeSelection(const string& studentId, const string& courseId);

    // 查看某学生的选课情况
    void displayByStudent(const string& studentId, CourseList& clist) const;

    // 查看某课程的选课情况
    void displayByCourse(const string& courseId, StudentList& slist) const;

    // 浏览所有选课记录
    void displayAll(StudentList& slist, CourseList& clist) const;

    // 检查学生是否已选某课程
    bool isSelected(const string& studentId, const string& courseId) const;

    // 计算学生已选总学分
    float getTotalCredits(const string& studentId, CourseList& clist) const;

    // 计算课程选课人数
    int getEnrollmentCount(const string& courseId) const;

    // 统计某课程选课人数
    int countByCourse(const string& courseId) const;

    // 按选课人数排序课程
    void sortByEnrollment(CourseList& clist);

    // 删除学生的所有选课记录
    void removeByStudent(const string& studentId);

    // 删除课程的所有选课记录
    void removeByCourse(const string& courseId);

    // 批量选课：某个班级所有学生选某门课
    void batchSelect(const string& className, const string& courseId,
                     StudentList& slist, CourseList& clist);
};

#endif
