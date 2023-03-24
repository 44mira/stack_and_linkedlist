#include <iostream>
#include <memory>   // for smart pointers (memory safety)

using namespace std;

class Node{
    public:
        int data;
        shared_ptr<Node> next;
        
        Node(int inp_data): data(inp_data){}
};

class LinkedList{
    private:
        shared_ptr<Node> head;

    public:
        LinkedList(){}
        LinkedList(shared_ptr<Node> head_node){
            head = head_node;
            cout << "List created successfully.";
        }

        bool empty(){
            return !head;
        }

        // prints the linked list
        void print(){
            shared_ptr<Node> current_node = head;

            cout << endl;
            while (current_node){
                cout << current_node->data << endl;   
                current_node = current_node->next;
            }
            cout << endl;
        }

        // inserts node into idx. if overflow; appends instead                
        LinkedList &insert(int idx, shared_ptr<Node> new_node){
            if (idx < 0){
                cout << "ERROR: Invalid index." << endl;
                exit(1);
            }

            if (idx-- == 0){
                new_node->next = head;
                head = new_node;
                cout << "Inserted at head." << endl;
                return *this;
            }

            shared_ptr<Node> current_node = head->next, prev_node = head;

            while (current_node){

                if (idx-- == 0){
                    prev_node->next = new_node;
                    new_node->next = current_node;
                    cout << "Node inserted at index." << endl;
                    return *this;
                } 

                prev_node = current_node;
                current_node = current_node->next;
            }
            prev_node->next = new_node;
            cout << "Node appended." << endl;

            return *this;
        }

        // searches for an in element in the list. returns -1 if not found
        int search(int sr_data){
            if (this->empty()){
                return -1;
            }

            shared_ptr<Node> current_node = head;
            int idx = 0;
            while (current_node){
                if (current_node->data == sr_data){
                    return idx;
                }                

                idx++;
                current_node = current_node->next;
            }

            return -1;
        }

        // removes an element from the list
        LinkedList &remove(int rm_data){
            if (this->empty()){
                cout << "ERROR: List is empty." << endl;
                return *this;
            } 

            int idx = this->search(rm_data);

            if (idx == -1){
                cout << "ERROR: Element not in list." << endl;
                return *this;
            }

            if (idx == 0){
                head = head->next;
                cout << "Head successfully removed." << endl;
                return *this;
            }

            shared_ptr<Node> current_node = head->next, prev_node = head;

            while (current_node){
                if (--idx == 0){
                    prev_node->next = current_node->next;
                    cout << "Node successfully removed." << endl;
                    return *this;
                }

                prev_node = current_node;
                current_node = current_node->next;
            }

            return *this;
        }

        // changes data in an existing node
        LinkedList &update(int rm_data, int up_data){
            if (this->empty()){
                cout << "ERROR: List is empty." << endl;
                return *this;
            } 

            int idx = this->search(rm_data);

            if (idx == -1){
                cout << "ERROR: Element not in list." << endl;
                return *this;
            }

            shared_ptr<Node> current_node = head;
            
            while (current_node){
                if (idx-- == 0){
                    current_node->data = up_data;
                    cout << "Node updated." << endl;
                    return *this;
                }
                current_node = current_node->next;
            } 
            return *this;
        }
};

void menu(LinkedList &llist);

#define make_node make_shared<Node>

int main(){
    LinkedList llist;
    string buf;
    while (true){
        cout << endl;
        menu(llist);
        cout << "\nType anything to continue: ";
        cin >> buf;
        cout << endl;
    }

    return 0;
}

void menu(LinkedList &llist){
    int choice;
    cout << "\n[1] Create new linked list.\n[2] Add an element. (Must create new list if empty)\n[3] Delete an existing element."
            "\n[4] Update an existing element.\n[5] List all elements.\n[6] Search for an element.\n[7] Exit."<<endl;
    cin >> choice;
    if (choice == 1){
        cout << "Input the integer data for the head node: ";
        cin >> choice;
        cout << endl;
        llist = LinkedList(make_node(choice));
    } else if (choice == 2 && !llist.empty()){
        int idx;
        cout << "Data to add: ";
        cin >> choice;
        cout << "\nIndex to add in (appends if overflow): ";
        cin >> idx;
        cout << endl;
        llist.insert(idx, make_node(choice));
    } else if (choice == 3 && !llist.empty()){
        cout << "Data to remove: ";
        cin >> choice;
        cout << endl;
        llist.remove(choice);
    } else if (choice == 4 && !llist.empty()){
        int up_data;
        cout << "Data to update: ";
        cin >> choice;
        cout << "\nNew data: ";
        cin >> up_data;
        cout << endl;
        llist.update(choice,up_data);
    } else if (choice == 5 && !llist.empty()){
        cout << "Here are the data in the list: ";
        llist.print();
    } else if (choice == 6 && !llist.empty()){
        cout << "Data to search for (-1 if not found): ";
        cin >> choice;
        cout << "\nThe element is found at: " << llist.search(choice) << endl;
    } else if (choice == 7){
        cout << "Exiting program." << endl;
        exit(0);
    } else {
        cout << "Invalid choice." << endl;
    }


    


}