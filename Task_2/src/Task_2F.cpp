#include "Task_2F.h"
using namespace std;

// improved function to handle even messy inputs like "3a3a"
double getValidNum() {
    double val;
    while (true) {
        if (cin >> val && val >= 0) {
            // clear anything left on the line after the number
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Error! Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

LibraryBook* createLibrary(int& size) {
    cout << "Enter number of books: ";
    size = (int)getValidNum();
    if (size <= 0) return nullptr;

    LibraryBook* arr = new LibraryBook[size];
    for (int i = 0; i < size; i++) {
        cout << "\n--- Book " << i + 1 << " ---" << endl;

        cout << "Reg number (e.g. 233fw, EN): ";
        cin.getline(arr[i].regNumber, 20);

        cout << "Author: ";
        cin.getline(arr[i].author, 50);

        cout << "Title: ";
        cin.getline(arr[i].title, 100);

        cout << "Year: ";
        arr[i].year = (int)getValidNum();

        cout << "Publisher: ";
        cin.getline(arr[i].publisher, 50);

        cout << "Pages: ";
        arr[i].pages = (int)getValidNum();

        do {
            cout << "Type (1-Paper, 2-Digital): ";
            arr[i].bookType = (int)getValidNum();
        } while (arr[i].bookType != 1 && arr[i].bookType != 2);

        if (arr[i].bookType == 1) {
            cout << "Weight (g): "; arr[i].spec.weight = (int)getValidNum();
        } else {
            cout << "File size (MB): "; arr[i].spec.fileSize = getValidNum();
        }
    }
    return arr;
}

void displayLibrary(LibraryBook* arr, int size) {
    if (!arr || size == 0) { cout << "\n[!] Library is empty" << endl; return; }
    cout << "\nRegNum\tAuthor\tTitle\tYear\tPages\tSpec" << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i].regNumber << "\t" << arr[i].author << "\t" << arr[i].title << "\t"
             << arr[i].year << "\t" << arr[i].pages << "\t";
        if (arr[i].bookType == 1) cout << arr[i].spec.weight << "g";
        else cout << arr[i].spec.fileSize << "MB";
        cout << endl;
    }
}

void filterAndSortBooks(LibraryBook* arr, int size) {
    if (!arr || size == 0) return;
    cout << "Enter year: ";
    int targetYear = (int)getValidNum();

    LibraryBook* temp = new LibraryBook[size];
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].year > targetYear) temp[count++] = arr[i];
    }

    if (count == 0) {
        cout << "No books found after " << targetYear << endl;
        delete[] temp;
        return;
    }

    // alphabetical sort by author surname
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(temp[j].author, temp[j + 1].author) > 0) {
                LibraryBook b = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = b;
            }
        }
    }
    displayLibrary(temp, count);
    delete[] temp;
}

void addBook(LibraryBook*& arr, int& size) {
    LibraryBook* newArr = new LibraryBook[size + 1];
    for (int i = 0; i < size; i++) newArr[i] = arr[i];

    cout << "\n--- Adding book ---" << endl;
    cout << "Reg number: "; cin.getline(newArr[size].regNumber, 20);
    cout << "Author: "; cin.getline(newArr[size].author, 50);
    cout << "Title: "; cin.getline(newArr[size].title, 100);
    cout << "Year: "; newArr[size].year = (int)getValidNum();
    cout << "Publisher: "; cin.getline(newArr[size].publisher, 50);
    cout << "Pages: "; newArr[size].pages = (int)getValidNum();

    cout << "Type (1-Paper, 2-Digital): "; newArr[size].bookType = (int)getValidNum();
    if (newArr[size].bookType == 1) { cout << "Weight: "; newArr[size].spec.weight = (int)getValidNum(); }
    else { cout << "File size: "; newArr[size].spec.fileSize = getValidNum(); }

    delete[] arr;
    arr = newArr;
    size++;
}

void deleteBook(LibraryBook*& arr, int& size) {
    if (size == 0) return;
    char reg[20];
    cout << "Enter reg number to delete: ";
    cin.getline(reg, 20);

    int idx = -1;
    for (int i = 0; i < size; i++) if (strcmp(arr[i].regNumber, reg) == 0) { idx = i; break; }

    if (idx != -1) {
        LibraryBook* newArr = (size - 1 > 0) ? new LibraryBook[size - 1] : nullptr;
        for (int i = 0, j = 0; i < size; i++) if (i != idx) newArr[j++] = arr[i];
        delete[] arr;
        arr = newArr;
        size--;
        cout << "Deleted successfully." << endl;
    } else cout << "Not found." << endl;
}

void modifyBookInFile(const char* filename) {
    fstream fs(filename, ios::binary | ios::in | ios::out);
    if (!fs) { cout << "File error. Save data first." << endl; return; }
    cout << "Index: ";
    int index = (int)getValidNum();
    fs.seekg(index * sizeof(LibraryBook), ios::beg);
    LibraryBook temp;
    if (!fs.read((char*)&temp, sizeof(LibraryBook))) return;
    cout << "New year: ";
    temp.year = (int)getValidNum();
    fs.seekp(index * sizeof(LibraryBook), ios::beg);
    fs.write((char*)&temp, sizeof(LibraryBook));
    fs.close();
    cout << "Year updated in file." << endl;
}