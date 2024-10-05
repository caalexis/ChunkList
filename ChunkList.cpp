//
// Your code here
//

#include "ChunkList.h"

// Default Constructor
template<class T>
ChunkList<T>::ChunkList() {
    head = nullptr;
    tail = nullptr;
    iterNode = nullptr;
    arrPos = 0;
    listLen = 0;
    numChunks = 0;
}

// Parameterized Constructor
template<class T>
ChunkList<T>::ChunkList(T arr[], int arrLen) {
    // Case: Invalid array len
    if (arrLen <= 0) {
        std::cerr << "Error: Invalid length" << std::endl;
        return;
    }

    // Variables
    head = nullptr;
    tail = nullptr;
    iterNode = nullptr;
    arrPos = 0;
    listLen = 0;
    numChunks = 0;

    // Add to list
    for (int i = 0; i < arrLen; ++i) {
        if (arrLen > ARRAY_SIZE) {
            std::cout << "Debug: Split" << std::endl;
        }
        Append(arr[i]);
    }
}


// Destructor
template<class T>
ChunkList<T>::~ChunkList() {
    // temp pointer
    Node* current = head;

    // iterate through, delete nodes by deleting temp
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;

        // bug check
        std::cout << "Node deleted" << std::endl;
    }

    // RESET MEMEBER VARS
    head = tail = iterNode = nullptr;
    listLen = 0;
    numChunks = 0;
}


// Append function
template<class T>
void ChunkList<T>::Append(T value) {
    // Check to see if full or empty
    if (tail == nullptr || tail->len == ARRAY_SIZE) {
        // initalize node
        Node* newNode = new Node();
        newNode->len = 0;
        newNode->next = nullptr;

        // Case: tail already there
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            // Case : List is empty
            head = newNode;
        }

        // Set tail as new node and update
        tail = newNode;
        numChunks++;
    }
    tail->values[tail->len++] = value; // Add val to current tail of chunk
    listLen++;
}


// Remove function
template<class T>
void ChunkList<T>::Remove(T value) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        // Case 1: Look in current node
        for (int i = 0; i < current->len; ++i) {
            if (current->values[i] == value) {

                // Case 2: If in current node, shift
                for (int j = i; j < current->len - 1; ++j) {
                    current->values[j] = current->values[j + 1];
                }

                current->len--; // decrease len
                listLen--;

                // Case 3: Current node empty
                if (current->len == 0) {
                    // Case 3.1: Node not head
                    if (previous != nullptr) {
                        previous->next = current->next;
                    }
                    // Case 3.2: Node is head
                    else {
                        head = current->next;
                    }

                    // Case 3.3: Node is tail
                    if (current == tail) {
                        tail = previous;
                    }

                    delete current;
                    numChunks--;
                }

                return;
            }
        }

        // Move to the next node
        previous = current;
        current = current->next;
    }
}


// GetLength function
template<class T>
int ChunkList<T>::GetLength() {
    return listLen;
}

// LoadFactor function
template<class T>
double ChunkList<T>::LoadFactor() {
    return listLen / (numChunks * ARRAY_SIZE * 1.0); // evaluated as double, will return floating point
}

// Contains function
template<class T>
bool ChunkList<T>::Contains(T value) {

}

// GetIndex function
template<class T>
T ChunkList<T>::GetIndex(int i) {
    // Check for out of bounds
    if (i < 0 || i >= listLen) {
        throw IndexOutOfBounds();
    }

    Node* current = head;
    int index = i;

    // Look to find node
    while (current != nullptr) {
        // Case 1: In bounds, search
        if (index < current->len) {
            return current->values[index];
        }
        index -= current->len;
        current = current->next;
    }

    // Case 2: No value, error
    throw IndexOutOfBounds();
}

// ResetIterator function
template<class T>
void ChunkList<T>::ResetIterator() {
    // Case 1: Empty list
    if (IsEmpty()) {
        iterNode = nullptr;
        arrPos = 0;
    }
    // Case 2: List not empty
    else {
        iterNode = head;
        arrPos = 0;
    }
}

// GetNextItem function
template<class T>
T ChunkList<T>::GetNextItem() {

}

// IsEmpty function
template<class T>
bool ChunkList<T>::IsEmpty() {
    return listLen == 0; // Returns true if equal to 0
}

