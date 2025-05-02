#include <iostream>
using namespace std;

class Student {
    int seat_no, cet;
    string name, city;

public:
    Student *LC, *RC;
    void create();
    void add();
    void insert(Student *root, Student *next);
    void inorderR(Student *root);
    void displayIITians(Student *root);
    void displayNonIITians(Student *root);
    int height(Student *root);
    Student* search(Student *root, int roll);
    void modifyStudent(Student *root, int roll);
} *root = NULL;

void Student::create() {
    if (root == NULL) {
        root = new Student;
        cout << "Enter Seat Number, Name, City, CET Score: ";
        cin >> root->seat_no >> root->name >> root->city >> root->cet;
        root->LC = root->RC = NULL;
        cout << "Root node created successfully!\n";
    } else {
        cout << "Tree already created! Use option 2 to add more students.\n";
    }
}

void Student::add() {
    if (root == NULL) {
        cout << "Tree is empty! Create the root node first.\n";
        return;
    }
    Student *next = new Student;
    cout << "Enter Seat Number, Name, City, CET Score: ";
    cin >> next->seat_no >> next->name >> next->city >> next->cet;
    next->LC = next->RC = NULL;
    insert(root, next);
    cout << "Student added successfully!\n";
}

void Student::insert(Student *root, Student *next) {
    if (next->seat_no < root->seat_no) {  
        if (root->LC == NULL) {
            root->LC = next;
        } else {
            insert(root->LC, next);
        }
    } else {
        if (root->RC == NULL) {
            root->RC = next;
        } else {
            insert(root->RC, next);
        }
    }
}


void Student::inorderR(Student *root) {
    if (root == NULL) return;
    inorderR(root->LC);
    cout << "\n" << root->seat_no << "\t" << root->name << "\t" << root->city << "\t" << root->cet;
    inorderR(root->RC);
}

void Student::displayIITians(Student *root) {
    if (root == NULL) return;
    displayIITians(root->LC);
    if (root->cet > 90) {
        cout << "\n" << root->seat_no << "\t" << root->name << "\t" << root->city << "\t" << root->cet;
    }
    displayIITians(root->RC);
}

void Student::displayNonIITians(Student *root) {
    if (root == NULL) return;
    displayNonIITians(root->LC);
    if (root->cet < 90) {
        cout << "\n" << root->seat_no << "\t" << root->name << "\t" << root->city << "\t" << root->cet;
    }
    displayNonIITians(root->RC);
}

int Student::height(Student *root) {
    if (root == NULL) return 0;
    int LeftHeight = height(root->LC);
    int RightHeight = height(root->RC);
    return max(LeftHeight, RightHeight) + 1;
}

Student* Student::search(Student *root, int key) {
    if (root == NULL) return NULL;
    if (root->seat_no == key) {
        cout << "\nSEAT NO\tNAME\tCITY\tCET";
        cout << "\n" << root->seat_no << "\t" << root->name << "\t" << root->city << "\t" << root->cet << "\n";
        return root;
    }
    if (key < root->seat_no) {
        return search(root->LC, key);
    }
    return search(root->RC, key);
}


void Student::modifyStudent(Student *root, int roll) {
    Student *student = search(root, roll);
    if (student != NULL) {
        cout << "Enter new details: ";
        cout << "\nEnter Name, City, CET Score: ";
        cin >> student->name >> student->city >> student->cet;
        cout << "\nStudent details updated successfully!\n";
    } else {
        cout << "\nStudent not found!\n";
    }
}


int main() {
    int choice;
    do {
        cout << "\nMENU:\n1. Create Root Student\n2. Add Student\n3. Display All Students\n4. Display IITians\n5. Display Non-IITians\n6. Display Height of BST\n7. Search Student\n8. Modify Student Details\n9. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Student().create(); 
                break;
            case 2:
                if (root != NULL) {
                    root->add();
                } else {
                    cout << "\nNo tree exists! Create the root first.";
                }
                break;
            case 3:
                if (root != NULL) {
                    cout << "\nSEAT NO\tNAME\tCITY\tCET";
                    root->inorderR(root);
                } else {
                    cout << "\nNo records to display!";
                }
                break;
            case 4:
                if (root != NULL) {
                    cout << "\nIIT Students:\nSEAT NO\tNAME\tCITY\tCET";
                    root->displayIITians(root);
                } else {
                    cout << "\nNo IIT students found!";
                }
                break;
            case 5:
                if (root != NULL) {
                    cout << "\nNon-IIT Students:\nSEAT NO\tNAME\tCITY\tCET";
                    root->displayNonIITians(root);
                } else {
                    cout << "\nNo non-IIT students found!";
                }
                break;
            case 6:
                cout << "\nHeight of BST: " << root->height(root);
                break;
            case 7:
                int roll;
                cout << "\nEnter Seat Number to search: ";
                cin >> roll;
                if (root->search(root, roll) != NULL)
                    cout << "\nStudent found!";
                else
                    cout << "\nStudent not found!";
                break;
            case 8:
                cout << "\nEnter Seat Number to modify: ";
                cin >> roll;
                root->modifyStudent(root, roll);
                break;
            case 9:
                cout << "Exiting program...";
                break;
            default:
                cout << "Invalid choice! Try again.";
        }
    } while (choice != 10);
    return 0;
}
