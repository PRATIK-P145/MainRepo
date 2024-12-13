#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    int rollNo;
    string name;
    char division;
    string address;
};

void addRecord(fstream &file) {
    Student student;

    cout << "Enter roll number: ";
    cin >> student.rollNo;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, student.name);
    cout << "Enter division (A, B, C, D): ";
    cin >> student.division;
    cin.ignore();
    cout << "Enter address: ";
    getline(cin, student.address);

    file.write(reinterpret_cast<char*>(&student), sizeof(Student));
    cout << "Record added successfully!" << endl;
}

void displayAllRecords(fstream &file) {
    Student student;

    file.seekg(0);
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        cout << "Roll No: " << student.rollNo << endl;
        cout << "Name: " << student.name << endl;
        cout << "Division: " << student.division << endl;
        cout << "Address: " << student.address << endl << endl;
    }
}

void searchRecord(fstream &file, int rollNo) {
    Student student;
    bool found = false;

    file.seekg(0);
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.rollNo == rollNo) {
            found = true;
            cout << "Record found:" << endl;
            cout << "Roll No: " << student.rollNo << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            break;
        }
    }

    if (!found) {
        cout << "Record not found!" << endl;
    }
}

void deleteRecord(fstream &file, int rollNo) {
    fstream tempFile("temp.dat", ios::out | ios::binary);
    Student student;
    bool found = false;

    file.seekg(0);
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.rollNo != rollNo) {
            tempFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        cout << "Record deleted successfully!" << endl;
    } else {
        cout << "Record not found!" << endl;
    }
}

int main() {
    fstream file;
    int choice, rollNo;

    file.open("student.dat", ios::in | ios::out | ios::binary | ios::app);

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    while (true) {
        cout << "1. Add Record" << endl;
        cout << "2. Display All Records" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayAllRecords(file);
                break;
            case 3:
                cout << "Enter roll number to search: ";
                cin >> rollNo;
                searchRecord(file, rollNo);
                break;
            case 4:
                cout << "Enter roll number to delete: ";
                cin >> rollNo;
                deleteRecord(file, rollNo);
                break;
            case 5:
                file.close();
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
