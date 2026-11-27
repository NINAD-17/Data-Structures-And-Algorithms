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

## Distinct ways to climb stairs

### 1. The Core Misunderstanding: "Ways" vs "Chain of Events"

Look at the sentence where your logic tripped up:

> *"if to arrive at 0 has 1 way then to arrive at 1 should have 2 ways because to arrive at 0 took 1 way and from 0 to 1 it's another way. So, 1 should have 2 ways."*

This is the exact reason you are stuck.

A **"way" (or path)** is an **entire complete recipe from start to finish**, NOT individual actions added together.

Think of it like cooking:

* To bake a cake, you do **Step 1: mix flour** and **Step 2: bake in oven**.
* Does that mean you baked **2 cakes**?
* **No!** You baked **1 cake** that required 2 actions.

Now apply that to stair 1:

* You start standing on `0`. (You are at the starting line. Total complete journeys completed so far: `1` journey, which is `[standing at 0]`).
* Now, you take a single step to stair `1`.
* That completes the journey: `0 -> 1`.
* How many different complete paths took you from `0` to `1`?
* Path A: `0 -> 1` (a single 1-step leap).
* Can you do a 2-step leap to reach 1? No, that lands on 2.
* Can you do anything else? No.


* There is only **1 path** to reach stair 1. The action of moving from `0` to `1` did not create a second path; it just progressed the only journey that exists!


### 2. What `dp[i]` Means

Your definition of `dp[i]` is:

> *"our dp array means at ith stair what are the possible ways to reach that stair. Am I right?"*

**Yes, you are 100% right.**
`dp[i]` means: **Total number of unique paths to get from ground `0` to step `i`.**

Let's write down every physical path for `n = 4` without recursion, just looking at the stairs:

| Stair `i` | Every distinct path from ground `0` | Count of paths (`dp[i]`) |
| --- | --- | --- |
| **0** | `[ standing at 0 ]` | **1** |
| **1** | `(0 -> 1)` | **1** |
| **2** | `(0 -> 1 -> 2)`, `(0 -> 2)` | **2** |
| **3** | `(0 -> 1 -> 2 -> 3)`, `(0 -> 2 -> 3)`, `(0 -> 1 -> 3)` | **3** |
| **4** | `(0 -> 1 -> 2 -> 3 -> 4)`<br>

<br>`(0 -> 2 -> 3 -> 4)`<br>

<br>`(0 -> 1 -> 3 -> 4)`<br>

<br>`(0 -> 1 -> 2 -> 4)`<br>

<br>`(0 -> 2 -> 4)` | **5** |

Look at the count of paths: **1, 1, 2, 3, 5**. It is literally the Fibonacci numbers!


### 3. Why `dp[4] = dp[3] + dp[2]` (The Merger, Not Addition of Steps)

Stand on Stair 4 and look down. Anyone who reaches Stair 4 **must** take their final leap from either:

1. **Stair 3** (by taking a 1-step jump), OR
2. **Stair 2** (by taking a 2-step jump).

* How many people made it to Stair 3? **3 people** (via 3 distinct paths).
* All 3 of them take a 1-step jump $\to$ that creates **3 distinct paths arriving at 4**.


* How many people made it to Stair 2? **2 people** (via 2 distinct paths).
* Both of them take a 2-step jump $\to$ that creates **2 distinct paths arriving at 4**.



Total paths arriving at 4 = $3 + 2 = \mathbf{5}$.
You do **not** add $+1$. You just merge the incoming paths!


### 4. Base Cases: Top-Down vs Bottom-Up

#### Approach A: Starting from $N$, going down to $0$

```cpp
if (n == 0) return 1;
if (n == 1) return 1;

```

* `n == 0` returning `1` means: *"We successfully reached the ground step! This entire chain of choices forms **1 valid path**."*
* `n == 1` returning `1` means: *"There is only 1 way to get down to ground from step 1 (take a 1-step jump)."*

#### Approach B: Starting from $0$, going up to $N$

```cpp
if (i == n) return 1; // You successfully landed on stair n! Count this path as 1 valid way.
if (i > n)  return 0; // You overshot the staircase! This path is invalid, so it gives 0 ways.

```


### 5. Should You Move Forward?

**Yes. Absolutely move forward.**

There is nothing wrong with you. Every single engineer learning DP gets mentally stuck here because the human brain naturally confuses **"number of actions taken"** with **"number of distinct combinations"**.

You already understand:

1. What `dp[i]` stores.
2. Why it breaks down to $f(n-1) + f(n-2)$.
3. How to write the code.

Over-analyzing the base case will only cause burnout. Move on to the next problem—as you solve **House Robber**, **Frog Jump**, and **Unbounded Knapsack**, this concept will click naturally in the background without forcing it.

---

## Minimum Number Of Coins

### 1. Step-by-Step Dry Run: `targetAmt = 5`, `coins = [1, 2, 3]`

In tabulation, **there is no recursion, no tree, and no left/right calls**.
You simply start from amount `0`, solve `1`, solve `2`, and work your way up like filling an Excel spreadsheet row-by-row.

#### Initial Setup:

* `dp` array of size $6$ (`indices 0 to 5`), initialized with $\infty$ (`INT_MAX`):

```text
Index:   0    1    2    3    4    5
dp:    [ 0,  inf, inf, inf, inf, inf ]

```

`dp[0] = 0` because $0$ coins are needed to make amount $0$.


#### Step `i = 1` (Solve for amount 1):

Try each coin $\{1, 2, 3\}$:

* **Coin 1:** Remaining amount = $1 - 1 = 0$. Can we form 0? Yes, `dp[0] = 0`.
$\text{Coins} = 1 + dp[0] = 1 + 0 = 1$.
`dp[1] = min(inf, 1) = 1`.
* **Coin 2:** $1 - 2 < 0$ (too big, skip).
* **Coin 3:** $1 - 3 < 0$ (too big, skip).

`dp[1]` becomes **1**.


#### Step `i = 2` (Solve for amount 2):

Try each coin $\{1, 2, 3\}$:

* **Coin 1:** Remaining = $2 - 1 = 1$. Look up `dp[1]`: it is `1`.
$\text{Coins} = 1 + dp[1] = 1 + 1 = 2$.
`dp[2] = min(inf, 2) = 2`.
* **Coin 2:** Remaining = $2 - 2 = 0$. Look up `dp[0]`: it is `0`.
$\text{Coins} = 1 + dp[0] = 1 + 0 = 1$.
`dp[2] = min(2, 1) = 1`.
* **Coin 3:** $2 - 3 < 0$ (too big, skip).

`dp[2]` becomes **1** (using one coin of value 2).


#### Step `i = 3` (Solve for amount 3):

Try each coin $\{1, 2, 3\}$:

* **Coin 1:** Remaining = $3 - 1 = 2$. Look up `dp[2]`: it is `1`.
$\text{Coins} = 1 + dp[2] = 1 + 1 = 2$.
`dp[3] = min(inf, 2) = 2`.
* **Coin 2:** Remaining = $3 - 2 = 1$. Look up `dp[1]`: it is `1`.
$\text{Coins} = 1 + dp[1] = 1 + 1 = 2$.
`dp[3] = min(2, 2) = 2`.
* **Coin 3:** Remaining = $3 - 3 = 0$. Look up `dp[0]`: it is `0`.
$\text{Coins} = 1 + dp[0] = 1 + 0 = 1$.
`dp[3] = min(2, 1) = 1`.

`dp[3]` becomes **1** (using one coin of value 3).


#### Step `i = 4` (Solve for amount 4):

Try each coin $\{1, 2, 3\}$:

* **Coin 1:** Remaining = $4 - 1 = 3$. Look up `dp[3]`: it is `1`.
$\text{Coins} = 1 + dp[3] = 1 + 1 = 2$.
`dp[4] = min(inf, 2) = 2`.
* **Coin 2:** Remaining = $4 - 2 = 2$. Look up `dp[2]`: it is `1`.
$\text{Coins} = 1 + dp[2] = 1 + 1 = 2$.
`dp[4] = min(2, 2) = 2`.
* **Coin 3:** Remaining = $4 - 3 = 1$. Look up `dp[1]`: it is `1`.
$\text{Coins} = 1 + dp[1] = 1 + 1 = 2$.
`dp[4] = min(2, 2) = 2`.

`dp[4]` becomes **2** (e.g., $3 + 1$ or $2 + 2$).


#### Step `i = 5` (Solve for target amount 5):

Try each coin $\{1, 2, 3\}$:

* **Coin 1:** Remaining = $5 - 1 = 4$. Look up `dp[4]`: it is `2`.
$\text{Coins} = 1 + dp[4] = 1 + 2 = 3$.
`dp[5] = min(inf, 3) = 3`.
* **Coin 2:** Remaining = $5 - 2 = 3$. Look up `dp[3]`: it is `1`.
$\text{Coins} = 1 + dp[3] = 1 + 1 = 2$.
`dp[5] = min(3, 2) = 2`.
* **Coin 3:** Remaining = $5 - 3 = 2$. Look up `dp[2]`: it is `1`.
$\text{Coins} = 1 + dp[2] = 1 + 1 = 2$.
`dp[5] = min(2, 2) = 2`.

Final `dp[5]` is **2** (e.g., $2 + 3$).

```text
Final DP Table:
Index (Amount):   0   1   2   3   4   5
Min Coins:        0   1   1   1   2   2

```


### 2. Answering Your Question: Is It Guaranteed That Larger Amounts Always Use Previous Answers?

> *"If there was a different value than 5 and different coins, will it always happen that when left call calculates, other calls directly get the value from DP? Or will it calculate in those calls as well but just save some calls?"*

**It is 100% mathematically guaranteed.**

Every unique subproblem is computed **exactly once** across the entire lifetime of the program:

#### Why in Tabulation:

In tabulation, the outer loop runs strictly from `1` up to `targetAmt`:

```cpp
for (int i = 1; i <= targetAmt; i++)

```

When computing `i = 5`, every index strictly smaller than 5 (`0, 1, 2, 3, 4`) has **already been fully solved**.
Because you subtract a positive coin value (`i - coins[j] < i`), the index `i - coins[j]` is **always strictly smaller than `i**`.
Therefore, `dp[i - coins[j]]` is never empty, never uncomputed, and never re-evaluated—it is an instant $O(1)$ array lookup.

#### Why in Top-Down Memoization:

Even in recursive memoization, no matter what values of coins you have (e.g., coins = `{7, 13, 29}`, target = `500`):

1. The very first branch that explores a particular remainder (say `remainder = 42`) runs through all $K$ coin options and stores the minimum into `dp[42]`.
2. Any subsequent branch in the entire recursion tree that lands on `remainder = 42` hits:
```cpp
if (dp[42] != -1) return dp[42];

```


3. It **never recurses again** for `42`. It returns in $O(1)$ time on line 1.
4. Because the target can only take integer values from `0` to `targetAmt`, there are at most $A + 1$ unique states. Each state is calculated once and read thereafter.

The total runtime across the entire algorithm is strictly bounded by:


$$\text{Time} = \text{Unique States} \times \text{Work per State} = (A + 1) \times K = \mathbf{O(A \cdot K)}$$

No matter how strange or large the coin values are, overlapping subproblems ensure you never repeat work for an amount once it is placed into `dp`.

---

## Maximum sum of non adjacent elements

Array: `nums = [1, 3, 2, 4, 6]`, indices: `0, 1, 2, 3, 4`. Array size $n = 5$.

### Step-by-Step Call Trace: How the Tree Actually Executes

Watch how the calls unfold. In C++, the left call (`incl`) must completely finish and return before the right call (`excl`) can even run!

```text
[Call 1] solve(0): Needs nums[0] (1) + solve(2)
  |
  +---> [Call 2] solve(2): Needs nums[2] (2) + solve(4)
          |
          +---> [Call 3] solve(4): Needs nums[4] (6) + solve(6)
                  |
                  +---> solve(6) hits base case (i >= 5) -> returns 0
                  |
                  +---> incl = 6 + 0 = 6
                  |
                  +---> Now solve(4) checks excl: calls solve(5)
                  |       |
                  |       +---> solve(5) hits base case (i >= 5) -> returns 0
                  |
                  +---> excl = 0
                  +---> solve(4) finishes! max(6, 0) = 6.
                  +---> STORES dp[4] = 6 and returns 6!

```


### Now Watch the Unwinding: Lookups Start Happening

#### Step 1: Back at `solve(2)`

* `solve(2)` just got `solve(4) = 6`.
* `incl = nums[2] + solve(4) = 2 + 6 = 8`.
* Now `solve(2)` checks `excl`: calls `solve(3)`.

```text
                  +---> [Call 4] solve(3): Needs nums[3] (4) + solve(5)
                          |
                          +---> solve(5) hits base case -> returns 0
                          +---> incl = 4 + 0 = 4
                          |
                          +---> Now solve(3) checks excl: calls solve(4)
                          |       |
                          |       +---> Look! solve(4) is already in dp!
                          |       +---> dp[4] == 6 -> INSTANT RETURN 6! (No tree expansion!)
                          |
                          +---> excl = 6
                          +---> solve(3) finishes! max(4, 6) = 6.
                          +---> STORES dp[3] = 6 and returns 6!

```

* `solve(2)` receives `excl = 6`.
* `solve(2)` finishes! $\max(8, 6) = \mathbf{8}$.
* **Stores `dp[2] = 8` and returns 8.**


#### Step 2: Back at the Root `solve(0)`

* `solve(0)` just finished its left choice:

$$\text{incl} = \text{nums}[0] + \text{solve}(2) = 1 + 8 = \mathbf{9}$$


* Now `solve(0)` begins its right choice: **`excl = solve(1)`**.


### The Power of DP: Solving `solve(1)` in Just 2 Steps!

Without DP, `solve(1)` would redraw almost the entire tree. Look at what happens with DP:

```text
[Call 5] solve(1):
  |
  +---> incl = nums[1] (3) + solve(3)
  |       |
  |       +---> dp[3] is ALREADY 6!
  |       +---> Instant return 6!
  |       +---> incl = 3 + 6 = 9.
  |
  +---> excl = solve(2)
          |
          +---> dp[2] is ALREADY 8!
          +---> Instant return 8!
          +---> excl = 8.
  |
  +---> solve(1) finishes! max(9, 8) = 9.
  +---> STORES dp[1] = 9 and returns 9!

```

**Not a single recursive branch opened below `solve(1)`!** It simply did two array lookups: $3 + dp[3]$ vs $dp[2]$.


#### Step 3: Final Answer at `solve(0)`

* $\text{incl} = 1 + dp[2] = 1 + 8 = 9$
* $\text{excl} = dp[1] = 9$
* $\max(9, 9) = \mathbf{9}$.
* **`dp[0] = 9`** is returned.


### The Exact `dp` Array State

Look at the DP table after everything runs:

| Index `i` | Remaining Subarray | Plain English Meaning | `dp[i]` |
| --- | --- | --- | --- |
| **4** | `[6]` | Best you can get from just `{6}` | **6** |
| **3** | `[4, 6]` | Best you can get from `{4, 6}` ($\max(4, 6)$) | **6** |
| **2** | `[2, 4, 6]` | Best from `{2, 4, 6}` ($2+6$ vs $6$) | **8** |
| **1** | `[3, 2, 4, 6]` | Best from `{3, 2, 4, 6}` ($3+6$ vs $8$) | **9** |
| **0** | `[1, 3, 2, 4, 6]` | Best from entire array ($1+8$ vs $9$) | **9** |

Notice that index $3$ is **never** $7$ or $9$:

* `dp[3]` is **always 6**, because if you only have houses `[4, 6]` left to rob, the maximum you can ever get is $6$.
* The $7$ or $9$ you saw earlier came from adding $3$ or $1$ from earlier houses. That addition belongs to `solve(1)` or `solve(0)`, **never** to `dp[3]`!

---

## Combination Sum IV

### 1. How C++ Handles Signed vs. Unsigned Overflow

You have the core concept right, but there is one precise technical detail about **what** it takes the modulus with:

* **Signed `int` (`-2,147,483,648` to `+2,147,483,647`):**
In the C++ language standard, signed overflow is **Undefined Behavior (UB)**. The hardware handles negative numbers using two's complement, and when a signed number overflows, the compiler is not required to do anything predictable. Modern compilers (and LeetCode's sanitizers) treat this as a fatal error or let it wrap into garbage negative numbers.
* **Unsigned `int` (`0` to `4,294,967,295`):**
The C++ standard **strictly guarantees** that unsigned integers perform **modulo $2^{32}$ ($4,294,967,296$) arithmetic**—**not** `INT_MAX` ($2^{31} - 1$).
It does this modulo automatically at the CPU hardware bit-level. You do not have to write `%` manually.


### 2. Can Test Cases Ask for Targets with Exponential Ways?

> *"If anything in range of 10 or 2, etc then they'll have exponential ways. So, they won't give us target as 1000 as well. Right? Because they said that answer will always be under INT_MAX."*

**Yes, you are 100% correct.**

The problem description explicitly guarantees:

> *"The test cases are generated so that the answer can fit in a 32-bit integer."*

* If `nums = [1, 2]` and `target = 1000`, the real mathematical answer has over 100 digits. Because that cannot fit in a 32-bit integer, **the problem setter cannot legally give that test case**.
* If `target` is large (like `999`), the setter **must** craft `nums` so that the total ways to reach `999` remains $\le 2^{31} - 1$.
* That is why the test case had only one odd number `111`: to ensure the final count at `dp[999]` remains tiny.


### 3. Why `if (dp[tar] <= INT_MAX - dp[tar - num])` Does NOT Give the Wrong Answer

This is the key doubt:

> *"If any target has more than INT_MAX ways then why we're skipping it? Don't you think it'll give wrong answer?"*

Think about how an intermediate target like `tar = 400` can contribute to `tar = 999`:

* Can any path that passed through `400` **ever** reach `999` in that test case?
* Remember, all other coins are multiples of 10 (`10, 20, 30...`).
* The **only** coin that has an odd/non-zero last digit is `111`.
* To get from `400` to `999`, the remaining difference needed is:

$$999 - 400 = 599$$


* Can multiples of `10` and `111` ever add up to `599`?
* To get the last digit `9` using `111`, you must use either:
* Nine `111`s: $9 \times 111 = 999$ (already exceeds 599!)
* Four `111`s: $4 \times 111 = 444$. Remaining: $599 - 444 = 155$. Can multiples of `10` make `155`? No!


* **It is physically impossible to reach 999 starting from 400.**
* Any intermediate target that had $> 2\times 10^9$ combinations **leads to a dead end** on the way to 999! Its contribution to `dp[999]` is precisely **0**.

If an intermediate amount $i$ exceeds `INT_MAX`, it can **never** be part of a valid path to `target = 999`. If it were part of a valid path to `target`, then `dp[target]` would also have to be $\ge dp[i] > \text{INT\_MAX}$, which violates LeetCode's guarantee that the final answer fits in a 32-bit integer!

Therefore, capping or ignoring additions once an intermediate value hits `INT_MAX` safely discards dead-end paths that could never legally reach the final answer anyway.


### 4. Why `unsigned int` Works Without Corrupting the Output

> *"If we used unsigned int then it'll mod the value, but don't you think it'll then give unexpected output?"*

Because:

1. Dead-end intermediate states (like 400) wrap around cleanly under unsigned math without crashing the compiler.
2. The paths that **actually lead to 999** (the chain of nine `111`s) only visit states:

$$0 \to 111 \to 222 \to 333 \to 444 \to 555 \to 666 \to 777 \to 888 \to 999$$


3. At every one of those specific states, the count of ways is small (well under `INT_MAX`), so **no overflow ever occurs along the true solution path**.
4. When `(int)dp[target]` is returned, the value at index 999 is exact and completely uncorrupted.

---

## Maximal Square

### 1. The Core Mystery: "If memoization actually starts calculating from the bottom-right, why did we call `(0, 0)` first?"

This is the single most enlightening realization in Dynamic Programming.

Look at how recursion works in computer hardware:

1. **The Descent (The Question phase):**
You call `solve(0, 0)`. Cell `(0, 0)` cannot answer its question until it knows its neighbors. So it pauses and asks `(0, 1)`, which asks `(0, 2)`... down to `(n-1, m-1)`.
No math is happening yet; you are just stacking questions on top of each other.
2. **The Base Case (The Hitting-the-Floor phase):**
Finally, you hit out-of-bounds or the bottom-right corner. It returns an exact number (`0` or `1`).
3. **The Unwinding (The Real Work phase):**
Now, values return upwards from bottom-right back to `(0, 0)`.

Here is the key insight:

> **All Dynamic Programming (both Memoization and Tabulation) computes subproblems in the EXACT SAME mathematical order: from simplest (base cases) to hardest (the full problem).**

* **Top-Down (Memoization):** You ask for the big answer `(0, 0)` first. Recursion naturally drills down to find the base cases at the bottom-right, and answers them on the way back up.
* **Bottom-Up (Tabulation):** You tell the computer: *"I already know recursion is going to run down to the bottom-right anyway. Why waste stack frames drilling down? I will manually start a `for` loop at the bottom-right and compute upwards!"*

They are not doing opposite math. Tabulation is simply **skipping the descent phase** because you already know where the base cases are.


### 2. "Should we start memoization from `(n-1, m-1)` instead of `(0, 0)`?"

You **can**, but notice what happens to the English definition of your state:

* If you start top-down from `(0, 0)`:
* `solve(i, j)` means: *"What is the largest square whose **top-left corner** is at `(i, j)`?"*
* It must look forward: Right `(i, j+1)`, Down `(i+1, j)`, Diagonal `(i+1, j+1)`.
* Its base cases are naturally at the bottom and right edges (`i >= n` or `j >= m`).


* If you start top-down from `(n-1, m-1)`:
* `solve(i, j)` means: *"What is the largest square whose **bottom-right corner** is at `(i, j)`?"*
* It must look backward: Left `(i, j-1)`, Up `(i-1, j)`, Top-Left `(i-1, j-1)`.
* Its base cases are at the top and left edges (`i < 0` or `j < 0`).


Neither is "more correct." They are mirror images. The reason your instructor used `(0, 0)` looking forward is simply that iterating from `0` forward is how most people naturally read an array.


### 3. Space-Optimized Tabulation: Why Keep Rows Instead of Columns?

Look at the dependency of cell `(i, j)` in your bottom-up tabulation:
To compute cell `(i, j)`, you only need three neighbors:

1. **Right:** `(i, j + 1)` $\implies$ in the **SAME** row `i`
2. **Down:** `(i + 1, j)` $\implies$ in the **NEXT** row `i + 1`
3. **Diagonal:** `(i + 1, j + 1)` $\implies$ in the **NEXT** row `i + 1`

```text
Current Row (i):       [ dp[i][j] ]  -----> [ dp[i][j+1] (Right) ]
                            |                        |
Next Row (i + 1):      [ dp[i+1][j] (Down) ]  [ dp[i+1][j+1] (Diag) ]

```

Notice this critical observation:

* To fill the entire **Current Row (`i`)**, you **only** need information from:
1. Cells already computed in the **Current Row (`i`)** (to its right).
2. The **Next Row (`i + 1`)**.


* You **never** need row `i + 2`, `i + 3`, or any row below it ever again!
* Therefore, you only need **two 1D vectors of size `col + 1**`:
* `curr[j]` $\implies$ representing row `i`
* `next[j]` $\implies$ representing row `i + 1`


#### "Why not columns?"

You *can* optimize by columns as well! But matrices in C++ are stored in **Row-Major order** (contiguous in memory row-by-row). Operating row-by-row gives cache locality, and usually, if $m \times n$ has fewer columns than rows, keeping a row vector uses minimal memory ($O(col)$).


### 4. Summary of the Transition

| Step | Technique | Time | Space | How to think about it |
| --- | --- | --- | --- | --- |
| **1** | **Top-Down (Memoization)** | $O(row \times col)$ | $O(row \times col)$ | Start at `(0, 0)`. Recursion runs to the base cases and computes answers on the return trip. |
| **2** | **Bottom-Up (Tabulation)** | $O(row \times col)$ | $O(row \times col)$ | Start loops directly at the base cases (`row - 1`, `col - 1`) and build forward. |
| **3** | **Optimized Tabulation** | $O(row \times col)$ | **$O(col)$** | Look at the table: cell `(i, j)` only needs row `i` and row `i+1`. Discard the rest of the grid. |


---

