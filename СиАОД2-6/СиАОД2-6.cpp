#include <iostream>
#include <vector>
#include <Windows.h>
#include <queue>

using namespace std;

class Graph {
    int numVertices;
    vector<vector<pair<int, int>>> adjLists;

public:
    Graph(int vertices) {
        numVertices = vertices + 1;
        adjLists.resize(numVertices);
    }

    void addEdge(int src, int dest, int weight) {
        adjLists[src].push_back(make_pair(dest, weight));
        adjLists[dest].push_back(make_pair(src, weight));
    }

    void printGraph() {
        for (int i = 1; i < numVertices; i++) {
            cout << "Список смежности вершины " << i << ": ";

            for (int j = 0; j < adjLists[i].size(); j++) {
                cout << "(вершина: " << adjLists[i][j].first << ", вес = " << adjLists[i][j].second << ") ";
            }
            cout << endl;
        }
    }

    void primMST() {
        vector<bool> visited(numVertices, false);
        vector<int> key(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int startVertex = 1;
        pq.push(make_pair(0, startVertex));
        key[startVertex] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            visited[u] = true;

            for (auto& edge : adjLists[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push(make_pair(key[v], v));
                }
            }
        }

        cout << "Остовное дерево, построенное с помощью алгоритма Прима:" << endl;
        for (int i = 2; i < numVertices; i++) {
            cout << "Ребро: " << parent[i] << " - " << i << " Вес: " << key[i] << endl;
        }
    }
};

int main() {
    system("chcp 1251");

    int choise;
    Graph graph(6);

    while (true) {
        cout << "1. Создать граф;" << endl;
        cout << "2. Вывести граф;" << endl;
        cout << "3. Построить остовное дерево с помощью алгоритма Прима;" << endl;
        cout << "4. Выход" << endl;

        cin >> choise;

        switch (choise) {
        case 1:
            graph.addEdge(1, 2, 2);
            graph.addEdge(2, 4, 4);
            graph.addEdge(2, 5, 8);
            graph.addEdge(4, 6, 8);
            graph.addEdge(4, 5, 8);
            graph.addEdge(4, 3, 8);
            graph.addEdge(1, 3, 6);
            graph.addEdge(1, 4, 4);
            graph.addEdge(6, 3, 5);
            graph.addEdge(6, 5, 4);

            break;
        case 2:
            graph.printGraph();

            break;
        case 3:
            graph.primMST();

            break;
        case 4:
            exit(1);
        }
    }

    return 0;
}