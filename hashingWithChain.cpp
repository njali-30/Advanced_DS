#include <iostream>
using namespace std;

int key[10], n;

class student {
public:
    int prn;
    string name, email, dob;
    int chain;

    void table();
    void accept();
    void search();
    void display();
    void modify();
    void Delete();
};

student h[10];

void student::table() {
    cout << "\nEnter the total number of keys (max 10): ";
    cin >> n;
    cout << "Enter the keys (PRNs): ";
    for (int i = 0; i < n; i++) {
        cin >> key[i];
    }
    for (int i = 0; i < 10; i++) {
        h[i].prn = -1;
        h[i].chain = -1;
    }
}

void student::accept() {
    int loc, i;
    for (int k = 0; k < n; k++) {
        loc = key[k] % 10;

        if (h[loc].prn == -1) {
            // Empty slot
            h[loc].prn = key[k];
            cout << "Enter the student name, email and DOB for PRN " << key[k] << ": ";
            cin >> h[loc].name >> h[loc].email >> h[loc].dob;
            h[loc].chain = -1;
        } else {
            // Collision occurred, apply linear probing
            int j = (loc + 1) % 10;
            while (h[j].prn != -1 && j != loc) {
                j = (j + 1) % 10;
            }
            if (j == loc) {
                cout << "\nHash table is full!\n";
                return;
            }

            h[j].prn = key[k];
            cout << "Enter the student name, email and DOB for PRN " << key[k] << ": ";
            cin >> h[j].name >> h[j].email >> h[j].dob;
            h[j].chain = -1;

            // Update chain
            int t = loc;
            while (h[t].chain != -1) {
                t = h[t].chain;
            }
            h[t].chain = j;
        }
    }
}

void student::display() {
    cout << "\nLoc\tPRN\tName\tEmail\tDOB\t\tChain";
    for (int i = 0; i < 10; i++) {
        if (h[i].prn != -1) {
            cout << "\n" << i << "\t" << h[i].prn << "\t" << h[i].name << "\t" << h[i].email << "\t" << h[i].dob << "\t" << h[i].chain;
        } else {
            cout << "\n" << i << "\t--\t--\t--\t--\t--";
        }
    }
}

void student::search() {
    int r, loc;
    cout << "\nEnter the PRN of the student to search: ";
    cin >> r;
    loc = r % 10;
    int i = loc;

    while (i != -1) {
        if (h[i].prn == r) {
            cout << "\nRecord Found.";
            cout << "\nPRN: " << h[i].prn << ", Name: " << h[i].name << ", Email: " << h[i].email << ", DOB: " << h[i].dob;
            return;
        }
        i = h[i].chain;
    }

    cout << "\nRecord Not Found.";
}

void student::modify() {
    int r, loc;
    cout << "\nEnter the PRN of the student to modify: ";
    cin >> r;
    loc = r % 10;
    int i = loc;

    while (i != -1) {
        if (h[i].prn == r) {
            cout << "Enter new name, email, and DOB: ";
            cin >> h[i].name >> h[i].email >> h[i].dob;
            cout << "Record updated successfully.\n";
            return;
        }
        i = h[i].chain;
    }

    cout << "Record not found.\n";
}

void student::Delete() {
    int r, loc;
    cout << "\nEnter the PRN of the student to delete: ";
    cin >> r;
    loc = r % 10;

    int prev = -1, i = loc;

    while (i != -1) {
        if (h[i].prn == r) {
            h[i].prn = -1;
            h[i].name = h[i].email = h[i].dob = "";
            if (prev != -1)
                h[prev].chain = h[i].chain;
            h[i].chain = -1;
            cout << "Record deleted successfully.\n";
            return;
        }
        prev = i;
        i = h[i].chain;
    }

    cout << "Record not found.\n";
}

int main() {
    student s;
    int choice;
    do {
        cout << "\n\n--- Menu ---";
        cout << "\n1. Create Table";
        cout << "\n2. Insert (Accept)";
        cout << "\n3. Display";
        cout << "\n4. Search";
        cout << "\n5. Modify";
        cout << "\n6. Delete";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: s.table(); break;
            case 2: s.accept(); break;
            case 3: s.display(); break;
            case 4: s.search(); break;
            case 5: s.modify(); break;
            case 6: s.Delete(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}
