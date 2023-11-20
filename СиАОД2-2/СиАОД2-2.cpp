#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <random>
#include <Windows.h>

using namespace std;

const int COUNT = 1000;

struct AutoInsurance {
    int registrationNumber = 0;
    string insuranceCompany = "";
};

struct tab {
    int key;
    int shift;
};

void create_text() {
    AutoInsurance* array = new AutoInsurance[COUNT];

    bool flag;

    for (int i = 0; i < COUNT; i++) {
        flag = true;

        int number = 100000 + rand() % 100000;

        for (int j = 0; j < i; j++) {
            if (number == array[j].registrationNumber) {
                flag = false;
                i--;

                break;
            }
        }

        if (flag) {
            array[i].registrationNumber = number;
            array[i].insuranceCompany = "Страховая_компания#" + to_string(rand() % 100000);
        }
    }

    ofstream fout("records.txt");

    if (!fout.is_open()) {
        cout << "Ошибка открытия файла";
    }
    else {
        for (int i = 0; i < COUNT; i++) {
            fout << endl << array[i].registrationNumber << " " << array[i].insuranceCompany;
            cout << array[i].registrationNumber << " " << array[i].insuranceCompany << endl;
        }
    }

    fout.close();
}

void create_bin() {
    AutoInsurance* array = new AutoInsurance[COUNT];

    ifstream fin("records.txt");

    if (!fin.is_open()) {
        cout << "Ошибка открытия файла";
    }
    else {
        for (int i = 0; i < COUNT; i++) {
            fin >> array[i].registrationNumber >> array[i].insuranceCompany;
        }
    }

    fin.close();

    ofstream fout("records.bin", ios::binary);

    if (!fout.is_open()) {
        cout << "Ошибка открытия файла";
    }
    else {
        for (int i = 0; i < COUNT; i++) {
            fout.write((char*)&array[i].registrationNumber, sizeof(int));
            fout.write((char*)&array[i].insuranceCompany, sizeof(string));
        }
    }

    fout.close();
}

void sort_id(tab*& x, int count) {
    tab temp;
    int min;

    for (int i = 0; i < count - 1; i++) {
        min = i;

        for (int j = i + 1; j < count; j++) {
            if (x[j].key < x[min].key) {
                min = j;
            }
        }

        temp = x[i];
        x[i] = x[min];
        x[min] = temp;
    }
}

int find_s(int number) {
    AutoInsurance* array = new AutoInsurance[COUNT];
    tab* ex = new tab[COUNT];

    FILE* fin = fopen("records.bin", "rb");

    if (fin == NULL) {
        exit(1);
    }

    for (int i = 0; i < COUNT; i++) {
        fread(reinterpret_cast<char*>(&array[i].registrationNumber), sizeof(int), 1, fin);
        fread(reinterpret_cast<char*>(&array[i].insuranceCompany), sizeof(string), 1, fin);

        ex[i].key = array[i].registrationNumber;
        ex[i].shift = i;
    }

    fclose(fin);

    sort_id(ex, COUNT);

    int left = 0;
    int right = COUNT - 1;

    while (ex[left].key < number && number < ex[right].key) {
        int mid = left + (number - ex[left].key) * (right - left) / (ex[right].key - ex[left].key);

        if (ex[mid].key < number) {
            left = mid + 1;
        }
        else if (ex[mid].key > number) {
            right = mid - 1;
        }
        else {
            return ex[mid].shift;
        }
    }

    if (ex[left].key == number) {
        return ex[left].shift;
    }
    else if (ex[right].key == number) {
        return ex[right].shift;
    }
    else {
        return -1;
    }
}

void find_line(int number) {
    AutoInsurance record;

    FILE* fin = fopen("records.bin", "rb");

    if (fin == NULL) {
        cout << "Ошибка открытия файла";
        exit(1);
    }

    if (number == -1) {
        cout << "-";
        exit(1);
    }
    else {
        fseek(fin, (sizeof(string) + sizeof(int)) * number, SEEK_SET);
    }

    fread(reinterpret_cast<char*>(&record.registrationNumber), sizeof(int), 1, fin);
    fread(reinterpret_cast<char*>(&record.insuranceCompany), sizeof(string), 1, fin);

    fclose(fin);

    cout << record.insuranceCompany;
}

void search(int id) {
    AutoInsurance* array = new AutoInsurance[COUNT];

    FILE* fin = fopen("records.bin", "rb");

    if (fin == NULL) {
        cout << "Ошибка открытия файла";
        exit(1);
    }

    for (int i = 0; i < COUNT; i++) {
        fread(reinterpret_cast<char*>(&array[i].registrationNumber), sizeof(int), 1, fin);
        fread(reinterpret_cast<char*>(&array[i].insuranceCompany), sizeof(string), 1, fin);
    }

    fclose(fin);

    bool flag = false;

    for (int i = 0; i < COUNT; i++) {
        if (array[i].registrationNumber == id) {
            cout << array[i].insuranceCompany << endl;
            flag = true;

            break;
        }
    }

    if (!flag) {
        cout << '-' << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    create_text();
    create_bin();

    string n;

    cout << "Введите регистрационный номер: ";
    cin >> n;

    while (n.length() > 6 || n.length() < 6) {
        cout << "Неправильный регистрационный номер" << endl;
        cout << "Введите, пожалуйста, правильный регистрационный номер (6 цифр): ";
        cin >> n;
    }

    int id = stoi(n);

    cout << "Как вы хотите найти запись:" << endl;
    cout << "0 - Линейный поиск;" << endl;
    cout << "1 - Интерполяционный поиск" << endl;

    int v;
    cin >> v;

    int start = clock();

    switch (v) {
    case 0:
        search(id);

        break;
    case 1:
        int m = find_s(id);
        find_line(m);
        cout << endl;

        break;
    }

    int stop = clock();
    int result = stop - start;

    cout << "Время: " << result << "мс" << endl;

    return 0;
}