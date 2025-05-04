#include <iostream>
#include <string>
using namespace std;

class Graph {
    int n;  
    string city[100];  
    int dist[100][100];  
    struct Node {  
        string city;
        int fuel;
        Node* next;
    } *head[100];  

public:
    Graph() {
        n = 0;
        for (int i = 0; i < 100; i++) {
            head[i] = nullptr;
            for (int j = 0; j < 100; j++) {
                dist[i][j] = (i == j) ? 0 : -1;  
            }
        }
    }

    void create();
    void addEdge();
    void displayAdjacencyList();
    void displayAdjacencyMatrix();
};

void Graph::create() {
    cout << "Enter total number of cities: ";
    cin >> n;
    
    cout << "Enter city names: ";
    for (int i = 0; i < n; i++) {
        cin >> city[i];
        head[i] = new Node{city[i], 0, nullptr};  // Create head node
    }
}

void Graph::addEdge() {
    if (n == 0) {
        cout << "Error: Please create the graph first!\n";
        return;
    }

    string src, dest;
    int fuel;
    char choice;

    do {
        cout << "Enter the source and destination cities: ";
        cin >> src >> dest;
        cout << "Enter the fuel required: ";
        cin >> fuel;

        // Find indices of cities
        int srcIndex = -1, destIndex = -1;
        for (int j = 0; j < n; j++) {
            if (city[j] == src) srcIndex = j;
            if (city[j] == dest) destIndex = j;
        }

        if (srcIndex == -1 || destIndex == -1) {
            cout << "Error: Invalid city names! Try again.\n";
            continue;
        }

        // Update adjacency list
        Node* newNode = new Node{dest, fuel, nullptr};
        Node* temp = head[srcIndex];
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;

        // Update adjacency matrix
        dist[srcIndex][destIndex] = fuel;
        dist[destIndex][srcIndex] = fuel;  // Undirected graph

        cout << "Do you want to add another edge? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void Graph::displayAdjacencyList() {
    if (n == 0) {
        cout << "Error: No graph created yet!\n";
        return;
    }
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        Node* temp = head[i];
        cout << temp->city;
        temp = temp->next;
        while (temp != nullptr) {
            cout << " -> " << temp->city << " (" << temp->fuel << ")";
            temp = temp->next;
        }
        cout << endl;
    }
}

void Graph::displayAdjacencyMatrix() {
    if (n == 0) {
        cout << "Error: No graph created yet!\n";
        return;
    }
    cout << "\nAdjacency Matrix (Distance Table):\n";
    cout << "       ";
    for (int i = 0; i < n; i++) {
        cout << city[i] << "\t";
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << city[i] << "\t";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == -1)
                cout << "INF\t";  // INF means no direct connection
            else
                cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main() {
    Graph g;
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create Graph (Cities)\n";
        cout << "2. Add Edges (Connections)\n";
        cout << "3. Display Adjacency List\n";
        cout << "4. Display Adjacency Matrix\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.create();
                break;
            case 2:
                g.addEdge();
                break;
            case 3:
                g.displayAdjacencyList();
                break;
            case 4:
                g.displayAdjacencyMatrix();
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}
