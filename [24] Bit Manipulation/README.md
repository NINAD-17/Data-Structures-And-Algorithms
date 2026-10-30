# Bit Manipulation

## 1. Counting Bits

Dynamic Programming simply means: **solve smaller subproblems first, save their answers in an array, and use those saved answers to solve bigger problems in $O(1)$ time.**

Here is the exact intuition, the pattern, and why the recurrence relation works.

---

### 1. Spotting the Pattern: Compare Numbers to Their Halves

Write down numbers in decimal and binary side-by-side:

| Decimal ($i$) | Binary | How it relates to $i / 2$ (or `i >> 1`) | Number of 1s |
| --- | --- | --- | --- |
| **0** | `0` | Base case | **0** |
| **1** | `1` | `0` shifted left + `1` | $0 + 1 =$ **1** |
| **2** | `10` | `1` (`1`) shifted left + `0` | Same as 1 $\rightarrow$ **1** |
| **3** | `11` | `1` (`1`) shifted left + `1` | 1s in (1) + 1 $\rightarrow$ **2** |
| **4** | `100` | `2` (`10`) shifted left + `0` | Same as 2 $\rightarrow$ **1** |
| **5** | `101` | `2` (`10`) shifted left + `1` | 1s in (2) + 1 $\rightarrow$ **2** |
| **6** | `110` | `3` (`11`) shifted left + `0` | Same as 3 $\rightarrow$ **2** |
| **7** | `111` | `3` (`11`) shifted left + `1` | 1s in (3) + 1 $\rightarrow$ **3** |

---

### 2. The Core Realization

Look at what happens when you shift a number right by 1 (`i >> 1` or `i / 2`):

#### Case A: The number is Even (ends in `0`)

Take $6$ (`110` in binary):

* Shift right by 1 bit: `6 >> 1` gives `3` (`11` in binary).
* Did we drop a `1` or a `0`? We dropped the last bit, which was **`0`**.
* That means the count of `1`s in $6$ is **exactly the same** as the count of `1`s in $3$!

$$\text{count}(6) = \text{count}(3) = \text{count}(6 >> 1)$$

#### Case B: The number is Odd (ends in `1`)

Take $7$ (`111` in binary):

* Shift right by 1 bit: `7 >> 1` gives `3` (`11` in binary).
* What did we drop? We dropped the last bit, which was **`1`**.
* That means $7$ has **all the `1`s of $3$, plus that extra `1**` on the end!

$$\text{count}(7) = \text{count}(3) + 1 = \text{count}(7 >> 1) + 1$$

---

### 3. Combining Both Cases into One DP Formula

Notice what checks if the last bit is `1` or `0`:

* `i & 1` gives:
* `0` if $i$ is even
* `1` if $i$ is odd



So whether $i$ is even or odd, the rule is identical:

$$\text{ans}[i] = \text{ans}[i / 2] + (\text{last bit})$$

Using bitwise operators:

$$\text{ans}[i] = \text{ans}[i \gg 1] + (i \ \& \ 1)$$

---

### 4. Why This is 1D Dynamic Programming

1. **Subproblem:** To find the answer for $i$, we need the answer for a strictly smaller number: $\lfloor i / 2 \rfloor$.
2. **Optimal Substructure / Overlapping Subproblems:** The answer for $\lfloor i / 2 \rfloor$ was already computed in an earlier iteration and is sitting in `ans[i >> 1]`.
3. **Table (State):** The 1D vector `ans` of size $n + 1$ acts as our DP memo table.
4. **Base Case:**

$$\text{ans}[0] = 0$$

### Step-by-Step Execution Trace for $n = 5$

Initialize: `ans = [0, 0, 0, 0, 0, 0]`

---

$i = 1$:

* `i >> 1` is $0$. `ans[0]` is `0`.
* `i & 1` is $1$.
* `ans[1] = ans[0] + 1 = 0 + 1 = 1`.
* Array: `[0, 1, 0, 0, 0, 0]`

---

$i = 2$:

* `i >> 1` is $1$. `ans[1]` is `1`.
* `i & 1` is $0$.
* `ans[2] = ans[1] + 0 = 1 + 0 = 1`.
* Array: `[0, 1, 1, 0, 0, 0]`

---

$i = 3$:

* `i >> 1` is $1$. `ans[1]` is `1`.
* `i & 1` is $1$.
* `ans[3] = ans[1] + 1 = 1 + 1 = 2`.
* Array: `[0, 1, 1, 2, 0, 0]`

---

$i = 4$:

* `i >> 1` is $2$. `ans[2]` is `1`.
* `i & 1` is $0$.
* `ans[4] = ans[2] + 0 = 1 + 0 = 1`.
* Array: `[0, 1, 1, 2, 1, 0]`

---

$i = 5$:

* `i >> 1` is $2$. `ans[2]` is `1`.
* `i & 1` is $1$.
* `ans[5] = ans[2] + 1 = 1 + 1 = 2`.
* Array: `[0, 1, 1, 2, 1, 2]`

### Why It's $O(n)$

Because we do **not** run a while loop to count bits for each number. We just look up a previously solved value in the array (`ans[i >> 1]`), add the last bit (`i & 1`), and move to the next index.

One loop, $O(1)$ work per index $\rightarrow$ overall time is strictly **$O(n)$**.


## 2. Single Number II

Think of it like counting coins.

Every number is just a bag of bits (0s and 1s).

The problem says:

* Every normal number appears **exactly 3 times**.
* Only **one special number** appears **once**.

---

### Imagine Looking at Just ONE Bit Position (say, the 1st bit)

Suppose an element has a `1` at that position.
Because that number appears **3 times**, it drops three `1`s into our count:

$$1 + 1 + 1 = 3$$

What if another normal number *also* has a `1` at that position?
It also appears 3 times, so it drops three more `1`s:

$$3 + 3 = 6$$

What if a normal number has a `0` at that position?
It drops zero `1`s:

$$6 + 0 = 6$$

**Notice the pattern:**
No matter how many normal numbers have a `1` at that spot, because every normal number comes as a **triplet (group of 3)**, their contribution to our count will **always be a multiple of 3**:

$$0, 3, 6, 9, 12, 15, \dots$$

---

### Now Add the Special Unique Number

The unique number appears **only 1 time** (not 3 times).

There are only two possibilities for this unique number at this bit:

#### Possibility 1: The unique number has a `0` at this bit

* The count of `1`s comes *only* from the triplets.
* Total count is still a multiple of 3:

$$\text{Count} = 3, 6, 9, \dots$$

* What is $(\text{multiple of 3}) \pmod 3$?

$$3 \pmod 3 = 0$$

$$6 \pmod 3 = 0$$

* Result is **`0`**. That tells us: the unique number has a **`0`** here.

#### Possibility 2: The unique number has a `1` at this bit

* It adds its single `1` to the total count.
* Total count becomes $(\text{a multiple of 3}) + 1$:

$$\text{Count} = 1, 4, 7, 10, \dots$$

* What happens when you divide by 3 and look at the remainder?

$$1 \pmod 3 = 1$$

$$4 \pmod 3 = 1$$

$$7 \pmod 3 = 1$$

* Result is **`1`**. That extra `1` remainder tells us: the unique number definitely has a **`1`** here!

---

### A Concrete Example

Take array: `[5, 5, 5, 2]`

* Unique number is `2`.
* Binary of $5$: `1 0 1`
* Binary of $2$: `0 1 0`

Let's inspect bit by bit:

1. **Rightmost bit (Bit 0):**
* $5$ has `1`
* $5$ has `1`
* $5$ has `1`
* $2$ has `0`
* Total `1`s = $1 + 1 + 1 + 0 = 3$.
* $3 \pmod 3 = \mathbf{0}$.
* So the unique number has a **`0`** at Bit 0.


2. **Middle bit (Bit 1):**
* $5$ has `0`
* $5$ has `0`
* $5$ has `0`
* $2$ has `1`
* Total `1`s = $0 + 0 + 0 + 1 = 1$.
* $1 \pmod 3 = \mathbf{1}$.
* So the unique number has a **`1`** at Bit 1.


3. **Leftmost bit (Bit 2):**
* $5$ has `1`
* $5$ has `1`
* $5$ has `1`
* $2$ has `0`
* Total `1`s = $1 + 1 + 1 + 0 = 3$.
* $3 \pmod 3 = \mathbf{0}$.
* So the unique number has a **`0`** at Bit 2.



Put the collected bits together:

$$\text{Bit 2} = 0, \quad \text{Bit 1} = 1, \quad \text{Bit 0} = 0 \implies 010_2 = 2_{10}$$

`% 3` throws away all the triplets (because anything grouped in 3s divides cleanly with no remainder) and keeps only the leftover bit that belonged to the single number.

---

### 1. What does `1U` mean?

The suffix **`U`** stands for **`Unsigned`**.

In C++:

* Writing `1` creates a **signed 32-bit integer** (`int`).
* Writing `1U` creates an **unsigned 32-bit integer** (`unsigned int`).

#### Why does that matter here?

Our loop goes from `bitIndex = 0` up to `bitIndex = 31`.

When `bitIndex = 31`:

* If you write `1 << 31`:
You take the signed integer `1` and shift it into the 31st position (the sign bit).
In C++, shifting a `1` into the sign bit of a standard signed `int` causes **signed integer overflow**, which is **Undefined Behavior (UB)**. Modern compilers like GCC/Clang may warn or crash with runtime sanitizers on LeetCode.
* If you write `1U << 31`:
`1U` is an `unsigned int`. Unsigned types do not have a sign bit, and bit shifting on unsigned integers is explicitly well-defined by the C++ standard.

---

### 2. How `result |= (1U << bitIndex)` Works

This is the standard bitwise pattern to **turn ON (set) a specific bit** in a number.

Let's break it into two parts:

#### Step A: `1U << bitIndex`

It creates a "mask" that has a `1` only at position `bitIndex`, and `0` everywhere else.

* If `bitIndex = 0`: `1U << 0` $\rightarrow$ `...00000001`
* If `bitIndex = 1`: `1U << 1` $\rightarrow$ `...00000010`
* If `bitIndex = 2`: `1U << 2` $\rightarrow$ `...00000100`

#### Step B: `result |= mask`

The bitwise OR operator (`|`) combines bits. If either bit is `1`, the answer is `1`.
Suppose `result` is currently `2` (`0010`), and we want to set bit 0:

```text
  result:        0000 0010  (2)
| (1U << 0):     0000 0001  (1)

```

---

new result:    0000 0011  (3)

```
Bit 0 is now switched to `1` without disturbing any other bit.

```
--- 

## 3. Single Number III
### 1. How Does `x & (-x)` Find the Rightmost Set Bit?

Recall that computers store negative numbers using **Two's Complement**:

$$-x = \sim x + 1 \quad (\text{invert all bits, then add } 1)$$

Let us trace `x = 6` using an 8-bit representation:

* $x = 6$:
```text
0000 0110

```


* Step 1: Flip all bits ($\sim x$):
```text
1111 1001

```


* Step 2: Add 1 to get $-x$:
```text
  1111 1001
+         1

```



---

```
1111 1010   <-- This is -6

```

```

Now, perform bitwise AND between \(x\) and \(-x\):
```text
x  = 0000 0110  (6)
-x  = 1111 1010  (-6)

```

---

```
   0000 0010  (2)

```

```
Only the rightmost `1` bit survived.
```

#### Why does this mathematically happen for ANY number?
Every binary number looks like this from left to right:


$$\text{[some bits]} \quad 1 \quad 000\dots$$

(A rightmost `1`, followed by a tail of trailing zeros).

1. Inverting bits ($\sim x$) changes the rightmost `1` into `0`, and all trailing `0`s into `1`s:

$$\text{[inverted bits]} \quad 0 \quad 111\dots$$

2. Adding `1` ripples carries all the way through those trailing `1`s until it hits that `0`:
* All trailing `1`s roll over back to `0`s.
* The `0` flips back to `1`.
* None of the carries travel further left!


3. Now compare original $x$ with $-x$:
* To the **left** of the rightmost bit: bits are opposite ($b$ vs $\sim b$) $\rightarrow$ `AND` gives **all 0s**.
* At the **rightmost set bit**: both are `1` $\rightarrow$ `AND` gives **1**.
* To the **right** of that bit: both are `0` $\rightarrow$ `AND` gives **all 0s**.



Thus, `x & (-x)` masks out every single bit except the lowest set bit.

---

### 2. What Happens After Getting `rightmostBit`?

For $6$, `rightmostBit = 2` (`...00010`).

In Step 3, we iterate through `nums`:

```cpp
for (int num : nums) {
    if (num & rightmostBit) {
        num1 ^= num; // Group 1
    } else {
        num2 ^= num; // Group 2
    }
}

```

* `num & rightmostBit`: This checks whether the bit at that specific position is `1` or `0`.
* The two unique numbers (3 and 5) have different bits at that exact position:
* For $3$ (`011`): bit 1 is `1` $\rightarrow$ goes into `num1` bucket.
* For $5$ (`101`): bit 1 is `0` $\rightarrow$ goes into `num2` bucket.


* What about duplicates?
* Take the two `1`s: both are identical, so both go to `num2`. Inside `num2`, they cancel each other out ($1 \oplus 1 = 0$).
* Take the two `2`s: both go to `num1`. Inside `num1`, they cancel each other out ($2 \oplus 2 = 0$).


* At the end:
* `num1` holds only $3$.
* `num2` holds only $5$.

## 5. Power of 2

### 1. Explanation of Modulo Solution

* **Step 1: Check `n <= 0`:**
* Powers of two ($2^0=1, 2^1=2, 2^2=4, \dots$) are strictly positive numbers.
* Negative numbers and $0$ cannot be powers of two, so return `false` immediately.


* **Step 2: Repeated Division (`n /= 2`):**
* A number is a power of 2 if and only if its only prime factor is $2$.
* If $n$ is divisible by 2 (`n % 2 == 0`), divide it by 2.
* Keep peeling off factors of 2 until the number is no longer divisible by 2.


* **Step 3: Verification (`return n == 1`):**
* If the original number had only factors of 2 (e.g., $16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1$), it ends up at **`1`** $\rightarrow$ returns `true`.
* If it had any other prime factor (e.g., $12 \rightarrow 6 \rightarrow 3$), the loop stops at **`3`** $\rightarrow$ `3 == 1` evaluates to `false`.


* **Complexity:**
* **Time Complexity:** $O(\log_2 n)$ — Halves $n$ in each iteration.
* **Space Complexity:** $O(1)$.

---

### 2. The Optimal $O(1)$ Follow-up: Bit Manipulation

Notice how powers of 2 look in binary:

$$\begin{aligned} 1 &= 2^0 = 0000\ 0001_2 \\ 2 &= 2^1 = 0000\ 0010_2 \\ 4 &= 2^2 = 0000\ 0100_2 \\ 8 &= 2^3 = 0000\ 1000_2 \\ 16 &= 2^4 = 0001\ 0000_2 \end{aligned}$$

> **Key Binary Property:**
> Every power of two has **exactly one set bit (`1`)**, with all other bits being `0`.

---

### Using Brian Kernighan's Trick

Recall that `n & (n - 1)` removes the rightmost set bit:

* If $n = 8$ (`1000`):
* $n - 1 = 7$ (`0111`)
* `8 & 7`:
```text
  1000
& 0111

```

---

```
  0000
```

```

* Because $8$ had **only one set bit**, erasing that single bit leaves **`0`**.
* If $n = 6$ (not a power of 2, `0110`):
* $n - 1 = 5$ (`0101`)
* `6 & 5`:
```text
  0110
& 0101

```

---

0100  (not 0!)

```

```

---

### Optimal Code ($O(1)$ Time, $O(1)$ Space, No Loops)

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        // n must be positive AND have exactly one set bit
        return (n > 0) && ((n & (n - 1)) == 0);
    }
};

```

* **Why check `n > 0`?**
* If $n = 0$: `0 & -1` is `0`, but $0$ is not a power of 2.
* If $n = -2147483648$ (`INT_MIN`, binary `1000...0000`): in Two's complement, subtracting 1 overflows signed 32-bit `int`, causing undefined behavior. The check `n > 0` shields against this.


* **Time Complexity:** $O(1)$ — Exactly two operations (one subtraction, one bitwise AND).
* **Space Complexity:** $O(1)$.