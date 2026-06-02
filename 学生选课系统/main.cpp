#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<limits>
#include "student.h"
#include "course.h"
#include "selection.h"
#include "studentlist.h"
#include "courselist.h"
#include "selectionlist.h"
using namespace std;

// 全局数据文件名
const string STUDENT_FILE = "students.txt";
const string COURSE_FILE = "courses.txt";
const string SELECTION_FILE = "selections.txt";

// 全局对象
StudentList studentList;
CourseList courseList;
SelectionList selectionList;

// 函数声明
void initSystem();
void saveSystem();
void clearScreen();
void pauseScreen();

// 主菜单
void mainMenu();
// 学生管理菜单
void studentMenu();
// 课程管理菜单
void courseMenu();
// 选课管理菜单
void selectionMenu();
// 查询菜单
void queryMenu();
// 统计排序菜单
void statMenu();

int main() {
    // 初始化：从文件加载数据
    initSystem();
    
    mainMenu();
    
    // 退出前保存
    saveSystem();
    cout << "谢谢使用学生选课系统!" << endl;
    return 0;
}

void initSystem() {
    cout << "===== 学生选课系统 =====" << endl;
    cout << "正在加载数据..." << endl;
    studentList.loadFromFile(STUDENT_FILE);
    courseList.loadFromFile(COURSE_FILE);
    selectionList.loadFromFile(SELECTION_FILE);
    cout << "数据加载完成!" << endl;
    pauseScreen();
}

void saveSystem() {
    cout << "正在保存数据..." << endl;
    studentList.saveToFile(STUDENT_FILE);
    courseList.saveToFile(COURSE_FILE);
    selectionList.saveToFile(SELECTION_FILE);
    cout << "数据保存完成!" << endl;
}

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << endl << "按回车键继续...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ==================== 主菜单 ====================
void mainMenu() {
    int choice = 0;
    while (choice != 6) {
        clearScreen();
        cout << "============================================" << endl;
        cout << "|            学生选课管理系统              |" << endl;
        cout << "============================================" << endl;
        cout << "|  1. 学生信息管理                         |" << endl;
        cout << "|  2. 课程信息管理                         |" << endl;
        cout << "|  3. 选课管理                             |" << endl;
        cout << "|  4. 信息查询                             |" << endl;
        cout << "|  5. 统计与排序                           |" << endl;
        cout << "|  6. 退出系统                             |" << endl;
        cout << "============================================" << endl;
        cout << "请选择 (1-6): ";
        cin >> choice;
        
        switch (choice) {
            case 1: studentMenu(); break;
            case 2: courseMenu(); break;
            case 3: selectionMenu(); break;
            case 4: queryMenu(); break;
            case 5: statMenu(); break;
            case 6:
                saveSystem();
                cout << "再见!" << endl;
                break;
            default:
                cout << "输入错误，请重新选择。" << endl;
                pauseScreen();
        }
    }
}

// ==================== 学生管理菜单 ====================
void studentMenu() {
    int choice = 0;
    while (choice != 7) {
        clearScreen();
        cout << "========== 学生信息管理 ==========" << endl;
        cout << "1. 添加学生信息" << endl;
        cout << "2. 修改学生信息" << endl;
        cout << "3. 删除学生信息" << endl;
        cout << "4. 浏览所有学生" << endl;
        cout << "5. 按学号查找学生" << endl;
        cout << "6. 模糊查找学生" << endl;
        cout << "7. 返回主菜单" << endl;
        cout << "==================================" << endl;
        cout << "请选择 (1-7): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Student s;
                s.input();
                studentList.add(s);
                cout << "添加成功!" << endl;
                saveSystem();
                pauseScreen();
                break;
            }
            case 2: {
                string id;
                cout << "请输入要修改的学生学号: ";
                cin >> id;
                studentList.modify(id);
                saveSystem();
                pauseScreen();
                break;
            }
            case 3: {
                string id;
                char confirm;
                cout << "请输入要删除的学生学号: ";
                cin >> id;
                cout << "确认删除学号为 " << id << " 的学生及其所有选课记录吗? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    selectionList.removeByStudent(id);
                    if (studentList.remove(id)) {
                        cout << "删除成功!" << endl;
                    } else {
                        cout << "未找到该学生。" << endl;
                    }
                    saveSystem();
                } else {
                    cout << "取消删除。" << endl;
                }
                pauseScreen();
                break;
            }
            case 4:
                studentList.displayAll();
                pauseScreen();
                break;
            case 5: {
                string id;
                cout << "请输入学号: ";
                cin >> id;
                Student* s = studentList.findById(id);
                if (s) {
                    cout << "找到学生:" << endl;
                    s->display();
                } else {
                    cout << "未找到该学生。" << endl;
                }
                pauseScreen();
                break;
            }
            case 6: {
                int field;
                string keyword;
                cout << "按字段模糊查找:" << endl;
                cout << "1.姓名  2.专业  3.班级  4.学号" << endl;
                cout << "请选择: ";
                cin >> field;
                cout << "请输入关键字: ";
                cin >> keyword;
                studentList.fuzzySearch(field, keyword);
                pauseScreen();
                break;
            }
            case 7: break;
            default:
                cout << "输入错误!" << endl;
                pauseScreen();
        }
    }
}

// ==================== 课程管理菜单 ====================
void courseMenu() {
    int choice = 0;
    while (choice != 7) {
        clearScreen();
        cout << "========== 课程信息管理 ==========" << endl;
        cout << "1. 添加课程信息" << endl;
        cout << "2. 修改课程信息" << endl;
        cout << "3. 删除课程信息" << endl;
        cout << "4. 浏览所有课程" << endl;
        cout << "5. 按编号查找课程" << endl;
        cout << "6. 模糊查找课程" << endl;
        cout << "7. 返回主菜单" << endl;
        cout << "==================================" << endl;
        cout << "请选择 (1-7): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Course c;
                c.input();
                courseList.add(c);
                cout << "添加成功!" << endl;
                saveSystem();
                pauseScreen();
                break;
            }
            case 2: {
                string id;
                cout << "请输入要修改的课程编号: ";
                cin >> id;
                courseList.modify(id);
                saveSystem();
                pauseScreen();
                break;
            }
            case 3: {
                string id;
                char confirm;
                cout << "请输入要删除的课程编号: ";
                cin >> id;
                cout << "确认删除课程 " << id << " 及其所有选课记录吗? (y/n): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    selectionList.removeByCourse(id);
                    if (courseList.remove(id)) {
                        cout << "删除成功!" << endl;
                    } else {
                        cout << "未找到该课程。" << endl;
                    }
                    saveSystem();
                } else {
                    cout << "取消删除。" << endl;
                }
                pauseScreen();
                break;
            }
            case 4:
                courseList.displayAll();
                pauseScreen();
                break;
            case 5: {
                string id;
                cout << "请输入课程编号: ";
                cin >> id;
                Course* c = courseList.findById(id);
                if (c) {
                    cout << "找到课程:" << endl;
                    c->display();
                } else {
                    cout << "未找到该课程。" << endl;
                }
                pauseScreen();
                break;
            }
            case 6: {
                int field;
                string keyword;
                cout << "按字段模糊查找:" << endl;
                cout << "1.课程名称  2.课程性质  3.开课学期  4.课程编号" << endl;
                cout << "请选择: ";
                cin >> field;
                cout << "请输入关键字: ";
                cin >> keyword;
                courseList.fuzzySearch(field, keyword);
                pauseScreen();
                break;
            }
            case 7: break;
            default:
                cout << "输入错误!" << endl;
                pauseScreen();
        }
    }
}

// ==================== 选课管理菜单 ====================
void selectionMenu() {
    int choice = 0;
    while (choice != 6) {
        clearScreen();
        cout << "========== 选课管理 ==========" << endl;
        cout << "1. 学生选课" << endl;
        cout << "2. 退选课程" << endl;
        cout << "3. 批量选课(按班级)" << endl;
        cout << "4. 查看某学生的选课情况" << endl;
        cout << "5. 查看某课程的选课学生" << endl;
        cout << "6. 返回主菜单" << endl;
        cout << "==============================" << endl;
        cout << "请选择 (1-6): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                string sid, cid;
                cout << "请输入学号: ";
                cin >> sid;
                cout << "请输入课程编号: ";
                cin >> cid;
                selectionList.addSelection(sid, cid, studentList, courseList);
                saveSystem();
                pauseScreen();
                break;
            }
            case 2: {
                string sid, cid;
                cout << "请输入学号: ";
                cin >> sid;
                cout << "请输入课程编号: ";
                cin >> cid;
                selectionList.removeSelection(sid, cid);
                saveSystem();
                pauseScreen();
                break;
            }
            case 3: {
                string className, cid;
                cout << "请输入班级名称: ";
                cin >> className;
                cout << "请输入课程编号: ";
                cin >> cid;
                selectionList.batchSelect(className, cid, studentList, courseList);
                saveSystem();
                pauseScreen();
                break;
            }
            case 4: {
                string sid;
                cout << "请输入学号: ";
                cin >> sid;
                selectionList.displayByStudent(sid, courseList);
                pauseScreen();
                break;
            }
            case 5: {
                string cid;
                cout << "请输入课程编号: ";
                cin >> cid;
                selectionList.displayByCourse(cid, studentList);
                cout << "选课人数: " << selectionList.countByCourse(cid) << endl;
                pauseScreen();
                break;
            }
            case 6: break;
            default:
                cout << "输入错误!" << endl;
                pauseScreen();
        }
    }
}

// ==================== 查询菜单 ====================
void queryMenu() {
    int choice = 0;
    while (choice != 5) {
        clearScreen();
        cout << "========== 信息查询 ==========" << endl;
        cout << "1. 按学分范围查询课程" << endl;
        cout << "2. 查看所有选课记录" << endl;
        cout << "3. 按课程查询选课人数" << endl;
        cout << "4. 按学生查询已选总学分" << endl;
        cout << "5. 返回主菜单" << endl;
        cout << "==============================" << endl;
        cout << "请选择 (1-5): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                float minC, maxC;
                cout << "请输入最低学分: ";
                cin >> minC;
                cout << "请输入最高学分: ";
                cin >> maxC;
                courseList.searchByCredits(minC, maxC);
                pauseScreen();
                break;
            }
            case 2:
                selectionList.displayAll(studentList, courseList);
                pauseScreen();
                break;
            case 3: {
                string cid;
                cout << "请输入课程编号: ";
                cin >> cid;
                Course* c = courseList.findById(cid);
                if (c) {
                    cout << "课程: " << c->getName() << "  选课人数: " 
                         << selectionList.countByCourse(cid) << endl;
                } else {
                    cout << "课程不存在。" << endl;
                }
                pauseScreen();
                break;
            }
            case 4: {
                string sid;
                cout << "请输入学号: ";
                cin >> sid;
                Student* s = studentList.findById(sid);
                if (s) {
                    float credits = selectionList.getTotalCredits(sid, courseList);
                    cout << "学生 " << s->getName() << " 已选总学分: " << credits << endl;
                    if (credits < 15) {
                        cout << "【警告】总学分不足15学分!" << endl;
                    }
                } else {
                    cout << "学生不存在。" << endl;
                }
                pauseScreen();
                break;
            }
            case 5: break;
            default:
                cout << "输入错误!" << endl;
                pauseScreen();
        }
    }
}

// ==================== 统计与排序菜单 ====================
void statMenu() {
    int choice = 0;
    while (choice != 8) {
        clearScreen();
        cout << "========== 统计与排序 ==========" << endl;
        cout << "1. 按专业统计学生人数" << endl;
        cout << "2. 按班级统计学生人数" << endl;
        cout << "3. 按性别统计学生人数" << endl;
        cout << "4. 学生信息排序" << endl;
        cout << "5. 课程信息排序" << endl;
        cout << "6. 按选课人数排序课程" << endl;
        cout << "7. 浏览所有选课记录" << endl;
        cout << "8. 返回主菜单" << endl;
        cout << "================================" << endl;
        cout << "请选择 (1-8): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                studentList.statisticsByMajor();
                pauseScreen();
                break;
            case 2:
                studentList.statisticsByClass();
                pauseScreen();
                break;
            case 3:
                studentList.statisticsByGender();
                pauseScreen();
                break;
            case 4: {
                int field;
                cout << "排序字段: 1.学号  2.姓名  3.专业  4.班级" << endl;
                cout << "请选择: ";
                cin >> field;
                studentList.sortByField(field);
                pauseScreen();
                break;
            }
            case 5: {
                int field;
                cout << "排序字段: 1.课程编号  2.课程名称  3.学分(从高到低)" << endl;
                cout << "请选择: ";
                cin >> field;
                courseList.sortByField(field);
                pauseScreen();
                break;
            }
            case 6:
                selectionList.sortByEnrollment(courseList);
                pauseScreen();
                break;
            case 7:
                selectionList.displayAll(studentList, courseList);
                pauseScreen();
                break;
            case 8: break;
            default:
                cout << "输入错误!" << endl;
                pauseScreen();
        }
    }
}
