/*
 *Author: Mumtozabegim Olimova
 *Header file for the StudentRecordSystem class, containing
 * method prototypes for managing students using a Binary Search Tree.
 */ 

#pragma once
#include <string>
#include <fstream>

struct Node 
{
public:
    int matriculation_number;
    std::string name;
    std::string programme;
    Node* left;
    Node* right;

    Node(int matriculation_number, std::string name, std::string programme);
};

class StudentRecordSystem {


public:
    StudentRecordSystem();
    ~StudentRecordSystem();

    void add_student(int matriculation_number, std::string name, std::string programme);
    bool find_student_by_matriculation(int matriculation_number);
    int lookup_matriculation_by_name(std::string name);
    int number_enrolled_students();
    void remove_student(int matriculation_number);
    std::string print_student_details();
    void save_to_file(std::string filename);
    void load_from_file(std::string filename);
	
private:
    Node* root;

	std::string print_student_details_recursive(Node *node);
    void add_student_recursive(Node **node, int matriculation_number, std::string name, std::string programme);
    bool find_student_by_matriculation_recursive(Node *node, int matriculation_number);
    int lookup_matriculation_by_name_recursive(Node *node, std::string name);
    int number_enrolled_students_recursive(Node *node);
    void remove_student_recursive(Node **node, int matriculation_number);
    void delete_tree(Node *node);
    void save_to_file_recursive(Node *node, std::ofstream &file);
 
};
