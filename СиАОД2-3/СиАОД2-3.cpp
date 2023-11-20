#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <Windows.h>

using namespace std;

struct Registration {
    long long number;
    string name;
    string founder;

    Registration(long long number, string name, string founder) {
        this->number = number;
        this->name = name;
        this->founder = founder;
    }
};

class HashTable {
public:
    int num = 0;
    int size;
    list<Registration*>* table;

    HashTable(int initialSize) {
        size = initialSize;
        table = new list<Registration*>[initialSize];
    }

    int hashFunction(long long key) {
        return key % size;
    }

    void resizeTable() {
        size *= 2;
        list<Registration*>* newTable = new list<Registration*>[size];

        for (int i = 0; i < size / 2; i++) {
            for (Registration* company : table[i]) {
                int index = hashFunction(company->number);

                newTable[index].push_back(company);
            }
        }

        delete[] table;

        table = newTable;
    }

    void insert(Registration* company) {
        if ((double)num / size > 0.75) {
            resizeTable();
        }
        num++;

        int index = hashFunction(company->number);

        table[index].push_back(company);
    }

    Registration* search(long long key) {
        int index = hashFunction(key);

        for (Registration* company : table[index]) {
            if (company->number == key) {
                return company;
            }
        }

        return nullptr;
    }

    void remove(long long key) {
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if ((*it)->number == key) {
                table[index].erase(it);
                num--;

                return;
            }
        }
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            cout << "Индекс " << i << ": ";

            for (Registration* company : table[i]) {
                cout << company->number << " " << company->name << " (" << company->founder << ")   ";
            }

            cout << endl;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HashTable hashTable(8);
    long long number, key;
    string name, founder;
    Registration* company;

    int command;

    while (true) {
        cout << "1. Добавить предприятие;" << endl;
        cout << "2. Найти предприятие;" << endl;
        cout << "3. Удалить предприятие;" << endl;
        cout << "4. Вывести предприятия;" << endl;
        cout << "5. Выход." << endl;

        cin >> command;

        switch (command) {
        case 1:
            cout << "Каким образом Вы хотите заполнить данные:" << endl;
            cout << "0 - вручную;" << endl;
            cout << "1 - случайным образом." << endl;

            int choice;

            cin >> choice;

            if (choice == 0) {
                cout << "Введите регистрационный номер предприятия: ";
                cin >> number;

                cout << "Введите название предприятия: ";
                cin >> name;

                cout << "Введите имя учредителя: ";
                cin >> founder;

                company = new Registration(number, name, founder);
            }
            else {
                number = rand() % 1000;
                name = "Предприятие#" + to_string(rand() % 1000);
                founder = "Учредитель_" + to_string(rand() % 1000);

                company = new Registration(number, name, founder);
            }

            hashTable.insert(company);

            cout << "Предприятие добавлено\n";

            break;
        case 2:
            cout << "Введите ключ для поиска: ";
            cin >> key;

            company = hashTable.search(key);

            if (company != nullptr) {
                cout << "Найдено предприятие: " << company->name << " (" << company->founder << ")\n";
            }
            else {
                cout << "Предприятие не найдено\n";
            }

            break;
        case 3:
            cout << "Введите ключ для удаления: ";
            cin >> key;

            company = hashTable.search(key);

            hashTable.remove(key);

            cout << "Предприятие удалено\n";

            break;
        case 4:
            hashTable.printTable();

            break;
        case 5:
            exit(1);
        default:
            cout << "Неправильная команда" << endl;
        }
    }

    return 0;
}