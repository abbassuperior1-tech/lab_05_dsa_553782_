#include <iostream>
#include <string>
using namespace std;

// Node of the circular doubly linked list (one browser tab)
struct Tab {
    int id;
    string title;
    string url;
    Tab* next;
    Tab* prev;
};

Tab* current = NULL;   // active tab

// Open a new tab after the current tab
void openTab(int id, string title, string url) {
    Tab* newTab = new Tab;
    newTab->id = id;
    newTab->title = title;
    newTab->url = url;

    if (current == NULL) {
        //  as  the  concept is first tab points to itself
        newTab->next = newTab;
        newTab->prev = newTab;
    } else {
        newTab->next = current->next;
        newTab->prev = current;
        current->next->prev = newTab;
        current->next = newTab;
    }
    current = newTab;   // new tab becomes the active tab
    cout << "Tab opened.\n";
}

// Close the current tab
void closeTab() {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    Tab* temp = current;
    if (current->next == current) {
        // only one tab
        current = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;   // next tab becomes current
    }
    delete temp;
    cout << "Tab closed.\n";
}

void moveNext() {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    current = current->next;
    cout << "Moved to next tab.\n";
}

void movePrevious() {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    current = current->prev;
    cout << "Moved to previous tab.\n";
}

void showCurrent() {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    cout << "ID: " << current->id << endl;
    cout << "Title: " << current->title << endl;
    cout << "URL: " << current->url << endl;
}

// Show all tabs going forward, starting from current
void showForward() {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    Tab* temp = current;
    do {
        cout << "ID: " << temp->id << " | Title: " << temp->title
             << " | URL: " << temp->url << endl;
        temp = temp->next;
    } while (temp != current);   // stop when we come back to start
}

// Show all tabs going backward, starting from current
void showBackward() {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    Tab* temp = current;
    do {
        cout << "ID: " << temp->id << " | Title: " << temp->title
             << " | URL: " << temp->url << endl;
        temp = temp->prev;
    } while (temp != current);
}

// Search a tab by ID
void searchTab(int id) {
    if (current == NULL) {
        cout << "No tabs are open.\n";
        return;
    }
    Tab* temp = current;
    do {
        if (temp->id == id) {
            cout << "Tab found!\n";
            cout << "ID: " << temp->id << endl;
            cout << "Title: " << temp->title << endl;
            cout << "URL: " << temp->url << endl;
            return;
        }
        temp = temp->next;
    } while (temp != current);
    cout << "Tab not found.\n";
}

// Delete all remaining tabs (no memory leak)
void deleteAll() {
    while (current != NULL) {
        closeTab();
    }
}

int main() {
    int choice;
    do {
        cout << "\n===== Browser Tab Manager =====\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, url;
            cout << "Enter tab ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter website title: ";
            getline(cin, title);
            cout << "Enter URL: ";
            getline(cin, url);
            openTab(id, title, url);
        }
        else if (choice == 2) closeTab();
        else if (choice == 3) moveNext();
        else if (choice == 4) movePrevious();
        else if (choice == 5) showCurrent();
        else if (choice == 6) showForward();
        else if (choice == 7) showBackward();
        else if (choice == 8) {
            int id;
            cout << "Enter tab ID to search: ";
            cin >> id;
            searchTab(id);
        }
        else if (choice != 0) cout << "Invalid choice.\n";
    } while (choice != 0);

    deleteAll();
    return 0;
}