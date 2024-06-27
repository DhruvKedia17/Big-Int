BigInt Operations

This program provides functionalities to perform arithmetic operations on arbitrarily large integers, termed as BigInt. BigInt allows handling integers beyond the standard range of data types by storing them in an array of digits. Operations such as addition, subtraction, and multiplication are supported.


Features
BigInt Representation:

BigInts are represented using a sign flag and an array of integers.
Each BigInt can hold integers of arbitrary length.
Supported Operations:

Addition: Adds two BigIntegers.
Subtraction: Subtracts one BigInt from another.
Multiplication: Multiplies two BigIntegers.
Error Handling:

Proper error messages are displayed if invalid inputs are provided.
Optimized Storage:

Utilizes a modular approach to store large numbers, optimizing memory usage.
Code Overview
convertIntoNum: Converts a string representation of a number into a BigInt.
addition: Adds two BigIntegers.
substraction: Subtracts one BigInt from another.
multiply: Multiplies two BigIntegers.
Conventions
The sign of a number is represented as 0 for positive and 1 for negative.
Sign is required when passing numbers as input.
The base used for calculations is 10^9 to optimize storage.
Limitations
Division operation is not implemented.
Numbers must fit within the constraints of available memory.
Future Improvements
Addition of division functionality.
Optimization for faster execution.
