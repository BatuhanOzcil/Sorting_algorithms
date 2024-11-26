
#include <iostream>
#include <string>
using namespace std;

struct node {
    string firstName;
    string lastName;
    int age;
    string gender;
    node* next;
};

class Ozcil {
private:
    node* head;

    void bubbleSort(node* start);
    void insertionSort(node*& start);
    void selectionSort(node*& start);
    void quickSort(node*& start);
    node* partition(node* start, node* end);
    void heapSort(node*& start);
    void mergeSort(node*& start);
    node* merge(node* left, node* right);

public:
    Ozcil() : head(nullptr) {}

    void addNode(string firstName, string lastName, int age, string gender);
    void displayList();
    void sortMenu();
};

void Ozcil::addNode(string firstName, string lastName, int age, string gender) {
    node* newNode = new node{firstName, lastName, age, gender, nullptr};
    if (!head) {
        head = newNode;
    } else {
        node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void Ozcil::displayList() {
    node* temp = head;
    while (temp) {
        cout << temp->firstName << " " << temp->lastName << ", Age: " << temp->age << ", Gender: " << temp->gender << endl;
        temp = temp->next;
    }
}

void Ozcil::bubbleSort(node* start) {
    bool swapped;
    node* ptr1;
    node* lptr = nullptr;

    if (!start)
        return;

    do {
        swapped = false;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->lastName > ptr1->next->lastName) {
                swap(ptr1->firstName, ptr1->next->firstName);
                swap(ptr1->lastName, ptr1->next->lastName);
                swap(ptr1->age, ptr1->next->age);
                swap(ptr1->gender, ptr1->next->gender);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void Ozcil::selectionSort(node*& start) {
    node* temp = start;

    while (temp) {
        node* minNode = temp;
        node* r = temp->next;

        while (r) {
            if (r->lastName < minNode->lastName) {
                minNode = r;
            }
            r = r->next;
        }

        swap(temp->firstName, minNode->firstName);
        swap(temp->lastName, minNode->lastName);
        swap(temp->age, minNode->age);
        swap(temp->gender, minNode->gender);

        temp = temp->next;
    }
}

void Ozcil::insertionSort(node*& start) {
    node* sorted = nullptr;
    node* current = start;

    while (current) {
        node* next = current->next;

        if (!sorted || sorted->lastName > current->lastName) {
            current->next = sorted;
            sorted = current;
        } else {
            node* temp = sorted;
            while (temp->next && temp->next->lastName <= current->lastName) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    start = sorted;
}

void Ozcil::quickSort(node*& start) {
    if (!start || !start->next)
        return;

    node* pivot = start;
    node* lessHead = nullptr, *lessTail = nullptr;
    node* greaterHead = nullptr, *greaterTail = nullptr;
    node* current = start->next;

    while (current) {
        node* next = current->next;
        if (current->lastName < pivot->lastName) {
            current->next = lessHead;
            lessHead = current;
        } else {
            current->next = greaterHead;
            greaterHead = current;
        }
        current = next;
    }

    quickSort(lessHead);
    quickSort(greaterHead);

    if (lessHead) {
        node* temp = lessHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = pivot;
        start = lessHead;
    } else {
        start = pivot;
    }

    pivot->next = greaterHead;
}

void Ozcil::heapSort(node*& start) {
    
}

void Ozcil::mergeSort(node*& start) {
    if (!start || !start->next)
        return;

    node* mid = start;
    node* fast = start->next;

    while (fast && fast->next) {
        mid = mid->next;
        fast = fast->next->next;
    }

    node* left = start;
    node* right = mid->next;
    mid->next = nullptr;

    mergeSort(left);
    mergeSort(right);

    start = merge(left, right);
}

node* Ozcil::merge(node* left, node* right) {
    if (!left)
        return right;
    if (!right)
        return left;

    if (left->lastName < right->lastName) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

void Ozcil::sortMenu() {
    int choice;
    do {
        cout << "~~ WELCOME Sorting Algorithms program ~~" << endl;
        cout << "Select and Enter Your Choice from the Menu:" << endl;
        cout << "1. Bubble Sort" << endl;
        cout << "2. Insertion Sort" << endl;
        cout << "3. Selection Sort" << endl;
        cout << "4. Quick Sort" << endl;
        cout << "5. Heap Sort" << endl;
        cout << "6. Merge Sort" << endl;
        cout << "7. Cancel" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                bubbleSort(head);
                cout << "List sorted using Bubble Sort." << endl;
                break;
            case 2:
                insertionSort(head);
                cout << "List sorted using Insertion Sort." << endl;
                break;
            case 3:
                selectionSort(head);
                cout << "List sorted using Selection Sort." << endl;
                break;
            case 4:
                quickSort(head);
                cout << "List sorted using Quick Sort." << endl;
                break;
            case 5:
                heapSort(head);
                cout << "List sorted using Heap Sort." << endl;
                break;
            case 6:
                mergeSort(head);
                cout << "List sorted using Merge Sort." << endl;
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice >= 1 && choice <= 6) {
            displayList();
        }

    } while (choice != 7);
}

int main() {
    Ozcil list;

    list.addNode("Batuhan", "Özçil", 30, "Male");
    list.addNode("Hakan", "Başhelvacı", 25, "Male");
    list.addNode("Günay", "Teymur", 35, "Female");

    list.sortMenu();

    return 0;
}
