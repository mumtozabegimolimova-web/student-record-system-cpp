/*
 * Author: Mumtozabegim
 * Implementation of the StudentRecordSystem class using a Binary Search Tree.
 */

#include "student_record_system.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Constructor for a Node
Node::Node(int matriculation_number, string name, string programme)
    : matriculation_number(matriculation_number), name(name), programme(programme), left(nullptr), right(nullptr) {}

// Constructor for the StudentRecordSystem
StudentRecordSystem::StudentRecordSystem() : root(nullptr) {}

// Destructor
StudentRecordSystem::~StudentRecordSystem() {
    delete_tree(root);
}

// Recursively delete all nodes to free memory
void StudentRecordSystem::delete_tree(Node *node) {
    if (node != nullptr) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

// Add student
void StudentRecordSystem::add_student(int matriculation_number, string name, string programme) {
    add_student_recursive(&root, matriculation_number, name, programme);
}

void StudentRecordSystem::add_student_recursive(Node **node, int matriculation_number, string name, string programme) {
    if (*node == nullptr) {
        *node = new Node(matriculation_number, name, programme);
    } else if (matriculation_number < (*node)->matriculation_number) {
        add_student_recursive(&((*node)->left), matriculation_number, name, programme);
    } else if (matriculation_number > (*node)->matriculation_number) {
        add_student_recursive(&((*node)->right), matriculation_number, name, programme);
    }
}

// Find by matriculation number
bool StudentRecordSystem::find_student_by_matriculation(int matriculation_number) {
    return find_student_by_matriculation_recursive(root, matriculation_number);
}

bool StudentRecordSystem::find_student_by_matriculation_recursive(Node *node, int matriculation_number) {
    if (node == nullptr) return false;
    if (node->matriculation_number == matriculation_number) return true;
    
    if (matriculation_number < node->matriculation_number)
        return find_student_by_matriculation_recursive(node->left, matriculation_number);
    else
        return find_student_by_matriculation_recursive(node->right, matriculation_number);
}

// Lookup matriculation by name (Linear search in BST as it's not keyed by name)
int StudentRecordSystem::lookup_matriculation_by_name(string name) {
    return lookup_matriculation_by_name_recursive(root, name);
}

int StudentRecordSystem::lookup_matriculation_by_name_recursive(Node *node, string name) {
    if (node == nullptr) return -1;
    if (node->name == name) return node->matriculation_number;

    int left_res = lookup_matriculation_by_name_recursive(node->left, name);
    if (left_res != -1) return left_res;

    return lookup_matriculation_by_name_recursive(node->right, name);
}

// Count enrolled students
int StudentRecordSystem::number_enrolled_students() {
    return number_enrolled_students_recursive(root);
}

int StudentRecordSystem::number_enrolled_students_recursive(Node *node) {
    if (node == nullptr) return 0;
    return 1 + number_enrolled_students_recursive(node->left) + number_enrolled_students_recursive(node->right);
}

// Remove student
void StudentRecordSystem::remove_student(int matriculation_number) {
    remove_student_recursive(&root, matriculation_number);
}

void StudentRecordSystem::remove_student_recursive(Node **node, int matriculation_number) {
    if (*node == nullptr) return;

    if (matriculation_number < (*node)->matriculation_number) {
        remove_student_recursive(&((*node)->left), matriculation_number);
    } else if (matriculation_number > (*node)->matriculation_number) {
        remove_student_recursive(&((*node)->right), matriculation_number);
    } else {
        // Node found
        Node *temp = *node;
        if ((*node)->left == nullptr) {
            *node = (*node)->right;
            delete temp;
        } else if ((*node)->right == nullptr) {
            *node = (*node)->left;
            delete temp;
        } else {
            // Node with two children: Get successor (smallest in right subtree)
            Node *successor = (*node)->right;
            while (successor->left != nullptr) successor = successor->left;
            
            (*node)->matriculation_number = successor->matriculation_number;
            (*node)->name = successor->name;
            (*node)->programme = successor->programme;
            
            remove_student_recursive(&((*node)->right), successor->matriculation_number);
        }
    }
}

// Printing details
string StudentRecordSystem::print_student_details() {
    return print_student_details_recursive(root);
}

string StudentRecordSystem::print_student_details_recursive(Node *node) {
    string result;
    if (node == nullptr) return result;

    result += print_student_details_recursive(node->left);
    result += to_string(node->matriculation_number) + "," + node->name + "," + node->programme + "\n";
    result += print_student_details_recursive(node->right);
    return result;
}

// File Operations
void StudentRecordSystem::save_to_file(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        save_to_file_recursive(root, file);
        file.close();
    }
}

void StudentRecordSystem::save_to_file_recursive(Node *node, ofstream& file) {
    if (node == nullptr) return;
    // Pre-order traversal
    file << node->matriculation_number << "," << node->name << "," << node->programme << "\n";
    save_to_file_recursive(node->left, file);
    save_to_file_recursive(node->right, file);
}

void StudentRecordSystem::load_from_file(string filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string m_str, name, prog;
        if (getline(ss, m_str, ',') && getline(ss, name, ',') && getline(ss, prog)) {
            add_student(stoi(m_str), name, prog);
        }
    }
}