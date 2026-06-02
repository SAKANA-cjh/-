#include "studentlist.h"
#include<algorithm>

StudentList::~StudentList() {
    Student* current = head;
    while (current) {
        Student* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void StudentList::loadFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "提示: 文件 " << filename << " 不存在，将创建新文件。" << endl;
        return;
    }
    string id, name, gender, major, className;
    while (infile >> id >> name >> gender >> major >> className) {
        Student s(id, name, gender, major, className);
        add(s);
    }
    infile.close();
    cout << "已从 " << filename << " 加载学生数据。" << endl;
}

void StudentList::saveToFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "错误: 无法打开文件 " << filename << " 进行写入。" << endl;
        return;
    }
    Student* current = head;
    while (current) {
        outfile << current->getId() << " " << current->getName() << " "
                << current->getGender() << " " << current->getMajor() << " "
                << current->getClassName() << endl;
        current = current->next;
    }
    outfile.close();
}

void StudentList::add(Student& s) {
    Student* newNode = new Student(s);
    newNode->next = nullptr;
    if (!head) {
        head = newNode;
    } else {
        Student* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool StudentList::remove(const string& id) {
    if (!head) return false;
    
    Student *prev = nullptr, *current = head;
    while (current) {
        if (current->getId() == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

bool StudentList::modify(const string& id) {
    Student* s = findById(id);
    if (!s) {
        cout << "未找到学号为 " << id << " 的学生。" << endl;
        return false;
    }
    cout << "当前学生信息:" << endl;
    s->display();
    cout << "请输入新的信息（直接回车保留原值）:" << endl;
    
    string input;
    cout << "姓名 [" << s->getName() << "]: ";
    cin.ignore();
    getline(cin, input);
    if (!input.empty()) s->setName(input);
    
    cout << "性别 [" << s->getGender() << "]: ";
    getline(cin, input);
    if (!input.empty()) s->setGender(input);
    
    cout << "专业 [" << s->getMajor() << "]: ";
    getline(cin, input);
    if (!input.empty()) s->setMajor(input);
    
    cout << "班级 [" << s->getClassName() << "]: ";
    getline(cin, input);
    if (!input.empty()) s->setClassName(input);
    
    cout << "修改成功!" << endl;
    return true;
}

Student* StudentList::findById(const string& id) {
    Student* current = head;
    while (current) {
        if (current->getId() == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void StudentList::fuzzySearch(int field, const string& keyword) const {
    Student* current = head;
    bool found = false;
    cout << "===== 查询结果 =====" << endl;
    while (current) {
        string fieldValue;
        switch (field) {
            case 1: fieldValue = current->getName(); break;     // 姓名
            case 2: fieldValue = current->getMajor(); break;    // 专业
            case 3: fieldValue = current->getClassName(); break;// 班级
            case 4: fieldValue = current->getId(); break;       // 学号
        }
        // 模糊匹配：包含关键字
        if (fieldValue.find(keyword) != string::npos) {
            current->display();
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "未找到匹配的学生信息。" << endl;
    }
}

void StudentList::displayAll() const {
    if (!head) {
        cout << "暂无学生信息。" << endl;
        return;
    }
    cout << "===== 所有学生信息 =====" << endl;
    cout << "学号\t姓名\t性别\t专业\t班级" << endl;
    Student* current = head;
    while (current) {
        cout << current->getId() << "\t" << current->getName() << "\t"
             << current->getGender() << "\t" << current->getMajor() << "\t"
             << current->getClassName() << endl;
        current = current->next;
    }
}

void StudentList::statisticsByMajor() const {
    if (!head) { cout << "暂无学生信息。" << endl; return; }
    cout << "===== 按专业统计 =====" << endl;
    // 简单的统计实现
    struct MajorCount {
        string name;
        int count;
        MajorCount* next;
        MajorCount(string n, int c) : name(n), count(c), next(nullptr) {}
    };
    MajorCount* mcHead = nullptr;
    
    Student* current = head;
    while (current) {
        string major = current->getMajor();
        MajorCount* mc = mcHead;
        bool found = false;
        while (mc) {
            if (mc->name == major) { mc->count++; found = true; break; }
            mc = mc->next;
        }
        if (!found) {
            MajorCount* newNode = new MajorCount(major, 1);
            newNode->next = mcHead;
            mcHead = newNode;
        }
        current = current->next;
    }
    
    MajorCount* mc = mcHead;
    while (mc) {
        cout << "专业: " << mc->name << "  人数: " << mc->count << endl;
        MajorCount* next = mc->next;
        delete mc;
        mc = next;
    }
}

void StudentList::statisticsByClass() const {
    if (!head) { cout << "暂无学生信息。" << endl; return; }
    cout << "===== 按班级统计 =====" << endl;
    struct ClassCount {
        string name;
        int count;
        ClassCount* next;
        ClassCount(string n, int c) : name(n), count(c), next(nullptr) {}
    };
    ClassCount* ccHead = nullptr;
    
    Student* current = head;
    while (current) {
        string className = current->getClassName();
        ClassCount* cc = ccHead;
        bool found = false;
        while (cc) {
            if (cc->name == className) { cc->count++; found = true; break; }
            cc = cc->next;
        }
        if (!found) {
            ClassCount* newNode = new ClassCount(className, 1);
            newNode->next = ccHead;
            ccHead = newNode;
        }
        current = current->next;
    }
    
    ClassCount* cc = ccHead;
    while (cc) {
        cout << "班级: " << cc->name << "  人数: " << cc->count << endl;
        ClassCount* next = cc->next;
        delete cc;
        cc = next;
    }
}

void StudentList::statisticsByGender() const {
    if (!head) { cout << "暂无学生信息。" << endl; return; }
    int male = 0, female = 0;
    Student* current = head;
    while (current) {
        if (current->getGender() == "男") male++;
        else if (current->getGender() == "女") female++;
        current = current->next;
    }
    cout << "===== 按性别统计 =====" << endl;
    cout << "男生: " << male << " 人" << endl;
    cout << "女生: " << female << " 人" << endl;
}

void StudentList::sortByField(int field) {
    // 冒泡排序（链表）
    if (!head || !head->next) return;
    
    bool swapped;
    do {
        swapped = false;
        Student *prev = nullptr, *curr = head, *next = head->next;
        while (next) {
            bool needSwap = false;
            switch (field) {
                case 1: needSwap = curr->getId() > next->getId(); break;
                case 2: needSwap = curr->getName() > next->getName(); break;
                case 3: needSwap = curr->getMajor() > next->getMajor(); break;
                case 4: needSwap = curr->getClassName() > next->getClassName(); break;
            }
            if (needSwap) {
                if (prev) prev->next = next;
                else head = next;
                curr->next = next->next;
                next->next = curr;
                swapped = true;
                
                prev = next;
                next = curr->next;
            } else {
                prev = curr;
                curr = next;
                next = next->next;
            }
        }
    } while (swapped);
    
    cout << "排序完成!" << endl;
    displayAll();
}
