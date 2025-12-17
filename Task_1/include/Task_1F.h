#ifndef LR8_TASK_1F_H
#define LR8_TASK_1F_H

const int MAX_NAME = 50;
const int MAX_DATE = 20;

union ProductID {
    int code;
    char serial[30];
};

struct Product {
    char name[MAX_NAME];
    int quantity;
    int workshop;
    char date[MAX_DATE];
    ProductID id;
    int id_type; // 1-код, 2-серийный
};

class ProductArray {
private:
    Product* data;
    int size;
    int capacity;

    void expand(); // Увеличивает массив

public:
    ProductArray();
    ~ProductArray();

    void add(const Product& p);
    void remove(int index);
    void clear();

    int getSize() const { return size; }
    Product* getData() { return data; }
};

void inputProducts(ProductArray& arr);
void printAll(const ProductArray& arr);
void addMore(ProductArray& arr);
void findWorkshop(const ProductArray& arr);
void removeProduct(ProductArray& arr);
void editProduct(ProductArray& arr);
void shakerSort(ProductArray& arr);
void saveToFile(const ProductArray& arr);
void loadFromFile(ProductArray& arr);
void editInFile();

#endif //LR8_TASK_1F_H