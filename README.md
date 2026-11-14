**A custom implementation of an RB-tree heap in C++ and its application for filtering in C++ and Python**

### About RB-tree
An RB-tree (Red-Black tree) is a balanced binary tree that satisfies the following simple rules:

1. Every node has a colour — red or black.  
2. The root must be black.  
3. Every newly inserted leaf is red.  
4. A red node cannot have a red child (no two consecutive red nodes).

### Insertion / Balancing procedure
The following simplified rules are used (they are not fully canonical, but they greatly simplify the implementation):

1. If a black node has two red children, recolour the black node red and its two children black. This prevents the situation where three nodes in a row would become red.  
2. If a red node has a red child, perform a rotation: rearrange the three nodes so that only the new root of the subtree remains red.  
3. If the overall root becomes red, recolour it black.  
4. After inserting a new node, check its parent.  
5. After fixing the current node, continue checking upwards toward the root.

### Filtering application
Building the tree costs \(O(h \log h)\).  
Each insertion and deletion costs \(O(\log h)\).

Therefore, for an array of size \(T\) filtered with an ordering filter of width \(h\):

1. The first window costs \(O(h \log h)\).  
2. Every subsequent window costs \(O(\log h)\).  
3. Total complexity:  
   \[
   O(h \log h) + (T - h) \cdot O(\log h) = O(T \log h)
   \]
