#include "Task_2F.h"
using namespace std;

int main() {
    LibraryBook* lib = nullptr;
    int size = 0;
    int choice;
    const char* file = "library.dat";

    while (true) {
        cout << "\n1. Create\t2. Show\t\t3. Add\t\t4. Filter & Sort\n5. Delete\t6. FileMod\t8. Save\t\t0. Exit" << endl;
        cout << "Choice: ";

        choice = (int)getPositiveNum();

        switch (choice) {
        case 1:
            if (lib) {
                delete[] lib;
                lib = nullptr;
                size = 0;
            }
            lib = createLibrary(size);
            break;
        case 2:
            displayLibrary(lib, size);
            break;
        case 3:
            addBook(lib, size);
            break;
        case 4:
            filterAndSortBooks(lib, size);
            break;
        case 5:
            deleteBook(lib, size);
            break;
        case 6:
            modifyBookInFile(file);
            break;
        case 8: {
                if (!lib || size == 0) {
                    cout << "Nothing to save." << endl;
                } else {
                    ofstream ofs(file, ios::binary | ios::trunc);
                    if (ofs.is_open()) {
                        ofs.write((char*)lib, size * sizeof(LibraryBook));
                        ofs.close();
                        cout << "Saved to binary file." << endl;
                    }
                }
                break;
        }
        case 0:
            if (lib) delete[] lib;
            return 0;
        default:
            cout << "No such choice, try again." << endl;
            break;
        }
    }
}