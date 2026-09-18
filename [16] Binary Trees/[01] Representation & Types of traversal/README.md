# Binary Trees Implementation

## Inorder Preorder Postorder

### Efficiency

- **Recursive**: O(n) time, O(h) space (stack depth = tree height).

- **Iterative**: O(n) time, O(h) space (explicit stack).

- Both are equally efficient in big‑O terms.

- Iterative avoids function call overhead and stack overflow risk for very deep trees.

- Recursive is simpler and more readable.


## Function Call Overhead
- When you call a function (especially recursively), the program must:

- Push a stack frame onto the call stack.

- That frame stores:

    - Return address (where to continue after the function finishes).
    
    - Local variables.
    
    - Parameters passed to the function.

    - Bookkeeping info for the runtime.

This extra work is called **function call overhead**. It’s not just the memory, but also the CPU instructions needed to manage the stack.

### Stack Overflow vs Overhead
- **Overhead** = the small cost of setting up and tearing down each function call.

    - Example: in recursion, every node visited adds a frame, even though the logic is simple.

**Stack Overflow** = when recursion goes too deep (like in a skewed tree with millions of nodes), the call stack exceeds its maximum size and the program crashes.

So:

- Function call overhead ≠ crash.

- Overhead is the extra cost per call.

- Stack overflow is the extreme case when too many calls exceed memory.

### Why Iterative avoids this
- Iterative solutions use an explicit stack data structure (allocated in heap memory).

- Heap is usually larger and more flexible than the call stack.

- So iterative avoids both the overhead of repeated function calls and the risk of stack overflow.

**Function call overhead = the extra CPU + memory work for each recursive call.**

## Time and Space Complexity

### Iterative Inorder `./3_inorder_preorder_postorder_iterative.cpp`

#### Time Complexity:
- Each node is pushed once and popped once.

- Push = O(1), Pop = O(1).

- Printing = O(1).

- Total work = O(n).

👉 Even though it feels like you “visit” nodes twice (once when pushing, once when popping), that’s not O(n²).

It’s still constant work per node, so overall O(n).

#### Space Complexity
- Stack holds nodes along the current path.

- Maximum depth = tree height h.

- So space = O(h).

- Skew tree → O(n).

- Balanced tree → O(log n).

### Why not O(n²)?
- Your confusion is natural:

    - In recursion, you thought “returning” to a node might count as revisiting.

    - In iteration, you thought “push + pop” might count as two visits.

    But in complexity analysis, we count total operations.

    - Each node contributes a fixed number of operations (push, pop, print).

    - That’s O(1) per node.

    - Summed over n nodes → O(n).

So no quadratic blow‑up.

### Time/Space complexity of 1_creation.cpp
#### 1. Creation Recursive
- **Time**: Each node is created once. Each node is visited once. So time = O(n), where n = number of nodes.
- **Space**: This comes from the recursion stack depth, which depends on the height (h) of the tree.
    - Unbalanced tree:  
        - Height = h.
        - Space = O(h).

    - Skewed tree:  
        - Height = n (every node has only one child).
        - Space = O(n).

    - Balanced tree:  
        - Height ≈ log₂(n).
        - Space = O(log n).
        - Example of Log
        ```
                1
              /   \
             2     3
            / \   / \
           4   5 6   7
        ```
        - n = 7, h = 3.
        - log₂(7) ≈ 2.8 → rounded up = 3.
        - So h ≈ log n.
        - Complexity = O(h·n) = O(3·7) = O(21).
        - Asymptotically → O(n log n).

#### 2. Level Order Traversal By Height
- Time: 
    - The loop runs $h$ times (from level = 0 to h - 1).
    - Each iteration calls printCurrentLevel, which takes at most $O(n)$ time.
    - Total time = $h \times O(n) =$ $O(h \cdot n)$.
        - Skewed tree: $h = n \implies O(n \cdot n) = \mathbf{O(n^2)}$
        - Balanced tree: $h \approx \log n \implies \mathbf{O(n \log n)}$ (loose upper bound)
- Space: Why Space is NOT $O(n \cdot h)$
    - Space does NOT multiply across iterations.
    - Time accumulates because past operations take time that is gone forever. But memory (RAM / stack) is reusable.
    - When a function call finishes in recursion, its stack frames are popped and destroyed. The memory is wiped clean and ready to be used by the next call.
    - Here is what happens in the loop:
        ```
        - Iteration 0 (level = 0): Stack grows to depth 1 $\rightarrow$ finishes $\rightarrow$ memory dropped to 0.
        
        - Iteration 1 (level = 1): Stack grows to depth 2 $\rightarrow$ finishes $\rightarrow$ memory dropped to 0.
        
        - Iteration 2 (level = 2): Stack grows to depth 3 $\rightarrow$ finishes $\rightarrow$ memory dropped to 0
        
        ....
        
        - Last Iteration (level = h - 1): Stack grows to depth $h$ $\rightarrow$ finishes $\rightarrow$ memory dropped to 0.
        ```

        - Auxiliary space complexity measures the maximum peak memory used at any single instant in time.   
            - It does not add up the levels: $1 + 2 + 3 + \dots + h$ is wrong for space.
            - It does not multiply: $h \times \text{space}$ is wrong for space.
            - You simply take the maximum peak depth:$$\text{Max Peak Depth} = \max(0, 1, 2, \dots, h - 1) = h - 1 \implies \mathbf{O(h)}$$
        - First height() runs and uses at most $O(h)$ stack frames, then completely finishes. Then the loop runs, and its highest peak is also $O(h)$.
