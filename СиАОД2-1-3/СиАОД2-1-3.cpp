#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream fin("file_input.txt");
    ofstream fout("file_out.txt");

    int n = pow(10, 7);

    vector<unsigned char> bitArray(n / 8 + 1, 0);
    int num;

    int start = clock();

    while (fin >> num) {
        bitArray[num / 8] |= (1 << (num % 8));
    }

    fin.close();

    for (int i = 0; i < bitArray.size(); i++) {
        for (int number = 0; bitArray[i] != 0; bitArray[i] <<= 1, number++) {
            if ((bitArray[i] & 1) == 1) {
                fout << number + 8 * i << " ";
            }
        }
    }

    fout.close();

    int stop = clock();
    int result = stop - start;

    cout << "Время: " << result << "мс" << endl;
    cout << "Память: " << sizeof(unsigned char) * bitArray.size() / (1024 * 1024) << " Мбайт" << endl;

    return 0;
}