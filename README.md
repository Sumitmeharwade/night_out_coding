
# Nightout Coding Challenge - Insignia 2024

## Overview

This repository contains a C++ program for encrypting and decrypting text files using two algorithms: **xrot** and **xplus**. Created for the *Insignia 2024 Nightout Coding Challenge*, this program enables secure file storage.

## Features

- **Two Modes**: Encrypt and decrypt text files using a password.
- **Algorithm Choice**: Select between `xrot` (bitwise rotation) or `xplus` (numeric transformation).

### Command-Line Arguments

| Argument | Description |
|----------|-------------|
| `--encrypt` or `--decrypt` | Action to perform |
| `--xrot` or `--xplus`      | Algorithm to use |
| `password`                 | Numeric password |
| `input file path`          | Path to input file |
| `output file path`         | Path to output file |

### Algorithms

1. **xrot Encryption**: Concatenates the password to match input length, then bitwise rotates each character based on the password.
2. **xplus Encryption**: Concatenates the password to match input length, then modifies each character using `(A[i] + i * B[i])`.

### Usage

1. Compile the program:

   ```bash
   g++ app.cpp -o encryptor
   ```

2. Run the program:

   ```bash
   ./encryptor --encrypt --xrot 3648 input.txt output.txt
   ```

