#include <iostream>
#include <string>
using namespace std;

struct Book{
    int id;
    string title;
    string author;
    bool isAvailable;
    Book* next;
};

void addBook(Book*& head, int id, string title, string author){
    Book* newBook=new Book{id, title, author, true, NULL};
    if(!head){
        head=newBook;
    } else{
        Book* temp=head;
        while(temp->next) temp=temp->next;
        temp->next=newBook;
    }
}

void displayBooks(Book* head){
    if(!head){
        cout<<"No books in inventory.\n";
        return;
    }
    Book* temp=head;
    while(temp){
        cout<<"ID: "<<temp->id<<"\nTitle: "<<temp->title
            <<"\nAuthor: "<<temp->author
            <<"\nStatus: "<<(temp->isAvailable ? "Available" : "Checked Out")<<"\n\n";
        temp=temp->next;
    }
}

void searchBook(Book* head, int id){
    Book* temp=head;
    while(temp){
        if(temp->id==id){
            cout<<"Book Found:\nTitle: "<<temp->title<<"\nAuthor: "<<temp->author
                <<"\nStatus: "<<(temp->isAvailable ? "Available" : "Checked Out")<<"\n";
            return;
        }
        temp=temp->next;
    }
    cout<<"Book not found.\n";
}

void deleteBook(Book*& head, int id){
    if(!head) return;
    if(head->id==id){
        Book* toDelete=head;
        head=head->next;
        delete toDelete;
        cout<<"Book deleted from inventory.\n";
        return;
    }
    Book* temp=head;
    while(temp->next && temp->next->id!=id) temp=temp->next;
    if(temp->next){
        Book* toDelete=temp->next;
        temp->next=temp->next->next;
        delete toDelete;
        cout<<"Book deleted from inventory.\n";
    } else{
        cout<<"Book not found.\n";
    }
}

void toggleAvailability(Book* head, int id){
    Book* temp=head;
    while(temp){
        if(temp->id==id){
            temp->isAvailable=!temp->isAvailable;
            cout<<"Book availability updated.\n";
            return;
        }
        temp=temp->next;
    }
    cout<<"Book not found.\n";
}

int main(){
    Book* head=NULL;
    int choice, id;
    string title, author;

    do{
        cout<<"\n1. Add Book\n2. Display Books\n3. Search Book\n4. Delete Book\n5. Toggle Availability\n6. Exit\nEnter choice: ";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:
                cout<<"Enter Book ID: "; cin>>id; cin.ignore();
                cout<<"Enter Title: "; getline(cin, title);
                cout<<"Enter Author: "; getline(cin, author);
                addBook(head, id, title, author);
                break;
            case 2:
                displayBooks(head);
                break;
            case 3:
                cout<<"Enter Book ID to search: "; cin>>id;
                searchBook(head, id);
                break;
            case 4:
                cout<<"Enter Book ID to delete: "; cin>>id;
                deleteBook(head, id);
                break;
            case 5:
                cout<<"Enter Book ID to toggle availability: "; cin>>id;
                toggleAvailability(head, id);
                break;
            case 6:
                cout<<"Exiting...\n";
                break;
            default:
                cout<<"Invalid choice.\n";
        }
    } while(choice!=6);

    return 0;
}
