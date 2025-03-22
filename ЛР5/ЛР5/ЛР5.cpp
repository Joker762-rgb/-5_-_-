//������� 9. ������ - ���������(����: ���, ����, ������ �� ������, ���������, ������� �����), �������� ��������� vector �������� � deque
// ���������� �� ������
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;

class Employee {
public:
    string name;
    string hireDate;
    string position;
    double salary;

    Employee() : name(""), hireDate(""), position(""), salary(0.0) {}

    Employee(string n, string hd, string p, double s)
        : name(n), hireDate(hd), position(p), salary(s) {}

    // ���������� ��������� ��� ������ ������� � �����
    friend ostream& operator<<(ostream& os, const Employee& emp) {
        os << "Name: " << emp.name << ", Hire Date: " << emp.hireDate
            << ", Position: " << emp.position << ", Salary: " << emp.salary;
        return os;
    }

    // ���������� ��������� ��� ���������� �� ������ (��� set)
    bool operator<(const Employee& other) const {
        return salary > other.salary; // ���������� �� �������� ��������
    }

    // ���������� ��������� ��������� (��� unordered_set)
    bool operator==(const Employee& other) const {
        return name == other.name && hireDate == other.hireDate &&
            position == other.position && salary == other.salary;
    }
};

// ���-������� ��� Employee (��� unordered_set)
struct EmployeeHash {
    size_t operator()(const Employee& emp) const {
        return hash<string>()(emp.name) ^ hash<string>()(emp.hireDate) ^
            hash<string>()(emp.position) ^ hash<double>()(emp.salary);
    }
};

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    vector<Employee> vec;
    set<Employee> empSet; // ��������� set ��� ���������� �� ��������
    unordered_set<Employee, EmployeeHash> empUnorderedSet; // ��������� unordered_set

    string name, hireDate, position;
    double salary;
    while (input >> name >> hireDate >> position >> salary) {
        Employee emp(name, hireDate, position, salary);
        vec.emplace_back(emp);
        empSet.insert(emp); // ���������� � set
        empUnorderedSet.insert(emp); // ���������� � unordered_set
    }

    // ����� ��������� �������
    output << "Original vector:\n";
    cout << "Original vector:\n";
    for (const auto& emp : vec) {
        output << emp << "\n";
        cout << emp << "\n";
    }

    // ����� ����������� set (���������������� �� ��������)
    output << "\nSet (sorted by salary):\n";
    cout << "\nSet (sorted by salary):\n";
    for (const auto& emp : empSet) {
        output << emp << "\n";
        cout << emp << "\n";
    }

    // ����� ����������� unordered_set
    output << "\nUnordered Set:\n";
    cout << "\nUnordered Set:\n";
    for (const auto& emp : empUnorderedSet) {
        output << emp << "\n";
        cout << emp << "\n";
    }

    input.close();
    output.close();

    return 0;
}