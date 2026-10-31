#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    int marks[5];

public:
    Student() {
        rollNo = 0;
        name = "";
        for (int i = 0; i < 5; i++) {
            marks[i] = 0;
        }
    }

    int getRollNo() {
        return rollNo;
    }

    string getName() {
        return name;
    }

    int getTotal() {
        int total = 0;
        for (int i = 0; i < 5; i++) {
            total += marks[i];
        }
        return total;
    }

    double getAverage() {
        return getTotal() / 5.0;
    }

    void input() {
        cout << "Enter Roll Number: ";
        while (!(cin >> rollNo) || rollNo <= 0) {
            cout << "Enter a positive roll number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Student Name: ";
        getline(cin, name);

        string subjects[5] = {
            "C++", "DBMS", "ADSA", "Mathematics", "AI"
        };

        for (int i = 0; i < 5; i++) {
            cout << "Enter marks in " << subjects[i]
                 << " (0-100): ";

            while (!(cin >> marks[i]) ||
                   marks[i] < 0 || marks[i] > 100) {
                cout << "Invalid marks! Enter between 0 and 100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void display() {
        string subjects[5] = {
            "C++", "DBMS", "ADSA", "Mathematics", "AI"
        };

        cout << "\nRoll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;

        for (int i = 0; i < 5; i++) {
            cout << subjects[i] << ": "
                 << marks[i] << "/100" << endl;
        }

        cout << "Total Marks: " << getTotal() << "/500" << endl;
        cout << "Average Marks: " << getAverage() << "/100" << endl;
    }
};

class StudentRecordManager {
private:
    Student students[50];
    int count;

    int findStudent(int roll) {
        for (int i = 0; i < count; i++) {
            if (students[i].getRollNo() == roll) {
                return i;
            }
        }
        return -1;
    }

public:
    StudentRecordManager() {
        count = 0;
    }

    void addStudent() {
        if (count >= 50) {
            cout << "Student record capacity is full!" << endl;
            return;
        }

        Student s;
        s.input();

        if (findStudent(s.getRollNo()) != -1) {
            cout << "Roll number already exists!" << endl;
            return;
        }

        students[count] = s;
        count++;

        cout << "Student added successfully!" << endl;
    }

    void displayStudents() {
        if (count == 0) {
            cout << "No student records available." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << "\n--- Student " << i + 1 << " ---" << endl;
            students[i].display();
        }
    }

    void searchStudent() {
        int roll;
        cout << "Enter roll number to search: ";

        if (!(cin >> roll)) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findStudent(roll);

        if (index == -1) {
            cout << "Student not found." << endl;
        } else {
            students[index].display();
        }
    }

    void updateStudent() {
        int roll;
        cout << "Enter roll number to update: ";

        if (!(cin >> roll)) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findStudent(roll);

        if (index == -1) {
            cout << "Student not found." << endl;
            return;
        }

        cout << "Enter updated student details:" << endl;

        Student updated;
        updated.input();

        int duplicate = findStudent(updated.getRollNo());

        if (duplicate != -1 && duplicate != index) {
            cout << "Roll number already exists! Update cancelled." << endl;
            return;
        }

        students[index] = updated;
        cout << "Student updated successfully!" << endl;
    }

    void deleteStudent() {
        int roll;
        cout << "Enter roll number to delete: ";

        if (!(cin >> roll)) {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findStudent(roll);

        if (index == -1) {
            cout << "Student not found." << endl;
            return;
        }

        for (int i = index; i < count - 1; i++) {
            students[i] = students[i + 1];
        }

        count--;
        cout << "Student deleted successfully!" << endl;
    }

    void marksAnalysis() {
        if (count == 0) {
            cout << "No records available for analysis." << endl;
            return;
        }

        int highest = 0;
        int lowest = 0;
        double totalAverage = 0;

        for (int i = 0; i < count; i++) {
            double avg = students[i].getAverage();
            totalAverage += avg;

            if (avg > students[highest].getAverage()) {
                highest = i;
            }

            if (avg < students[lowest].getAverage()) {
                lowest = i;
            }
        }

        cout << "\n--- Marks Analysis ---" << endl;

        cout << "Highest Average: "
             << students[highest].getName() << " ("
             << students[highest].getAverage() << ")" << endl;

        cout << "Lowest Average: "
             << students[lowest].getName() << " ("
             << students[lowest].getAverage() << ")" << endl;

        cout << "Class Average: "
             << totalAverage / count << endl;
    }

    void menu() {
        int choice = 0;

        do {
            cout << "\n===== STUDENT RECORD MANAGEMENT SYSTEM =====" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Display Students" << endl;
            cout << "3. Search Student" << endl;
            cout << "4. Update Student" << endl;
            cout << "5. Delete Student" << endl;
            cout << "6. Marks Analysis" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input! Enter a number from 1 to 7." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    displayStudents();
                    break;
                case 3:
                    searchStudent();
                    break;
                case 4:
                    updateStudent();
                    break;
                case 5:
                    deleteStudent();
                    break;
                case 6:
                    marksAnalysis();
                    break;
                case 7:
                    cout << "Exiting the system. Thank you!" << endl;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }

        } while (choice != 7);
    }
};

int main() {
    StudentRecordManager manager;
    manager.menu();
    return 0;
}