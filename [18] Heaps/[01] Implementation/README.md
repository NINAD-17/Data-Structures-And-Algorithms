# Heap

**What is Heap?**

- Heap is a Complete Binary Tree that comes with a heap order property.

**What is Complete Binary Tree?**

- Complete Binary Tree is a tree where every level is completely filled except the last level.

- Nodes always gets added from the left (node always lean towards the left).

- In CBT, leaf nodes lie in `(n/2 + 1)` to `n`-th index.


**Heap Order Property**

There're two type of Heaps.

1. **Max Heap**: Child values will always be less than current (parent) node.

2. **Min Heap**: Node will always be less than its children.


## Insertion

We do heap implementation in an array form.

```
       60
      /  \
     50  40
    /  \ 
   30  20 

   ______________________________
   | x | 60 | 50 | 40 | 30 | 20 |
   ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾

   For 1 based indexing
      Parent Node = i-th index
      Left Child = 2 * i
      Right Child = (2 * i) + 1

   For 0 based indexgin
      Parent Node = i-th index
      Left Child = (2 * i) + 1
      Right Child = (2 * i) + 2

   To access parent node from child (1 based indexing) = i/2
   To access parent node from child (0 based indexing) = (i - 1)/2

   Leaf Nodes (1 based indexing):
      - Internal Nodes: 1 to (n/2)
      - Leaf Nodes: (n/2 + 1) to n

   Leaf Nodes (0 based indexing):
      - Internal Nodes: 0 to (n/2 - 1)
      - Leaf Nodes: (n/2) to (n - 1)
```

## Heapify

- **Leaf nodes** = (n/2 + 1) to n = (5/2 + 1) to 5 => **3 to 5** index

- Leaf nodes are always CBT as they're single values (no child)

- We won't process leaf nodes as they're already CBT. We'll process 1 to n/2 elements.

- Heapify function takes current node to its correct position below.


## Heapify Time Complexity

### Complexity Analysis: Is it $O(n \log n)$?

$O(n \log n)$ is the classic upper bound that almost everyone assumes at first glance:

- The loop runs $\approx n/2$ times $\rightarrow O(n)$.
- A single heapify takes at most $O(\log n)$ (or $O(h)$) time because it traverses down a single branch from the node to a leaf.
- Therefore, naive estimation: $\frac{n}{2} \times O(\log n) = O(n \log n)$.However, this bound is not tight. The true time complexity of building a heap from an array is strictly $O(n)$.

### Why does it take $O(n)$ instead of $O(n \log n)$?
The key detail is that not every node sits at the top of the tree.

- Most nodes in a Complete Binary Tree sit near the bottom, where their height $h$ is very small.

- A single heapify call does work proportional to the height of that specific node, not the total height of the tree.

   - About 50% of nodes are leaves ($h = 0$) $\rightarrow$ they do 0 swaps (we don't even call heapify on them).
   - About 25% of nodes sit just 1 level above leaves ($h = 1$) $\rightarrow$ they can do at most 1 swap.
   - About 12.5% of nodes sit 2 levels above leaves ($h = 2$) $\rightarrow$ they can do at most 2 swaps.
   - Only 1 node (the root) can travel the full height of $\log n$
   
Mathematically, the total work is:
$$\text{Total Operations} = \sum_{h=0}^{\log n} \left(\frac{n}{2^{h+1}} \times O(h)\right) = \frac{n}{4} \cdot 1 + \frac{n}{8} \cdot 2 + \frac{n}{16} \cdot 3 + \dots$$

Factoring out $n$:$$\text{Total Operations} = n \sum_{h=1}^{\log n} \frac{h}{2^{h+1}} \approx n \cdot O(1) = O(n)$$

Because the infinite geometric-arithmetic series $\sum \frac{h}{2^h}$ converges to a constant ($2$), the total runtime is bounded linearly by $O(n)$.