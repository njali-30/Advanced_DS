#include <iostream>
#include <climits>
#include <string>

#define MAX_CITIES 100 // Max cities limit

using namespace std;

class Graph {
private:
    int numCities;
    int adjMatrix[MAX_CITIES][MAX_CITIES];
    string cityNames[MAX_CITIES];

public:
    Graph(int n); // Constructor

    void addCityNames();
    void addEdges();
    int getCityIndex(string city);
    void primMST(int startCity);
};

// Constructor definition
Graph::Graph(int n) {
    numCities = n;
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            adjMatrix[i][j] = INT_MAX; // Initialize with infinity
        }
    }
}

// Add city names
void Graph::addCityNames() {
    cout << "Enter names of " << numCities << " cities:\n";
    for (int i = 0; i < numCities; i++) {
        cin >> cityNames[i];
    }
}

// Add edges between cities
void Graph::addEdges() {
    int edges;
    cout << "Enter the number of roads between cities (including parallel roads if any): ";
    cin >> edges;

    cout << "Enter the roads with distances (format: City1 City2 Distance):\n";
    for (int i = 0; i < edges; i++) {
        string city1, city2;
        int distance;
        cin >> city1 >> city2 >> distance;

        int index1 = getCityIndex(city1);
        int index2 = getCityIndex(city2);

        if (index1 == -1 || index2 == -1) {
            cout << "Invalid city name entered! Please enter again.\n";
            i--; // Retry input
            continue;
        }

        if (index1 == index2) {
            cout << "Self-loops are ignored.\n";
            continue;
        }

        // Take the minimum distance if multiple roads exist
        if (adjMatrix[index1][index2] > distance) {
            adjMatrix[index1][index2] = distance;
            adjMatrix[index2][index1] = distance; // Undirected graph
        }
    }
}

// Get index of a city
int Graph::getCityIndex(string city) {
    for (int i = 0; i < numCities; i++) {
        if (cityNames[i] == city)
            return i;
    }
    return -1;
}

// Prim's Algorithm to find MST
void Graph::primMST(int startCity) {
    int key[MAX_CITIES];
    bool inMST[MAX_CITIES];
    int parent[MAX_CITIES];

    for (int i = 0; i < numCities; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[startCity] = 0;

    cout << "\nStep-by-step selection of shortest paths:\n";

    for (int count = 0; count < numCities; count++) {
        int minKey = INT_MAX, u = -1;

        for (int v = 0; v < numCities; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break; // Graph may be disconnected

        inMST[u] = true;

        if (parent[u] != -1) {
            cout << cityNames[parent[u]] << " -> " << cityNames[u]
                 << " (Distance: " << adjMatrix[u][parent[u]] << ")\n";
        }

        for (int v = 0; v < numCities; v++) {
            if (adjMatrix[u][v] != INT_MAX && !inMST[v] && adjMatrix[u][v] < key[v]) {
                key[v] = adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }
}

// Main function
int main() {
    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    Graph g(numCities);
    g.addCityNames();
    g.addEdges();

    string startCity;
    cout << "Enter your starting city: ";
    cin >> startCity;

    int startIndex = g.getCityIndex(startCity);
    if (startIndex == -1) {
        cout << "Invalid starting city!\n";
        return 1;
    }

    g.primMST(startIndex);

    return 0;
}
