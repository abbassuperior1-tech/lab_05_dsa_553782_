#include <iostream>
#include <string>
using namespace std;

// Node of the circular doubly linked list (one coach)
struct Coach {
    int number;
    string type;
    int capacity;
    int passengers;
    Coach* next;
    Coach* prev;
};

Coach* head = NULL;      // first coach
Coach* current = NULL;   // selected coach

// Make a new coach by taking input from user
Coach* createCoach() {
    Coach* c = new Coach;
    cout << "Enter coach number: ";
    cin >> c->number;
    cin.ignore();
    cout << "Enter coach type: ";
    getline(cin, c->type);
    cout << "Enter passenger capacity: ";
    cin >> c->capacity;
    cout << "Enter current passengers: ";
    cin >> c->passengers;
    c->next = NULL;
    c->prev = NULL;
    return c;
}

// Find a coach by number (returns NULL if not found)
Coach* findCoach(int number) {
    if (head == NULL) {
        return NULL;
    }
    Coach* temp = head;
    do {
        if (temp->number == number) {
            return temp;
        }
        temp = temp->next;
    } while (temp != head);
    return NULL;
}

// Add coach at the end of the train
void addCoach(Coach* c) {
    if (head == NULL) {
        c->next = c;
        c->prev = c;
        head = c;
        current = c;
    } else {
        Coach* tail = head->prev;
        c->next = head;
        c->prev = tail;
        tail->next = c;
        head->prev = c;
    }
    cout << "Coach added.\n";
}

// Insert coach after a given coach number
void insertCoach(int afterNumber, Coach* c) {
    Coach* temp = findCoach(afterNumber);
    if (temp == NULL) {
        cout << "Coach " << afterNumber << " not found. Cannot insert.\n";
        delete c;
        return;
    }
    c->next = temp->next;
    c->prev = temp;
    temp->next->prev = c;
    temp->next = c;
    cout << "Coach inserted.\n";
}

// Remove a given node from the list
void removeNode(Coach* target) {
    if (target->next == target) {
        // only one coach
        head = NULL;
        current = NULL;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        if (target == head) {
            head = target->next;
        }
        if (target == current) {
            current = target->next;   // next coach becomes current
        }
    }
    delete target;
}

void removeCoach(int number) {
    Coach* temp = findCoach(number);
    if (temp == NULL) {
        cout << "Coach not found.\n";
        return;
    }
    removeNode(temp);
    cout << "Coach removed.\n";
}

void moveForward() {
    if (current == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    current = current->next;
    cout << "Moved to next coach.\n";
}

void moveBackward() {
    if (current == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    current = current->prev;
    cout << "Moved to previous coach.\n";
}

void printCoach(Coach* c) {
    cout << "Coach No: " << c->number << " | Type: " << c->type
         << " | Capacity: " << c->capacity
         << " | Passengers: " << c->passengers << endl;
}

void displayClockwise() {
    if (head == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    Coach* temp = head;
    do {
        printCoach(temp);
        temp = temp->next;
    } while (temp != head);
}

void displayAntiClockwise() {
    if (head == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    Coach* temp = head->prev;   // start from last coach
    Coach* start = temp;
    do {
        printCoach(temp);
        temp = temp->prev;
    } while (temp != start);
}

void searchCoach(int number) {
    Coach* temp = findCoach(number);
    if (temp == NULL) {
        cout << "Coach not found.\n";
    } else {
        cout << "Coach found!\n";
        printCoach(temp);
    }
}

// Find coach with most empty seats
void findMaxAvailable() {
    if (head == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    Coach* best = head;
    Coach* temp = head->next;
    while (temp != head) {
        if ((temp->capacity - temp->passengers) > (best->capacity - best->passengers)) {
            best = temp;
        }
        temp = temp->next;
    }
    cout << "Coach with maximum empty seats ("
         << best->capacity - best->passengers << " seats):\n";
    printCoach(best);
}

void displayCurrent() {
    if (current == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    printCoach(current);
}

// Reverse the train by swapping next and prev of every node
void reverseTrain() {
    if (head == NULL) {
        cout << "Train is empty.\n";
        return;
    }
    Coach* temp = head;
    do {
        Coach* t = temp->next;     // swap next and prev
        temp->next = temp->prev;
        temp->prev = t;
        temp = temp->prev;         // old next (because of swap)
    } while (temp != head);

    head = head->next;   // old last coach becomes the new first coach
    cout << "Train direction reversed.\n";
}

// Free all memory at the end
void deleteAll() {
    while (head != NULL) {
        removeNode(head);
    }
}

int main() {
    int n;
    cout << "Enter number of coaches: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "\nCoach " << i << ":\n";
        Coach* c = createCoach();
        addCoach(c);
    }

    int choice;
    do {
        cout << "\n===== Train Coach Navigation =====\n";
        cout << "1. Add Coach\n";
        cout << "2. Insert Coach After a Coach Number\n";
        cout << "3. Remove Coach\n";
        cout << "4. Move Forward\n";
        cout << "5. Move Backward\n";
        cout << "6. Display Train Clockwise\n";
        cout << "7. Display Train Anti-clockwise\n";
        cout << "8. Search Coach\n";
        cout << "9. Find Maximum Available Capacity\n";
        cout << "10. Display Current Coach\n";
        cout << "11. Reverse Train Direction\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Coach* c = createCoach();
            addCoach(c);
        }
        else if (choice == 2) {
            int after;
            cout << "Insert after which coach number? ";
            cin >> after;
            Coach* c = createCoach();
            insertCoach(after, c);
        }
        else if (choice == 3) {
            int num;
            cout << "Enter coach number to remove: ";
            cin >> num;
            removeCoach(num);
        }
        else if (choice == 4) moveForward();
        else if (choice == 5) moveBackward();
        else if (choice == 6) displayClockwise();
        else if (choice == 7) displayAntiClockwise();
        else if (choice == 8) {
            int num;
            cout << "Enter coach number to search: ";
            cin >> num;
            searchCoach(num);
        }
        else if (choice == 9) findMaxAvailable();
        else if (choice == 10) displayCurrent();
        else if (choice == 11) reverseTrain();
        else if (choice != 0) cout << "Invalid choice.\n";
    } while (choice != 0);

    deleteAll();
    return 0;
}