#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

vector<int> sortNumbers(vector<int> numbers) {
    unsigned char bitArray = 0;
    vector<int> sortedNumbers;

    for (int num : numbers) {
        bitArray |= 1 << num;
    }

    for (int i = 0; i < 8; i++) {
        if (bitArray & (1 << i)) {
            sortedNumbers.push_back(i);
        }
    }

    return sortedNumbers;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<int> numbers;
    int num;
    int count;

    cin >> count;

    for (int i = 0; i < count; i++) {
        cout << "Введите число (от 0 до 7): ";

        cin >> num;
        numbers.push_back(num);
    }

    vector<int> sortedNumbers = sortNumbers(numbers);

    cout << "Отсортированный вектор чисел:";

    for (int num : sortedNumbers) {
        cout << " " << num;
    }
    cout << endl;

    return 0;
}