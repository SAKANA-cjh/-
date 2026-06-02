#include "student.h"

void Student::display() const {
    cout << "学号: " << id << "  姓名: " << name << "  性别: " << gender
         << "  专业: " << major << "  班级: " << className << endl;
}

void Student::input() {
    cout << "请输入学生信息:" << endl;
    cout << "学号: "; cin >> id;
    cout << "姓名: "; cin >> name;
    cout << "性别: "; cin >> gender;
    cout << "专业: "; cin >> major;
    cout << "班级: "; cin >> className;
}
