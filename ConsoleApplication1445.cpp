#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Завдання 1: Використання std::unique_ptr та спільне використання ресурсів

class Employee {
public:
    Employee(const std::string& name, int id) : name(name), id(id) {}
    void display() const {
        std::cout << "Employee Name: " << name << ", ID: " << id << std::endl;
    }
private:
    std::string name;
    int id;
};

std::unique_ptr<Employee> createEmployee(const std::string& name, int id) {
    return std::make_unique<Employee>(name, id);
}

void transferOwnership(std::unique_ptr<Employee>& from, std::unique_ptr<Employee>& to) {
    to = std::move(from);
}

// Завдання 2: Використання std::shared_ptr і std::weak_ptr

class Department; // Попереднє оголошення класу Department

class Company {
public:
    Company(const std::string& name) : name(name) {}
    void addDepartment(const std::shared_ptr<Department>& dept) {
        departments.push_back(dept);
    }
    void display() const;
private:
    std::string name;
    std::vector<std::weak_ptr<Department>> departments;
};

class Department {
public:
    Department(const std::string& name, const std::shared_ptr<Company>& company)
        : name(name), company(company) {}
    void display() const {
        std::cout << "Department: " << name << std::endl;
    }
private:
    std::string name;
    std::weak_ptr<Company> company;
};

void Company::display() const {
    std::cout << "Company: " << name << std::endl;
    for (const auto& dept : departments) {
        if (auto deptPtr = dept.lock()) {
            deptPtr->display();
        }
    }
}

int main() {
    // Завдання 1: Використання std::unique_ptr
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(createEmployee("John Doe", 1));
    employees.push_back(createEmployee("Jane Smith", 2));

    std::vector<std::unique_ptr<Employee>> transferredEmployees;
    transferOwnership(employees[0], transferredEmployees.emplace_back());

    for (const auto& emp : transferredEmployees) {
        emp->display();
    }

    // Завдання 2: Використання std::shared_ptr і std::weak_ptr
    auto company = std::make_shared<Company>("Tech Corp");
    auto dept1 = std::make_shared<Department>("HR", company);
    auto dept2 = std::make_shared<Department>("IT", company);

    company->addDepartment(dept1);
    company->addDepartment(dept2);

    company->display();

    return 0;
}
