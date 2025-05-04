#include<iostream>
using namespace std;

class Student {
    int roll_no, cgpa;
    string name, address, dob;

public:
    Student *LC, *RC;
    void create();
    void insert(Student *root, Student *next);
    void inorderR(Student *root);
    void inorderNR(Student *root);
    void displayLeafNodes(Student *root);
    void displayInternalNodes(Student *root);
    int calculateHeight(Student *root);
    Student() : LC(NULL), RC(NULL) {}  //constructor initialization list
} *root = NULL, *S[100];

void Student::create() {
    root = new Student;
    cout << "Enter Roll number, Name, DOB, Address, CGPA: ";
    cin >> root->roll_no >> root->name >> root->dob >> root->address >> root->cgpa;
    root->LC = root->RC = NULL;
    
    int ch;
    do {
        cout << "Enter 1 to add another student, 0 to exit: ";
        cin >> ch;
        if (ch == 1) {
            Student *next = new Student;
            cout << "Enter Roll number, Name, DOB, Address, CGPA: ";
            cin  >> next->roll_no >> next->name >> next->dob >> next->address >> next->cgpa;
            next->LC = next->RC = NULL;
            insert(root, next);
        }
    } while (ch == 1);
}

void Student::insert(Student *root, Student *next) {
    char c;
    cout << "Insert at LEFT('L') OR Insert at RIGHT('R'): ";
    cin >> c;
    
    if (c == 'L' || c == 'l') {
        if (root->LC == NULL)
            root->LC = next;
        else
            insert(root->LC, next);
    } else if (c == 'R' || c == 'r') {
        if (root->RC == NULL)
            root->RC = next;
        else
            insert(root->RC, next);
    }
}

void Student::inorderR(Student *root) {
    if (root == NULL) return;
    inorderR(root->LC);
    cout << "\n" << root->roll_no << " " << root->name << " " << root->dob << " " << root->address << " " << root->cgpa;
    inorderR(root->RC);
}

void Student::inorderNR(Student *root) {
    if (root == NULL) return;  

    int top = -1;              
    Student *temp = root;      

    while (temp != NULL || top != -1) {  
        // Step 1: Traverse left subtree and push nodes onto stack
        while (temp != NULL) {
            S[++top] = temp;  
            temp = temp->LC;  
        }

        // Step 2: Pop and process node
        temp = S[top--];  
        cout << "\n" << temp->roll_no << " " << temp->name << " " 
             << temp->dob << " " << temp->address << " " << temp->cgpa;

        // Step 3: Move to right subtree
        temp = temp->RC;
    }
}


void Student::displayLeafNodes(Student *root) {
    if (root == NULL) return;
    if (root->LC == NULL && root->RC == NULL) {
        cout << "\n" << root->roll_no << " " << root->name;
    }
    displayLeafNodes(root->LC);
    displayLeafNodes(root->RC);
}

void Student::displayInternalNodes(Student *root) {
    if (root == NULL || (root->LC == NULL && root->RC == NULL)) return;

    if ((root->LC != NULL || root->RC != NULL) && root != ::root) { 
        cout << "\n" << root->roll_no << " " << root->name;
    }
    displayInternalNodes(root->LC);
    displayInternalNodes(root->RC);
}

int Student::calculateHeight(Student *root) {
    if (root == NULL) return 0;
    int leftHeight = calculateHeight(root->LC);
    int rightHeight = calculateHeight(root->RC);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    int choice;
    do {
        cout << "\nMENU:\n1. Create Tree\n2. Inorder Recursive Traversal\n3. Inorder Non-Recursive Traversal\n4. Display Leaf Nodes\n5. Display Internal Nodes\n6. Calculate Height of Tree\n7. Exit\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (root == NULL) {
                    Student().create();
                } else {
                    cout << "Tree already created!";
                }
                break;
            case 2:
                if (root != NULL) {
                    cout << "\nInorder Recursive Traversal:";
                    root->inorderR(root);
                } else {
                    cout << "Tree is empty!";
                }
                break;
            case 3:
                if (root != NULL) {
                    cout << "\nInorder Non-Recursive Traversal:";
                    root->inorderNR(root);
                } else {
                    cout << "Tree is empty!";
                }
                break;
            case 4:
                if (root != NULL) {
                    cout << "\nLeaf Nodes:";
                    root->displayLeafNodes(root);
                } else {
                    cout << "Tree is empty!";
                }
                break;
            case 5:
                if (root != NULL && (root->LC != NULL || root->RC != NULL)) {
                    cout << "\nInternal Nodes:";
                    root->displayInternalNodes(root);
                } else {
                    cout << "No internal nodes!";
                }
                break;
            case 6:
                if (root != NULL) {
                    cout << "\nHeight of Tree: " << root->calculateHeight(root);
                } else {
                    cout << "Tree is empty!";
                }
                break;
            case 7:
                cout << "Exiting program...";
                break;
            default:
                cout << "Invalid choice! Try again.";
        }
    } while (choice != 7);
    return 0;
}
