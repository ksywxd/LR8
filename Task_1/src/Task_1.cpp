#include "Task_1F.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int main() {
    FactoryProduct* catalog = nullptr;
    int size = 0;
    int choice;
    const char* filename = "factory.dat";

    while (true)
    {
        cout << "1. Create List\t\t2. Show Catalog" << endl;
        cout << "3. Add Product\t\t4. Total Workshop Qty" << endl;
        cout << "5. Delete Product\t6. Modify in File" << endl;
        cout << "7. Shaker Sort (Qty)\t8. Save to File" << endl;
        cout << "0. Exit" << endl;
        cout << "Your Choice: ";

        choice = (int)getPositiveNum();

        switch (choice) {
        case 1:
            // Если массив уже существует, удаляем его перед созданием нового
            if (catalog) {
                delete[] catalog;
                catalog = nullptr;
                size = 0;
            }
            catalog = createArray(size);
            break;

        case 2:
            displayArray(catalog, size);
            break;

        case 3:
            addElement(catalog, size);
            break;

        case 4:
            searchByWorkshop(catalog, size);
            break;

        case 5:
            deleteElement(catalog, size);
            break;

        case 6:
            modifyInFile(filename);
            break;

        case 7:
            shakerSort(catalog, size);
            cout << "Sorted by Quantity (Descending):" << endl;
            displayArray(catalog, size);
            break;

        case 8: {
            if (!catalog || size == 0) {
                cout << "Error: Nothing to save. Create list first." << endl;
            } else {
                // ios::trunc перезаписывает файл заново
                ofstream ofs(filename, ios::binary | ios::trunc);
                if (ofs.is_open()) {
                    //количество товаров × размер одного товара в байтах
                    ofs.write((char*)catalog, size * sizeof(FactoryProduct));
                    ofs.close();
                    cout << "Success: Data saved to " << filename << endl;
                } else {
                    cout << "File error: Could not open file for writing." << endl;
                }
            }
            break;
        }

        case 0:
            cout << "Exiting program..." << endl;
            if (catalog) delete[] catalog;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}