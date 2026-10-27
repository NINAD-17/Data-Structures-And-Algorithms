# Dynamic Programming

## Why Recursion is Inefficient?

### Fibonacci with Recursion
- **Recurrence**: f(n) = f(n-1) + f(n-2)

- **Time Complexity**:
    - Each call branches into 2 calls → exponential growth.

    - Roughly O(2^n).

- **Space Complexity**:
    - Recursion stack depth = n.

    - So O(n) space.

That’s why recursion alone is inefficient: it repeats the same subproblems many times.


## Two Approaches to solve a problem using DP:
### Memoization (Top‑Down DP)
- Store results of subproblems in a dp array.

- When recursion revisits a subproblem, return the stored result instead of recalculating.

- **Time Complexity**: `O(n)` (each state solved once).

- **Space Complexity**: `O(n)` (dp array + recursion stack).

**Visualization**:
Instead of a huge binary tree, you get a linear chain of calls:
`f(4) → f(3) → f(2) → f(1) → f(0)`
Each solved once, then reused.


### Tabulation (Bottom‑Up DP)
- Build solutions iteratively from base cases upward.

- Example:

```cpp
dp[0] = 0; dp[1] = 1;
for(int i=2; i<=n; i++) dp[i] = dp[i-1] + dp[i-2];
```

- **Time Complexity**: `O(n)`

- **Space Complexity**: `O(n)` (can be reduced to O(1) by storing only last two values).

---

## The Famous Quote
*“Those who forget the past are condemned to repeat it.”*

Yes — this fits recursion without memoization.
If you don’t remember past results, recursion repeats the same calculations endlessly.
Memoization = “remember the past.”


## When to Apply DP
Two golden conditions (you’re right):

1. **Optimal substructure**:
    
    - Bigger problem’s optimal solution can be built from smaller subproblems.

    - Example: shortest path, knapsack, coin change.

2. **Overlapping subproblems**:

    - Same subproblem appears multiple times.

    - Example: Fibonacci, edit distance.

If both hold → DP is a good fit.

---

