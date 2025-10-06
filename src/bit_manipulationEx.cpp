#include <iostream>
#include <bitset>    // For std::bitset to easily print binary representations
#include "helloEx.h" // for printLine
#include "bit_manipulationEx.h"

/**
 * @brief Prints the binary representation of an 8-bit number.
 * @param n The number to print in binary.
 * @param title A descriptive title to print before the binary string.
 */
void printBinary(unsigned char n, const std::string& title) {
    std::cout << title << ": " << std::bitset<8>(n) << " (Decimal: " << static_cast<int>(n) << ")" << std::endl;
}

void bit_manipulationEx(void) {
    printLine("Bit Manipulation Example");

    // We'll use an unsigned char (8 bits) for simplicity.
    unsigned char flags = 0b00001010; // Initial value: 10 in decimal
    printBinary(flags, "Initial flags  ");
    std::cout << std::endl;

    // --- 1. Setting a bit (turning a bit ON) ---
    // To set the 3rd bit (from the right, 0-indexed), we use the OR operator with a mask.
    // The mask is created by left-shifting 1 by 3 positions: 1 << 3  (which is 0b00001000)
    std::cout << "--- 1. Setting bit 3 ---\n";
    unsigned char mask_on = 1 << 3;
    printBinary(mask_on, "Mask (1 << 3)  ");
    flags = flags | mask_on;
    printBinary(flags, "Result (flags|mask)");
    std::cout << std::endl;

    // --- 2. Clearing a bit (turning a bit OFF) ---
    // To clear the 1st bit, we use the AND operator with an inverted mask.
    // The mask is ~(1 << 1). 1 << 1 is 0b00000010, so ~(1 << 1) is 0b11111101.
    std::cout << "--- 2. Clearing bit 1 ---\n";
    unsigned char mask_off = ~(1 << 1);
    printBinary(mask_off, "Mask (~(1 << 1))");
    flags = flags & mask_off;
    printBinary(flags, "Result (flags&mask)");
    std::cout << std::endl;

    // --- 3. Toggling a bit (flipping its value) ---
    // To toggle the 4th bit, we use the XOR operator.
    std::cout << "--- 3. Toggling bit 4 ---\n";
    
    unsigned char mask_toggle = 1 << 4;
    flags = 0b00001010;

    printBinary(mask_toggle, "Mask (1 << 4)      ");
    printBinary(flags, "        flags      ");
    flags = flags ^ mask_toggle;
    printBinary(flags, "Result (flags^mask)");
    
    std::cout << "Toggling it again...\n";
    flags = flags ^ mask_toggle;
    printBinary(flags, "Result (flags^mask)");
    std::cout << std::endl;

    // --- 4. Checking a bit ---
    // To check if the 3rd bit is set.
    std::cout << "--- 4. Checking bit 3 ---\n";
    unsigned char mask_check = 1 << 3;
    bool is_bit_3_set = (flags & mask_check) != 0;
    printBinary(flags, "Flags          ");
    printBinary(mask_check, "Mask (1 << 3)  ");
    std::cout << "Is bit 3 set? " << (is_bit_3_set ? "Yes" : "No") << std::endl;
}