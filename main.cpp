#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Node
{
    char url[300];
    Node *next;
};

class Stack
{
public:
    Node *top;

    Stack() 
    { 
        top = NULL; 
    }

    void push(char newUrl[])
    {
        Node *newNode = new Node;
        strcpy(newNode->url, newUrl);
        newNode->next = top;
        top = newNode;
    }

    bool isEmpty() { return top == NULL; }

    void pop(char poppedUrl[])
    {
        if (isEmpty())
            return;
        strcpy(poppedUrl, top->url);
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    void peek(char current[])
    {
        if (!isEmpty())
            strcpy(current, top->url);
    }

    void clear()
    {
        while (!isEmpty())
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }
};

class BrowHist
{
public:
    Stack backStack;
    Stack forwardStack;
    char currentUrl[300];

    BrowHist(const char *startUrl)
    {
        strcpy(currentUrl, startUrl);
        backStack.push(currentUrl);
    }

    void visit(char newUrl[])
    {
        forwardStack.clear();
        backStack.push(newUrl);
        strcpy(currentUrl, newUrl);
        cout << "Visited---> " << currentUrl << endl;
    }

    void goBack()
    {
        if (backStack.isEmpty())
        {
            cout << "No previous page" << endl;
            return;
        }

        char temp[300];
        backStack.pop(temp);

        if (backStack.isEmpty())
        {
            backStack.push(temp);
            cout << "Can't go back further" << endl;
        }
        else
        {
            forwardStack.push(currentUrl);
            backStack.peek(currentUrl);
            cout << "Went back to---> " << currentUrl << endl;
        }
    }

    void goForward()
    {
        if (forwardStack.isEmpty())
        {
            cout << "No forward history" << endl;
        }
        else
        {
            forwardStack.pop(currentUrl);
            backStack.push(currentUrl);
            cout << "Went forward to---> " << currentUrl << endl;
        }
    }

    void showCurrent()
    {
        cout << "\nCurrent page---> " << currentUrl << endl;
    }
};

void manualInput(BrowHist &browser)
{
    char command[20];
    char url[300];
    while (true)
    {
        cout << "\nChoose:\n1. VISIT\n2. BACK\n3. FORWARD\n4. EXIT\n>> ";
        cin >> command;

        if (strcmp(command, "1") == 0)
        {
            cout << "Enter URL: ";
            cin.ignore();
            cin.getline(url, 300);
            browser.visit(url);
        }
        else if (strcmp(command, "2") == 0)
        {
            browser.goBack();
        }
        else if (strcmp(command, "3") == 0)
        {
            browser.goForward();
        }
        else if (strcmp(command, "4") == 0)
        {
            break; // Return to main menu
        }
        else
        {
            cout << "Invalid command.\n";
        }
    }
}

void readFromFile(BrowHist &browser)
{
    ifstream file("test.txt");
    if (!file)
    {
        cout << "Error: Could not open file.\n";
        return;
    }

    char command[20];
    char url[300];

    while (file >> command)
    {
        if (strcmp(command, "VISIT") == 0)
        {
            file.get();
            file.getline(url, 300);
            browser.visit(url);
        }
        else if (strcmp(command, "BACK") == 0)
        {
            browser.goBack();
        }
        else if (strcmp(command, "FORWARD") == 0)
        {
            browser.goForward();
        }
    }

    file.close();
    browser.showCurrent();
}

int main()
{
    BrowHist browser("https://www.google.com");

    while (true)
    {
        int choice;
        cout << "\n--- Browser Menu ---\n";
        cout << "1. Manual Input\n";
        cout << "2. Read from File\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            manualInput(browser);
        }
        else if (choice == 2)
        {
            readFromFile(browser);
        }
        else if (choice == 3)
        {
            cout << "  GOOD BYE\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
