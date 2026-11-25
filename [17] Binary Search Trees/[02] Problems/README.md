# Binary Search Tree Problems

## Predecessor and Successor

Your rule ("go left once, then all the way right") works **ONLY when the target node actually has a left child**. What if the target node is a **leaf** (has `NULL` left and right children), or `key` isn't even present in the BST?

### The Two Cases for Predecessor & Successor

In a BST, the **Inorder Predecessor** is simply the **largest value strictly smaller than `key**`, and the **Inorder Successor** is the **smallest value strictly larger than `key**`.

Look at your `main()` tree:

```text
          21
        /    \
      10      50
     /  \    /  \
    5   15  40  60
           /  \ / \
          30 45 55 70

```

#### Case A: Target node HAS a left/right subtree (e.g., `key = 50`)
* Your rule works! Go left (`40`) $\to$ rightmost (`45`) = **Predecessor `45**`.
* Go right (`60`) $\to$ leftmost (`55`) = **Successor `55**`.


#### Case B: Target node has NO left/right subtree (e.g., `key = 45`)
* `45` has `left == NULL` and `right == NULL`! Your rule stops at `NULL` and gives nothing.
* Where do `45`'s predecessor and successor live? **Higher up in its ancestors!**
* As we walked down from `21` $\to$ `50` $\to$ `40` $\to$ `45`:
* Every time we turned **right** (`21` $\to$ `50`, `40` $\to$ `45`), the parent (`21`, then `40`) was smaller than `45`. The last right-turn parent (**`40`**) is the **Predecessor**.
* Every time we turned **left** (`50` $\to$ `40`), the parent (`50`) was larger than `45`. The last left-turn parent (**`50`**) is the **Successor**.

---

