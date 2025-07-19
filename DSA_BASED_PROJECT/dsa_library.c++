#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ==================== ARRAY OPERATIONS ====================
class Array {
private:
    int* arr;
    int size;
    int capacity;

public:
    Array(int cap) : capacity(cap), size(0) {
        arr = new int[capacity];
    }

    ~Array() {
        delete[] arr;
    }

    void insert(int element) {
        if (size < capacity) {
            arr[size++] = element;
        } else {
            cout << "Array is full!" << endl;
        }
    }

    void deleteElement(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
    }

    int search(int element) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == element) return i;
        }
        return -1;
    }

    void display() {
        cout << "Array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void bubbleSort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// ==================== LINKED LIST ====================
struct ListNode {
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(int data) {
        ListNode* newNode = new ListNode(data);
        newNode->next = head;
        head = newNode;
    }

    void insertEnd(int data) {
        ListNode* newNode = new ListNode(data);
        if (!head) {
            head = newNode;
            return;
        }
        ListNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteNode(int data) {
        if (!head) return;
        
        if (head->data == data) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        ListNode* temp = head;
        while (temp->next && temp->next->data != data) {
            temp = temp->next;
        }
        
        if (temp->next) {
            ListNode* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
    }

    bool search(int data) {
        ListNode* temp = head;
        while (temp) {
            if (temp->data == data) return true;
            temp = temp->next;
        }
        return false;
    }

    void display() {
        cout << "Linked List: ";
        ListNode* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void reverse() {
        ListNode* prev = nullptr;
        ListNode* current = head;
        ListNode* next = nullptr;
        
        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }
};

// ==================== STACK ====================
class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    Stack(int cap) : capacity(cap), top(-1) {
        arr = new int[capacity];
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int element) {
        if (top < capacity - 1) {
            arr[++top] = element;
        } else {
            cout << "Stack Overflow!" << endl;
        }
    }

    int pop() {
        if (top >= 0) {
            return arr[top--];
        }
        cout << "Stack Underflow!" << endl;
        return -1;
    }

    int peek() {
        if (top >= 0) {
            return arr[top];
        }
        cout << "Stack is empty!" << endl;
        return -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void display() {
        cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// ==================== QUEUE ====================
class Queue {
private:
    int* arr;
    int front, rear;
    int capacity;

public:
    Queue(int cap) : capacity(cap), front(0), rear(-1) {
        arr = new int[capacity];
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int element) {
        if (rear < capacity - 1) {
            arr[++rear] = element;
        } else {
            cout << "Queue Overflow!" << endl;
        }
    }

    int dequeue() {
        if (front <= rear) {
            int element = arr[front];
            for (int i = 0; i < rear; i++) {
                arr[i] = arr[i + 1];
            }
            rear--;
            return element;
        }
        cout << "Queue Underflow!" << endl;
        return -1;
    }

    bool isEmpty() {
        return front > rear;
    }

    void display() {
        cout << "Queue: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// ==================== BINARY SEARCH TREE ====================
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int data) {
        if (!node) return new TreeNode(data);
        
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode* deleteNode(TreeNode* node, int data) {
        if (!node) return node;
        
        if (data < node->data) {
            node->left = deleteNode(node->left, data);
        } else if (data > node->data) {
            node->right = deleteNode(node->right, data);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(TreeNode* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(TreeNode* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    bool search(TreeNode* node, int data) {
        if (!node) return false;
        if (node->data == data) return true;
        if (data < node->data) return search(node->left, data);
        return search(node->right, data);
    }

public:
    BST() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    void remove(int data) {
        root = deleteNode(root, data);
    }

    bool find(int data) {
        return search(root, data);
    }

    void inorderTraversal() {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }

    void preorderTraversal() {
        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }

    void postorderTraversal() {
        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }
};

// ==================== GRAPH (Adjacency List) ====================
class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;

    void dfsUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited);
            }
        }
    }

public:
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // For undirected graph
    }

    void dfs(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS traversal: ";
        dfsUtil(start, visited);
        cout << endl;
    }

    void bfs(int start) {
        vector<bool> visited(vertices, false);
        vector<int> queue;
        
        visited[start] = true;
        queue.push_back(start);
        
        cout << "BFS traversal: ";
        
        while (!queue.empty()) {
            int current = queue[0];
            cout << current << " ";
            queue.erase(queue.begin());
            
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push_back(neighbor);
                }
            }
        }
        cout << endl;
    }

    void displayGraph() {
        cout << "\nAdjacency List:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

// ==================== SORTING ALGORITHMS ====================
class Sorting {
public:
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void merge(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<int> leftArr(n1), rightArr(n2);
        
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
};

// ==================== MAIN FUNCTION - DEMO ====================
int main() {
    cout << "=== COMPREHENSIVE DSA LIBRARY DEMO ===" << endl;

    // Array Demo
    cout << "\n--- Array Operations ---" << endl;
    Array arr(5);
    arr.insert(64);
    arr.insert(34);
    arr.insert(25);
    arr.insert(12);
    arr.insert(22);
    arr.display();
    cout << "Element 25 found at index: " << arr.search(25) << endl;
    arr.bubbleSort();
    cout << "After sorting: ";
    arr.display();

    // Linked List Demo
    cout << "\n--- Linked List Operations ---" << endl;
    LinkedList ll;
    ll.insertEnd(1);
    ll.insertEnd(2);
    ll.insertEnd(3);
    ll.insertFront(0);
    ll.display();
    ll.reverse();
    cout << "After reversing: ";
    ll.display();

    // Stack Demo
    cout << "\n--- Stack Operations ---" << endl;
    Stack stack(5);
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();
    cout << "Popped: " << stack.pop() << endl;
    stack.display();

    // Queue Demo
    cout << "\n--- Queue Operations ---" << endl;
    Queue queue(5);
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display();
    cout << "Dequeued: " << queue.dequeue() << endl;
    queue.display();

    // BST Demo
    cout << "\n--- Binary Search Tree Operations ---" << endl;
    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    bst.inorderTraversal();
    bst.preorderTraversal();
    bst.postorderTraversal();
    cout << "Search 40: " << (bst.find(40) ? "Found" : "Not Found") << endl;

    // Graph Demo
    cout << "\n--- Graph Operations ---" << endl;
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.displayGraph();
    graph.dfs(0);
    graph.bfs(0);

    // Sorting Demo
    cout << "\n--- Sorting Algorithms ---" << endl;
    vector<int> data1 = {64, 34, 25, 12, 22, 11, 90};
    vector<int> data2 = data1;
    
    cout << "Original array: ";
    for (int x : data1) cout << x << " ";
    cout << endl;
    
    Sorting::quickSort(data1, 0, data1.size() - 1);
    cout << "Quick Sort result: ";
    for (int x : data1) cout << x << " ";
    cout << endl;
    
    Sorting::mergeSort(data2, 0, data2.size() - 1);
    cout << "Merge Sort result: ";
    for (int x : data2) cout << x << " ";
    cout << endl;

    cout << "\n=== DSA LIBRARY DEMO COMPLETE ===" << endl;
    return 0;
}
