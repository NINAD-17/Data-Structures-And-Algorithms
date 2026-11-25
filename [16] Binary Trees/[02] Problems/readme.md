# Binary Trees

## 1. Height of Binary Tree
### i. Recursive Method Complexity
#### Time Complexity
- Each node is processed once: you compute its left height, right height, then return.
- Even though the call stack “returns” back to a node, that’s not a new visit — it’s just unwinding the stack.
- So total work = O(n), not more.

👉 Your doubt: “Aren’t we revisiting Node(3) when we return?”

- No — we don’t recompute Node(3). Its frame was already on the stack.
- Returning to Node(3) just means finishing its pending computation (combine left and right results).
- That’s why we count each node once.

#### Space Complexity
- At most, the stack depth = tree height h.
- In a skew tree, h = n, so worst case space = O(n).
- In a balanced tree, h ≈ log n.

### ii. Iterative Method Complexity
#### Time Complexity
- Each node is enqueued once and dequeued once.
- Work per node = O(1).
- Total = O(n).
- The nested while + for doesn’t make it O(n²) because the inner loop runs exactly once per node overall.

#### Space Complexity
- Queue holds nodes level by level.
- Worst case = maximum width of the tree.
- For a complete binary tree, width ≈ n/2 → O(n).
- For a skew tree, width = 1 → O(1).

## 2. Diameter of Binary Tree
<img src="diameter_of_binary_tree.jpg">

### What is Diameter?
- Diameter = **longest path between any two nodes** in the tree.
- This path may or may not pass through the root.
- Think of it as “the maximum distance between two leaves.”
- Example:
    ```
          1
        /   \
       2     3
      / \   /
     4   5 6
    ```
- Longest path is `4 → 2 → 1 → 3 → 6`.
- Length = 5 nodes (or 4 edges, depending on definition).

### Code Breakdown
- op1 → the diameter of the left subtree.
- op2 → the diameter of the right subtree.
- op3 → the longest path that goes through the current node (left height + right height + 1).

👉 Why all three? Because the longest path might:
1. Lie completely in the left subtree.
2. Lie completely in the right subtree.
3. Pass through the current node (root of this subtree).

You need to check all three possibilities.

#### Why not just op3?

**The formula height(left) + height(right) + 1 (op3) captures the longest path through a given node, but it alone is not sufficient to guarantee the true diameter of the entire tree. The reason op1 and op2 are included is that the longest path may lie entirely inside a subtree and not pass through the current node.**

- The diameter is the maximum of three values — diameter of left subtree, diameter of right subtree, and height(left) + height(right) through the current node. This ensures correctness even when the longest path is deep inside one branch and doesn’t cross the root.

- A common mistake is assuming diameter always passes through the root. In skewed trees, the longest path lies entirely in one subtree. That’s why we must compare subtree diameters (op1/op2) with the path through the node (op3).

- The recursion must track both depth (for op3) and subtree diameters (op1/op2). The “two‑quantity post‑order” pattern is the standard way to solve diameter correctly.

#### Example
```
            1
           / \
          2   3
         / \
        4   5
       /     \
      6       7
     /       /
    11       8
             \
              9
               \
                10

```
- In this example, The longest path is indeed
11 → 6 → 4 → 2 → 5 → 7 → 8 → 9 → 10 → total **9 nodes**. This path lies entirely inside the left subtree, not through the root 1.
- The longest path lies entirely inside the left subtree, not through the root 1.
- If we only use op3 then, 
    - At root 1:
        - height(left) = 6
        - height(right) = 1
        - op3 = 6 + 1 + 1 = 8

    That looks large, but the actual longest path (diameter) is inside the left subtree, not crossing 1. [with op3 we got 8 but actual longest path is of 9 nodes]
    If you compute op3 only at 1, you’ll miss that the left subtree itself has a longer internal path that doesn’t involve 1.
    That’s why we must also compute: op1 and op2.
- At Node(2), it'll get `op1 = 3`, `op2 = 5` and `op3 = 3 + 5 + 1 = 9`.
- `op1` was the diameter from left subtree and `op2` was diameter from right subtree.
- `op3` is diameter by including root. Means diameter forming through root. That's why it joined both left and right subtree and added 1 (for root).
- If we had just reliead on height1 + height2 + 1 on root element only then it won't able to give answer `9` because height of left subtree is just `6`.
⁡
## 3. Balanced Tree
**A binary tree is balanced if, for every node, the difference in height between its left and right subtrees is at most 1.**

Formally: `height(left) - height(right) <= 1`

- **0 difference** → perfectly symmetric at that node.

- **1 difference** → still balanced (slight tilt allowed).

- **\>1 difference** → unbalanced.

Example:

```
            1
           / \
          2   3
         / \
        4   5
```
- Height(left) = 2, Height(right) = 1 → difference = 1 → ✅ balanced.

### Why abs?
`abs()` = absolute value.
We use it because the difference could be negative (e.g., left taller than right).
We only care about the magnitude of the difference, not the sign.

Example:

- Left height = 4, Right height = 2 → difference = 2.

- Without abs, you’d get -2, which doesn’t make sense for comparison.

- With abs, you get 2, which correctly shows imbalance.

### Why diff works with <= 1
`bool diff = abs(height(root->left) - height(root->right)) <= 1;`

- This is a boolean expression, not a number.

- If the difference ≤ 1 → diff = true.

- If the difference > 1 → diff = false.

So don’t confuse it with integers. diff is already true or false.

### Why check left && right && diff
Even if the root’s difference is fine, the tree could still be unbalanced deeper down.
That’s why we combine:

- **left** → is the left subtree balanced?

- **right** → is the right subtree balanced?

- **diff** → is the current node balanced?

Only if all three are true, the whole tree is balanced.

### Example of imbalance in a subtree
```
            1
           / \
          2   3
         /      \
        4        6
       /
      5
```

- At root (1): left height = 3, right height = 2 → difference = 1 → ✅ balanced.

- But at node (2): left height = 2, right height = 0 → difference = 2 → ❌ unbalanced.

So imbalance can occur inside a subtree, not just at the root.


## Time & Space Complexity of Diameter and Balanced Tree Problem

### Time Complexity

- isBalanced() traverses every node in the tree $\rightarrow$ visits $n$ nodes.
- At every single node, it calls height().
- Calling height() on a subtree is not $O(1)$; it walks down the subtree to count depth.

Because of this nested call to height() inside every step of isBalanced():

1. Skewed Tree ($h = n$)
    - At the root, height() visits $n-1$ nodes.- At the 2nd node, height() visits $n-2$ nodes.
    - At the 3rd node, height() visits $n-3$ nodes
    - ....
    - Total Time: $(n-1) + (n-2) + \dots + 1 = \mathbf{O(n^2)}$.
    
2. Balanced Tree ($h \approx \log n$)
- At level 0 (root): height() checks $n$ nodes $\rightarrow n$ work.
- At level 1 (2 nodes): height() checks $n/2 + n/2$ nodes $\rightarrow n$ work.
- At each level, the total work of all height() calls sums to $O(n)$.
- There are $\log n$ levels.
- Total Time: $n \times \log n = \mathbf{O(n \log n)}$.

**Overall Time Complexity**:$$\mathbf{O(n \cdot h)}$$(Worst case $O(n^2)$, Best/Balanced case $O(n \log n)$).

### Space Complexity
Suppose the tree has height $h$, and we are at node $X$ at depth $d$ (where $d \le h$):

1. isBalanced() is on the call stack at depth $d$.
2. Now, from node $X$, height() is called.
3. height() starts adding its own stack frames on top of the existing isBalanced() stack.
4. How deep can height() go from node $X$? Down to the deepest leaf below $X$, which is at most $(h - d)$ levels deeper!
5. So, total depth on the stack at that moment:$$\text{Current Depth of isBalanced} + \text{Depth of height} = d + (h - d) = h$$
6. Once height() finishes, its frames are popped and destroyed, freeing the memory before isBalanced continues.

At no point does the call stack ever exceed the total height of the tree $h$.

Therefore, the Auxiliary Space Complexity is simply:$$\mathbf{O(h)}$$
- Skewed Tree: $\mathbf{O(n)}$
- Balanced Tree: $\mathbf{O(\log n)}$

---

## 4. K-Sum Paths in a Binary Tree (LeetCode 437)

### Core Intuition: Prefix Sum on a Tree
Every root-to-node path in a binary tree behaves just like a **1D subarray**. 

If the running sum from the root down to an ancestor node is `oldSum`, and the running sum down to the current node is `currSum`, then the sum of the downward path segment strictly *between* them is:

$$\text{segmentSum} = \text{currSum} - \text{oldSum}$$

We want $\text{segmentSum} = \text{targetSum}$. Rearranging the equation gives:

$$\text{oldSum} = \text{currSum} - \text{targetSum}$$

Instead of re-scanning all ancestors at every node ($O(N^2)$), we maintain a hash map `prefixCount` storing `{prefix_sum : frequency}` along the **current active root-to-node path**. At any node, we simply ask: *"How many ancestors above me had a running sum equal to `currSum - targetSum`?"*


### Step-by-Step Breakdown

#### 1. Why `prefixCount[0] = 1`?
This handles paths that **start directly at the `root` node** (meaning no prefix is subtracted).

* **Example:** Suppose `root = 8` and `targetSum = 8`.
* At the root: `currSum = 8`.
* `needed = currSum - targetSum = 8 - 8 = 0`.
* Without `prefixCount[0] = 1`, `needed` (`0`) wouldn't exist in the map, and the valid single-node path `[8]` starting from the root would be missed!
* Think of `0` as the "empty path sum" right before entering the root.

#### 2. How `countPaths` Works (4 Phases at Each Node)

1. **Extend Running Sum & Check Valid Paths:**
   * Add `root->data` to `currSum`.
   * Calculate `needed = currSum - targetSum`.
   * If `needed` exists in `prefixCount`, add `prefixCount[needed]` to `totalPaths`. Each occurrence represents a distinct ancestor where a valid `targetSum` path starts and ends at the current node.

2. **Record Current Prefix Sum:**
   * `prefixCount[currSum]++` adds the current node's running sum so its descendants (left and right children) can use it.

3. **Recurse Left & Right:**
   * Explore both subtrees while carrying the updated `currSum` and `prefixCount`.

4. **Backtrack (Crucial Cleanup Step):**
   * `prefixCount[currSum]--` (and `erase` if frequency hits `0`) happens **after** both left and right recursive calls finish.
   * **Why?** Because a valid path must go strictly **downwards** (parent $\to$ child). Once we finish exploring a node's subtree and return back up to its parent, `currSum` is no longer an ancestor of the sibling branch. Leaving it in the map would falsely match nodes across completely separate branches!

#### Dry Run Example

**Tree:** `10 -> 5 -> 3` (left chain), `targetSum = 8`

| Step / Node | `currSum` | `needed` (`currSum - 8`) | Map Lookup (`prefixCount[needed]`) | `totalPaths` Found | Map State After Recording |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **Start** | `0` | — | — | `0` | `{0: 1}` |
| **Visit `10`** | `10` | `2` | `0` (not found) | `0` | `{0: 1, 10: 1}` |
| **Visit `5`** | `15` | `7` | `0` (not found) | `0` | `{0: 1, 10: 1, 15: 1}` |
| **Visit `3`** | `18` | `10` | **`1`** (found `10`!) | **`1`** (path `5 -> 3`) | `{0: 1, 10: 1, 15: 1, 18: 1}` |
| **Backtrack `3`** | — | — | — | — | `{0: 1, 10: 1, 15: 1}` (`18` erased) |

#### Complexity Analysis
* **Time Complexity:** **$O(N)$** — Every node in the tree is visited once, and hash map lookups/updates take $O(1)$ average time.
* **Space Complexity:** **$O(H)$** — The recursion stack and hash map hold at most $H$ entries at once (where $H$ is the height of the tree: $O(\log N)$ balanced, $O(N)$ skewed).

---

## K Sum Paths

### 1. How Did This Approach Even Come About?

Think about how you solve the exact same problem on a **1D array** first (LeetCode 560: *Subarray Sum Equals K*):
Suppose you have an array `[10, -2, 2, 5, 3]` and `targetSum = 8`.

If you keep adding numbers as you walk forward (`currSum`), look at the running sums:

* Before starting: `0`
* After `10`: `10`
* After `-2`: `8`
* After `+2`: `10`  *(Notice `10` appeared a **second time** because `-2 + 2 = 0`!)*
* After `+5`: `15`
* After `+3`: `18`

Now you are standing at `3` (`currSum = 18`). You want a subarray ending at `3` that sums to `8`.
That means you need to chop off a prefix from the beginning whose sum was `18 - 8 = 10`.
Look back at the running sums above: **how many times did `10` appear?**
**Twice!**

1. Chop off `[10]` $\implies$ remaining subarray is `[-2, 2, 5, 3]` (sum = `8`).
2. Chop off `[10, -2, 2]` $\implies$ remaining subarray is `[5, 3]` (sum = `8`).

Because `10` appeared **2 times** earlier in the path, there are **2 distinct starting points** that both end at `3` and sum to `8`! That is why the map stores `{prefixSum : count}` and why we do `totalPaths += prefixCount[needed]`.

A binary tree is just a collection of 1D arrays sharing a root—every time we go down a branch, we add to the map, and every time we climb back up (backtrack), we remove from the map so sibling branches don't mix.


### 2. Full Dry Run on a Tree (With Duplicates & Right Branch)

Let's use **`targetSum = 8`** on this tree:

```text
          10           <-- Root
         /  \
       -2    8         <-- Right child '8' already equals targetSum!
       /
      2                <-- Causes running sum '10' to repeat!
     /
    5
   /
  3                    <-- Ends with TWO valid paths ending here!

```

We start with `prefixCount = {0: 1}` and `totalPaths = 0`.


#### Phase A: Going Down the Long Left Branch (`10 -> -2 -> 2 -> 5 -> 3`)

1. **At Node `10` (Root):**
* `currSum = 0 + 10 = 10`
* `needed = 10 - 8 = 2`. Is `2` in map? **No.** (`+0` paths)
* Record `10`: `prefixCount` is now **`{0: 1, 10: 1}`**


2. **At Node `-2`:**
* `currSum = 10 + (-2) = 8`
* `needed = 8 - 8 = 0`. Is `0` in map? **YES! `prefixCount[0] = 1**`
* *Why?* Because `prefixCount[0] = 1` catches the path starting right from the root: **`[10 -> -2]`** (sum = `8`).
* `totalPaths` becomes **`1`**.


* Record `8`: `prefixCount` is now **`{0: 1, 10: 1, 8: 1}`**


3. **At Node `2`:**
* `currSum = 8 + 2 = 10`
* `needed = 10 - 8 = 2`. Is `2` in map? **No.** (`+0` paths)
* Record `10`: `10` was ALREADY in the map! Its count increments to `2`.
* `prefixCount` is now **`{0: 1, 10: 2, 8: 1}`**


4. **At Node `5`:**
* `currSum = 10 + 5 = 15`
* `needed = 15 - 8 = 7`. Is `7` in map? **No.** (`+0` paths)
* Record `15`: `prefixCount` is now **`{0: 1, 10: 2, 8: 1, 15: 1}`**


5. **At Node `3` (The Magic Moment):**
* `currSum = 15 + 3 = 18`
* `needed = 18 - 8 = 10`. Is `10` in map? **YES! `prefixCount[10] = 2**`
* We add **`2`** to `totalPaths` (`totalPaths` becomes `1 + 2 = 3`).
* Those 2 paths ending at `3` are:
1. **`[-2 -> 2 -> 5 -> 3]`** (everything after the first `10`)
2. **`[5 -> 3]`** (everything after the second `10`)

* Record `18`: `prefixCount` is now **`{0: 1, 10: 2, 8: 1, 15: 1, 18: 1}`**


#### Phase B: Backtracking Up the Left Branch

Node `3` has no children, so the recursion unwinds back up to the root (`10`), cleaning up the map step by step:

* Leaving `3`: remove `18` $\to$ `{0: 1, 10: 2, 8: 1, 15: 1}`
* Leaving `5`: remove `15` $\to$ `{0: 1, 10: 2, 8: 1}`
* Leaving `2`: decrement `10` $\to$ `{0: 1, 10: 1, 8: 1}`
* Leaving `-2`: remove `8` $\to$ **`{0: 1, 10: 1}`**

Look at the map when we arrive back at root `10` before going right: **`{0: 1, 10: 1}`**. Every trace of `-2, 2, 5, 3` is completely gone!


#### Phase C: Going Down the Right Branch (`10 -> 8`)

6. **At Node `8` (Right Child of `10`):**
* `currSum = 10 + 8 = 18` *(Note: `currSum` passed into `10->right` was `10`)*
* `needed = 18 - 8 = 10`. Is `10` in map? **YES! `prefixCount[10] = 1**`
* Notice `prefixCount[10]` is **`1`** (not `2`!) because we backtracked the left branch.
* It catches the single-node path **`[8]`** (everything after root `10`).
* `totalPaths` becomes `3 + 1 =` **`4`**.

* Record `18`, hit `NULL` children, backtrack `18`, and finish.


### Final Summary of All 4 Paths Found

1. `[10 -> -2]` (found at `-2` using `prefixCount[0]`)
2. `[-2 -> 2 -> 5 -> 3]` (found at `3` using first occurrence of `10`)
3. `[5 -> 3]` (found at `3` using second occurrence of `10`)
4. `[8]` (found at right child `8` using root's `10`)

--- 

1. boundary traversal approach
    <img src="boundary traversal.png" >

    here, red part is leaf nodes
    orange is left part and yellow is right part (reverse order)

2. vertical order traversal
    <img src="vertical traversal.jpg">

3. lowest common ancestor
    <img src="lowest common ancestor.png" >
    here, 5 is the lowest common ancestor of node 8 and node 27.

4. k sum paths
    <img src="k sum path.png">

5. build tree from inorder and preorder
    <img src="build_tree_from_inorder_and_preorder.jpg">
