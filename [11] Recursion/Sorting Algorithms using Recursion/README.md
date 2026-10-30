# Sorting algorithms using recursion

## Merge Sort

**Note**: Merge Sort is faster than Selection, Insersion and Bubble sort.

Merge Sort: You can sort is using **two methods**,
- **Create a new array and copy values**
- **Use indexes**

**Visualizing the recursive flow**

Initial array:
```
[38, 27, 43, 3, 9, 82, 10]
```

Step 1: First split
```
Left: [38, 27, 43, 3]
Right: [9, 82, 10]
```

Step 2: Split left part [38, 27, 43, 3]
```
Left: [38, 27]
Right: [43, 3]
```

Step 3: Split [38, 27]
```
Left: [38]
Right: [27]
→ Merge → [27, 38]
```

Step 4: Split [43, 3]
```
Left: [43]
Right: [3]
→ Merge → [3, 43]
```

Step 5: Merge [27, 38] and [3, 43]
```
→ [3, 27, 38, 43]
```

Step 6: Split right part [9, 82, 10]
```
Left: [9, 82]
Right: [10]
```

Step 7: Split [9, 82]
```
Left: [9]
Right: [82]
→ Merge → [9, 82]
```

Step 8: Merge [9, 82] and [10]
```
→ [9, 10, 82]
```

Step 9: Final merge
Merge left sorted part [3, 27, 38, 43] and right sorted part [9, 10, 82]:
```
→ [3, 9, 10, 27, 38, 43, 82]
```

**Recursion Flow**
```
[38,27,43,3,9,82,10]
        /                 \
 [38,27,43,3]           [9,82,10]
   /       \              /     \
[38,27] [43,3]       [9,82]   [10]
 /   \    /   \       /   \
[38] [27] [43] [3]  [9] [82]

```
- Recursion goes down to single elements.
- Then merges happen bottom-up:
    - `[38] + [27] → [27,38]`
    - `[43] + [3] → [3,43]`
    - Then `[27,38] + [3,43] → [3,27,38,43]`
- Similarly on the right side.
- Finally, the two halves merge into the fully sorted array.

**Time Complexity**:
- Merge sort works in two phases: divide and merge.

1. Divide phase (recursion depth):
    - Each time, the array is split into two halves.
    - This continues until subarrays of size 1.
    - Number of times you can split an array of size n = log n
    - So recursion depth = O(log n)

2. Merge phase (work per level):
    - At each level of recursion, you merge all subarrays back together.
    - Merging two sorted halves of total size n takes O(n)
    - Across a level, all merges together still process the entire array once → O(n)

3. Total work:
    - Work per level = O(n)
    - Number of levels = O(log n)
    - Total = O(n log n)

**Space Complexity**
Merge sort needs extra arrays to merge halves:
- At each merge step, temporary arrays are created to hold left and right halves.
- For an array of size 𝑛, the largest temporary storage needed is O(n)
- Recursion stack depth = O(log n), but that’s much smaller than O(n)
- So overall space complexity = O(n).

## Merge Sort (Inplace) using indexes
- ![alt text](image.png)

**Note**:
- Merge sort with O(n) extra space is optimal for performance (O(n log n)).
- In‑place merge sort reduces space to O(log n), but increases time complexity (can degrade to O(n²)).
- That’s why in practice, we accept O(n) space for merge sort.

- Standard merge sort: O(n log n) time, O(n) space.
- In‑place merge sort: O(log n) space, but merging requires shifting → can degrade to O(n²).

## Why Quick Sort preferred for Arrays and Merge Sort for Linked Lists?
**Quick Sort is generally preferred for arrays because it is in‑place and cache‑friendly, while Merge Sort is preferred for linked lists because it avoids extra memory allocation and works efficiently with pointer manipulation.**

![alt text](image-1.png)

![alt text](image-2.png)


## Quick Sort:
**Time complexity**:
![alt text](image-3.png)

**Space complexity**:
- Quick Sort is in-place (explained below), so no extra arrays are created.
- Only recursion stack consumes space.
- Depth of recursion:
    - Best/Average case: O(log n)
    - Worst case: O(n)

So space complexity = O(log n) average, O(n) worst case.

---

## 3-Way Randomized Quick Sort (using Dutch National Flag Algorithm)
### 1. Which Method Was Your Code?

Your code was **not** Lomuto, Hoare, or 3-Way.

It was an **ad-hoc "Counting-based Partition"** (often taught in entry-level tutorials):

1. **Pass 1:** Count all elements strictly smaller than `pivot` to compute `pivotIndex = st + count`.
2. **Swap:** Place `pivot` at `pivotIndex`.
3. **Pass 2:** Use two converging pointers (`i` and `j`) to swap elements across `pivotIndex`.

Textbooks avoid this scheme because it requires **two passes** over the array segment instead of one, and it becomes brittle when duplicates match the pivot.

---

### 2. Why Your Approach Failed on Duplicates (Detailed Trace)

Let’s trace your exact code on an array with duplicate pivots:

```text
nums = [3, 5, 3, 2, 8]
st = 0, en = 4
pivot = nums[st] = 3

```

#### Step 1: Your Counting Logic

```cpp
int count = 0;
for(int i = st; i <= en; i++) {
    if(nums[i] < pivot) count++;
}

```

* Only `2` is strictly `< 3`.
* `count = 1`.
* `pivotIndex = st + count = 0 + 1 = 1`.
* `swap(nums[0], nums[1])` runs.
* Array becomes: `[5, 3, 3, 2, 8]` (the pivot `3` is now at index 1).

Notice what this implies:

* **Index 0** must contain strictly `< 3` elements.
* **Indices 2, 3, 4** must contain $\ge 3$ elements.

#### Step 2: Your Two-Pointer Loop

```cpp
int i = st, j = en; // i = 0, j = 4
while(i < pivotIndex && j > pivotIndex) {
    while(nums[i] < pivot) i++;
    while(nums[j] > pivot) j--;

    if(i < pivotIndex && j > pivotIndex)
        swap(nums[i++], nums[j--]);
}

```

Let's trace the pointers:

1. `i = 0`: `nums[0] = 5`. Is $5 < 3$? **No.** The `i` loop stops at `i = 0`.
2. `j = 4`: `nums[4] = 8`. Is $8 > 3$? Yes $\implies j$ becomes 3.
3. `j = 3`: `nums[3] = 2`. Is $2 > 3$? **No.** The `j` loop stops at `j = 3`.
4. Swap `nums[0]` and `nums[3]`. Array becomes:
```text
[2, 3, 3, 5, 8]

```


`i` advances to `1`, `j` advances to `2`.
5. Now `i < pivotIndex` ($1 < 1$) is false. The loop terminates!

Now look at index 2: `nums[2] = 3`.

* It is a duplicate of the pivot.
* What if the array was `[3, 3, 2]`?
* `count = 1`, `pivotIndex = 1`. Swap gives `[3, 3, 2]`.
* `i = 0` sees `nums[0] = 3` (stops because $3 < 3$ is false).
* `j = 2` sees `nums[2] = 2` (stops because $2 > 3$ is false).
* You swap them: `[2, 3, 3]`.
* But if you have duplicates on the right side and write `nums[j] > pivot`, `j` stops on identical values and swaps them to the left side, polluting the `< pivot` partition.



---

### 3. Why Randomization Works (Clearing the "Confusion")

Randomization is not about pretending worst cases don't exist; it is about **preventing test cases or attackers from intentionally triggering them**.

1. **Deterministic Pivot (`nums[st]`):**
* If an algorithm always picks `nums[st]`, someone can craft an already-sorted array `[1, 2, 3, 4, 5, ...]` specifically designed to force $O(N^2)$ runtime and cause a timeout.


2. **Random Pivot:**
* Could random pick `st`? **Yes.**
* Could it pick the worst element twice? **Yes, but with very low probability.**
* For the algorithm to degrade to $O(N^2)$, the random generator would have to pick the worst element **$N$ times in a row**.
* The probability of that happening is:

$$P = \frac{1}{N} \times \frac{1}{N-1} \times \frac{1}{N-2} \times \dots \times 1 = \frac{1}{N!}$$



For $N = 50,000$, $\frac{1}{50000!}$ is practically zero.
* Even if you make 2 or 3 bad picks, a single pick near the median will split the problem size in half, restoring the average **$O(N \log N)$** performance.



---

### 4. Library and Formula Breakdown

#### What library provides `rand()`?

`rand()` is declared in the standard C library header **`<cstdlib>`** (or `<stdlib.h>`).

#### Dissecting `st + rand() % (en - st + 1)`:

* **`en - st + 1`**: The total count of elements in the current subarray range `[st ... en]`.
* Example: if `st = 3` and `en = 7`, elements are $\{3, 4, 5, 6, 7\}$. Total count = $7 - 3 + 1 = 5$.


* **`rand() % (en - st + 1)`**:
* `rand()` returns a pseudo-random integer between `0` and `RAND_MAX`.
* The modulo operator `% K` restricts the output to the range `[0, K - 1]`.
* For $K = 5$, `% 5` yields a value in $\{0, 1, 2, 3, 4\}$ (an offset).


* **`st + offset`**:
* Shifts the offset from `0` back to the starting index `st`.
* If offset is `0`, index is `3`. If offset is `4`, index is `7`.
* This guarantees a valid index strictly inside `[st, en]`.



---

### 5. What are `lt` and `gt`?

They are abbreviations used in Dijkstra's **Dutch National Flag (3-Way Partitioning)**:

* **`lt` stands for "Less Than"**
* **`gt` stands for "Greater Than"**

The array is maintained in four distinct zones during the scan:

```text
[  < pivot  |  == pivot  |  unprocessed elements  |  > pivot  ]
 st       lt-1 lt        i                       gt gt+1      en

```

1. **`[st ... lt - 1]`**: Elements strictly **less than** `pivot`.
2. **`[lt ... i - 1]`**: Elements **equal to** `pivot`.
3. **`[i ... gt]`**: Elements waiting to be processed.
4. **`[gt + 1 ... en]`**: Elements strictly **greater than** `pivot`.

When `i > gt`, all elements have been processed. All duplicates of the pivot are grouped in `[lt ... gt]`. The recursive calls skip that middle block and sort only the remaining boundaries:

```cpp
quickSort3Way(nums, st, lt - 1); // Sort smaller elements
quickSort3Way(nums, gt + 1, en); // Sort larger elements

```

---

### 6. Why MergeSort for Linked Lists, QuickSort for Arrays?

#### Arrays Prefer QuickSort:

1. **Random Access in $O(1)$:** Arrays let you access any index instantly (`nums[i]`), allowing pointers to jump and swap across opposite ends.
2. **CPU Cache Locality:** Arrays occupy contiguous physical memory. QuickSort works in-place, repeatedly scanning nearby elements, which keeps hardware cache hit rates high.
3. **MergeSort Waste on Arrays:** MergeSort requires allocating a temporary helper array of size $O(N)$ to merge elements, introducing allocation and copying overhead.

#### Linked Lists Prefer MergeSort:

1. **No Random Access ($O(N)$ lookup):** A linked list has no index jumping; moving to a random pivot or scanning backwards with a decrementing pointer `j--` is slow ($O(N)$ per move).
2. **MergeSort Needs $O(1)$ Extra Space on Lists:** Merging two sorted linked lists only requires rearranging existing `next` pointers—no auxiliary buffer needs to be allocated:
```text
Node1 -> Node2 -> Node3

```


3. **Finding the Middle is Fast:** You can split a linked list in half in a single pass using the fast and slow pointer technique.