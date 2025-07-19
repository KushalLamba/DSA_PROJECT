#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include<string>
using namespace std;

// ==================== PROCESS STRUCTURE ====================
struct Process {
    int pid;              // Process ID
    int arrivalTime;      // Arrival Time
    int burstTime;        // Burst Time (Original)
    int priority;         // Priority (Lower number = Higher priority)
    int remainingTime;    // Remaining Time for preemptive algorithms
    int completionTime;   // Completion Time
    int turnaroundTime;   // Turnaround Time
    int waitingTime;      // Waiting Time
    int responseTime;     // Response Time
    bool started;         // Has process started execution?
    
    Process(int id, int arrival, int burst, int prio = 0) {
        pid = id;
        arrivalTime = arrival;
        burstTime = burst;
        priority = prio;
        remainingTime = burst;
        completionTime = 0;
        turnaroundTime = 0;
        waitingTime = 0;
        responseTime = -1;
        started = false;
    }
};

// ==================== GANTT CHART ENTRY ====================
struct GanttEntry {
    int pid;
    int startTime;
    int endTime;
    
    GanttEntry(int id, int start, int end) : pid(id), startTime(start), endTime(end) {}
};

// ==================== QUEUE IMPLEMENTATION ====================
template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        Node* temp = front;
        T data = front->data;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        size--;
        return data;
    }
    
    T peek() {
        if (isEmpty()) return T();
        return front->data;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    int getSize() {
        return size;
    }
};

// ==================== PRIORITY QUEUE (MIN HEAP) ====================
template<typename T, typename Compare>
class PriorityQueue {
private:
    vector<T> heap;
    Compare comp;
    
    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (comp(heap[index], heap[parent])) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }
    
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        
        if (left < heap.size() && comp(heap[left], heap[smallest])) {
            smallest = left;
        }
        if (right < heap.size() && comp(heap[right], heap[smallest])) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    PriorityQueue() {}
    
    void push(T data) {
        heap.push_back(data);
        heapifyUp(heap.size() - 1);
    }
    
    T pop() {
        if (isEmpty()) return T();
        T top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return top;
    }
    
    T top() {
        if (isEmpty()) return T();
        return heap[0];
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
};

// ==================== CPU SCHEDULER CLASS ====================
class CPUScheduler {
private:
    vector<Process> originalProcesses;
    vector<GanttEntry> ganttChart;
    
    void calculateMetrics(vector<Process>& processes) {
        for (auto& p : processes) {
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
        }
    }
    
    void displayResults(const vector<Process>& processes, const string& algorithmName) {
        cout << "\n=== " << algorithmName << " SCHEDULING RESULTS ===" << endl;
        
        // Display process details
        cout << "\nProcess Details:" << endl;
        cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse" << endl;
        cout << "--------------------------------------------------------------------" << endl;
        
        double totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
        
        for (const auto& p : processes) {
            cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
                 << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t"
                 << p.waitingTime << "\t" << p.responseTime << endl;
            
            totalTurnaround += p.turnaroundTime;
            totalWaiting += p.waitingTime;
            totalResponse += (p.responseTime != -1) ? p.responseTime : 0;
        }
        
        // Display averages
        int n = processes.size();
        cout << "\nAverage Turnaround Time: " << totalTurnaround / n << endl;
        cout << "Average Waiting Time: " << totalWaiting / n << endl;
        cout << "Average Response Time: " << totalResponse / n << endl;
        
        // Display Gantt Chart
        cout << "\nGantt Chart:" << endl;
        cout << "|";
        for (const auto& entry : ganttChart) {
            cout << " P" << entry.pid << " |";
        }
        cout << endl;
        
        cout << "0";
        for (const auto& entry : ganttChart) {
            cout << "    " << entry.endTime;
        }
        cout << endl;
    }

public:
    CPUScheduler(const vector<Process>& processes) : originalProcesses(processes) {}
    
    // ==================== FIRST COME FIRST SERVE (FCFS) ====================
    void fcfs() {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        // Sort by arrival time
        sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });
        
        int currentTime = 0;
        
        for (auto& process : processes) {
            if (currentTime < process.arrivalTime) {
                currentTime = process.arrivalTime;
            }
            
            process.responseTime = currentTime - process.arrivalTime;
            process.completionTime = currentTime + process.burstTime;
            currentTime = process.completionTime;
            
            ganttChart.push_back(GanttEntry(process.pid, currentTime - process.burstTime, currentTime));
        }
        
        calculateMetrics(processes);
        displayResults(processes, "FIRST COME FIRST SERVE (FCFS)");
    }
    
    // ==================== SHORTEST JOB FIRST (NON-PREEMPTIVE) ====================
    void sjfNonPreemptive() {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();
        vector<bool> isCompleted(n, false);
        
        while (completed < n) {
            int shortestJob = -1;
            int minBurst = INT_MAX;
            
            // Find shortest job among arrived processes
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                    if (processes[i].burstTime < minBurst) {
                        minBurst = processes[i].burstTime;
                        shortestJob = i;
                    }
                }
            }
            
            if (shortestJob == -1) {
                currentTime++;
                continue;
            }
            
            Process& p = processes[shortestJob];
            p.responseTime = currentTime - p.arrivalTime;
            p.completionTime = currentTime + p.burstTime;
            currentTime = p.completionTime;
            isCompleted[shortestJob] = true;
            completed++;
            
            ganttChart.push_back(GanttEntry(p.pid, currentTime - p.burstTime, currentTime));
        }
        
        calculateMetrics(processes);
        displayResults(processes, "SHORTEST JOB FIRST (NON-PREEMPTIVE)");
    }
    
    // ==================== SHORTEST REMAINING TIME FIRST (PREEMPTIVE SJF) ====================
    void srtf() {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();
        int lastExecuted = -1;
        
        while (completed < n) {
            int shortestRemaining = -1;
            int minRemaining = INT_MAX;
            
            // Find process with shortest remaining time
            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    if (processes[i].remainingTime < minRemaining) {
                        minRemaining = processes[i].remainingTime;
                        shortestRemaining = i;
                    }
                }
            }
            
            if (shortestRemaining == -1) {
                currentTime++;
                continue;
            }
            
            Process& p = processes[shortestRemaining];
            
            // Set response time if process starts for first time
            if (!p.started) {
                p.responseTime = currentTime - p.arrivalTime;
                p.started = true;
            }
            
            // Add to Gantt chart if different process or first entry
            if (lastExecuted != shortestRemaining) {
                if (!ganttChart.empty() && ganttChart.back().pid != -1) {
                    ganttChart.back().endTime = currentTime;
                }
                ganttChart.push_back(GanttEntry(p.pid, currentTime, currentTime + 1));
            }
            
            p.remainingTime--;
            currentTime++;
            lastExecuted = shortestRemaining;
            
            if (p.remainingTime == 0) {
                p.completionTime = currentTime;
                completed++;
                if (!ganttChart.empty()) {
                    ganttChart.back().endTime = currentTime;
                }
            }
        }
        
        calculateMetrics(processes);
        displayResults(processes, "SHORTEST REMAINING TIME FIRST (SRTF)");
    }
    
    // ==================== PRIORITY SCHEDULING (NON-PREEMPTIVE) ====================
    void priorityNonPreemptive() {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();
        vector<bool> isCompleted(n, false);
        
        while (completed < n) {
            int highestPriority = -1;
            int minPriority = INT_MAX;
            
            // Find highest priority process (lower number = higher priority)
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                    if (processes[i].priority < minPriority) {
                        minPriority = processes[i].priority;
                        highestPriority = i;
                    }
                }
            }
            
            if (highestPriority == -1) {
                currentTime++;
                continue;
            }
            
            Process& p = processes[highestPriority];
            p.responseTime = currentTime - p.arrivalTime;
            p.completionTime = currentTime + p.burstTime;
            currentTime = p.completionTime;
            isCompleted[highestPriority] = true;
            completed++;
            
            ganttChart.push_back(GanttEntry(p.pid, currentTime - p.burstTime, currentTime));
        }
        
        calculateMetrics(processes);
        displayResults(processes, "PRIORITY SCHEDULING (NON-PREEMPTIVE)");
    }
    
    // ==================== PRIORITY SCHEDULING (PREEMPTIVE) ====================
    void priorityPreemptive() {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();
        int lastExecuted = -1;
        
        while (completed < n) {
            int highestPriority = -1;
            int minPriority = INT_MAX;
            
            // Find highest priority process
            for (int i = 0; i < n; i++) {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    if (processes[i].priority < minPriority) {
                        minPriority = processes[i].priority;
                        highestPriority = i;
                    }
                }
            }
            
            if (highestPriority == -1) {
                currentTime++;
                continue;
            }
            
            Process& p = processes[highestPriority];
            
            if (!p.started) {
                p.responseTime = currentTime - p.arrivalTime;
                p.started = true;
            }
            
            if (lastExecuted != highestPriority) {
                if (!ganttChart.empty() && ganttChart.back().pid != -1) {
                    ganttChart.back().endTime = currentTime;
                }
                ganttChart.push_back(GanttEntry(p.pid, currentTime, currentTime + 1));
            }
            
            p.remainingTime--;
            currentTime++;
            lastExecuted = highestPriority;
            
            if (p.remainingTime == 0) {
                p.completionTime = currentTime;
                completed++;
                if (!ganttChart.empty()) {
                    ganttChart.back().endTime = currentTime;
                }
            }
        }
        
        calculateMetrics(processes);
        displayResults(processes, "PRIORITY SCHEDULING (PREEMPTIVE)");
    }
    
    // ==================== ROUND ROBIN ====================
    void roundRobin(int timeQuantum) {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        Queue<int> readyQueue;
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();
        vector<bool> inQueue(n, false);
        
        // Add initial processes to ready queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime) {
                readyQueue.enqueue(i);
                inQueue[i] = true;
            }
        }
        
        while (completed < n || !readyQueue.isEmpty()) {
            if (readyQueue.isEmpty()) {
                currentTime++;
                // Add newly arrived processes
                for (int i = 0; i < n; i++) {
                    if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                        readyQueue.enqueue(i);
                        inQueue[i] = true;
                    }
                }
                continue;
            }
            
            int current = readyQueue.dequeue();
            inQueue[current] = false;
            Process& p = processes[current];
            
            if (!p.started) {
                p.responseTime = currentTime - p.arrivalTime;
                p.started = true;
            }
            
            int executeTime = min(timeQuantum, p.remainingTime);
            ganttChart.push_back(GanttEntry(p.pid, currentTime, currentTime + executeTime));
            
            p.remainingTime -= executeTime;
            currentTime += executeTime;
            
            // Add newly arrived processes to queue
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && 
                    processes[i].remainingTime > 0 && i != current) {
                    readyQueue.enqueue(i);
                    inQueue[i] = true;
                }
            }
            
            if (p.remainingTime == 0) {
                p.completionTime = currentTime;
                completed++;
            } else {
                readyQueue.enqueue(current);
                inQueue[current] = true;
            }
        }
        
        calculateMetrics(processes);
        displayResults(processes, "ROUND ROBIN (Time Quantum: " + to_string(timeQuantum) + ")");
    }
    
    // ==================== MULTILEVEL QUEUE SCHEDULING ====================
    void multilevelQueue() {
        vector<Process> processes = originalProcesses;
        ganttChart.clear();
        
        // Separate processes into different queues based on priority
        Queue<int> systemQueue;      // Priority 0-1
        Queue<int> interactiveQueue; // Priority 2-3
        Queue<int> batchQueue;       // Priority 4-5
        
        int currentTime = 0;
        int completed = 0;
        int n = processes.size();
        vector<bool> inQueue(n, false);
        
        auto addToQueues = [&]() {
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    if (processes[i].priority <= 1) {
                        systemQueue.enqueue(i);
                    } else if (processes[i].priority <= 3) {
                        interactiveQueue.enqueue(i);
                    } else {
                        batchQueue.enqueue(i);
                    }
                    inQueue[i] = true;
                }
            }
        };
        
        addToQueues();
        
        while (completed < n) {
            bool executed = false;
            
            // System queue (highest priority) - FCFS
            if (!systemQueue.isEmpty()) {
                int current = systemQueue.dequeue();
                inQueue[current] = false;
                Process& p = processes[current];
                
                if (!p.started) {
                    p.responseTime = currentTime - p.arrivalTime;
                    p.started = true;
                }
                
                ganttChart.push_back(GanttEntry(p.pid, currentTime, currentTime + p.remainingTime));
                currentTime += p.remainingTime;
                p.remainingTime = 0;
                p.completionTime = currentTime;
                completed++;
                executed = true;
            }
            // Interactive queue - Round Robin with quantum 2
            else if (!interactiveQueue.isEmpty()) {
                int current = interactiveQueue.dequeue();
                inQueue[current] = false;
                Process& p = processes[current];
                
                if (!p.started) {
                    p.responseTime = currentTime - p.arrivalTime;
                    p.started = true;
                }
                
                int executeTime = min(2, p.remainingTime);
                ganttChart.push_back(GanttEntry(p.pid, currentTime, currentTime + executeTime));
                p.remainingTime -= executeTime;
                currentTime += executeTime;
                
                if (p.remainingTime == 0) {
                    p.completionTime = currentTime;
                    completed++;
                } else {
                    interactiveQueue.enqueue(current);
                    inQueue[current] = true;
                }
                executed = true;
            }
            // Batch queue - FCFS
            else if (!batchQueue.isEmpty()) {
                int current = batchQueue.dequeue();
                inQueue[current] = false;
                Process& p = processes[current];
                
                if (!p.started) {
                    p.responseTime = currentTime - p.arrivalTime;
                    p.started = true;
                }
                
                ganttChart.push_back(GanttEntry(p.pid, currentTime, currentTime + p.remainingTime));
                currentTime += p.remainingTime;
                p.remainingTime = 0;
                p.completionTime = currentTime;
                completed++;
                executed = true;
            }
            
            if (!executed) {
                currentTime++;
            }
            
            addToQueues();
        }
        
        calculateMetrics(processes);
        displayResults(processes, "MULTILEVEL QUEUE SCHEDULING");
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    cout << "=== CPU SCHEDULING ALGORITHMS PROJECT ===" << endl;
    
    // Sample processes: {PID, Arrival Time, Burst Time, Priority}
    vector<Process> processes = {
        Process(1, 0, 8, 2),
        Process(2, 1, 4, 1),
        Process(3, 2, 9, 3),
        Process(4, 3, 5, 0),
        Process(5, 4, 2, 4)
    };
    
    cout << "\nInput Processes:" << endl;
    cout << "PID\tArrival\tBurst\tPriority" << endl;
    cout << "--------------------------------" << endl;
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" << p.priority << endl;
    }
    
    CPUScheduler scheduler(processes);
    
    // Run all scheduling algorithms
    scheduler.fcfs();
    
    scheduler.sjfNonPreemptive();
    
    scheduler.srtf();
    
    scheduler.priorityNonPreemptive();
    
    scheduler.priorityPreemptive();
    
    scheduler.roundRobin(3);
    
    scheduler.multilevelQueue();
    
    cout << "\n=== ALL SCHEDULING ALGORITHMS COMPLETED ===" << endl;
    
    return 0;
}
