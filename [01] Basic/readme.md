# Basics

## Using namespace std?
- In C++, there are many namespaces.
- using namespace std is a statement that tells the compiler to use the std namespace.
- Namespaces are used to organize code into logical groups and prevent name collisions.
- The std namespace contains the identifiers of the C++ standard library, such as cout, cin, string, vector, map, etc.
- To use an identifier from the standard library, you need to specify that it belongs to the std namespace using the scope resolution operator `::`.
- Adding using namespace std at the top of your source code means you won’t have to type the `std::` prefix constantly.
- However, using this statement can lead to name collisions if you’re using multiple libraries.
- **Identifiers**: Identifier is a name used to identify a variable or function. However, in C++, identifiers are not just limited to variables and functions. They can also refer to other entities such as objects, classes, structures, and more.
- In the context of `std::cout`, `std::cin`, and `std::endl`:
    - `std::cout` and `std::cin` are objects of the `ostream` and `istream` classes respectively. They are used for output and input operations.
    - `std::endl` is a function that inserts a new line character and flushes the output buffer.
- When we say `using namespace std`, we’re telling the compiler to look into the std namespace if it doesn’t find an identifier in the current scope. This allows us to use cout, cin, endl, and other identifiers from the std namespace directly, without prefixing them with `std::`.


## return 0;
- In C++, the `return 0;` statement at the end of the main function is optional. If you don’t explicitly return a value, the compiler automatically adds a `return 0;` statement. 
- The return value of the main function is considered the "**Exit Status**" of the application. On most operating systems, returning 0 is a success status, indicating that the program worked fine. However, you can also return other values to indicate different exit statuses. 
- For example, you can `return -1` or any other non-zero value to indicate that an error occurred during the execution of your program. So, while it’s not strictly necessary to include a `return 0;` statement at the end of your main function, it’s good practice to do so to explicitly indicate that your program executed successfully


## Data Types and Variables
- **Int**: 4 bytes
- **Char**: 1 byte
- **bool**: 1 byte
- **float**: 8 byte
- **double**: 8 byte


## TypeCasting in CPP
Type casting in C++ refers to the process of converting a value of one data type to another data type. This can be useful in situations where we need to change the type of a variable to perform a certain operation or pass it to a function that requires a different data type.

- **Implicit Type Conversion**: is automatically performed by the compiler when a value is copied to a compatible type.
Ex. `int a = 'a'`
Here we're copying ASCII value of char 'a' to into a.

- **Explicit Type Conversion:**: The user can typecast the result to make it of a particular data type


Explaination: `/Type_Casting.cpp`
- In given example, When you assign an integer value to a char variable, the value is implicitly converted to a char by taking the value modulo 256 (since a char is 1 byte and can represent values from 0 to 255). In this case, 123456 modulo 256 is 64, which is the ASCII value of the character '@'. That’s why you get '@' as the output.


## Operators
- int/int = int
- float/int = float
- double/int = double


## cin
- `cin` not reads '_'(space), '\t'(tab), '\n'(enter)
- To get these as input use `cin.get()`
- It returns ASCII value of that character


## Bitwise Operator: NOT
**To print negetive number we use 2's compliment**
**Value of Not(~) of 2 is -3**

- Here 1st we took 1's compliment of integer 2.
- 000....0010 ----> 1's compliment ----> 111....1101
- 111....1101 is the value of ~num. So, this is an answer of our question.
- But we want it in decimal number. So, now we've to convert it in decimal number.

- In answer 111....1101, 1st bit is 1 which is showing that number is negetive
- **To display negetive number we've to take its 2's compliment.**
- For 2's compliment, we take 1's compliment and then add 1 to it.
- And finally we give -ve sign to that output number.

- 2's compliment process...
- To print this negetive number, you've to take 2's compliment of that value(111...- 1101)
- We're ignoring 1st bit, because it's showing that the number is negetive.
- Now take 1's compliment of remaining bits --> (00....0010) remember that we ignored- 1st bit.
- Now add 1 to this value --> 00....0010 + 1 = 00....0011
- 00....0011 So by (bin to decimal) value is 3
- So answer is -ve 3 (-3)

<br>
<br>

# Deep Dive: Bit-Level Memory Representation of Integers (32-Bit Systems)

## 1. Physical Memory Foundation
- In modern computing (C++, Java, C, etc.), a standard `int` occupies:
  $$\text{Size} = 4 \text{ bytes} = 4 \times 8 \text{ bits} = 32 \text{ bits}$$
- Each bit has exactly 2 states (`0` or `1`).
- By the fundamental counting principle, 32 bits arranged in series provide:
  $$\text{Total Unique States} = 2^{32} = 4,294,967,296 \text{ states}$$
- **Absolute Rule:** Any 32-bit data type—regardless of how it is labeled—can represent **exactly $4,294,967,296$ unique numeric values**. It cannot represent even a single number more.

---

## 2. Unsigned Integer (`unsigned int`)

### Mechanics:
- All 32 bits are dedicated exclusively to **magnitude** (value).
- There is no sign indicator; every bit pattern represents a positive value or zero.

### Mathematical Derivation of Range:
- Bits: Indexed $b_{31}$ down to $b_0$.
- Formula for the value of the bit sequence:
  $$\text{Value} = \sum_{i=0}^{31} b_i \cdot 2^i = (b_{31} \cdot 2^{31}) + (b_{30} \cdot 2^{30}) + \dots + (b_0 \cdot 2^0)$$
- **Minimum Value:** All bits set to `0`
  $$\text{Pattern: } 00000000\ 00000000\ 00000000\ 00000000_2 = 0$$
- **Maximum Value:** All bits set to `1`
  $$\text{Pattern: } 11111111\ 11111111\ 11111111\ 11111111_2$$
  $$\text{Sum} = 2^{31} + 2^{30} + \dots + 2^1 + 2^0 = 2^{32} - 1 = 4,294,967,295$$

### Why $2^{32} - 1$ instead of $2^{32}$?
- If we start counting from $1$, the $2^{32}$-th number would be $2^{32}$.
- But computers must represent $0$. 
- Since $0$ consumes the very first bit pattern (`0x00000000`), the remaining $4,294,967,295$ patterns represent the positive integers $1$ through $2^{32} - 1$.

$$\text{Range: } [0, 2^{32} - 1] \implies [0, 4,294,967,295]$$
$$\text{Total numbers represented: } (4,294,967,295 - 0) + 1 = 2^{32}$$

---

## 3. Signed Integer (`int` / `signed int`)

### Mechanics (Two's Complement System):
- Bit $b_{31}$ (the Most Significant Bit / MSB) is reserved as the **Sign Bit**:
  - `0` indicates non-negative ($\ge 0$).
  - `1` indicates negative ($< 0$).
- This leaves only **31 bits** ($b_{30}$ down to $b_0$) for the magnitude.

### Splitting the $2^{32}$ States:
Since 1 bit is fixed for the sign, the total $2^{32}$ combinations are split strictly in half:
- **$2^{31}$ combinations** where $\text{MSB} = 0$ ($2,147,483,648$ values)
- **$2^{31}$ combinations** where $\text{MSB} = 1$ ($2,147,483,648$ values)

### A. The Non-Negative Half ($\text{MSB} = 0$):
- $b_{31} = 0$, leaving 31 bits free ($b_{30} \dots b_0$).
- Number of available unique bit patterns: $2^{31} = 2,147,483,648$.
- Smallest pattern: `0` followed by 31 zeros $\rightarrow 0$.
- Largest pattern: `0` followed by 31 ones $\rightarrow 2^{30} + 2^{29} + \dots + 2^0 = 2^{31} - 1$.
- **Positive Range:** 
  $$[0, 2^{31} - 1] \implies [0, 2,147,483,647]$$
  *(Note: Exactly $2,147,483,647$ positive numbers, plus $0$, makes $2^{31}$ values).*

### B. The Negative Half ($\text{MSB} = 1$):
- $b_{31} = 1$, leaving 31 bits free ($b_{30} \dots b_0$).
- Number of available unique bit patterns: $2^{31} = 2,147,483,648$.
- In Two's Complement arithmetic, the MSB has a negative weight: $-2^{31}$.
- Largest negative number (closest to zero):
  $$\text{Pattern: } 11111111\ 11111111\ 11111111\ 11111111_2 = -2^{31} + (2^{31} - 1) = -1$$
- Smallest negative number (most negative):
  $$\text{Pattern: } 10000000\ 00000000\ 00000000\ 00000000_2 = -2^{31} = -2,147,483,648$$
- **Negative Range:** 
  $$[-2^{31}, -1] \implies [-2,147,483,648, -1]$$

### Full Signed Range:
$$\text{Range: } [-2^{31}, 2^{31} - 1] \implies [-2,147,483,648, \text{ to } 2,147,483,647]$$

### Why is Negative Min $-2^{31}$ but Positive Max is only $2^{31} - 1$?
Because zero is not negative. Zero has an MSB of `0`, meaning **zero is grouped with the positive side**.
- Positive bucket has to share its $2^{31}$ slots with `0` $\rightarrow$ Max positive is $2^{31} - 1$.
- Negative bucket has no zero to share with $\rightarrow$ All $2^{31}$ slots go to negative numbers, reaching $-2^{31}$.

---

## 4. Why Does `unsigned int` Have ~2 Billion Higher Max Value?

Comparing the maximum positive numbers:
- Max `signed int` = $2^{31} - 1 = 2,147,483,647$
- Max `unsigned int` = $2^{32} - 1 = 4,294,967,295$

$$\text{Difference} = (2^{32} - 1) - (2^{31} - 1) = 2^{32} - 2^{31} = 2^{31}(2 - 1) = 2^{31} = 2,147,483,648$$

By sacrificing negative numbers, `unsigned int` reclaims the 31st bit to represent positive magnitude ($+2^{31}$), doubling the positive ceiling from $\approx 2.14 \text{ billion}$ to $\approx 4.29 \text{ billion}$.

---

## 5. Direct Side-by-Side Comparison

| Feature | `unsigned int` | `signed int` (default `int`) |
| :--- | :--- | :--- |
| **Storage** | 4 Bytes (32 bits) | 4 Bytes (32 bits) |
| **Total States** | $2^{32} = 4,294,967,296$ | $2^{32} = 4,294,967,296$ |
| **Sign Bit (MSB)** | None (all 32 bits are magnitude) | 1 bit ($b_{31}$: `0` for $+$, `1` for $-$) |
| **Magnitude Bits**| 32 bits ($b_{31} \dots b_0$) | 31 bits ($b_{30} \dots b_0$) |
| **Min Value** | $0$ | $-2^{31} = -2,147,483,648$ |
| **Max Value** | $2^{32} - 1 = 4,294,967,295$ | $2^{31} - 1 = 2,147,483,647$ |
| **Hex for Min** | `0x00000000` | `0x80000000` |
| **Hex for Max** | `0xFFFFFFFF` | `0x7FFFFFFF` |

<br/>
<br/>

# Time Complexity Analysis of Binary To Decimal (with getPowOf() function)
The UI broke because nesting code blocks (````cpp`) inside an outer markdown code block (````markdown`) closes the markdown block prematurely.

Here is the entire note rendered cleanly as native Markdown with proper headings, code blocks, and math formulas so you can copy and read it seamlessly:

---

## 1. Core Functions Overview

### A. The Power Function (`getPowOf`)

```cpp
int getPowOf(int base, int exponent) {
    int ans = 1;
    for (int i = 0; i < exponent; i++) ans *= base;
    return ans;
}

```

* **Independent Time Complexity:** $O(\text{exponent})$
* **Reason:** The loop executes strictly from `0` to `exponent - 1`, performing a single multiplication each step.

---

### B. The Base Conversion Loop (`binToDec_2`)

```cpp
int binToDec_2(int binaryNo) {
    int ans = 0, i = 0;
    while (binaryNo != 0) {
        int digit = binaryNo % 10;
        ans += getPowOf(2, i++) * digit;
        binaryNo /= 10;
    }
    return ans;
}

```

* **Number of while loop iterations ($k$):**
* In each step, `binaryNo /= 10` repeatedly divides the input $n$ by $10$.
* Repeated division by a constant base yields a logarithmic count of steps.
* The number of digits in $n$ is:



$$k = \lfloor \log_{10} n \rfloor + 1 \approx \log_{10} n$$

* In Big-O notation, we drop the base-10 constant factor:

$$k = O(\log n)$$

---

## 2. The Mental Model: The Warehouse Box Analogy

To avoid double-counting loops, think of time complexity like packing boxes:

* **Outer loop:** How many **boxes** you pack in total ($k$ boxes, where $k = \log_{10} n$).
* **Inner loop / Function call:** How many **items** go inside each box.
* **Total Work:** Total count of all items packed across every single box.

$$\text{Total Work} = \text{Items in Box 1} + \text{Items in Box 2} + \dots + \text{Items in Box } k$$

---

## 3. Case Analysis

### Case 1: Fixed Inner Work (`getPowOf(2, m)`)

Suppose the exponent is a fixed parameter $m$ that does **not** change between iterations:

* Box 1: $m$ items
* Box 2: $m$ items
* Box 3: $m$ items
* ...
* Box $k$: $m$ items

Since every box has the exact same amount of work, you multiply directly:

$$\text{Total Operations} = k \times m$$

Substitute $k = \log n$:

$$\text{Time Complexity} = O(m \cdot \log n)$$

---

### Case 2: Growing Inner Work (`getPowOf(2, i++)`) — Our Scenario

In our code, `i` starts at `0` and increments by `1` on every turn (`i++`):

* Box 1 (`i = 0`): $0$ items
* Box 2 (`i = 1`): $1$ item
* Box 3 (`i = 2`): $2$ items
* Box 4 (`i = 3`): $3$ items
* ...
* Box $k$ (`i = k - 1`): $k - 1$ items

#### Step-by-Step Mathematical Aggregation:

Because the work changes per iteration, we cannot multiply. We sum the items across all $k$ boxes:

$$\text{Total Operations} = 0 + 1 + 2 + 3 + \dots + (k - 1)$$

Using the arithmetic progression sum (Gauss's trick):

$$\sum_{i=0}^{k-1} i = \frac{(k - 1) \cdot k}{2} = \frac{k^2 - k}{2}$$

In asymptotic notation:

* Ignore the lower-order term ($-k$).
* Ignore the constant denominator ($\frac{1}{2}$).
* This yields:

$$\text{Total Operations} = O(k^2)$$

#### The Final Substitution:

* The summation already added up all $k$ boxes. The outer loop is **already accounted for**.
* Now, substitute $k$ with what it physically represents ($k = \log n$):

$$\text{Time Complexity} = O\left((\log n)^2\right)$$

---

## 4. Why $O(\log n) \times O(k^2)$ is a Fallacy (Double Counting)

* **The trap:** Multiplying $\text{outer loop } O(\log n)$ by the summation result $O(k^2)$.
* **Why it's wrong:**
The summation $0 + 1 + 2 + \dots + (k-1)$ has **$k$ terms**. Adding them up already steps through all the outer loop passes.
Multiplying by $\log n$ again counts the outer iterations twice.
* **Correct Rule:**
* If inner work is **constant**: $\text{iterations} \times \text{work per iteration}$
* If inner work **varies**: $\sum (\text{work of each iteration})$, then substitute the variable.



---

## 5. Optimal vs. Sub-Optimal Comparison

| Implementation | Work per Iteration | Total Work Formula | Final Time Complexity | Auxiliary Space | Verdict |
| --- | --- | --- | --- | --- | --- |
| **`binToDec_2` with `getPowOf**` | Increases by $1$ each step | $\sum_{i=0}^{k-1} i = \frac{k(k-1)}{2}$ | $O((\log n)^2)$ | $O(1)$ | Slow; recalculates powers from scratch every step |
| **`binToDec_without_pow` (running `i *= 2`)** | Exactly $1$ operation (`i *= 2`) | $\sum_{i=0}^{k-1} 1 = k$ | $O(\log n)$ | $O(1)$ | **Optimal**; uses result of previous iteration |

<br>
<br>

# Is Two's Complement "Just Theoretical" or How Computers Work?

Computer actually **does** physical Two's Complement inside its hardware (the Arithmetic Logic Unit, or ALU). It is not just theoretical:

1. **When evaluating `~2`:**
* The CPU's NOT gate physically inverts every bit: `0000...0010` $\rightarrow$ `1111...1101`.
* In memory, those bits stay exactly `1111...1101`.


2. **When printing to screen (`cout << ~num`):**
* The standard library needs to print human-readable ASCII characters (`'-'`, `'3'`).
* The CPU looks at the sign bit (MSB). Since it is `1`, the hardware arithmetic unit extracts the magnitude by negating it (inverting bits and adding 1) to get `3`, and prepends the minus sign: **`-3`**.


3. **One correction in your note:**
* You wrote: *"We're ignoring 1st bit... Now take 1's complement of remaining bits..."*
* In standard Two's Complement, **you do not manually skip the first bit during the bit-flip**.
* You invert **all 32 bits**, add 1, and the magnitude pops out automatically:



$$\text{Original: } 1111\dots1101_2$$

$$\text{Flip ALL bits: } 0000\dots0010_2$$

$$\text{Add 1: } 0000\dots0011_2 = 3_{10}$$

$$\text{Append sign: } -3$$
