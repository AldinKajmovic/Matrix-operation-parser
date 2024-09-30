
## Overview

This project implements a `Matrica` class for matrix operations in C++. The class handles matrices as vectors of vectors with `double` values, allowing for decimal entries. While most functions are private to restrict access to the user, public operators and methods provide the necessary functionality.

## Work in Progress

Please note that this project is a work in progress and is not 100% complete. Features and functionalities are being continuously developed and refined.

## Features

- **Matrix Addition and Subtraction**: 
  - `dodaj`: Adds two matrices and stores the result in a third matrix.
  - `oduzmi`: Subtracts one matrix from another, ensuring they have the same dimensions.

- **Scalar Multiplication**: 
  - `pomnoziBrojem`: Multiplies each element of the matrix by a given scalar.

- **Matrix Transposition**: 
  - `transponuj`: Transposes the matrix, swapping rows and columns, regardless of dimensions.

- **Matrix Exponentiation**: 
  - `stepenuj`: Raises the matrix to a specified power using an efficient algorithm to minimize multiplications.

- **Identity Matrix Generation**: 
  - `jedinicnaMatrica`: Generates an identity matrix of the same dimensions as the input matrix.

- **Operations Execution**: 
  - `izvršiOperaciju`: Supports multiple versions for matrix operations.

- **Input and Output Handling**: 
  - `>>` and `<<` operators for reading and displaying matrices.

- **Advanced Multiplication**: 
  - Utilizes Strassen’s algorithm for efficient matrix multiplication.

- **Inverse Matrix Calculation**: 
  - Implements the Gauss-Jordan method for finding the inverse of matrices.

- **Determinant Calculation**: 
  - Uses LU decomposition to compute the determinant of a matrix.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/AldinKajmovic/Matrix-opereation-parser.git
   cd Matrix-opereation-parser

Usage

You can create a Matrica object and perform various operations using the provided methods. Here’s a simple example:



Matrica A, B, C;
cin >> A;
cout<< A;
