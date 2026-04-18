# Author: Mumtozabegim Olimova
# Makefile for Student Record System

CXX = g++
CXXFLAGS = -Wall -std=c++11

LIBRARY = libstudent.a
LIB_OBJ = student_record_system.o
TEST_EXE = test_system
MENU_EXE = student_app

all: $(TEST_EXE) $(MENU_EXE)

$(LIB_OBJ): student_record_system.cpp student_record_system.h
	$(CXX) $(CXXFLAGS) -c student_record_system.cpp -o $(LIB_OBJ)

$(LIBRARY): $(LIB_OBJ)
	ar rcs $(LIBRARY) $(LIB_OBJ)

$(TEST_EXE): test.cpp $(LIBRARY)
	$(CXX) $(CXXFLAGS) test.cpp -L. -lstudent -o $(TEST_EXE)

$(MENU_EXE): main.cpp $(LIBRARY)
	$(CXX) $(CXXFLAGS) main.cpp -L. -lstudent -o $(MENU_EXE)

clean:
	rm -f *.o *.a $(TEST_EXE) $(MENU_EXE)