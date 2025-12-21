#include "Task_1F.h"
using namespace std;

int main() {
    FactoryProduct* catalog = nullptr; // тут лежит наш массив
    int size = 0; // текущее количество элементов
    int choice;
    const char* filename = "factory.dat"; // имя файла для сохранения

    while (true)
    {
        // главное меню программы
        cout << "\n1. Create\t2. Show\t\t3. Add\t\t4. Workshop Qty\n5. Delete\t6. FileMod\t7. Sort\t\t8. Save\t\t0. Exit" << endl;
        cout << "Choice: ";

        // проверка чтобы не ввели буквы вместо цифр
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
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
            displayArray(catalog, size);
            break;
        case 8: {
            // сохраняем массив в бинарный файл
            ofstream ofs(filename, ios::binary | ios::trunc);
            if (ofs.is_open()) {
                ofs.write((char*)catalog, size * sizeof(FactoryProduct));
                cout << "Data saved to " << filename << endl;
            }
            break;
        }
        case 0:
            // выход из программы
            cout << "Exiting..." << endl;
            if (catalog) delete[] catalog; // чистим память перед самым выходом
            return 0; // вот теперь программа закроется
        default:
            // если ввели число которого нет в меню
            cout << "No such choice" << endl;
            break;
        }
    }
}