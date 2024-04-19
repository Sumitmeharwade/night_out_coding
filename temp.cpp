#include <iostream>
#include <bitset> // Include the bitset library for binary representation

std::string charToBinary(char c) {
    // Cast the character to an integer to get its ASCII value
    int decimalValue = static_cast<int>(c);
    // Convert the decimal value to binary using bitset
    std::bitset<8> binary(decimalValue);
    // Convert the binary representation to a string and return it
    return binary.to_string();
}
uint32_t rotr32 (uint32_t value, unsigned int count) {
    const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
    count &= mask;
    return (value >> count) | (value << (-count & mask));
}
int main() {
    char inputChar;
    std::cout << "Enter a character: ";
    std::cin >> inputChar;

    std::string binaryValue = charToBinary(inputChar);
    std::cout << "Binary value of '" << inputChar << "' is: " << binaryValue << std::endl;

    // Convert the binary value to an integer before passing it to rotr32
    uint32_t binaryInt = std::bitset<32>(binaryValue).to_ulong();
    // int x=4;
    // unsigned int unsignedX = static_cast<unsigned int>(x);
    std::cout << "rotr32: " << rotr32(binaryInt, 1) << std::endl;

    return 0;
}
