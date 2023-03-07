#include <bits/stdc++.h>
#include <fstream>
using namespace std;

//node for line input
class Node {
public:
    string line;
    Node* next;
    Node(string l) {
        line = l;
        next = NULL;
    }
};

//class for controller for text editor
class TextEditor {
public:
    Node* head;
    int size;
    TextEditor()
    {
        //constructor
        head = nullptr;
        size = 0;
    }

    void insert(string l, int n)
     {
        //input a new line at line n
        if(n < 1 || n > size + 1)
        {
            cout<<"Invalid line number\n";
            return;
        }
        Node* newLine = new Node(l);
        if (n == 1) {
            newLine->next = head;
            head = newLine;
        }
        else {
            Node* curr = head;
            for(int i = 1; i < n - 1; i++) {
                curr = curr->next;
            }
            newLine->next = curr->next;
            curr->next = newLine;
        }
        size++;
    }

    void del(int n) {
        //delete line n
        if (n < 1 || n > size)
        {
            cout << "Invalid line number\n";
            return;
        }
        Node* temp;
        if (n == 1)
        {
            temp = head;
            head = head->next;
        }
        else 
        {
            Node* curr = head;
            for (int i = 1; i < n - 1; i++) {
                curr = curr->next;
            }
            temp = curr->next;
            curr->next = curr->next->next;
        }
        
        delete temp;
        size--;
    }
    void move(int n, int m)
    {
        //replace line n with line m
        if (n < 1 || n > size || m < 1 || m > size || n == m) 
        {
            cout << "Invalid line number\n";
            return;
        }

        Node* currN = head;
        Node* prevN = nullptr;
        for(int i = 1; i < n; i++)
        {
            prevN = currN;
            currN = currN->next;
        }
        Node* currM = head;
        Node* prevM = nullptr;
        for(int i = 1; i < m; i++) 
        {
            prevM = currM;
            currM = currM->next;
        }
        if (n == 1 && m == size) 
        {
            head = currN->next;
            currN->next = nullptr;
            currM->next = currN;
        }
        else if (n == 1) 
        {
            head = currN->next;
            currN->next = currM->next;
            currM->next = currN;
        }
        else if (m == size) 
        {
            prevN->next = currN->next;
            currN->next = nullptr;
            prevM->next = currN;
        }
        else 
        {
            prevN->next = currN->next;
            currN->next = currM->next;
            currM->next = currN;
        }
    }


    void replace(string l, int n) 
    {   //replace old text with new text
        if (n < 1 || n > size) 
        {
            cout << "Invalid line number\n";
            return;
        }
        Node* curr = head;
        for(int i = 1; i < n; i++) 
        curr = curr->next;
        
        curr->line = l;
        
    }


    void print() 
    {
        //print the data
        Node* curr = head;
        int lineNumber = 1;
        while (curr != nullptr) 
        {
        cout << lineNumber << ": " << curr->line << endl;
        curr = curr->next;
        lineNumber++;
        }
    }

    void saveToFile(string filename) 
    {
        //utilizing file handling for saving and reading files
    ofstream fileOutput(filename);
    if (!fileOutput.is_open()) 
    {
        cout << "Could not open file for writing\n";
        return;
    }
    Node* curr = head;
    while (curr != nullptr) 
    {
        fileOutput << curr->line << endl;
        curr = curr->next;
    }
    fileOutput.close();
    cout << "Data saved to " << filename << endl;
    }

    void readFromFile(string filename) {
         //utilizing file handling for saving and reading files
    ifstream fileInput(filename);
    if (!fileInput.is_open()) {
        cout << "could not open file..." << filename << "\"\n";
        return;
    }
    string line;
    while (getline(fileInput, line)) {
        insert(line, size);
    }

    fileInput.close();
    }
};


int main() {
    int choice;
    string filename;
    TextEditor editor;
    //menu driven main function
    while (1) 
    {
        cout << "\nTEXT EDITOR\n";
        cout << "1. Insert line to a line number\n";
        cout << "2. Delete a specific line number\n";
        cout << "3. Replace text in a line\n";
        cout << "4. Move line from one to another\n";
        cout << "5. Print all data\n";
        cout << "6. Open a file with a name\n";
        cout << "7. Save to a file with a name\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int lineNumber;
                string lineText;
                cout << "Enter line number: ";
                cin >> lineNumber;
                cin.ignore();
                cout << "Enter text: ";
                getline(cin, lineText);

                editor.insert(lineText, lineNumber);
                break;
            }
            case 2: {
                int lineNumber;

                cout << "Enter line number: ";
                cin >> lineNumber;

                editor.del(lineNumber);
                break;
            }
            case 3: {
                int lineNumber;
                string newText;

                cout << "Enter line number: ";
                cin >> lineNumber;
                cin.ignore(); 
                cout << "Enter text: ";
                getline(cin, newText);

                editor.replace(newText, lineNumber);
                break;
            }
            case 4: {
                int lineNum, destNum;

                cout << "Enter line number to move : ";
                cin >> lineNum;
                cout << "Enter destination: ";
                cin >> destNum;

                editor.move(lineNum, destNum);
                break;
            }
            case 5: {
                editor.print();
                break;
            }
           
            case 6: {
                cout << "Enter filename to open the data from: ";
                cin >> filename;
                editor.readFromFile(filename);
                break;
            }
            case 7: {
                cout << "Enter filename to save the data in: ";
                cin >> filename;
                editor.saveToFile(filename);
                break;
            }
            case 8: {
                cout << "Exitting..\n";
                exit(0);
            }
            default: {
                cout << "Invalid.\n";
                break;
            }
        }
    }

    return 0;
}

           
