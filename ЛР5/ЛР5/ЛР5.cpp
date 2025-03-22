//Вариант 9. объект - сотрудник(поля: ФИО, дата, приема на работу, должность, базовый оклад), исходный контейнер vector копируем в deque
// сортировка по окладу
//Для класса, разработанного в ЛР4, обеспечить возможность добавления объектов в
//контейнер set(сортировка как указано в задании на ЛР4) и в контейнер unordered_set.
//Исходные данные как в ЛР4 читать из файла, вывести на печать для контроля объекты
//контейнеров
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

    // Перегрузка оператора для вывода объекта в поток
    friend ostream& operator<<(ostream& os, const Employee& emp) {
        os << "Name: " << emp.name << ", Hire Date: " << emp.hireDate
            << ", Position: " << emp.position << ", Salary: " << emp.salary;
        return os;
    }

    // Перегрузка оператора для сортировки по окладу (для set)
    bool operator<(const Employee& other) const {
        return salary > other.salary; // // Сортировка по убыванию зарплаты
    }

    // Перегрузка оператора равенства (для unordered_set)
    bool operator==(const Employee& other) const {
        return name == other.name && hireDate == other.hireDate &&
            position == other.position && salary == other.salary;
    }
};

// Хэш-функция для Employee (для unordered_set)
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
    set<Employee> empSet; // Контейнер set для сортировки по зарплате
    unordered_set<Employee, EmployeeHash> empUnorderedSet; // Контейнер unordered_set

    string name, hireDate, position;
    double salary;
    while (input >> name >> hireDate >> position >> salary) {
        Employee emp(name, hireDate, position, salary);
        vec.emplace_back(emp);
        empSet.insert(emp); // Добавление в set
        empUnorderedSet.insert(emp); // Добавление в unordered_set
    }

    // Вывод исходного вектора
    output << "Original vector:\n";
    cout << "Original vector:\n";
    for (const auto& emp : vec) {
        output << emp << "\n";
        cout << emp << "\n";
    }

    // Вывод содержимого set (отсортированного по зарплате)
    output << "\nSet (sorted by salary):\n";
    cout << "\nSet (sorted by salary):\n";
    for (const auto& emp : empSet) {
        output << emp << "\n";
        cout << emp << "\n";
    }

    // Вывод содержимого unordered_set
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
