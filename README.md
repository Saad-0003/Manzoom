# Manzoom (منظوم)
### A Literary Management System 

## 📌 Project Overview

**Manzoom (منظوم)** is a console-based **Literary Management System** developed in **C++**, with a strong emphasis on **Data Structures and Algorithms (DSA)**.  
The system digitally preserves, organizes, and enables efficient exploration of classical and modern **Urdu poetry**, addressing the limitations of manual and unstructured literary archiving.

This project demonstrates the practical application of core DSA concepts to a real-world problem while ensuring **scalability**, **performance**, and **data integrity**.

---

## 🎯 Objectives

- Digitally archive Urdu poetry in a structured format  
- Apply appropriate data structures for efficient storage and retrieval  
- Enforce role-based access control  
- Implement persistent storage using file handling  
- Demonstrate real-world usage of DSA concepts in C++

---

## 🧠 Core Data Structures Used

### 1. Binary Search Tree (BST) — Poetry Repository
- Stores poetry records sorted alphabetically by title
- Enables efficient insertion, searching, and traversal
- In-order traversal displays poetry in a reader-friendly sequence

**Supported Operations:**
- Insert poetry
- Search poetry by title or keyword
- Display poetry in sorted order

---

### 2. Hash Maps (`std::unordered_map`) — User Authentication
- Manages credentials for readers and poets
- Provides constant-time average lookup
- Ensures fast and secure authentication

---

### 3. Singly Linked List — Search History
- Maintains dynamic search history for users
- New searches are inserted at the head
- Lightweight and efficient for frequent insertions

---

### 4. File Handling — Persistent Storage
- Poetry content and user credentials stored in text files
- Custom delimiters (e.g., `<<END_CONTENT>>`) safely handle multi-line Urdu verses
- Reliable reconstruction of data at program startup

---

## 👥 User Roles and Permissions

| Role | Capabilities | Access Level |
|----|----|----|
| **Reader** | View poetry, search content, view search history | Read-only |
| **Poet** | Submit and manage poetry | Write access |
| **Administrator** | Review, approve, or remove poetry | Full control |

> Administrative access is hidden from the main interface to prevent unauthorized usage.

---

## ⚙️ Technical Specifications

- **Language:** C++  
- **Interface:** Console-based  
- **Persistence:** File I/O  
- **Parsing:** `stringstream` for robust text handling  
- **Platform:** Windows (console color support utilized)

---

## ⏱️ Time Complexity Overview

| Operation | Data Structure | Average Case |
|----|----|----|
| Poetry Search | Binary Search Tree | O(log n) |
| User Authentication | Hash Map | O(1) |
| Search History Insertion | Linked List | O(1) |
| File Read / Write | File I/O | O(n) |

---

## 🔐 Security Considerations

- Role-based credential separation
- Hidden administrative logic
- Segregated storage files
- Prevention of privilege escalation

---

## 🖥️ User Interface Design

Although console-based, Manzoom improves usability by:
- Color-coded output for clarity
- Clear distinction between prompts, errors, and system messages
- Menu-driven navigation structure

---

## 🚀 Future Enhancements

- Self-balancing BST (AVL or Red-Black Tree)
- Database-backed persistence
- Advanced search filters (genre, mood, poet metadata)
- Graphical or web-based interface

---

## 📚 Academic Relevance

This project serves as:
- A practical demonstration of Data Structures and Algorithms  
- An example of system design guided by data structure selection  
- A scalable foundation for further development  

---

## 👨‍💻 Contributors

- **Saad Ali** (245163)  
- **Muhammad Ali** (245165)  
- **Abdullah Gulfraz** (245149)

---

## 📄 License

This project is intended for **academic use only**.
