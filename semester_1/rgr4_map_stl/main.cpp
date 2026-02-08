#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

struct Mark {
    std::string subject;
    size_t mark;
};

struct StudentData {
    std::string name;
    size_t number;
    std::vector<Mark> marks;

    double average() const {
        if (marks.empty()) return 0.0;
        double sum = 0.0;
        for (std::vector<Mark>::const_iterator it = marks.begin(); it != marks.end(); ++it) {
            sum += static_cast<double>(it->mark);
        }
        return sum / marks.size();
    }

    size_t total() const {
        size_t sum = 0;
        for (std::vector<Mark>::const_iterator it = marks.begin(); it != marks.end(); ++it) {
            sum += it->mark;
        }
        return sum;
    }

    bool hasBadMarks() const {
        for (std::vector<Mark>::const_iterator it = marks.begin(); it != marks.end(); ++it) {
            if (it->mark <= 3) return true;
        }
        return false;
    }
};

struct SubjectAverage {
    std::string subject;
    double average;
};

bool compareByName(const StudentData& a, const StudentData& b) {
    if (a.name == b.name) return a.average() > b.average();
    return a.name < b.name;
}

bool compareByAverageDesc(const StudentData& a, const StudentData& b) {
    return a.average() > b.average();
}

bool compareSubjectsByAverage(const SubjectAverage& a, const SubjectAverage& b) {
    return a.average > b.average;
}

std::map<size_t, StudentData> loadStudents(const std::string& filename) {
    std::map<size_t, StudentData> students;
    std::ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        std::cerr << "Error: cannot open file " << filename << "\n";
        return students;
    }
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        StudentData st;
        iss >> st.name >> st.number;
        std::string subject;
        size_t mark;
        while (iss >> subject >> mark) {
            Mark m;
            m.subject = subject;
            m.mark = mark;
            st.marks.push_back(m);
        }
        students[st.number] = st;
    }
    return students;
}

void task4(const std::map<size_t, StudentData>& students) {
    std::vector<StudentData> sorted;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        sorted.push_back(it->second);
    }
    std::sort(sorted.begin(), sorted.end(), compareByName);
    int idx = 1;
    std::cout << "Task 4:\n";
    for (std::vector<StudentData>::const_iterator it = sorted.begin(); it != sorted.end(); ++it) {
        std::cout << idx++ << " " << it->name << " " << it->number << " " << it->average() << "\n";
    }
}

void task5(const std::map<size_t, StudentData>& students, double low, double high) {
    std::vector<StudentData> filtered;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        double avg = it->second.average();
        if (avg >= low && avg <= high) filtered.push_back(it->second);
    }
    std::sort(filtered.begin(), filtered.end(), compareByAverageDesc);
    std::cout << "\nTask 5:\n";
    for (std::vector<StudentData>::const_iterator it = filtered.begin(); it != filtered.end(); ++it) {
        std::cout << it->name << " " << it->average() << "\n";
    }
}

void task6(const std::map<size_t, StudentData>& students, const std::string& subject) {
    std::cout << "\nTask 6:\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        for (std::vector<Mark>::const_iterator m = it->second.marks.begin(); m != it->second.marks.end(); ++m) {
            if (m->subject == subject) {
                std::cout << it->second.name << " " << it->second.number << "\n";
                break;
            }
        }
    }
}

void task7(const std::map<size_t, StudentData>& students) {
    std::map<std::string, size_t> subjectCount;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        for (std::vector<Mark>::const_iterator m = it->second.marks.begin(); m != it->second.marks.end(); ++m) {
            subjectCount[m->subject]++;
        }
    }
    std::cout << "\nTask 7:\n";
    for (std::map<std::string, size_t>::const_iterator it = subjectCount.begin(); it != subjectCount.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }
}

void task8(const std::map<size_t, StudentData>& students) {
    struct SubjectStat {
        double sum;
        size_t count;
        SubjectStat() : sum(0.0), count(0) {}
    };
    std::map<std::string, SubjectStat> stats;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        for (std::vector<Mark>::const_iterator m = it->second.marks.begin(); m != it->second.marks.end(); ++m) {
            stats[m->subject].sum += m->mark;
            stats[m->subject].count++;
        }
    }
    std::vector<SubjectAverage> averages;
    for (std::map<std::string, SubjectStat>::const_iterator it = stats.begin(); it != stats.end(); ++it) {
        SubjectAverage sa;
        sa.subject = it->first;
        sa.average = it->second.sum / it->second.count;
        averages.push_back(sa);
    }
    std::sort(averages.begin(), averages.end(), compareSubjectsByAverage);
    std::cout << "\nTask 8:\n";
    for (std::vector<SubjectAverage>::const_iterator it = averages.begin(); it != averages.end(); ++it) {
        std::cout << it->subject << ": " << it->average << "\n";
    }
}

void task9(const std::map<size_t, StudentData>& students) {
    size_t maxSum = 0;
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        if (it->second.total() > maxSum) maxSum = it->second.total();
    }
    std::cout << "\nTask 9:\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        if (it->second.total() == maxSum) {
            std::cout << it->second.name << " " << it->second.total() << "\n";
        }
    }
}

void task10(const std::map<size_t, StudentData>& students) {
    std::cout << "\nTask 10:\n";
    for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it) {
        if (it->second.hasBadMarks()) {
            std::cout << it->second.name << " " << it->second.number << "\n";
        }
    }
}

int main() {
    std::map<size_t, StudentData> students = loadStudents("students.txt");
    if (students.empty()) {
        std::cout << "No data.\n";
        return 0;
    }
    task4(students);
    task5(students, 5.0, 8.0);
    task6(students, "PE");
    task7(students);
    task8(students);
    task9(students);
    task10(students);
    return 0;
}
