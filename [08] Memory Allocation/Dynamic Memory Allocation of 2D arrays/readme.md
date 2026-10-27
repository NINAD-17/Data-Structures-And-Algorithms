# Dynamic Memory Allocation in 2D arrays

## How to make 2D arrays dynamically?

**What `arr[3][4]` means?**
- It means that 3 arrays and each has 4 columns in it.
<img src="2D_array_example.png" />

- `int *arr = new int[n]` It means that, bring `n` numbers of `int` blocks.
- We know that arrays are showed by `int*`. So we need multiple `int*` for 2D array. 
- `int **arr = new int*[n]` It means bring multiple `n` numbers of `int*` and store in `int** arr`.

```cpp
    // Creating multiple rows (Or it's just an array but assuming each element of this array as a starting point of new array or a row)
    int **arr = new int*[rows];

    // For each element of that array, assign new array of size 'cols'
    for(int i = 0; i < rows; i++)
        arr[i] = new int[cols];
```

- Visualization:
<img src="2D_array_visualization.png" />

Here for each element of array `arr` we've allocate an array whose first element address will store in `arr`'s elements.

- int **arr = new int*[rows]; Allocates an array of rows pointers. Each element is a pointer to a row, but initially uninitialized.

- arr[i] = new int[cols]; Allocates a row of cols integers and stores its first address in arr[i].

- Visualization (3×3):
```
arr
 ├── arr[0] → [1][2][3]
 ├── arr[1] → [4][5][6]
 └── arr[2] → [7][8][9]
```


## Always Keep in mind to free used heap memory.

```
    // Step 1: First we've deallocate memory taken by each elements array.
    for(int i = 0; i < rows; i++) 
        delete []arr[i];
    
    // Step 2: Release memory of `arr`
    delete []arr;
```

- To release memory of 2D array, 1st we've to release memory of each array which is linked to `arr` elements.
- Then we've to release memory of `arr` array.
- If we did 2nd step first then each arrays memory will not be deleted and all pointers will also lost and you can't access it.
- When dealing with a dynamically allocated 2D array in C++, it’s crucial to first delete the memory allocated for each sub-array (or row), and then delete the memory allocated for the main array (or array of pointers). This is because each sub-array is a separate block of memory on the heap, and deleting the main array only deletes the memory where the pointers to these sub-arrays are stored, not the sub-arrays themselves.
- If you were to delete the main array first, you would lose access to the pointers to the sub-arrays, resulting in a memory leak as you would no longer be able to properly delete the sub-arrays.


## Jagged Arrays
- In computer science, a jagged array is a collection of arrays where each array can contain a different number of elements. Jagged arrays are also known as "ragged arrays" or "irregular arrays".
- Jagged arrays are a special type of multidimensional array where there are a variable number of columns in each row. For example, a 2D array that consists of a different-sized array in every row will be a jagged array.
- Example: arr[][] = { {0, 1, 2}, {6, 4}, {1, 7, 6, 8, 9}, {5} }