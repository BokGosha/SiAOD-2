#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

vector<int> sortNumbers(vector<int> numbers) {
    unsigned long long bitArray = 0;
    vector<int> sortedNumbers;

    for (int num : numbers) {
        bitArray |= 1ULL << num;
    }

    for (int i = 0; i < 64; i++) {
        if (bitArray & (1ULL << i)) {
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
        cout << "Введите число (от 0 до 63): ";

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