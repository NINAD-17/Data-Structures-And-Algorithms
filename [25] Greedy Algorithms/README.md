# Greedy Algorithms

It's a programming technique where we find optimal solution at that particular movement. It doesn't guarantee about getting optimal solution for entire problem. It's optimal solution for that particular movement.

## Maximum Number Of Events That Can Be Attended

Step-by-Step Dry Run of findParent() and the Loop

Let’s trace with this concrete input:

```
events = [[1, 2], [1, 2], [1, 3]]
```

After sorting by endDay (and then startDay):

- Event 0: [1, 2]

- Event 1: [1, 2]

- Event 2: [1, 3]

Here, $\max(endDay) = 3$, so maxDay = 3.

We allocate parent of size $\text{maxDay} + 2 = 5$ (indices 0 to 4)

```
Initial Parent Array:
Index (Day):   [0]   [1]   [2]   [3]   [4]
Parent value:   0     1     2     3     4

```
Rule: If parent[d] == d, it means Day d is free.

### Iteration 1: Event 0 = [1, 2] (start = 1, end = 2)

```
int freeDay = findParent(1, parent);
```

1. findParent(1) checks: Is parent[1] == 1? Yes!

2. It immediately returns 1.

3. Check if (freeDay <= end): $1 \le 2$ $\rightarrow$ Valid!

4. We attend Event 0 on Day 1. attended++ (now 1).

5. Book Day 1:
    ```
    parent[1] = findParent(1 + 1, parent); // findParent(2) -> returns 2
    ```
    
    So parent[1] becomes 2!PlaintextState after Event 0:

    ```
    Index (Day):   [0]   [1]   [2]   [3]   [4]
    Parent value:   0     2     2     3     4
                        ^
                Day 1 now points to Day 2!
    ```

### Iteration 2: Event 1 = [1, 2] (start = 1, end = 2)

```
int freeDay = findParent(1, parent);
```

Watch the recursion happen:

1. Call findParent(1):
    
    - Is parent[1] == 1? No, parent[1] is 2.
    
    - It makes recursive call: findParent(2).
    
2. Inside findParent(2):

    - Is parent[2] == 2? Yes!
    
    - Returns 2.

3. Back in findParent(1):

    - Path Compression line: parent[1] = 2.
    
    - Returns 2.
    
4. freeDay = 2.

5. Check if (freeDay <= end): $2 \le 2$ $\rightarrow$ Valid!

6. We attend Event 1 on Day 2. attended++ (now 2).

7. Book Day 2:
    ```
    parent[2] = findParent(2 + 1, parent); // findParent(3) -> returns 3
    ```
    
    So parent[2] becomes 3!PlaintextState after Event 1:

    ```
    Index (Day):   [0]   [1]   [2]   [3]   [4]
    Parent value:   0     2     3     3     4
                                ^
                    Day 2 points to 3!
    ```

### Iteration 3: Event 2 = [1, 3] (start = 1, end = 3)

Event 2 also wants to start at Day 1:

```
int freeDay = findParent(1, parent);
```

Watch how Path Compression "teleports" past already booked days:

1. Call findParent(1):
    
    - parent[1] is 2.
    
    - Calls findParent(2).
    
2. Inside findParent(2):
    
    - parent[2] is 3.
    
    - Calls findParent(3).
    
3. Inside findParent(3):

    - parent[3] == 3 is true!
    
    - Returns 3.
    
4. Back in findParent(2):

    - parent[2] = 3 (stores it).
    
    - Returns 3.
    
5. Back in findParent(1):

    - Compression in action: parent[1] = 3.
    
    - Next time anything asks about Day 1, it will jump directly to Day 3 without even touching Day 2!
    
6. freeDay = 3.

7. Check if (freeDay <= end): $3 \le 3$ $\rightarrow$ Valid!

8. Attend Event 2 on Day 3. attended++ (now 3).

9. Book Day 3:

```
parent[3] = findParent(4); // returns 4
PlaintextFinal State:
Index (Day):   [0]   [1]   [2]   [3]   [4]
Parent value:   0     3     3     4     4
                      ^-----^
    Both Day 1 and Day 2 point straight to 3, and 3 points to 4!
```

Final answer returned: 3.

### What Happens If No Day is Available?

Suppose a 4th event arrived: [1, 2].

1. It calls findParent(1).

2. parent[1] points to 3, parent[3] points to 4 $\rightarrow$ returns 4.

3. Check if (freeDay <= end):

    - freeDay = 4, but end = 2.
    
    - $4 \le 2$ is false!
    
- The event is skipped because the earliest free slot (Day 4) is past its deadline.