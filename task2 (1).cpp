#include <iostream>
#include <string>
using namespace std;

// Node of the circular doubly linked list (one photo)
struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo* next;
    Photo* prev;
};

Photo* head = NULL;      // first photo
Photo* current = NULL;   // selected photo

// Make a new photo by taking input from user
Photo* createPhoto() {
    Photo* p = new Photo;
    cout << "Enter photo ID: ";
    cin >> p->id;
    cin.ignore();
    cout << "Enter photo name: ";
    getline(cin, p->name);
    cout << "Enter date taken: ";
    getline(cin, p->date);
    cout << "Enter location: ";
    getline(cin, p->location);
    p->next = NULL;
    p->prev = NULL;
    return p;
}

// Add photo at the end of the list
void addPhoto(Photo* p) {
    if (head == NULL) {
        p->next = p;
        p->prev = p;
        head = p;
        current = p;
    } else {
        Photo* tail = head->prev;
        p->next = head;
        p->prev = tail;
        tail->next = p;
        head->prev = p;
    }
    cout << "Photo added.\n";
}

// Insert photo after the current photo
void insertAfterCurrent(Photo* p) {
    if (head == NULL) {
        p->next = p;
        p->prev = p;
        head = p;
        current = p;
    } else {
        p->next = current->next;
        p->prev = current;
        current->next->prev = p;
        current->next = p;
    }
    cout << "Photo inserted after current.\n";
}

// Remove a given node from the list
void removeNode(Photo* target) {
    if (target->next == target) {
        // only one photo in album
        head = NULL;
        current = NULL;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        if (target == head) {
            head = target->next;
        }
        if (target == current) {
            current = target->next;   // next photo becomes current
        }
    }
    delete target;
}

// Remove photo by ID
void removeById(int id) {
    if (head == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    Photo* temp = head;
    do {
        if (temp->id == id) {
            removeNode(temp);
            cout << "Photo removed.\n";
            return;
        }
        temp = temp->next;
    } while (temp != head);
    cout << "Photo not found.\n";
}

void removeCurrent() {
    if (current == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    removeNode(current);
    cout << "Current photo removed.\n";
}

void moveNext() {
    if (current == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    current = current->next;
    cout << "Moved to next photo.\n";
}

void movePrevious() {
    if (current == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    current = current->prev;
    cout << "Moved to previous photo.\n";
}

void printPhoto(Photo* p) {
    cout << "ID: " << p->id << " | Name: " << p->name
         << " | Date: " << p->date << " | Location: " << p->location << endl;
}

void displayForward() {
    if (current == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    Photo* temp = current;
    do {
        printPhoto(temp);
        temp = temp->next;
    } while (temp != current);
}

void displayBackward() {
    if (current == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    Photo* temp = current;
    do {
        printPhoto(temp);
        temp = temp->prev;
    } while (temp != current);
}

void searchPhoto(int id) {
    if (head == NULL) {
        cout << "Album is empty.\n";
        return;
    }
    Photo* temp = head;
    do {
        if (temp->id == id) {
            cout << "Photo found!\n";
            printPhoto(temp);
            return;
        }
        temp = temp->next;
    } while (temp != head);
    cout << "Photo not found.\n";
}

void countPhotos() {
    if (head == NULL) {
        cout << "Total photos: 0\n";
        return;
    }
    int count = 0;
    Photo* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    cout << "Total photos: " << count << endl;
}

// Free all memory at the end
void deleteAll() {
    while (head != NULL) {
        removeNode(head);
    }
}

int main() {
    int n;
    cout << "Enter number of photos: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "\nPhoto " << i << ":\n";
        Photo* p = createPhoto();
        addPhoto(p);
    }

    int choice;
    do {
        cout << "\n===== Circular Photo Album =====\n";
        cout << "1. Add Photo\n";
        cout << "2. Insert Photo After Current\n";
        cout << "3. Remove Photo (by ID)\n";
        cout << "4. Remove Current Photo\n";
        cout << "5. Move Next\n";
        cout << "6. Move Previous\n";
        cout << "7. Display Album Forward\n";
        cout << "8. Display Album Backward\n";
        cout << "9. Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Photo* p = createPhoto();
            addPhoto(p);
        }
        else if (choice == 2) {
            Photo* p = createPhoto();
            insertAfterCurrent(p);
        }
        else if (choice == 3) {
            int id;
            cout << "Enter photo ID to remove: ";
            cin >> id;
            removeById(id);
        }
        else if (choice == 4) removeCurrent();
        else if (choice == 5) moveNext();
        else if (choice == 6) movePrevious();
        else if (choice == 7) displayForward();
        else if (choice == 8) displayBackward();
        else if (choice == 9) {
            int id;
            cout << "Enter photo ID to search: ";
            cin >> id;
            searchPhoto(id);
        }
        else if (choice == 10) countPhotos();
        else if (choice != 0) cout << "Invalid choice.\n";
    } while (choice != 0);

    deleteAll();
    return 0;
}