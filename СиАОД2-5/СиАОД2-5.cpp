#include <iostream>
#include <string>
#include <Windows.h>
#include <queue>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
};

class RedBlackTree {
private:
    Node* root;
    Node* nil;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nil) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nil) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nil) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == nil) {
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

    void inorderTraversal(Node* x) {
        if (x != nil) {
            inorderTraversal(x->left);

            cout << x->data << " ";

            inorderTraversal(x->right);
        }
    }

    void reverseTraversal(Node* x) {
        if (x != nil) {
            reverseTraversal(x->right);

            cout << x->data << " ";

            reverseTraversal(x->left);
        }
    }

    int findPathLength(Node* x, int value) {
        int pathLength = 0;
        Node* current = x;

        while (current != nullptr && current->data != value) {
            if (value < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }

            pathLength++;
        }

        return pathLength;
    }

    int findHeight(Node* x) {
        if (x == nil) {
            return 0;
        }

        int leftHeight = findHeight(x->left);
        int rightHeight = findHeight(x->right);

        return max(leftHeight, rightHeight) + 1;
    }

public:
    RedBlackTree() {
        nil = new Node;
        nil->color = BLACK;
        root = nil;
    }

    ~RedBlackTree() {
    }

    void insert(int data) {
        Node* z = new Node;
        z->data = data;
        z->left = nil;
        z->right = nil;
        z->color = RED;

        Node* y = nil;
        Node* x = root;
        while (x != nil) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nil) {
            root = z;
        }
        else if (z->data < y->data) {
            y->left = z;
        }
        else {
            y->right = z;
        }

        insertFixup(z);
    }

    void reverseTraversal() {
        reverseTraversal(root);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

    int findPathLength(int value) {
        return findPathLength(root, value);
    }

    int findHeight() {
        return findHeight(root);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    RedBlackTree tree;

    int choise;
    int value;

    while (true) {
        cout << "1. Вставить элемент в дерево;" << endl;
        cout << "2. Обратный обход;" << endl;
        cout << "3. Симметричный обход;" << endl;
        cout << "4. Найти длину пути от корня до заданного значения;" << endl;
        cout << "5. Найти высоту дерева;" << endl;
        cout << "6. Выход" << endl;

        cin >> choise;

        switch (choise) {
        case 1:
            cout << "Введите значение: ";
            cin >> value;

            tree.insert(value);

            break;
        case 2:
            tree.reverseTraversal();
            cout << endl;

            break;
        case 3:
            tree.inorderTraversal();
            cout << endl;

            break;
        case 4:
            cout << "Введите значение: ";
            cin >> value;

            cout << "Длина пути от корня до заданного значения: " << tree.findPathLength(value) << endl;

            break;
        case 5:
            cout << "Высота дерева: " << tree.findHeight() << endl;

            break;
        case 6:
            exit(1);
        }
    }

    return 0;
}