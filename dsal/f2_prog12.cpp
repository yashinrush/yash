#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    int empID;
    string name, designation;
    double salary;

    void input() {
        cout << "Enter Employee ID: "; cin >> empID;
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Designation: "; getline(cin, designation);
        cout << "Enter Salary: "; cin >> salary;
    }

    void display() {
        cout << "ID: " << empID << ", Name: " << name << ", Designation: " << designation << ", Salary: " << salary << endl;
    }

    void writeToFile(ofstream &outFile) {
        outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }

    void readFromFile(ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(this), sizeof(*this));
    }
};

void addEmployee() {
    ofstream outFile("employee.dat", ios::binary | ios::app);
    ofstream idxFile("employee.idx", ios::binary | ios::app);
    Employee emp;
    emp.input();
    emp.writeToFile(outFile);
    idxFile.write(reinterpret_cast<char*>(&emp.empID), sizeof(emp.empID));
}

void deleteEmployee(int empID) {
    ifstream inFile("employee.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    ifstream idxFile("employee.idx", ios::binary);
    ofstream tempIdx("temp.idx", ios::binary);

    Employee emp;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        if (emp.empID == empID) {
            found = true;
        } else {
            emp.writeToFile(outFile);
        }
    }

    int id;
    while (idxFile.read(reinterpret_cast<char*>(&id), sizeof(id))) {
        if (id != empID) tempIdx.write(reinterpret_cast<char*>(&id), sizeof(id));
    }

    inFile.close(); outFile.close(); idxFile.close(); tempIdx.close();
    remove("employee.dat");
    rename("temp.dat", "employee.dat");
    remove("employee.idx");
    rename("temp.idx", "employee.idx");

    if (found) cout << "Employee deleted successfully!" << endl;
    else cout << "Employee not found." << endl;
}

void displayEmployee(int empID) {
    ifstream inFile("employee.dat", ios::binary);
    Employee emp;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        if (emp.empID == empID) {
            emp.display();
            found = true;
            break;
        }
    }
    if (!found) cout << "Employee not found." << endl;
}

void displayAllEmployees() {
    ifstream inFile("employee.dat", ios::binary);
    Employee emp;
    while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        emp.display();
    }
}

int main() {
    int choice, empID;
    do {
        cout << "\n1. Add Employee\n2. Delete Employee\n3. Display Employee\n4. Display All Employees\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: cout << "Enter Employee ID to delete: "; cin >> empID; deleteEmployee(empID); break;
            case 3: cout << "Enter Employee ID to display: "; cin >> empID; displayEmployee(empID); break;
            case 4: displayAllEmployees(); break;
        }
    } while (choice != 5);
    return 0;
}
