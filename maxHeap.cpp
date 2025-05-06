#include <iostream>
using namespace std;

int n, count = 0;

class HT {
    int key[20];  
public:
    void accept();
    void built(int key[], int m, int value);
    void insert();
    void display();
};

void HT::accept() {
    int value;
    cout << "\nTotal no. of keys: ";
    cin >> n;
    cout << "\nEnter the keys: ";
    for (int i = 1; i <= n; i++) {
        cin >> value;
        built(key, i, value);
        count++;
    }
}

void HT::built(int key[], int m, int value) {
    int loc, parent;
    key[m] = value;
    loc = m;
    while (loc > 1) {
        parent = loc / 2;
        if (key[parent] < key[loc]) {
            swap(key[parent], key[loc]);
            loc = parent;
        } else {
            break;
        }
    }
}

void HT::insert() {
    int newKey;
    cout << "Enter the new key: ";
    cin >> newKey;
    count++;
    if (count >= 20) {
        cout << "Heap is full. Cannot insert more elements.\n";
        count--;
        return;
    }
    built(key, count, newKey);
}

void HT::display() {
    if (count == 0) {
        cout << "Heap is empty.\n";
        return;
    }
    cout << "Heap elements (level order): ";
    for (int i = 1; i <= count; i++) {
        cout << key[i] << " ";
    }
    cout << endl;
}

int main() {
    HT h;
    int choice;

    do {
        cout << "\n----- MAX HEAP MENU -----";
        cout << "\n1. Build Heap";
        cout << "\n2. Insert Element";
        cout << "\n3. Display Heap";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                h.accept();
                break;
            case 2:
                h.insert();
                break;
            case 3:
                h.display();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
