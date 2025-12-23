#ifndef TASK_1F_H
#define TASK_1F_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>

// выбор между весом и объемом
union ProductSpec {
    double volume;
    double weight;
};

struct FactoryProduct {
    char name[50];
    int quantity;
    int workshop_num;
    double unit_price;
    double batch_value;
    int spec_type;
    ProductSpec spec;
};

FactoryProduct* createArray(int& size);
double getPositiveNum();
void displayArray(FactoryProduct* arr, int size);
void addElement(FactoryProduct*& arr, int& size);
void deleteElement(FactoryProduct*& arr, int& size);
void searchByWorkshop(FactoryProduct* arr, int size);
void shakerSort(FactoryProduct* arr, int size);
void modifyInFile(const char* filename);

#endif