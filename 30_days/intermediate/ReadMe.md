Learning

Does pointer occupy space?
Pointers need space because they store memory addresses.


The (int**) before malloc is a type cast, which explicitly tells the compiler to treat the memory block returned by malloc as a pointer to a pointer to an integer. Let me explain why this is needed:

What malloc returns:
void* malloc(size_t size);   // malloc returns a void pointer (void*)

Why we need the cast:
// Without cast
void* memory = malloc(2 * sizeof(int*));     // Returns generic pointer

// With cast
int** matrix = (int**)malloc(2 * sizeof(int*));  // Converts void* to int**

Think of it like this:

malloc returns a generic pointer (void*)
We need to tell the compiler: "treat this memory block as a pointer to integer pointers"
The cast (int**) does this conversion



The expression matrix[i][j] is equivalent to *(*(matrix + i) + j), which:

Gets the i-th row pointer (*(matrix + i))
Then gets the j-th value in that row (*(pointer + j))

This is why you get the actual value and not an address when using matrix[i][j].
