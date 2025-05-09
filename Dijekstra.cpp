#include<iostream>
using namespace std;

class pizza_par {
    int v, adj[10][10];
    string city[10];

public:
    void accept();
    void SSSP();
    void display();
} p;

void pizza_par::accept() {
    cout << "\nEnter the number of customer locations: ";
    cin >> v;

    cout << "\nEnter the names of the cities or locations:\n";
    for (int i = 0; i < v; i++) {
        cout << "City " << i + 1 << ": ";
        cin >> city[i];
    }

    cout << "\nEnter the distances between cities:\n";
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (i == j) {
                adj[i][j] = 0;
            } else {
                cout << "Distance from " << city[i] << " to " << city[j] << ": ";
                cin >> adj[i][j];
            }
        }
    }
}

void pizza_par::display() {
    cout << "\nDistance Matrix:\n\t";
    for (int i = 0; i < v; i++) {
        cout << city[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < v; i++) {
        cout << city[i] << "\t";
        for (int j = 0; j < v; j++) {
            cout << adj[i][j] << "\t";
        }
        cout << endl;
    }
}

void pizza_par::SSSP() {
    int dist[10], visited[10], min, u = 0;

    for (int i = 0; i < v; i++) {
        dist[i] = 999;
        visited[i] = 0;
    }

    dist[0] = 0;

    for (int count = 0; count < v - 1; count++) {
        min = 999;

        for (int i = 0; i < v; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int j = 0; j < v; j++) {
            if (!visited[j] && adj[u][j] && dist[u] + adj[u][j] < dist[j]) {
                dist[j] = dist[u] + adj[u][j];
            }
        }
    }

    cout << "\nShortest distances from source (" << city[0] << "):\n";
    for (int i = 1; i < v; i++) {
        cout << "To " << city[i] << ": " << dist[i] << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Accept\n";
        cout << "2. Display\n";
        cout << "3. Shortest distance from source location\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            p.accept();
            break;
        case 2:
            p.display();
            break;
        case 3:
            p.SSSP();
            break;
        case 0:
            cout << "Exiting the program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
