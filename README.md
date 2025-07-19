# DSA_PROJECT
Comprehensive Data Structures &amp; Algorithms Implementation Suite in C++



# Data Structures & Scheduling Suite

A comprehensive C++ implementation of fundamental Data Structures, core Algorithms, and classic CPU Scheduling techniques—no external libraries, just the STL (`iostream`, `vector`, `climits`) and clean, commented code.

---

## Table of Contents

1. [Overview](#overview)  
2. [Features](#features)  
   - [Data Structures Implemented](#data-structures-implemented)  
   - [Algorithms Included](#algorithms-included)  
   - [Implemented Scheduling Algorithms](#implemented-scheduling-algorithms)  
3. [Complexity Analysis](#complexity-analysis)  


---

## Overview

This project provides a **pure C++** codebase demonstrating:

- Core data structures with insert/delete/search/display operations  
- Classic sorting and searching algorithms  
- Graph traversals  
- Six major CPU scheduling strategies  
- Memory management via constructors/destructors  
- A single `main()` demo that ties everything together

---

## Features

### Data Structures Implemented

- **Array**: insert, delete, search, display, bubble sort  
- **Linked List**: insert (front/end), delete, search, display, reverse  
- **Stack**: push, pop, peek, isEmpty, display  
- **Queue**: enqueue, dequeue, isEmpty, display  
- **Binary Search Tree**: insert, delete, search, inorder/preorder/postorder traversals  
- **Graph**: add edges, DFS, BFS, display adjacency list  

### Algorithms Included

- **Sorting**: Quick Sort, Merge Sort, Bubble Sort  
- **Searching**: Linear Search, BST Search  
- **Graph Traversal**: Depth‑First Search (DFS), Breadth‑First Search (BFS)  

### Implemented Scheduling Algorithms

- **First Come First Serve (FCFS)** – Non‑preemptive  
- **Shortest Job First (SJF)** – Non‑preemptive  
- **Shortest Remaining Time First (SRTF)** – Preemptive SJF  
- **Priority Scheduling** – Both Non‑preemptive & Preemptive  
- **Round Robin (RR)** – Customizable time quantum  
- **Multilevel Queue** – System, Interactive & Batch queues  

---

## Complexity Analysis

| Operation/Algorithm           | Time Complexity     | Space Complexity                |
|-------------------------------|---------------------|---------------------------------|
| Array insert/delete/search    | O(n)                | O(1)                            |
| Bubble Sort                   | O(n²)               | O(1)                            |
| Quick Sort                    | O(n log n) avg.     | O(log n) recursion stack        |
| Merge Sort                    | O(n log n)          | O(n)                            |
| BST operations                | O(log n) avg.       | O(n)                            |
| Graph BFS/DFS                 | O(V + E)            | O(V)                            |
| FCFS, SJF, Priority Scheduling| O(n log n)          | O(n)                            |
| Round Robin                   | O(n * (n/quantum))  | O(n)                            |

---

