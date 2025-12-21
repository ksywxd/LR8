#ifndef TASK_2F_H
#define TASK_2F_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

union BookSpec {
    int weight;
    double fileSize;
};

struct LibraryBook {
    char regNumber[20];
    char author[50];
    char title[100];
    int year;
    char publisher[50];
    int pages;
    int bookType;
    BookSpec spec;
};

LibraryBook* createLibrary(int& size);
void displayLibrary(LibraryBook* arr, int size);
void addBook(LibraryBook*& arr, int& size);
void deleteBook(LibraryBook*& arr, int& size);
void filterAndSortBooks(LibraryBook* arr, int size);
void modifyBookInFile(const char* filename);

#endif