# Ti_AVL_Tree
AVL Tree Data Structure

---

## Definition

<b>AVL tree</b> is a <i>binary search tree</i> in which the difference of heights of left and right subtrees of any node is less than or equal to one. The technique of balancing the height of binary trees was developed by <b>A</b>delson, <b>V</b>elskii, and <b>L</b>andi and hence given the short form as AVL tree or Balanced Binary Tree.

<p align="center">
  <img width="70%" height="70%" src="img/avl_tree.svg">
</p>

| Operation     | Average       | Worst case   |
| ------------- | ------------- | ------------ |
| Space         | **O(n)**      | **O(n)**     |
| Search        | **O(log n)**  | **O(log n)** |
| Insert        | **O(log n)**  | **O(log n)** |
| Delete        | **O(log n)**  | **O(log n)** |




## Properties

Balance factors can be kept up-to-date by knowing the previous balance factors and the change in height – it is not necessary to know the absolute height. For holding the AVL balance information in the traditional way, two bits per node are sufficient. However, later research showed if the AVL tree is implemented as a rank balanced tree with delta ranks allowed of 1 or 2 – with meaning "when going upward there is an additional increment in height of one or two", this can be done with one bit.

The height ![h](img/h.gif) of an AVL tree with ![n](img/n.gif) nodes lies in the interval:

<p align="center">
  <img src="img/log_inequality.gif">
</p>

with the golden ratio φ := (1+√5)⁄2 ≈ 1.618, c := 1⁄ log2 φ ≈ 1.44,  and  b := c⁄2 log2 5 – 2 ≈ –0.328. This is because an AVL tree of height h contains at least ![F_hplus2](img/F_hplus2.gif) – 1 nodes where {![F_h](img/F_h.gif)} is the Fibonacci sequence with the seed values ![F_1](img/F_1.gif) = 1, ![F_2](img/F_2.gif) = 1.
