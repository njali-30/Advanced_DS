#include <iostream>
#include <iomanip>
using namespace std;

class OBST {
    int n;
    string key[10];
    float p[10], q[11];
    float W[11][11], C[11][11];
    int R[11][11];

public:
    void accept();
    void calculate();
    void display();
    void showTree(int i, int j, string parent, string direction);
};

void OBST::accept() {
    cout << "Enter number of keys: ";
    cin >> n;
    cout << "Enter keys in sorted order:\n";
    for (int i = 0; i < n; i++) {
        cin >> key[i];
    }
    cout << "Enter successful search probabilities (p):\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    cout << "Enter unsuccessful search probabilities (q):\n";
    for (int i = 0; i <= n; i++) {
        cin >> q[i];
    }
}

void OBST::calculate() {
    for (int i = 0; i <= n; i++) {
        W[i][i] = q[i];
        C[i][i] = 0;
        R[i][i] = 0;
    }

    for (int gap = 1; gap <= n; gap++) {
        for (int i = 0; i <= n - gap; i++) {
            int j = i + gap;
            W[i][j] = W[i][j - 1] + p[j - 1] + q[j];

            float min = 9999;
            int root = 0;

            for (int k = i + 1; k <= j; k++) {
                float cost = C[i][k - 1] + C[k][j];
                if (cost < min) {
                    min = cost;
                    root = k;
                }
            }

            C[i][j] = W[i][j] + min;
            R[i][j] = root;
        }
    }
}

void OBST::display() {
    cout << fixed << setprecision(2);

    cout << "\nMatrix W (Weights):\n";
    for (int gap = 0; gap <= n; gap++) {
        for (int i = 0; i <= n - gap; i++) {
            int j = i + gap;
            cout << "W[" << i << "][" << j << "] = " << W[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nMatrix C (Costs):\n";
    for (int gap = 0; gap <= n; gap++) {
        for (int i = 0; i <= n - gap; i++) {
            int j = i + gap;
            cout << "C[" << i << "][" << j << "] = " << C[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nMatrix R (Roots):\n";
    for (int gap = 0; gap <= n; gap++) {
        for (int i = 0; i <= n - gap; i++) {
            int j = i + gap;
            cout << "R[" << i << "][" << j << "] = " << R[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nMinimum cost of Optimal BST = " << C[0][n] << endl;

    cout << "\nOptimal Binary Search Tree Structure:\n";
    showTree(0, n, "None", "Root");
}

void OBST::showTree(int i, int j, string parent, string direction) {
    int rootIndex = R[i][j];
    if (rootIndex == 0 || rootIndex == -1)
        return;

    string currKey = key[rootIndex - 1];
    cout << currKey << " is the " << direction << " of " << parent << endl;

    showTree(i, rootIndex - 1, currKey, "Left");
    showTree(rootIndex, j, currKey, "Right");
}

int main() {
    OBST t;
    t.accept();
    t.calculate();
    t.display();
    return 0;
}
