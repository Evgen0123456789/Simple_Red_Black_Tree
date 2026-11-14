A custom realization of RB tree heap on C++ and it's application for filtering on C++ and Python.

## About RB-tree
RB-tree is a type of binary heap, that satisfice some simple rules:
1. Every node has a colour -- red or black.
2. The root may be only black.
3. Every new leaf should be read.
4. Red node can't have another red node as decendant.
# Prepairing
1. It isn't canonical, but it simplify a lot: a black node, whose both decendant are red, becomes red while the decendants become black.  This step protect us from case when all three nodes are red.
2. In case of when one of a red node is red you should make a turn, swapping al three nodes and making red only the head.
3. If the root is red -- repaint it.
4. After adding the new node check it's parant.
5. After checking the current check it's head.

## Filtering
To make a tree costs *O(h log h)* data. To delete and add costs *O(log h)*. SO, for array *T* to filt with ordering filter with width *h*:
1. For first elem it will cost *O(h log h)*
2. For every next *O(log h)*
3. Total: *O(h log h) + (T - h) O(log h) = T log h*


