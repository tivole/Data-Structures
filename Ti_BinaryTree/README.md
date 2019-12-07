# Ti_BinaryTree


## Introdution

In computer science, a <b>binary tree</b> is an hierarchical data structure formed of nodes linked together. The first node is called the root, and every node can have up to two child nodes — one left and one right.

<p align="center">
  <img width="70%" height="70%" src="img/binary_tree.jpg">
</p>


### Important Terms:

Following are the important terms with respect to tree.

* <b>Path</b> − Path refers to the sequence of nodes along the edges of a tree.
* <b>Root</b> − The node at the top of the tree is called root. There is only one root per tree and one path from the root node to any node.
* <b>Parent</b> − Any node except the root node has one edge upward to a node called parent.
* <b>Child</b> − The node below a given node connected by its edge downward is called its child node.
* <b>Leaf</b> − The node which does not have any child node is called the leaf node.
* <b>Subtree</b> − Subtree represents the descendants of a node.
* <b>Visiting</b> − Visiting refers to checking the value of a node when control is on the node.
* <b>Traversing</b> − Traversing means passing through nodes in a specific order.
* <b>Levels</b> − Level of a node represents the generation of a node. If the root node is at level 0, then its next child node is at level 1, its grandchild is at level 2, and so on.
* <b>Keys</b> − Key represents a value of a node based on which a search operation is to be carried out for a node.

### Binary Search Tree Representation

Binary Search tree exhibits a special behavior. A node's left child must have a value less than its parent's value and the node's right child must have a value greater than its parent value.

<p align="center">
  <img width="70%" height="70%" src="img/binary_search_tree.jpg">
</p>


## Usage

```cpp
#include "Ti_BinaryTree.hpp" // To include Red Black Tree structure

Ti_Tree<int> Binary_Tree; // To initialize Red Black Tree

Binary_Tree.AddElement(key); // To insert element

Binary_Tree.DeleteElement(key); // To delete element

Binary_Tree.Ti_Show(); // To "beautiful" print

Binary_Tree.ShowUD(); // To Up Down print

Binary_Tree.ShowLR(); // To Left Right print

Binary_Tree.ShowDU(); // To Down Up print
```