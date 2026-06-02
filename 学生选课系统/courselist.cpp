#include "courselist.h"

CourseList::~CourseList() {
    Course* current = head;
    while (current) {
        Course* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void CourseList::loadFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "提示: 文件 " << filename << " 不存在，将创建新文件。" << endl;
        return;
    }
    string id, name, type, semester;
    int totalHours, lectureHours, labHours;
    float credits;
    while (infile >> id >> name >> type >> totalHours >> lectureHours 
           >> labHours >> credits >> semester) {
        Course c(id, name, type, totalHours, lectureHours, labHours, 
                 credits, semester);
        add(c);
    }
    infile.close();
    cout << "已从 " << filename << " 加载课程数据。" << endl;
}

void CourseList::saveToFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "错误: 无法打开文件 " << filename << " 进行写入。" << endl;
        return;
    }
    Course* current = head;
    while (current) {
        outfile << current->getId() << " " << current->getName() << " "
                << current->getType() << " " << current->getTotalHours() << " "
                << current->getLectureHours() << " " << current->getLabHours() << " "
                << current->getCredits() << " " << current->getSemester() << endl;
        current = current->next;
    }
    outfile.close();
}

void CourseList::add(Course& c) {
    Course* newNode = new Course(c);
    newNode->next = nullptr;
    if (!head) {
        head = newNode;
    } else {
        Course* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool CourseList::remove(const string& id) {
    if (!head) return false;
    
    Course *prev = nullptr, *current = head;
    while (current) {
        if (current->getId() == id) {
            if (prev) prev->next = current->next;
            else head = current->next;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

bool CourseList::modify(const string& id) {
    Course* c = findById(id);
    if (!c) {
        cout << "未找到课程编号为 " << id << " 的课程。" << endl;
        return false;
    }
    cout << "当前课程信息:" << endl;
    c->display();
    cout << "请输入新的信息（输入-1保留原值）:" << endl;
    
    string inputStr;
    int inputInt;
    float inputFloat;
    
    cout << "课程名称 [" << c->getName() << "]: ";
    cin.ignore();
    getline(cin, inputStr);
    if (inputStr != "-1") c->setName(inputStr);
    
    cout << "课程性质 [" << c->getType() << "]: ";
    getline(cin, inputStr);
    if (inputStr != "-1") c->setType(inputStr);
    
    cout << "总学时 [" << c->getTotalHours() << "]: ";
    cin >> inputInt;
    if (inputInt != -1) c->setTotalHours(inputInt);
    
    cout << "授课学时 [" << c->getLectureHours() << "]: ";
    cin >> inputInt;
    if (inputInt != -1) c->setLectureHours(inputInt);
    
    cout << "实验/上机学时 [" << c->getLabHours() << "]: ";
    cin >> inputInt;
    if (inputInt != -1) c->setLabHours(inputInt);
    
    cout << "学分 [" << c->getCredits() << "]: ";
    cin >> inputFloat;
    if (inputFloat != -1) c->setCredits(inputFloat);
    
    cout << "开课学期 [" << c->getSemester() << "]: ";
    cin.ignore();
    getline(cin, inputStr);
    if (inputStr != "-1") c->setSemester(inputStr);
    
    cout << "修改成功!" << endl;
    return true;
}

Course* CourseList::findById(const string& id) {
    Course* current = head;
    while (current) {
        if (current->getId() == id) return current;
        current = current->next;
    }
    return nullptr;
}

void CourseList::fuzzySearch(int field, const string& keyword) const {
    Course* current = head;
    bool found = false;
    cout << "===== 查询结果 =====" << endl;
    while (current) {
        string fieldValue;
        switch (field) {
            case 1: fieldValue = current->getName(); break;
            case 2: fieldValue = current->getType(); break;
            case 3: fieldValue = current->getSemester(); break;
            case 4: fieldValue = current->getId(); break;
        }
        if (fieldValue.find(keyword) != string::npos) {
            current->display();
            found = true;
        }
        current = current->next;
    }
    if (!found) cout << "未找到匹配的课程信息。" << endl;
}

void CourseList::searchByCredits(float minCredits, float maxCredits) const {
    Course* current = head;
    bool found = false;
    cout << "===== 学分范围 " << minCredits << " - " << maxCredits << " 的课程 =====" << endl;
    while (current) {
        if (current->getCredits() >= minCredits && current->getCredits() <= maxCredits) {
            current->display();
            found = true;
        }
        current = current->next;
    }
    if (!found) cout << "未找到符合条件的课程。" << endl;
}

void CourseList::displayAll() const {
    if (!head) {
        cout << "暂无课程信息。" << endl;
        return;
    }
    cout << "===== 所有课程信息 =====" << endl;
    cout << "编号\t名称\t性质\t总学时\t授课\t实验\t学分\t学期" << endl;
    Course* current = head;
    while (current) {
        cout << current->getId() << "\t" << current->getName() << "\t"
             << current->getType() << "\t" << current->getTotalHours() << "\t"
             << current->getLectureHours() << "\t" << current->getLabHours() << "\t"
             << current->getCredits() << "\t" << current->getSemester() << endl;
        current = current->next;
    }
}

void CourseList::sortByField(int field) {
    if (!head || !head->next) return;
    
    bool swapped;
    do {
        swapped = false;
        Course *prev = nullptr, *curr = head, *next = head->next;
        while (next) {
            bool needSwap = false;
            switch (field) {
                case 1: needSwap = curr->getId() > next->getId(); break;
                case 2: needSwap = curr->getName() > next->getName(); break;
                case 3: needSwap = curr->getCredits() < next->getCredits(); break;
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
