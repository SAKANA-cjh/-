#include "course.h"

void Course::display() const {
    cout << "课程编号: " << id << "  课程名称: " << name
         << "  课程性质: " << type << "  总学时: " << totalHours
         << "  授课学时: " << lectureHours << "  实验/上机学时: " << labHours
         << "  学分: " << credits << "  开课学期: " << semester << endl;
}

void Course::input() {
    cout << "请输入课程编号: "; cin >> id;
    cout << "课程名称: "; cin >> name;
    cout << "课程性质: "; cin >> type;
    cout << "总学时: "; cin >> totalHours;
    cout << "授课学时: "; cin >> lectureHours;
    cout << "实验/上机学时: "; cin >> labHours;
    cout << "学分: "; cin >> credits;
    cout << "开课学期: "; cin >> semester;
}
