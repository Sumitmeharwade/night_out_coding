#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;
string charToBinary(char c) {
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
uint32_t rotl32 (uint32_t value, unsigned int count) {
    const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
    count &= mask;
    return (value << count) | (value >> (-count & mask));
}

// Base class for encryption algorithms
class EncryptionAlgorithm {
public:
    virtual void encrypt(const string& password, const string& inputPath, const string& outputPath) = 0;
    virtual void decrypt(const string& password, const string& inputPath, const string& outputPath) = 0;
};

// Class for XROT encryption/decryption
class XROT : public EncryptionAlgorithm {
public:
    

    void encrypt(const string& password, const string& inputPath, const string& outputPath) {
        // Read input string from file
        ifstream inputFile(inputPath);
        if (!inputFile.is_open()) {
            cerr << "Unable to open input file." << endl;
            return;
        }
        string inputString;
        string line;
        while (getline(inputFile, line)) {
            inputString += line +"\n";
        }
        inputString.pop_back();
        inputFile.close();

        // Step 1: Concatenate password to match the length of input string
        string concatenatedPassword;
        int passwordIndex = 0;
        for (char c : inputString) {
            concatenatedPassword += password[passwordIndex % password.length()];
            passwordIndex++;
        }

        // Step 2: Bitwise rotate each character of input string
        string encryptedString = "";
        string convertedString = "";
        for (int i = 0; i < inputString.length(); ++i) {
            char originalChar = inputString[i];
            char passwordChar = concatenatedPassword[i];

            // Convert original character to its binary representation
            string originalBinary = "";
            for (int j = 7; j >= 0; --j) {
                originalBinary += ((originalChar >> j) & 1) ? '1' : '0';
            }

            // Determine rotation count based on password character
            int rotationCount = passwordChar % 8;

            // Bitwise rotation to the right
            string rotatedBinary = "";
            for (int j = 0; j < 8; ++j) {
                rotatedBinary += originalBinary[(j - rotationCount + 8) % 8];
            }

            // Convert rotated binary back to decimal and append to encrypted string
            int rotatedDecimal = stoi(rotatedBinary, nullptr, 2);
            encryptedString += to_string(rotatedDecimal) + " ";

            // Append the converted character to the converted string
            convertedString += static_cast<char>(rotatedDecimal);
        }

        // Write encrypted output string to output file
        ofstream outputFile(outputPath);
        if (outputFile.is_open()) {
            // outputFile << "Encrypted string (in decimal): " << encryptedString << endl;
            // outputFile << "Converted string: " << convertedString << endl;
            outputFile <<  convertedString ;
            outputFile.close();
            cout << "Encryption completed. Check output file: " << outputPath << endl;
        } else {
            cerr << "Unable to open output file." << endl;
        }
    }

    void decrypt(const string& password, const string& inputPath, const string& outputPath) override {
        // Read input string from file
        ifstream inputFile(inputPath);
        if (!inputFile.is_open()) {
            cerr << "Unable to open input file." << endl;
            return;
        }
        string inputString;
        string line;
        while (getline(inputFile, line)) {
            inputString += line +"\n";
        }
        inputString.pop_back();
        inputFile.close();

        // Step 1: Concatenate password to match the length of input string
        string concatenatedPassword;
        int passwordIndex = 0;
        for (char c : inputString) {
            concatenatedPassword += password[passwordIndex % password.length()];
            passwordIndex++;
        }

        // Step 2: Bitwise rotate each character of input string
        string encryptedString = "";
        string convertedString = "";
        for (int i = 0; i < inputString.length(); ++i) {
            char originalChar = inputString[i];
            char passwordChar = concatenatedPassword[i];

            // Convert original character to its binary representation
            string originalBinary = "";
            for (int j = 7; j >= 0; --j) {
                originalBinary += ((originalChar >> j) & 1) ? '1' : '0';
            }

            // Determine rotation count based on password character
            int rotationCount = passwordChar % 8;

            // Bitwise rotation to the right
            string rotatedBinary = "";
            for (int j = 0; j < 8; ++j) {
                rotatedBinary += originalBinary[(j + rotationCount) % 8];
            }

            // Convert rotated binary back to decimal and append to encrypted string
            int rotatedDecimal = stoi(rotatedBinary, nullptr, 2);
            encryptedString += to_string(rotatedDecimal) + " ";

            // Append the converted character to the converted string
            convertedString += static_cast<char>(rotatedDecimal);
        }

        // Write encrypted output string to output file
        ofstream outputFile(outputPath);
        if (outputFile.is_open()) {
            // outputFile << "Encrypted string (in decimal): " << encryptedString << endl;
            // outputFile << "Converted string: " << convertedString << endl;
            outputFile << convertedString ;
            outputFile.close();
            cout << "Decryption completed. Check output file: " << outputPath << endl;
        } else {
            cerr << "Unable to open output file." << endl;
        }
    }

private:
    void displayFileContents(const string& filePath) {
        ifstream inputFile(filePath);
        int charCount = 0;
        if (inputFile.is_open()) {
            string line;
             // Variable to count characters
            cout << "Contents of " << filePath << ":" << endl;
            while (getline(inputFile, line)) {
                cout << line << endl;
                charCount += line.size(); // Add the length of each line to charCount
            }
            inputFile.close();
            cout << "Number of characters in the file: " << charCount << endl;
        } else {
            cerr << "Unable to open file: " << filePath << endl;
        }

        // cout<<"pass:: "<<concatenatePassword(charCount, "3648")<<endl;
    }
    
};

// Class for XPLUS encryption/decryption
class XPLUS : public EncryptionAlgorithm {
public:
    void encrypt(const std::string& password, const std::string& inputPath, const std::string& outputPath) {
    // Read input string from file
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file." << std::endl;
        return;
    }
    std::string inputString;
    string line;
        while (getline(inputFile, line)) {
            inputString += line +"\n";
        }
        inputString.pop_back();
    inputFile.close();

    // Step 1: Concatenate password to match the length of input string
    std::string concatenatedPassword;
    int passwordIndex = 0;
    for (char c : inputString) {
        concatenatedPassword += password[passwordIndex % password.length()];
        passwordIndex++;
    }

    // Step 2: Encrypt each character of input string
    std::string encryptedString = "";
    for (int i = 0; i < inputString.length(); ++i) {
        char originalChar = inputString[i];
        char passwordChar = concatenatedPassword[i];
        
        // Convert passwordChar to its ASCII value
        int passwordCharValue = int(passwordChar)-48;
        
        // Encrypt using the formula
        inputString[i] = originalChar + (i * passwordCharValue);

        cout<<"inputString[i]: "<<inputString[i]<<endl;
        // Append the encrypted character to the encrypted string
        encryptedString += inputString[i];
    }

    // Write encrypted output string to output file
    std::ofstream outputFile(outputPath);
    if (outputFile.is_open()) {
        outputFile << encryptedString ;
        outputFile.close();
        std::cout << "Encryption completed. Check output file: " << outputPath << std::endl;
    } else {
        std::cerr << "Unable to open output file." << std::endl;
    }
}

    
    void decrypt(const std::string& password, const std::string& inputPath, const std::string& outputPath) {
    // Read input string from file
    std::ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file." << std::endl;
        return;
    }
    std::string inputString;
    string line;
        while (getline(inputFile, line)) {
            inputString += line +"\n";
        }
        inputString.pop_back();
    inputFile.close();

    // Step 1: Concatenate password to match the length of input string
    std::string concatenatedPassword;
    int passwordIndex = 0;
    for (char c : inputString) {
        concatenatedPassword += password[passwordIndex % password.length()];
        passwordIndex++;
    }

    // Step 2: Encrypt each character of input string
    std::string encryptedString = "";
    for (int i = 0; i < inputString.length(); ++i) {
        char originalChar = inputString[i];
        char passwordChar = concatenatedPassword[i];
        
        // Convert passwordChar to its ASCII value
        int passwordCharValue = int(passwordChar)-48;
        
        // Encrypt using the formula
        inputString[i] = originalChar - (i * passwordCharValue);

        cout<<"inputString[i]: "<<inputString[i]<<endl;
        // Append the encrypted character to the encrypted string
        encryptedString += inputString[i];
    }

    // Write encrypted output string to output file
    std::ofstream outputFile(outputPath);
    if (outputFile.is_open()) {
        outputFile << encryptedString ;
        outputFile.close();
        std::cout << "Decryption completed. Check output file: " << outputPath << std::endl;
    } else {
        std::cerr << "Unable to open output file." << std::endl;
    }
}

private:
    void displayFileContents(const string& filePath) {
        ifstream inputFile(filePath);
        if (inputFile.is_open()) {
            string line;
            int charCount = 0; // Variable to count characters
            cout << "Contents of " << filePath << ":" << endl;
            while (getline(inputFile, line)) {
                cout << line << endl;
                charCount += line.size(); // Add the length of each line to charCount
            }
            inputFile.close();
            cout << "Number of characters in the file: " << charCount << endl;
        } else {
            cerr << "Unable to open file: " << filePath << endl;
        }
    }
};

string concatenatePassword(int num, const string& password) {
    int passwordLength = password.length();
    string newPassword;

    if (passwordLength >= num) {
        // If password length is greater than or equal to num, just return the password
        return password.substr(0, num);
    }

    // Calculate how many times to repeat the password
    int repeatCount = num / passwordLength;
    int remainder = num % passwordLength;

    // Concatenate the password to itself
    for (int i = 0; i < repeatCount; ++i) {
        newPassword += password;
    }

    // Append the remaining characters if necessary
    if (remainder > 0) {
        newPassword += password.substr(0, remainder);
    }

    return newPassword;
}

string displayFileContents(const string& filePath, const string& password) {
    ifstream inputFile(filePath);
    int charCount = 0;
    if (inputFile.is_open()) {
        string line;
            // Variable to count characters
        cout << "Contents of " << filePath << ":" << endl;
        while (getline(inputFile, line)) {
            cout << line << endl;
            charCount += line.size(); // Add the length of each line to charCount
        }
        inputFile.close();
        cout << "Number of characters in the file: " << charCount << endl;
    } else {
        cerr << "Unable to open file: " << filePath << endl;
    }

    cout<<"pass:: "<<concatenatePassword(charCount, password)<<endl;
    return concatenatePassword(charCount, password);
}

int main(int argc, char* argv[]) {
    // Check if there are enough command-line arguments
    if (argc != 6) {
        cerr << "Please use the appropriate format :\nUsage: " << argv[0] << " --encrypt/--decrypt --xrot/--xplus password input_path output_path" << endl;
        return 1;
    }

    string operation = argv[1];
    string algorithm = argv[2];
    string password = argv[3];
    string inputPath = argv[4];
    string outputPath = argv[5];

    // Validate if the password is between 0-9
    for (char c : password) {
        if (c < '0' || c > '9') {
            cerr << "Invalid password. Password should only contain digits from 0 to 9." << endl;
            return 1;
        }
    }

    // Check operation and algorithm, then create appropriate object
    EncryptionAlgorithm* encryptionObject = nullptr;
    if (operation == "--encrypt") {
        if (algorithm == "--xrot") {
            encryptionObject = new XROT();
        } else if (algorithm == "--xplus") {
            encryptionObject = new XPLUS();
        } else {
            cerr << "Invalid encryption algorithm specified" << endl;
            return 1;
        }
    } else if (operation == "--decrypt") {
        if (algorithm == "--xrot") {
            encryptionObject = new XROT();
        } else if (algorithm == "--xplus") {
            encryptionObject = new XPLUS();
        } else {
            cerr << "Invalid encryption algorithm specified" << endl;
            return 1;
        }
    } else {
        cerr << "Invalid operation specified. Use --encrypt or --decrypt" << endl;
        return 1;
    }



    //password contatination
    password = displayFileContents(inputPath, password);


    // Perform encryption or decryption
    if (operation == "--encrypt") {
        encryptionObject->encrypt(password, inputPath, outputPath);
    } else if (operation == "--decrypt") {
        encryptionObject->decrypt(password, inputPath, outputPath);
    }

    delete encryptionObject;
    
    return 0;
}