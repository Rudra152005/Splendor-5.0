// # Answer
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* npx; // XOR of next and previous node
    
    Node(int val) : data(val), npx(NULL) {}
};

// Utility function to XOR two pointers
Node* XOR(Node* a, Node* b) {
    return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Function to insert a new node at the beginning of the XOR linked list
Node* insert(Node* head, int data) {
    Node* newNode = new Node(data);           // Create new node with given data
    newNode->npx = XOR(NULL, head);           // XOR NULL and head since it's the first node
    
    // If list is not empty, update the npx of current head node
    if (head != NULL) {
        head->npx = XOR(newNode, XOR(NULL, head->npx)); // Update current head node
    }
    
    // Return the new head, which is the newly inserted node
    return newNode;
}

// Function to return the list as a vector (forward traversal)
vector<int> getList(Node* head) {
    vector<int> result;
    Node* curr = head;
    Node* prev = NULL;
    Node* next;

    // Traverse the list until the end
    while (curr != NULL) {
        result.push_back(curr->data); // Add the data to the result
        
        // Calculate the next node using XOR of prev and npx
        next = XOR(prev, curr->npx);
        
        // Move pointers one step forward
        prev = curr;
        curr = next;
    }
    
    return result;
}

// Driver code to demonstrate the functionality
int main() {
    Node* head = NULL; // Initial empty XOR linked list

    // Insert data into the XOR linked list
    head = insert(head, 9);
    head = insert(head, 5);
    head = insert(head, 4);
    head = insert(head, 7);
    head = insert(head, 3);
    head = insert(head, 10);

    // Get the list in forward traversal
    vector<int> forwardList = getList(head);
    
    // Print forward traversal
    for (int i = 0; i < forwardList.size(); i++) {
        cout << forwardList[i] << " ";
    }
    cout << endl;

    // Reverse traversal by passing the head of the list in reverse order
    reverse(forwardList.begin(), forwardList.end());

    // Print reverse traversal
    for (int i = 0; i < forwardList.size(); i++) {
        cout << forwardList[i] << " ";
    }
    cout << endl;

    return 0;
}
