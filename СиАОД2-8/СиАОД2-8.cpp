#include <iostream>
#include <vector>

using namespace std;

struct State {
    vector<vector<int>> paper;
    int area;
};

int computeLowerBound(const vector<vector<int>>& paper) {
    int height = paper.size();
    int width = paper[0].size();

    int lowerBound = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (paper[i][j] == 0) {
                if ((i - 1 >= 0 && paper[i - 1][j] == 1) || (i + 1 < height && paper[i + 1][j] == 1) ||
                    (j - 1 >= 0 && paper[i][j - 1] == 1) || (j + 1 < width && paper[i][j + 1] == 1)) {
                    lowerBound++;
                }
            }
        }
    }

    return lowerBound;
}

void branchAndBound(State currentState, int& maxArea) {
    int height = currentState.paper.size();
    int width = currentState.paper[0].size();

    if (currentState.area > maxArea) {
        maxArea = currentState.area;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (currentState.paper[i][j] == 0) {
                int newArea = currentState.area + 1;

                vector<vector<int>> newPaper = currentState.paper;

                newPaper[i][j] = 1;

                int lowerBound = newArea + computeLowerBound(newPaper);

                if (lowerBound > maxArea) {
                    State newState;
                    newState.paper = newPaper;
                    newState.area = newArea;

                    branchAndBound(newState, maxArea);
                }
            }
        }
    }
}

int calculateArea(const vector<vector<int>>& paper) {
    int maxArea = 0;
    State initialState;
    initialState.paper = paper;
    initialState.area = 0;

    branchAndBound(initialState, maxArea);

    int totalCells = paper.size() * paper[0].size();
    int actualArea = totalCells - maxArea;

    return actualArea;
}

int main() {
    system("chcp 1251");

    vector<vector<int>> paper = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1}
    };

    int actualArea = calculateArea(paper);
    cout << "Площадь вырезанной фигуры: " << actualArea << endl;

    return 0;
}