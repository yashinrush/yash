#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to hold student information
struct Student {
    int rollNo;
    string name;
    string division;
    string address;

    // Function to take student details as input
    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore(); // to ignore the newline character
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);
    }

    // Function to display student details
    void display() {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }

    // Function to write student details to a file
    void writeToFile(ofstream &outFile) {
        outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }

    // Function to read student details from a file
    void readFromFile(ifstream &inFile) {
        inFile.read(reinterpret_cast<char*>(this), sizeof(*this));
    }
};

// Function to add a new student record to the file
void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student student;
    student.input();
    student.writeToFile(outFile);
    outFile.close();
    cout << "Student added successfully!" << endl;
}

// Function to delete a student record by roll number
void deleteStudent(int rollNo) {
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student student;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.rollNo == rollNo) {
            found = true;
        } else {
            student.writeToFile(outFile);
        }
    }

    inFile.close();
    outFile.close();

    // Remove the old file and rename the new one
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student record deleted successfully!" << endl;
    else
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
}

// Function to display a student's details by roll number
void displayStudent(int rollNo) {
    ifstream inFile("students.dat", ios::binary);
    Student student;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        if (student.rollNo == rollNo) {
            student.display();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found)
        cout << "Student with Roll Number " << rollNo << " not found." << endl;
}

// Function to display all students' details
void displayAllStudents() {
    ifstream inFile("students.dat", ios::binary);
    Student student;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(student))) {
        student.display();
        cout << "-----------------------------" << endl;
        found = true;
    }

    inFile.close();

    if (!found)
        cout << "No records found." << endl;
}

int main() {
    int choice;
    int rollNo;

    do {
        cout << "\nStudent Information System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Display All Students" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNo;
                deleteStudent(rollNo);
                break;
            case 3:
                cout << "Enter Roll Number to display: ";
                cin >> rollNo;
                displayStudent(rollNo);
                break;
            case 4:
                displayAllStudents();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
