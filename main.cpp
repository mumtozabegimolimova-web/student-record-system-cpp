/*
 * Author: Mumtozabegim Olimova
 * Menu-based user interface for the Student Record System.
 */

#include "student_record_system.h"
#include <iostream>
#include <string>

using namespace std;

void show_menu() {
    cout << "\n--- Student Record System Menu ---" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Find Student by Matriculation" << endl;
    cout << "3. Lookup Matriculation by Name" << endl;
    cout << "4. Count Enrolled Students" << endl;
    cout << "5. Print All Students" << endl;
    cout << "6. Remove Student" << endl;
    cout << "7. Save to File" << endl;
    cout << "8. Load from File" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    StudentRecordSystem system;
    int choice;
    int matric;
    string name, prog, filename;

    do {
        show_menu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter matriculation number: "; cin >> matric;
                cin.ignore();
                cout << "Enter name: "; getline(cin, name);
                cout << "Enter programme: "; getline(cin, prog);
                system.add_student(matric, name, prog);
                break;
            case 2:
                cout << "Enter matriculation number to find: "; cin >> matric;
                if (system.find_student_by_matriculation(matric))
                    cout << "Student found!" << endl;
                else
                    cout << "Student not found." << endl;
                break;
            case 3:
                cin.ignore();
                cout << "Enter name to lookup: "; getline(cin, name);
                matric = system.lookup_matriculation_by_name(name);
                if (matric != -1)
                    cout << "Matriculation number: " << matric << endl;
                else
                    cout << "No student found with that name." << endl;
                break;
            case 4:
                cout << "Total students: " << system.number_enrolled_students() << endl;
                break;
            case 5:
                cout << "Student List:\n" << system.print_student_details();
                break;
            case 6:
                cout << "Enter matriculation to remove: "; cin >> matric;
                system.remove_student(matric);
                cout << "Student removed (if they existed)." << endl;
                break;
            case 7:
                cout << "Enter filename to save: "; cin >> filename;
                system.save_to_file(filename);
                break;
            case 8:
                cout << "Enter filename to load: "; cin >> filename;
                system.load_from_file(filename);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}