# Numerical Analysis Methods Calculator in C

This project is a comprehensive Numerical Analysis tool written in C. It allows users to perform various numerical methods, matrix operations, and integration calculations through a command-line interface.

## 🚀 Features

The application supports the following methods:

### 🧮 Advanced Expression Parser
* **Dynamic Input:** Users can input mathematical functions as strings (e.g., `sin(x) + x^2 - 4*log(x)`) directly from the console. No hardcoding required!
* **Supported Operators:** `+`, `-`, `*`, `/`, `^` (power).
* **Supported Functions:** `sin`, `cos`, `tan`, `asin`, `acos`, `atan`, `ln`, `log_base`, `exp`.
* **Constants:** Supports `pi` and `e`.

### Root Finding Methods
* **Bisection Method:** Finds roots by repeatedly bisecting an interval.
* **Newton-Raphson Method:** Uses linear approximation to find roots using derivatives.
* **Regula-Falsi Method:** A bracketing method for finding roots.

### Linear Algebra & Matrix Operations
* **Inverse Matrix Calculation:** Computes the inverse of an NxN matrix.
* **Cholesky Decomposition:** Solves systems of linear equations.
* **Gauss-Seidel Method:** Iterative method to solve a linear system of equations (includes pivoting).

### Numerical Integration & Differentiation
* **Numerical Derivative:** Calculates Forward, Backward, and Central differences.
* **Simpson's Rule:** Implements both 1/3 and 3/8 rules for integration.
* **Trapezoidal Rule:** Approximates the definite integral.
* **Gregory-Newton Interpolation:** Computes intermediate values using forward differences.

## 🛠️ Technology Stack

* **Language:** C
* **Standard Libraries:** `stdio.h`, `stdlib.h`, `math.h`, `string.h`
* **Custom Parser:** Built-in recursive descent parser to handle complex mathematical expressions.


## 👤 Author

**Yiğit Aytürk**
* Computer Engineering Student at YTÜ
* GitHub: [yigitaytt](https://github.com/yigitaytt)
