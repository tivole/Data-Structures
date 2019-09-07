# Ti_AVL_Tree
AVL Tree Data Structure

---

## Definition

<b>AVL tree</b> is a <i>binary search tree</i> in which the difference of heights of left and right subtrees of any node is less than or equal to one. The technique of balancing the height of binary trees was developed by <b>A</b>delson, <b>V</b>elskii, and <b>L</b>andi and hence given the short form as AVL tree or Balanced Binary Tree.

<p align="center">
  <img width="70%" height="70%" src="img/formulas/avl_tree.svg">
</p>

---

## Properties

Balance factors can be kept up-to-date by knowing the previous balance factors and the change in height – it is not necessary to know the absolute height. For holding the AVL balance information in the traditional way, two bits per node are sufficient. However, later research showed if the AVL tree is implemented as a rank balanced tree with delta ranks allowed of 1 or 2 – with meaning "when going upward there is an additional increment in height of one or two", this can be done with one bit.

The height ![h](img/formulas/h.gif) of an AVL tree with ![n](img/formulas/n.gif) nodes lies in the interval:

<p align="center">
  <img src="img/formulas/log_inequality.gif">
</p>


with the golden ratio φ := ![one_plus_sqrt5_div_2](img/formulas/one_plus_sqrt5_div_2.gif) ≈ 1.618, c := ![one_div_log2_varphi](img/formulas/one_div_log2_varphi.gif) ≈ 1.44,  and  b := ![cdiv2_log2_5](img/formulas/cdiv2_log2_5.gif) – 2 ≈ –0.328. This is because an AVL tree of height h contains at least ![F_hplus2](img/formulas/F_hplus2.gif) – 1 nodes where {![F_h](img/formulas/F_h.gif)} is the Fibonacci sequence with the seed values ![F_1](img/formulas/F_1.gif) = 1, ![F_2](img/formulas/F_2.gif) = 1.


| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(log n)**  | **O(log n)** |
| Insert        | **O(log n)**  | **O(log n)** |
| Delete        | **O(log n)**  | **O(log n)** |


---

## Usage

```cpp
#include "Ti_AVL_Tree.hpp" // To include AVL Tree structure

Ti_AVL_Tree AVLTree; // To initialize AVL Tree

AVLTree.AddElement(key); // To insert element

AVLTree.DeleteElement(key); // To delete element

AVLTree.Ti_Show(); // To "beautiful" print

AVLTree.ShowUD(); // To Up Down print

AVLTree.ShowLR(); // To Left Right print

AVLTree.ShowDU(); // To Down Up print

```

---

## Insertion examples

Initial state of the tree

![Initial state of the tree](img/insert_screen/insert_1.png)

Inserting <b>5</b>

![After inserting 5](img/insert_screen/insert_2.png)

Inserting <b>14</b>

![After inserting 14](img/insert_screen/insert_3.png)

Inserting <b>7</b>

![After inserting 7](img/insert_screen/insert_4.png)

Inserting <b>12</b>

![After inserting 12](img/insert_screen/insert_5.png)

---

## Removing examples

Initial state of the tree

![Initial state of the tree](img/remove_screen/rem_1.png)

Removing <b>7</b>

![After removing 7](img/remove_screen/rem_2.png)

Removing <b>20</b>

![After removing 20](img/remove_screen/rem_3.png)