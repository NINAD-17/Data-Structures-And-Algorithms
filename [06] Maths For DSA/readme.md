# Maths for DSA

1. Sum of Factors
2. Prime Numbers
3. Count Primes
4. Count primes with multiple testcases
5. Count primes using sieve of eratosthenes
6. Prime Factorization
7. GCD
8. LCM
9. Factorial
10. Fast Exponentiation
11. Inclusive Exclusive Principle
12. Pigeonhole Principle
13. N-th Catalan Number

## Sieve of Eratosthenes
- The Sieve of Eratosthenes is an ancient algorithm used to find all prime numbers up to any given limit
- in `/count_primes.cpp`(brute force approach) code we're calculating each number from `2` to `num` to determine is it prime or not. So time complexity is `O(n^n)`.

- *Sieve of Eratostehnes approach for count_primes problem*
    1. Mark each number as a prime number
    2. Mark non-prime to the numbers which are in table of current selected number except selected number.

### Explaination by Striver:
If a problem provides a  10<sup>6</sup> number of testcases and each number is very close to or equal to a 10<sup>6</sup>.
Then the worst-case scenario becomes, 
```
O(T*sqrt(n)) = O(10^6, sqrt(10^6))
             = 10^6 * 10^3
             = equivalent to 10^9 operations
```
If we assumed 10^8 as 1 second/ 2 second at max then this is going to take 10 seconds and it will give you TLE(time limit exceeded) error. Therefore we've to use Sieve of Erastothenes algorithm.

**Note:** If you define `int` array in main function or any other function then maximum limit is `10^6` and for `bool` it's `10^7`.
But if you define `int` array globally then it's max limit is `10^7` and for `bool` it's `10^8`

### Why outer loop till i*i < n?

> Every composite number has at least one factor ≤ √n. After processing up to √n, all composite numbers are already marked.

### Why inner loop starts from i*i?

> Multiples smaller than i\*i (like 2\*i, 3\*i, etc.) were already marked when processing smaller factors, so starting from i*i avoids redundant work.

> We start from i\*i because every multiple smaller than i\*i can be written as i × k where k < i. Since k was processed earlier, those multiples have already been marked as non-prime. Starting from i*i avoids redundant work.

Example: 
```
i = 5

10 = 2×5  -> already marked by 2
15 = 3×5  -> already marked by 3
20 = 4×5  -> already marked by 2

First new multiple = 5×5 = 25
```

This i*i optimization is what makes Sieve of Eratosthenes much faster than a naive approach.

### Sieve of Eratosthenes VS Segmented Sieve
**Sieve of Eratosthenes**:
- This algorithm creates a list of all integers from 2 to `n`.
- It iteratively marks the multiples of each number starting from 2.
- The numbers that are not marked in the end are the primes.
- The time complexity is **O(n log log n)**.
- The space complexity is **O(n)**, which can be a problem for large `n` as it may not fit in memory.
- when n is large, the Simple Sieve faces the following issues.
    - An array of size Θ(n) may not fit in memory
    - The simple Sieve is not cached friendly even for slightly bigger n. The algorithm traverses the array without locality of reference

## Segmented Sieve
- This algorithm overcomes the space complexity issue of the Sieve of Eratosthenes.
- If we've input `n` very large (say 10<sup>9</sup> or higher) then normal sieve will try to create an array of size `n + 1`. And many programming language environment may not allow to create this big size of array. It's very inefficient, consuming too much memory.
- It divides the range `[0..n-1]` into different segments and computes primes in all segments one by one.
- It first uses the Sieve of Eratosthenes to find primes smaller than or equal to `√(n)`.
- For every segment, it creates an array `mark[high-low+1]` and marks multiples of primes in this range.
- The time complexity remains **O(n log log n)**.
- The space complexity reduces to **O(√n)**, making it more efficient for large `n`.

So, while both algorithms are used for finding prime numbers, the Segmented Sieve is more efficient when dealing with large numbers due to its lower space complexity.


## GCD (Greatest common divisor)/ HCF

It's a one factor which is maximum and can divide both the numbers perfectly and give remainder 0. The GCD of two numbers is the largest number that divides both of them without leaving a remainder.

Example
```
36 = [1, 2, 3, 4, 6, 9, 12, 18, 36] factors
60 = [1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30] factors

Greatest common divisor of 36 and 60 is 12.
```

### Ways to find GCD: 
#### 1. Prime Factorization

<img src="image.png" width=300 alt="GCD/HCF" />
    
In this example, prime factorization approach is used. We get GCD by multiplying common prime factors from both numbers. (refer: `./Prime_Factorization.cpp`)

- Time complexity analysis: 
    for `getPrimeFactors(num)`
    - `k1 = factors1.size();  k2 = factors2.size()`
    - Outer Loop: `for(int i = 2; i * i <= num; i++)` - Runs up to √n → O(√n)
    - Inner Loop: `while(num % i == 0) num /= i;` runs only when i is a prime factor
        - The inner while loop does NOT run for every i.
        - It runs only when i divides the number.
        - And each time it runs, it divides the number by i, reducing it drastically.
        - If the number is like: `n = 2 × 2 × 2 × 2 × ... (log n times)`
            - Then inner loop runs log n times.
            - But this is only for i = 2.
            - For all other i, the inner loop runs 0 or 1 times.
        - So total time complexity: `O(√n)   // outer loop   + O(log n)  // inner loop total work`
        - Since, `log n << √n`, we simplify it to `O(√n)` - Because the loops are not truly nested in the worst-case sense. The inner loop does NOT run `log n` times for every `i`. It runs `log n` times in total, across the entire function.

    - Getting prime factors of num1 → O(√num1)
    - Getting prime factors of num2 → O(√num2)
    - Comparing factors → O(k1 × k2)
    So total: `O(√num1 + √num2 + k1 × k2)`
    - Example: 
        ```
        num1 = 10^12
        num2 = 10^12
        ```
        Then: 
        ```
        √num1 = 10^6
        k1 ≈ log2(10^12) ≈ 40
        ```

        So, `k1 × k2 = 40 × 40 = 1600`
        This is tiny compared to 10^6.
    

#### 2. Brute Force
Traverse till min(num1, num2) to find GCD by checking if number (i) is divisible by both numbers (num1, num2).

#### 3. Euclidean Substraction Method OR Naive Euclidean
Keep subtracting the smaller number from the larger one until both numbers become equal. That final value is the GCD.

**Example: GCD(36, 60)**
```
60 - 36 = 24 → (36, 24)
36 - 24 = 12 → (24, 12)
24 - 12 = 12 → (12, 12)
→ GCD = 12
```

#### 4. Euclidean Algorithm
The Euclidean Algorithm is based on this mathematical identity:
- Formula: `gcd(a, b) = gcd(b, a % b)`
- This means:
    - The first number becomes the second number
    - The second number becomes the remainder
- And this process stops when the remainder becomes 0. Because `gcd(a, 0) = a`

This is a fundamental property of GCD.

Learn more about Euclid's Algorithm at: <a href="https://www.codingninjas.com/studio/library/gcd-euclidean-algorithm">codingninjas.com</a>

Example:
```
GCD(36, 60)

a = 36, b = 60
→ (60, 36 % 60 = 36)

a = 60, b = 36
→ (36, 60 % 36 = 24)

a = 36, b = 24
→ (24, 36 % 24 = 12)

a = 24, b = 12
→ (12, 24 % 12 = 0)

STOP because b == 0
Return a = 12
```

Note:
- The algorithm always stops when the second number becomes 0
- The first number at that moment is the GCD

#### 5. Efficient Approach: Binary GCD algorithm or Stein’s algorithm.
- Initialize a variable shift to count the number of common factors of 2 in `num1` and `num2`
- `((num1 | num2) & 1) == 0` This is a bitwise operation that checks if both numbers are even. Here’s how it works:
    - The `|` operator performs a bitwise `OR` operation. If either of the bits is `1`, the result is `1`. Otherwise, it’s `0`.
    - The `&` operator performs a bitwise `AND` operation. If both bits are `1`, the result is `1`. Otherwise, it’s `0`.
    - In binary, the least significant bit (LSB) of an even number is always `0`. So, `(num1 | num2) & 1` checks the LSB of the result of the bitwise `OR` operation between `num1` and `num2`. If the result is `0`, it means both numbers are even.
- If `num1` is even, divide it by 2 until it becomes odd. Same for `num2` in do-while loop
- Finally, we return the GCD by shifting left num1 by shift bits (i.e., multiplying it by 4).

- **Why we don't use normal operators and used bitwise operators?**
    - The reason we use bitwise operators in the Binary GCD algorithm is because bitwise operations are generally faster than arithmetic operations. Here’s why:

    - Division and modulus operations (/ and %): These operations are relatively slow because they involve multiple steps of subtraction and shifting.

    - Bitwise operations (>>, <<, &, |): These operations are very fast because they directly manipulate the bits of the numbers, and each operation can be done in a single step.

    - In your code, you’re using division by 2 (num1 /= 2; num2 /= 2;) and modulus by 2 (num1 % 2 == 0) to check if a number is even and to halve it. These can be replaced with right shift (num1 >>= 1; num2 >>= 1;) and bitwise AND with 1 (num1 & 1 == 0), respectively, to make the code faster.

    - Also, in your return statement, you’re multiplying num1 by 4 (return num1 * 4;). This can be replaced with left shift by 2 (return num1 << shift;) to multiply num1 by the number of common factors of 2 in the original numbers.

    - So, while your code is correct, using bitwise operators can make it more efficient.

## LCM (Least common multiple)
- It is a method to find the smallest common multiple between any two or more numbers.

- Formula: <br>
    <img src="image-1.png" width=300 />

- `LCM(a, b) * GCD(a, b) = a * b`


## Modular Arithmatics
- Modular arithmetic is a type of arithmetic that deals with numbers that are divided by a certain number, called the modulus. Modular arithmetic involves numbers “wrapping around” upon reaching a certain value, known as the modulus.
- It’s like a clock: when you add 4 hours to 11 o’clock, you get 3 o’clock, not 15 o’clock. This is because clocks “wrap around” every 12 hours
- The modulus is usually a prime number, but it can be any number.
- In modular arithmetic, we only care about the remainder of a division operation, not the quotient.
- Modular arithmetic is useful for a variety of reasons, including simplifying calculations and solving competitive programming problems.
- The result of the expression `n mod m` is known as n's residue modulo m.
- In programming, modular arithmetic is often used for several reasons:
    - To keep numbers within a certain range: If you’re working with an array of size n, you might use the modulus operator to ensure that an index stays within the range 0 to n-1.
    - To prevent overflow: When dealing with large numbers, you can use the modulus operator to prevent the number from exceeding the maximum limit of the data type.
    - To cycle through values: If you want to cycle through a set of values, you can use the modulus operator. For example, in graphics programming, colors might be represented as integers from 0 to 255. If you want to cycle through these colors, you could use the modulus operator.
    - In hash functions: The modulus operator is often used in hash functions to distribute values evenly across an array.

- Answer of `a % n` is always between `0` & `(n - 1)` included.
    `a % n ===> [0 -----> (n - 1)]`

- Learn more about Modulo Operator on: <a href="https://codeforces.com/blog/entry/72527">codeforces.com</a>

- Some important identities about the modulo operator
    - `(a + b) % m = (a % m) + (b % m) % m`
    - `(a - b) % m = (a % m) - (b % m) % m`
    - `(a * b) % m = (a % m) * (b % m) % m`

- That's a great question! In modular arithmetic, it's true that different numbers can have the same remainder when divided by the modulus. For example, if the modulus is 12, then 15 and 3 both have a remainder of 3. 

- However, in many applications of modular arithmetic, this "wrapping around" behavior is exactly what we want. For example, when working with hours on a clock, we don't care about the difference between 3 AM and 3 PM - we just care that they're both "3 hours past the hour". 

- In other cases, we might use modular arithmetic to keep numbers within a certain range to prevent overflow, even though this means that different numbers might map to the same result.

- If we need to differentiate between numbers that have the same remainder when divided by the modulus, then we would need to use a different technique. For example, we might choose a larger modulus, or use a different system altogether.

- In summary, while modular arithmetic does mean that different numbers can map to the same result, this is often a useful property and not a problem. When it is a problem, there are other techniques we can use.

`Factorial.cpp` example:
- Think of “mod” as remainder math.
    - `𝑎 % 𝑚` = the remainder when ``𝑎`` is divided by 𝑚
.

- Examples:
    - 10 % 3 = 1
 (because 10 = 3 ⋅ 3 + 1)17


### Why do we need modulo here? (in calcFactorialUsingModularArithmetics())

- Suppose: 

    ```
    20!
    ```

    ```
    20! = 2432902008176640000
    ```

- Already very large.

- Now imagine:

    ```
    100!
    ```

- or

    ```
    1000!
    ```

- These won't fit even in long long.

- So we do:

    ```
    result = (result * num) % MOD;
    ```

- after every multiplication.

- This keeps the value bounded:
    
    ```
    0 <= result < MOD
    ```

- Note: `10^9 + 7` is a large prime number that fits within a 32-bit signed integer and has useful mathematical properties for modular arithmetic. It is commonly used to prevent overflow while preserving correctness of calculations under modulo.
 

## Fast Exponentiation
- To reduce time complexity of brute force apporoach to find solution of problem `a^b` we use this.
```
        |--> (a^(b/2))^2 -----------> If b is even
a^b ----|
        |--> [(a^(b/2))^2] * a -----> If b is odd
```

![Exponentiation by Squaring](Fast_Exponentiation.png)


## Pigeonhole Principle
- The principle states that if you have more items (pigeons) than containers (pigeonholes), then at least one container must contain more than one item. For example, if you have 10 pigeons and 9 pigeonholes, then at least one pigeonhole must contain more than one pigeon.
- Example: Given that the population of London is greater than the maximum number of hairs that can be present on a human’s head, then the pigeonhole principle requires that there must be at least two people in London who have the same number of hairs on their heads.
- Ex
    ```
    Hole counts after assignment
    Hole 0 → 1 pigeon (ID 8)

    Hole 1 → 2 pigeons (IDs 1, 9)

    Hole 2 → 2 pigeons (IDs 2, 10)

    Hole 3 → 1 pigeon (ID 3)

    Hole 4 → 1 pigeon (ID 4)

    Hole 5 → 1 pigeon (ID 5)

    Hole 6 → 1 pigeon (ID 6)

    Hole 7 → 1 pigeon (ID 7)
    ```


## Inclusive Exclusive Principle
- **Principle**: The Inclusion-Exclusion Principle is a combinatorial way to compute the size of a set or the probability of complex events². It relates the sizes of individual sets with their union².

- **Statement**: To compute the size of a union of multiple sets, it is necessary to sum the sizes of these sets separately, and then subtract the sizes of all pairwise intersections of the sets, then add back the size of the intersections of triples of the sets, subtract the size of quadruples of the sets, and so on, up to the intersection of all sets².

- **Example 1**: How many binary strings of length 8 either start with a ‘1’ bit or end with two bits ’00’?¹
    - If the string starts with one, there are 7 characters left which can be filled in 2^7 = 128 ways.
    - If the string ends with ’00’ then 6 characters can be filled in 2^6 = 64 ways.
    - Strings that start with ‘1’ and end with ’00’ have five characters that can be filled in 2^5 =32 ways.
    - So by the inclusion-exclusion principle we get- Total strings = 128 + 64 – 32 = 160¹

- **Example 2**: How many numbers between 1 and 1000, including both, are divisible by 3 or 4?¹
    - Number of numbers divisible by 3 = floor(1000/3) = 333.
    - Number of numbers divisible by 4 = floor(1000/4) = 250.
    - Number of numbers divisible by both (i.e., divisible by their LCM which is 12) = floor(1000/12) = 83.
    - Therefore, number of numbers divisible by either 3 or 4 = 333 + 250 – 83 = 500¹



## Catalan Numbers ($C_n$)

The Catalan numbers form a sequence of natural numbers that appear repeatedly in combinatorics. In simple terms: it counts how many valid structures you can form under symmetrical pairing constraints.

A sequence of positive integers that solves recursive structural combination problems.

<a href="https://youtu.be/0pTN0qzpt-Y">Refer this video to understand Catalan Numbers</a>

### Sequence
`1, 1, 2, 5, 14, 42, 132, 429, 1430, ...`
- $C_0 = 1, \quad C_1 = 1$

---

### Core Recurrence Formula
$$C_n = \sum_{j=0}^{n-1} C_j \cdot C_{n - 1 - j}$$

- $C_2 = C_0 C_1 + C_1 C_0 = 1(1) + 1(1) = 2$
- $C_3 = C_0 C_2 + C_1 C_1 + C_2 C_0 = 1(2) + 1(1) + 2(1) = 5$

---

### Direct Formula (Combinatorics)
$$C_n = \frac{1}{n + 1} \binom{2n}{n} = \frac{(2n)!}{(n + 1)! \; n!}$$

---

### Where It Appears in DSA
1. **Count Unique BSTs:** Number of structurally unique BSTs with $n$ keys.
2. **Balanced Parentheses:** Number of valid expressions using $n$ pairs of `()`.
3. **Mountain Ranges:** Number of up/down stroke paths of length $2n$ that never cross below the horizon.
4. **Matrix Chain Multiplication:** Number of ways to parenthesize the product of $n + 1$ matrices.

---

### Complexity (DP Approach)
- **Time Complexity:** $O(n^2)$ (two nested loops)
- **Space Complexity:** $O(n)$ (DP array `res`)