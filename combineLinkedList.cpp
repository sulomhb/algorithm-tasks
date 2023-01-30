/*
Problem: How can combine two doubly linked lists?

In the below section, there is explanation about how to combine two Doubly Linked Lists.

Algorithm Instruction:

Create two pointers for the Doubly Linked List one (Head1 and Tail1) and two other pointers for the Doubly Linked List two (Head2 and Tail2)
Create another list with two pointers (Head3 and Tail3)
Write a function and gets the nodes for the lists from the user
Write a function and sort all elements of the two Doubly Linked Lists, in ascending order or descending order
Create another function and combine the two sorted Doubly Linked Lists in sorted order
Print the combined two Doubly Linked Lists
*/

#include <iostream>
/* Written by Andreas Stiansen, Suleyman Selcuk, Odd-Harald Lillestø Myhren and 
Shaheen Thayalan */
struct Node{
    Node* next;
    Node* prev;
    int value;
};
class linkedList{
public:
    Node* head;
    Node* tail;
    linkedList(){
        head = nullptr;
        tail = nullptr;
    }
    void addNodeAtFront(int value){
        Node* newNode = new Node();
        newNode->value = value;
        if (head == nullptr) {
            tail = newNode;
            head = newNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            return;
        }
        newNode->next = head;
        head = newNode;
    }
    void addNodeAtEnd(int value){
        Node* newNode = new Node();
        newNode->value = value;
        if (tail == nullptr) {
            tail = newNode;
            head = newNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            return;
        }
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    void sortAsc() {
        Node* tmp = head;
        while (tmp != nullptr) {
            Node* tmp2 = tmp->next;
            while (tmp2 != nullptr) {
                if (tmp2->value < tmp->value) {
                    int t = tmp->value;
                    tmp->value = tmp2->value;
                    tmp2->value = t;
                }
                tmp2 = tmp2->next;
            }
            tmp = tmp->next;
        }
    }
    void sortDesc() {
        Node* tmp = head;
        while (tmp != nullptr) {
            Node* tmp2 = tmp->next;
            while (tmp2 != nullptr) {
                if (tmp2->value > tmp->value) {
                    int t = tmp->value;
                    tmp->value = tmp2->value;
                    tmp2->value = t;
                }
                tmp2 = tmp2->next;
            }
            tmp = tmp->next;
        }
    }
    void display() const {
        Node* tmp = head;
        while(tmp != nullptr){
            std::cout<<tmp->value<<std::endl;
            tmp = tmp->next;
        }
    }
};
linkedList combine(linkedList list1, linkedList list2) {
    linkedList newList = list1;
    list1.tail->next = list2.head;
    newList.head = list1.head;
    newList.tail = list2.tail;
    return newList;
}
int main() {
    linkedList list1 = linkedList();
    linkedList list2 = linkedList();
    linkedList combined = linkedList();
    while(true) {
        std::cout
                << "1. List 1: Add to front\n2. List 1: Add to end\n3. List 1: Sort
ascending\n4. List 1: Sort descending\n5. List 2: Add to front\n6. List 2: Add to 
end\n"
                   "7. List 2: Sort ascending\n8. List 2: Sort descending\n9. 
Combine lists\n10. Combined list: Sort ascending\n11. Combined list: Sort 
descending\n12. Combined list: Display"
                   << std::endl;
        int option = 0;
        std::cin >> option;
        switch (option) {
            case 1: {
                int value;
                std::cin >> value;
                list1.addNodeAtFront(value);
                break;
            }
            case 2: {
                int value;
                std::cin >> value;
                list1.addNodeAtEnd(value);
                break;
            }
            case 3: {
                list1.sortAsc();
                break;
            }
            case 4: {
                list1.sortDesc();
                break;
            }
            case 5: {
                int value;
                std::cin >> value;
                list2.addNodeAtFront(value);
                break;
            }
            case 6: {
                int value;
                std::cin >> value;
                list2.addNodeAtEnd(value);
                break;
            }
            case 7: {
                list2.sortAsc();
                break;
            }
            case 8: {
                list2.sortDesc();
                break;
            }
            case 9: {
                combined = combine(list1, list2);
                break;
            }
            case 10: {
                combined.sortAsc();
                break;
            }
            case 11: {
                combined.sortDesc();
                break;
            }
            case 12: {
                combined.display();
                break;
            }
        }
    }
}