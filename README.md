# Gator AVL Tree 🔀🌱

---

## 📊 Overview

This project is a full implementation of an **AVL Tree**, a self-balancing Binary Search Tree. The goal was to store and manage student data (name + ID) using efficient operations for **insertion**, **deletion**, and **search**. The tree remains balanced after every modification, guaranteeing logarithmic time complexities for major operations.

---

## ⚖️ Worst Case Complexities

| Operation         | Time Complexity | Description                                                            |
| ----------------- | --------------- | ---------------------------------------------------------------------- |
| `Insert NAME ID`  | O(log n)        | Recursive insertion with AVL rotations to maintain balance             |
| `Remove ID`       | O(log n)        | Balanced deletion using recursive calls                                |
| `Search ID`       | O(log n)        | Standard BST search, tree is balanced                                  |
| `Search NAME`     | O(n)            | Full preorder traversal + linear name filtering                        |
| `printInorder`    | O(n)            | Inorder traversal + output                                             |
| `printPreorder`   | O(n)            | Preorder traversal + output                                            |
| `printPostorder`  | O(n)            | Postorder traversal + output                                           |
| `printLevelCount` | O(log n)        | Counts levels by traversing tree depth                                 |
| `removeInorder N` | O(n)            | Inorder traversal to find Nth node (O(n)) + removal (O(log n)) => O(n) |

---

## 🔧 Key Learnings

* Mastered **recursive tree traversal** and how recursive calls connect
* Improved ability to design and run **unit tests using Catch2**
* Strengthened **debugging strategy** by thinking logically and taking breaks
* Implemented **encapsulation** for sensitive pointers (made private)
* Learned to sketch out the structure and write **pseudocode** before coding
* Understood the value of handling **edge cases** early (e.g., empty tree deletion)

---

