#include "Task_1F.h"
using namespace std;

// проверка чтобы не вводили буквы или минусы
double getPositiveNum() {
    double val;
    while (true) {
        if (cin >> val && val >= 0) return val;
        cout << "Error! Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// создание списка товаров с нуля
FactoryProduct* createArray(int& size) {
    cout << "Enter count of products: ";
    size = (int)getPositiveNum();
    if (size <= 0) return nullptr;

    FactoryProduct* arr = new FactoryProduct[size];
    for (int i = 0; i < size; i++) {
        cout << "\n   Product " << i + 1 << endl;
        cout << "Name (EN): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(arr[i].name, 50);

        cout << "Qty: "; arr[i].quantity = (int)getPositiveNum();
        cout << "Workshop: "; arr[i].workshop_num = (int)getPositiveNum();
        cout << "Price: "; arr[i].unit_price = getPositiveNum();
        arr[i].batch_value = arr[i].quantity * arr[i].unit_price;

        // выбираем литры или килограммы
        do {
            cout << "Type (1-Vol, 2-Weight): ";
            arr[i].spec_type = (int)getPositiveNum();
        } while (arr[i].spec_type != 1 && arr[i].spec_type != 2);

        if (arr[i].spec_type == 1) { cout << "Volume: "; arr[i].spec.volume = getPositiveNum(); }
        else { cout << "Weight: "; arr[i].spec.weight = getPositiveNum(); }
    }
    return arr;
}

// вывод всего списка на экран
void displayArray(FactoryProduct* arr, int size) {
    if (!arr || size == 0) { cout << "\nList is empty." << endl; return; }
    cout << "\nID\tName\tQty\tShop\tPrice\tTotal\tSpec" << endl;
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ".\t" << arr[i].name << "\t" << arr[i].quantity << "\t"
             << arr[i].workshop_num << "\t" << arr[i].unit_price << "\t"
             << arr[i].batch_value << "\t";
        if (arr[i].spec_type == 1) cout << arr[i].spec.volume << "L";
        else cout << arr[i].spec.weight << "kg";
        cout << endl;
    }
}

// добавление одного товара в существующий массив
void addElement(FactoryProduct*& arr, int& size) {
    FactoryProduct* newArr = new FactoryProduct[size + 1];
    for (int i = 0; i < size; i++) newArr[i] = arr[i];

    cout << "\n   Adding product" << endl;
    cout << "Name (EN): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(newArr[size].name, 50);

    cout << "Qty: "; newArr[size].quantity = (int)getPositiveNum();
    cout << "Shop: "; newArr[size].workshop_num = (int)getPositiveNum();
    cout << "Price: "; newArr[size].unit_price = getPositiveNum();
    newArr[size].batch_value = newArr[size].quantity * newArr[size].unit_price;

    do {
        cout << "Type (1-Vol, 2-Weight): ";
        newArr[size].spec_type = (int)getPositiveNum();
    } while (newArr[size].spec_type != 1 && newArr[size].spec_type != 2);

    if (newArr[size].spec_type == 1) { cout << "Vol: "; newArr[size].spec.volume = getPositiveNum(); }
    else { cout << "Weight: "; newArr[size].spec.weight = getPositiveNum(); }

    delete[] arr;
    arr = newArr;
    size++;
}

// считаем сколько всего товаров в конкретном цехе
void searchByWorkshop(FactoryProduct* arr, int size) {
    if (!arr || size == 0) return;
    cout << "Enter workshop number: ";
    int shop = (int)getPositiveNum();
    int totalQty = 0;
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (arr[i].workshop_num == shop) {
            totalQty += arr[i].quantity;
            found = true;
        }
    }
    if (found) cout << "Total products in workshop " << shop << ": " << totalQty << endl;
    else cout << "Workshop not found." << endl;
}

// удаление товара из памяти по его имени
void deleteElement(FactoryProduct*& arr, int& size) {
    if (size == 0) return;
    char target[50];
    cout << "Enter name to delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(target, 50);

    int idx = -1;
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].name, target) == 0) { idx = i; break; }
    }

    if (idx != -1) {
        FactoryProduct* newArr = (size - 1 > 0) ? new FactoryProduct[size - 1] : nullptr;
        for (int i = 0, j = 0; i < size; i++) {
            if (i != idx) newArr[j++] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        size--;
        cout << "Deleted successfully." << endl;
    } else cout << "Product not found." << endl;
}


// сортировка шейкером по убыванию количества
void shakerSort(FactoryProduct* arr, int size) {
    if (size < 2) return;
    int left = 0, right = size - 1;
    bool swapped = true;
    while (left < right && swapped) {
        swapped = false;
        for (int i = left; i < right; i++) {
            if (arr[i].quantity < arr[i + 1].quantity) { swap(arr[i], arr[i + 1]); swapped = true; }
        }
        right--;
        for (int i = right; i > left; i--) {
            if (arr[i].quantity > arr[i - 1].quantity) { swap(arr[i], arr[i - 1]); swapped = true; }
        }
        left++;
    }
}

// изменение количества товара прямо в бинарном файле
void modifyInFile(const char* filename) {
    fstream fs(filename, ios::binary | ios::in | ios::out);
    if (!fs) { cout << "File error! Save data first." << endl; return; }
    cout << "Enter record index: ";
    int index = (int)getPositiveNum();

    fs.seekg(index * sizeof(FactoryProduct), ios::beg);
    FactoryProduct temp;
    if (!fs.read((char*)&temp, sizeof(FactoryProduct))) {
        cout << "Record not found." << endl;
        return;
    }

    cout << "Modifying " << temp.name << ". New Qty: ";
    temp.quantity = (int)getPositiveNum();
    temp.batch_value = temp.quantity * temp.unit_price;

    fs.seekp(index * sizeof(FactoryProduct), ios::beg);
    fs.write((char*)&temp, sizeof(FactoryProduct));
    fs.close();
    cout << "File updated." << endl;
}