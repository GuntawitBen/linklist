#include "node.h"

class LL {
  NodePtr hol; // head of linked list
  NodePtr tail;
  int size;

public:
  LL();
  int deletes(int value);
  int isEmpty();
  void insert(int value);
  void printForward();
  void printReverse();
  ~LL();
};

LL::LL() {
  this->hol = NULL;
  this->tail = NULL;
  size = 0;
}

LL::~LL() {
  cout << "deleting all nodes" << endl;
  NodePtr t = hol;
  int i;
  for (i = 0; i < size; i++) {
    hol = hol->get_next();
    delete t;
    t = hol;
  }
}

void LL::insert(int value) {
  NodePtr newNode = new Node(value); // Create a new node with the given value

  if (hol == nullptr) {
    // If the list is empty, make the new node the head and tail
    hol = newNode;
    tail = newNode;
  } else if (value <= hol->get_data()) {
    // If the value is smaller or equal to the head value, insert at the beginning
    newNode->set_next(hol);
    hol->set_prev(newNode);
    hol = newNode;
  } else if (value >= tail->get_data()) {
    // If the value is larger or equal to the tail value, insert at the end
    tail->set_next(newNode);
    newNode->set_prev(tail);
    tail = newNode;
  } else {
    // Find the correct position to insert the new node in the sorted order
    NodePtr current = hol->get_next();
    while (current != nullptr && current->get_data() < value) {
      current = current->get_next();
    }

    // Insert the new node before the current node
    NodePtr previous = current->get_prev();
    previous->set_next(newNode);
    newNode->set_prev(previous);
    newNode->set_next(current);
    current->set_prev(newNode);
  }

  size++;
}


// delete a list element
int LL::deletes(int value) {
    if (isEmpty()) {
        cout << "List is empty." << endl;
        return 0;
    }

    int count = 0;
    NodePtr current = hol;
    NodePtr previous = nullptr;

    // Traverse the list to find and delete nodes with the given value
    while (current != nullptr) {
        if (current->get_data() == value) {
            // Update the next pointer of the previous node
            if (previous != nullptr) {
                previous->set_next(current->get_next());
            } else {
                // If the node to be deleted is the head node
                hol = current->get_next();
            }

            // Update the previous pointer of the next node (for doubly linked list)
            if (current->get_next() != nullptr) {
                current->get_next()->set_prev(previous);
            } else {
                // If the node to be deleted is the tail node
                tail = previous;
            }

            NodePtr temp = current;
            current = current->get_next();
            delete temp;
            size--;
            count++;
        } else {
            previous = current;
            current = current->get_next();
        }
    }

    return count;
}



// return 1 if the list is empty, 0 otherwise
int LL::isEmpty() { return hol == NULL; } // end function isEmpty

// print the list
void LL::printForward() {
  NodePtr current = hol;
  if (isEmpty()) {
    std::cout << "List is empty." << std::endl;
  } else {
    std::cout << "List (forward): ";
    while (current != nullptr) {
      current->print();
      std::cout << "  ->";
      current = current->get_next();
    }
    std::cout << "NULL" << std::endl;
  }
}

void LL::printReverse() {
  NodePtr current = tail;
  if (isEmpty()) {
    std::cout << "List is empty." << std::endl;
  } else {
    std::cout << "List (reverse): ";
    while (current != nullptr) {
      current->print();
      std::cout << "  ->";
      current = current->get_prev(); // Traverse in reverse direction using the get_prev() function
    }
    std::cout << "NULL" << std::endl;
  }
}

