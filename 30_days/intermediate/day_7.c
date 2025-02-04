#include <stdio.h>

// Function prototypes
unsigned int setBit(unsigned int num, int position);
unsigned int clearBit(unsigned int num, int position);
unsigned int toggleBit(unsigned int num, int position);
unsigned int getBit(unsigned int num, int position);
void printBinary(unsigned int num);

int main() {
    unsigned int number = 101;  // Binary: 01100101
    int position = 3;
    
    printf("Original number: ");
    printBinary(number);
    
    // Set bit at position 3
    number = setBit(number, position);
    printf("After setting bit %d: ", position);  // 01101101 
    printBinary(number);
    
    // Clear bit at position 3
    number = clearBit(number, position);
    printf("After clearing bit %d: ", position);  // 01100101 
    printBinary(number);
    
    // Toggle bit at position 3
    number = toggleBit(number, position);
    printf("After toggling bit %d: ", position);  // 01101101
    printBinary(number);
    
    return 0;
}

// Set a bit at given position to 1
unsigned int setBit(unsigned int num, int position) {
    return num | (1 << position);
}

// Clear a bit at given position (set to 0)
unsigned int clearBit(unsigned int num, int position) {
    return num & ~(1 << position);
}

// Toggle a bit at given position
unsigned int toggleBit(unsigned int num, int position) {
    return num ^ (1 << position);
}

// Get the value of a bit at given position
unsigned int getBit(unsigned int num, int position) {
    return (num >> position) & 1;
}

// Helper function to print binary representation
void printBinary(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}
