#include "selectionlist.h"

SelectionList::~SelectionList() {
    Selection* current = head;
    while (current) {
        Selection* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void SelectionList::loadFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "提示: 文件 " << filename << " 不存在，将创建新文件。" << endl;
        return;
    }
    string sid, cid;
    while (infile >> sid >> cid) {
        Selection sel(sid, cid);
        // 尾插法
        Selection* newNode = new Selection(sel);
        newNode->next = nullptr;
        if (!head) {
            head = newNode;
        } else {
            Selection* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
    }
    infile.close();
    cout << "已从 " << filename << " 加载选课数据。" << endl;
}

void SelectionList::saveToFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "错误: 无法打开文件 " << filename << " 进行写入。" << endl;
        return;
    }
    Selection* current = head;
    while (current) {
        outfile << current->getStudentId() << " " << current->getCourseId() << endl;
        current = current->next;
    }
    outfile.close();
}

bool SelectionList::addSelection(const string& studentId, const string& courseId,
                                  StudentList& slist, CourseList& clist) {
    // 检查学生是否存在
    if (!slist.findById(studentId)) {
        cout << "错误: 学号为 " << studentId << " 的学生不存在。" << endl;
        return false;
    }
    // 检查课程是否存在
    if (!clist.findById(courseId)) {
        cout << "错误: 课程编号为 " << courseId << " 的课程不存在。" << endl;
        return false;
    }
    // 检查是否已选
    if (isSelected(studentId, courseId)) {
        cout << "错误: 该学生已选此课程，不能重复选课。" << endl;
        return false;
    }
    // 检查学分要求
    float currentCredits = getTotalCredits(studentId, clist);
    Course* c = clist.findById(courseId);
    if (currentCredits + c->getCredits() < 15) {
        cout << "警告: 选课后总学分为 " << (currentCredits + c->getCredits()) 
             << "，不足15学分的最低要求。" << endl;
    }
    
    Selection* newNode = new Selection(studentId, courseId);
    newNode->next = nullptr;
    if (!head) {
        head = newNode;
    } else {
        Selection* current = head;
        while (current->next) current = current->next;
        current->next = newNode;
    }
    cout << "选课成功! 当前总学分: " << (currentCredits + c->getCredits()) << endl;
    return true;
}

bool SelectionList::removeSelection(const string& studentId, const string& courseId) {
    if (!head) return false;
    
    Selection *prev = nullptr, *current = head;
    while (current) {
        if (current->getStudentId() == studentId && current->getCourseId() == courseId) {
            if (prev) prev->next = current->next;
            else head = current->next;
            delete current;
            cout << "退课成功!" << endl;
            return true;
        }
        prev = current;
        current = current->next;
    }
    cout << "未找到该选课记录。" << endl;
    return false;
}

void SelectionList::displayByStudent(const string& studentId, CourseList& clist) const {
    Selection* current = head;
    float totalCredits = 0;
    bool found = false;
    cout << "===== 学生 " << studentId << " 的选课情况 =====" << endl;
    while (current) {
        if (current->getStudentId() == studentId) {
            Course* c = clist.findById(current->getCourseId());
            if (c) {
                cout << c->getId() << " " << c->getName() << " "
                     << c->getCredits() << "学分 " << c->getSemester() << endl;
                totalCredits += c->getCredits();
            }
            found = true;
        }
        current = current->next;
    }
    if (found) {
        cout << "总学分: " << totalCredits << endl;
        if (totalCredits < 15) {
            cout << "【警告】总学分不足15学分!" << endl;
        }
    } else {
        cout << "该学生尚未选课。" << endl;
    }
}

void SelectionList::displayByCourse(const string& courseId, StudentList& slist) const {
    Selection* current = head;
    bool found = false;
    cout << "===== 课程 " << courseId << " 的选课学生 =====" << endl;
    while (current) {
        if (current->getCourseId() == courseId) {
            Student* s = slist.findById(current->getStudentId());
            if (s) {
                s->display();
            }
            found = true;
        }
        current = current->next;
    }
    if (!found) cout << "暂无学生选修此课程。" << endl;
}

void SelectionList::displayAll(StudentList& slist, CourseList& clist) const {
    if (!head) {
        cout << "暂无选课记录。" << endl;
        return;
    }
    cout << "===== 所有选课记录 =====" << endl;
    cout << "学号\t姓名\t\t课程编号\t课程名称" << endl;
    Selection* current = head;
    while (current) {
        Student* s = slist.findById(current->getStudentId());
        Course* c = clist.findById(current->getCourseId());
        if (s && c) {
            cout << current->getStudentId() << "\t" << s->getName() << "\t\t"
                 << current->getCourseId() << "\t" << c->getName() << endl;
        }
        current = current->next;
    }
}

bool SelectionList::isSelected(const string& studentId, const string& courseId) const {
    Selection* current = head;
    while (current) {
        if (current->getStudentId() == studentId && current->getCourseId() == courseId)
            return true;
        current = current->next;
    }
    return false;
}

float SelectionList::getTotalCredits(const string& studentId, CourseList& clist) const {
    float total = 0;
    Selection* current = head;
    while (current) {
        if (current->getStudentId() == studentId) {
            Course* c = clist.findById(current->getCourseId());
            if (c) total += c->getCredits();
        }
        current = current->next;
    }
    return total;
}

int SelectionList::getEnrollmentCount(const string& courseId) const {
    return countByCourse(courseId);
}

int SelectionList::countByCourse(const string& courseId) const {
    int count = 0;
    Selection* current = head;
    while (current) {
        if (current->getCourseId() == courseId) count++;
        current = current->next;
    }
    return count;
}

void SelectionList::sortByEnrollment(CourseList& clist) {
    // 按选课人数降序排列课程并显示
    if (!clist.getHead()) {
        cout << "暂无课程。" << endl;
        return;
    }
    
    // 收集课程编号和人数
    struct CourseEnroll {
        string courseId;
        int count;
        CourseEnroll* next;
        CourseEnroll(string id, int c) : courseId(id), count(c), next(nullptr) {}
    };
    CourseEnroll* ceHead = nullptr;
    
    Course* current = clist.getHead();
    while (current) {
        int count = countByCourse(current->getId());
        CourseEnroll* newNode = new CourseEnroll(current->getId(), count);
        // 按人数降序插入
        if (!ceHead || count > ceHead->count) {
            newNode->next = ceHead;
            ceHead = newNode;
        } else {
            CourseEnroll* ce = ceHead;
            while (ce->next && ce->next->count >= count) ce = ce->next;
            newNode->next = ce->next;
            ce->next = newNode;
        }
        current = current->next;
    }
    
    cout << "===== 按选课人数排序 =====" << endl;
    cout << "排名\t课程编号\t课程名称\t\t学分\t选课人数" << endl;
    int rank = 1;
    CourseEnroll* ce = ceHead;
    while (ce) {
        Course* c = clist.findById(ce->courseId);
        if (c) {
            cout << rank++ << "\t" << ce->courseId << "\t" << c->getName() << "\t\t"
                 << c->getCredits() << "\t" << ce->count << endl;
        }
        CourseEnroll* next = ce->next;
        delete ce;
        ce = next;
    }
}

void SelectionList::removeByStudent(const string& studentId) {
    if (!head) return;
    Selection *prev = nullptr, *current = head;
    while (current) {
        if (current->getStudentId() == studentId) {
            if (prev) prev->next = current->next;
            else head = current->next;
            Selection* toDelete = current;
            current = (prev) ? prev->next : head;
            delete toDelete;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void SelectionList::removeByCourse(const string& courseId) {
    if (!head) return;
    Selection *prev = nullptr, *current = head;
    while (current) {
        if (current->getCourseId() == courseId) {
            if (prev) prev->next = current->next;
            else head = current->next;
            Selection* toDelete = current;
            current = (prev) ? prev->next : head;
            delete toDelete;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void SelectionList::batchSelect(const string& className, const string& courseId,
                                  StudentList& slist, CourseList& clist) {
    // 检查课程是否存在
    if (!clist.findById(courseId)) {
        cout << "错误: 课程编号为 " << courseId << " 的课程不存在。" << endl;
        return;
    }
    
    int successCount = 0;
    Student* current = slist.getHead();
    while (current) {
        if (current->getClassName() == className) {
            if (!isSelected(current->getId(), courseId)) {
                Selection* newNode = new Selection(current->getId(), courseId);
                newNode->next = nullptr;
                if (!head) {
                    head = newNode;
                } else {
                    Selection* sel = head;
                    while (sel->next) sel = sel->next;
                    sel->next = newNode;
                }
                successCount++;
            }
        }
        current = current->next;
    }
    cout << "批量选课完成! 成功为 " << successCount << " 名学生选了此课程。" << endl;
}
