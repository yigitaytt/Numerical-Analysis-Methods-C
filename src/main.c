#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 256

// Function Prototypes
double log_custom(double, double);
double parse_expr(char **);
double parse_number(char **);
double parse_factor(char **);
double parse_power(char **);
double parse_term(char **);
int is_space(char );
void replace_x(char *, double, char *);
void evaluate_fx();
void bisectionMethod();
void newtonRaphsonMethod();
void regulaFalsiMethod();
double forward_difference(char *, double , double );
double backward_difference(char *, double , double );
double central_difference(char *, double , double );
void printDerivativesAtPoint();
void inverseMatrixMethod();
void trapezMethod();
void choleskyMethod();
void gaussSeidelMethod();
void simpsonMethod();
int gregoryNewtonMethod();

// Helper: Check for whitespace
int is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

// Helper: Custom Logarithm base
double log_custom(double base, double x) {
    return log(x) / log(base);
}

// Parser: Number parsing
double parse_number(char **str) {
    double val = strtod(*str, str);
    return val;
}

// Parser: Factor parsing (parentheses, functions, constants)
double parse_factor(char **str) {
    while (is_space(**str)) (*str)++;

    if (**str == '(') {
        (*str)++;
        double val = parse_expr(str);
        if (**str == ')') (*str)++;
        return val;
    }

    if (strncmp(*str, "sin", 3) == 0) {
        *str += 3;
        return sin(parse_factor(str));
    }

    if (strncmp(*str, "cos", 3) == 0) {
        *str += 3;
        return cos(parse_factor(str));
    }

    if (strncmp(*str, "tan", 3) == 0) {
        *str += 3;
        return tan(parse_factor(str));
    }

    if (strncmp(*str, "asin", 4) == 0) {
        *str += 4;
        return asin(parse_factor(str));
    }

    if (strncmp(*str, "acos", 4) == 0) {
        *str += 4;
        return acos(parse_factor(str));
    }

    if (strncmp(*str, "atan", 4) == 0) {
        *str += 4;
        return atan(parse_factor(str));
    }

    if (strncmp(*str, "e", 1) == 0) {
        *str += 1;
        return M_E; 
    }

    if (strncmp(*str, "pi", 2) == 0) {
        *str += 2;
        return M_PI; 
    }

    if (strncmp(*str, "ln", 2) == 0) {
        *str += 2;
        return log(parse_factor(str));
    }

    if (strncmp(*str, "log_", 4) == 0) {
        *str += 4;
        double base = parse_expr(str);
        if (**str == '(') (*str)++;
        double val = parse_expr(str);
        if (**str == ')') (*str)++;
        return log_custom(base, val);
    }

    if (**str == 'x') {
        (*str)++;
        return NAN;
    }

    return parse_number(str);
}

// Parser: Power operation (^)
double parse_power(char **str) {
    double base = parse_factor(str);
    while (**str == '^') {
        (*str)++;
        double exponent = parse_factor(str);
        base = pow(base, exponent);
    }
    return base;
}

// Parser: Multiplication and Division
double parse_term(char **str) {
    double val = parse_power(str);
    while (**str == '*' || **str == '/') {
        char op = *(*str)++;
        double next = parse_power(str);
        if (op == '*') val *= next;
        else val /= next;
    }
    return val;
}

// Parser: Addition and Subtraction
double parse_expr(char **str) {
    double val = parse_term(str);
    while (**str == '+' || **str == '-') {
        char op = *(*str)++;
        double next = parse_term(str);
        if (op == '+') val += next;
        else val -= next;
    }
    return val;
}

// Helper: Replace 'x' variable with a numeric value in the string
void replace_x(char *input, double x, char *output) {
    char buffer[50];
    sprintf(buffer, "(%lf)", x);

    while (*input) {
        if (*input == 'x') {
            strcat(output, buffer);
            input++;
        } else {
            strncat(output, input, 1);
            input++;
        }
    }
}

// Function to simply evaluate f(x)
void evaluate_fx(){
    char funcInput[MAX_LEN];
    char funcWithX[MAX_LEN * 2] = "";
    double xVal;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0'; 

    printf("Enter value for x: ");
    scanf("%lf", &xVal);
    getchar();

    replace_x(funcInput, xVal, funcWithX);

    char *exprPtr = funcWithX;
    double result = parse_expr(&exprPtr);
    printf("f(%.4lf) = %.8lf\n", xVal, result);
}

void printMenu() {
    printf("\n===== Numerical Methods Menu =====\n");
    printf("1. Bisection Method\n");
    printf("2. Newton-Raphson Method\n");
    printf("3. Regula-Falsi Method\n");
    printf("4. Matrix Inverse\n");
    printf("5. Cholesky Method\n");
    printf("6. Gauss-Seidel Method\n");
    printf("7. Numerical Derivative Method\n");
    printf("8. Simpson Method\n");
    printf("9. Trapezoidal Method\n");
    printf("10. Gregory-Newton Interpolation\n");
    printf("11. Calculate Function Value\n");
    printf("12. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, keepRunning = 1;

    while (keepRunning) {
        printMenu();
        scanf("%d", &choice);
        getchar(); 

        if (choice == 11) {
            evaluate_fx();
        }
        else if (choice == 12) {
            printf("Exiting...\n");
            keepRunning = 0;
        }
        else if (choice == 1) bisectionMethod();
        else if (choice == 2) newtonRaphsonMethod();
        else if (choice == 3) regulaFalsiMethod();
        else if (choice == 4) inverseMatrixMethod();
        else if (choice == 5) choleskyMethod();
        else if (choice == 6) gaussSeidelMethod();
        else if (choice == 7) printDerivativesAtPoint();
        else if (choice == 8) simpsonMethod();
        else if (choice == 9) trapezMethod();
        else if (choice == 10) gregoryNewtonMethod();
        else printf("Invalid selection.\n");
    }

    return 0;
}

void bisectionMethod() {
    char funcInput[MAX_LEN];
    double a, b, tol;
    int iter = 0, maxIter;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0'; 

    printf("Enter initial interval (a and b): ");
    scanf("%lf %lf", &a, &b);
    getchar(); 

    printf("Enter error tolerance: ");
    scanf("%lf", &tol);
    printf("Enter max iterations: ");
    scanf("%d", &maxIter);

    char exprBufferA[MAX_LEN * 2] = "";
    char exprBufferB[MAX_LEN * 2] = "";
    char exprBufferM[MAX_LEN * 2] = "";
    double ya, yb, ym, m;

    replace_x(funcInput, a, exprBufferA);
    char *pa = exprBufferA;
    ya = parse_expr(&pa);

    replace_x(funcInput, b, exprBufferB);
    char *pb = exprBufferB;
    yb = parse_expr(&pb);

    if (ya * yb >= 0) {
        printf("No root in this interval or multiple roots exist.\n");
        return;
    }

    printf("Iter |    a    |    b    |    m    |  f(m)   |   Error\n");
    printf("------------------------------------------------------------\n");

    do {
        m = (a + b) / 2;

        exprBufferM[0] = '\0'; 
        replace_x(funcInput, m, exprBufferM);
        char *pm = exprBufferM;
        ym = parse_expr(&pm);

        printf("%5d     | %.6lf | %.6lf | %.6lf | %.6lf | %.6lf\n",
               iter, a, b, m, ym, fabs(m - a));

        if (fabs(ym) < tol || fabs(b - a) < tol) {
            printf("Root is approximately: %.10lf\n", m);
            return;
        }

        if (ya * ym < 0) {
            b = m;
            yb = ym;
        } else {
            a = m;
            ya = ym;
        }

        iter++;
    } while (iter < maxIter);

    printf("Maximum iterations reached.\n");
}

void newtonRaphsonMethod() {
    char funcInput[MAX_LEN];
    double x0, x1, fx, dfx, h = 1e-6;
    int iter = 0, maxIter;
    double tol;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0';

    printf("Enter initial value x0: ");
    scanf("%lf", &x0);
    getchar();

    printf("Enter error tolerance: ");
    scanf("%lf", &tol);
    getchar();

    printf("Enter max iterations: ");
    scanf("%d", &maxIter);
    getchar();

    printf("Iter |    x    |   f(x)   |  f'(x)   |   Error\n");
    printf("---------------------------------------------------\n");

    do {
        char fxExpr[MAX_LEN * 2] = "";
        replace_x(funcInput, x0, fxExpr);
        char *pfx = fxExpr;
        fx = parse_expr(&pfx);

        // Using central difference for derivative approximation
        dfx = central_difference(funcInput, x0, h);

        if (dfx == 0) {
            printf("Derivative is close to zero, method stopped.\n");
            return;
        }

        x1 = x0 - (fx / dfx);

        printf("%5d     | %.6lf | %.6lf | %.6lf | %.6lf\n",
               iter, x0, fx, dfx, fabs(x1 - x0));

        if (fabs(x1 - x0) < tol) {
            printf("Root is approximately: %.10lf\n", x1);
            return;
        }

        x0 = x1;
        iter++;
    } while (iter < maxIter);

    printf("Maximum iterations reached.\n");
}

void regulaFalsiMethod() {
    char funcInput[MAX_LEN];
    double x0, x1, x2, fx0, fx1, fx2;
    int iter = 0, maxIter;
    double tol;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0';

    printf("Enter initial interval x0: ");
    scanf("%lf", &x0);
    getchar();

    printf("Enter initial interval x1: ");
    scanf("%lf", &x1);
    getchar();

    printf("Enter error tolerance: ");
    scanf("%lf", &tol);
    getchar();

    printf("Enter max iterations: ");
    scanf("%d", &maxIter);
    getchar();

    char expr0[MAX_LEN * 2] = "";
    replace_x(funcInput, x0, expr0);
    char *p0 = expr0;
    fx0 = parse_expr(&p0);
    
    char expr1[MAX_LEN * 2] = "";
    replace_x(funcInput, x1, expr1);
    char *p1 = expr1;
    fx1 = parse_expr(&p1);

    if (fx0 * fx1 > 0) {
        printf("Warning: f(x0) and f(x1) have same signs. Method cannot be applied.\n");
        return;
    }

    printf("Iter |    x0    |    x1    |    x2    |   f(x2)  |   Error\n");
    printf("-----------------------------------------------------------------\n");

    do {
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

        char expr2[MAX_LEN * 2] = "";
        replace_x(funcInput, x2, expr2);
        char *p2 = expr2;
        fx2 = parse_expr(&p2);

        printf("%5d     | %.6lf | %.6lf | %.6lf | %.6lf | %.6lf\n",
               iter, x0, x1, x2, fx2, fabs(fx2));

        if (fabs(fx2) < tol) {
            printf("Root is approximately: %.10lf\n", x2);
            return;
        }

        if (fx0 * fx2 < 0) {
            x1 = x2;
            fx1 = fx2;
        } else {
            x0 = x2;
            fx0 = fx2;
        }

        iter++;
    } while (iter < maxIter);

    printf("Maximum iterations reached.\n");
}

double forward_difference(char *funcInput, double x, double h) {
    char fx1Expr[MAX_LEN * 2] = "", fxExpr[MAX_LEN * 2] = "";
    replace_x(funcInput, x + h, fx1Expr);
    replace_x(funcInput, x, fxExpr);

    char *p1 = fx1Expr;
    char *p = fxExpr;
    double fx1 = parse_expr(&p1);
    double fx = parse_expr(&p);

    return (fx1 - fx) / h;
}

double backward_difference(char *funcInput, double x, double h) {
    char fxExpr[MAX_LEN * 2] = "", fx0Expr[MAX_LEN * 2] = "";
    replace_x(funcInput, x, fxExpr);
    replace_x(funcInput, x - h, fx0Expr);

    char *p = fxExpr;
    char *p0 = fx0Expr;
    double fx = parse_expr(&p);
    double fx0 = parse_expr(&p0);

    return (fx - fx0) / h;
}

double central_difference(char *funcInput, double x, double h) {
    char fx1Expr[MAX_LEN * 2] = "", fx0Expr[MAX_LEN * 2] = "";
    replace_x(funcInput, x + h, fx1Expr);
    replace_x(funcInput, x - h, fx0Expr);

    char *p1 = fx1Expr;
    char *p0 = fx0Expr;
    double fx1 = parse_expr(&p1);
    double fx0 = parse_expr(&p0);

    return (fx1 - fx0) / (2 * h);
}

void printDerivativesAtPoint() {
    char funcInput[MAX_LEN];
    double x, h;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0';

    printf("Enter h value: ");
    scanf("%lf", &h);

    printf("Enter x value for derivative: ");
    scanf("%lf", &x);
    getchar();

    double fwd = forward_difference(funcInput, x, h);
    double bwd = backward_difference(funcInput, x, h);
    double ctr = central_difference(funcInput, x, h);

    printf("\n--- Derivative Approximations ---\n");
    printf("Forward diff: f'(%.5lf) ≈ %.10lf\n", x, fwd);
    printf("Backward diff: f'(%.5lf) ≈ %.10lf\n", x, bwd);
    printf("Central diff:  f'(%.5lf) ≈ %.10lf\n", x, ctr);
}

// Matrix Helpers
void getMinor(double **src, double **dest, int row, int col, int n) {
    int r = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        c = 0;
        for (int j = 0; j < n; j++) {
            if (j == col) continue;
            dest[r][c] = src[i][j];
            c++;
        }
        r++;
    }
}

double determinant(double **mat, int n) {
    if (n == 1) return mat[0][0];

    double det = 0;
    double **minor = (double **)malloc((n - 1) * sizeof(double *));
    for (int i = 0; i < n - 1; i++)
        minor[i] = (double *)malloc((n - 1) * sizeof(double));

    for (int col = 0; col < n; col++) {
        getMinor(mat, minor, 0, col, n);
        double sign = (col % 2 == 0) ? 1 : -1;
        det += sign * mat[0][col] * determinant(minor, n - 1);
    }

    for (int i = 0; i < n - 1; i++) free(minor[i]);
    free(minor);
    return det;
}

double **allocate_matrix(int n) {
    double **mat = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        mat[i] = (double *)malloc(n * sizeof(double));
    return mat;
}

void free_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void adjoint(double **mat, double **adj, int n) {
    double **minor = allocate_matrix(n - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getMinor(mat, minor, i, j, n);
            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant(minor, n - 1); 
        }
    }
    free_matrix(minor, n - 1);
}

void print_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.5lf ", mat[i][j]);
        }
        printf("\n");
    }
}

void inverseMatrixMethod() {
    int n;
    printf("Enter matrix size (N): ");
    scanf("%d", &n);
    getchar();

    double **mat = allocate_matrix(n);
    printf("Enter matrix row by row: \n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &mat[i][j]);
    getchar();

    double det = determinant(mat, n);

    if (fabs(det) < 1e-9) {
        printf("\nMatrix has no inverse. (Determinant = 0)\n");
        free_matrix(mat, n);
        return;
    }

    double **adj = allocate_matrix(n);
    double **inv = allocate_matrix(n);

    adjoint(mat, adj, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = adj[i][j] / det;

    printf("\nInverse Matrix:\n");
    print_matrix(inv, n);

    free_matrix(mat, n);
    free_matrix(adj, n);
    free_matrix(inv, n);
}

void trapezMethod(){
    char funcInput[MAX_LEN];
    int n;
    double a, b, sum = 0.0, fxa, fxb;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0';

    printf("Enter integral interval [a,b]: ");
    scanf("%lf %lf",&a,&b);
    printf("Enter N value: ");
    scanf("%d",&n);

    char exprA[MAX_LEN * 2] = "";
    replace_x(funcInput, a, exprA);
    char *pa = exprA;
    fxa = parse_expr(&pa);

    char exprB[MAX_LEN * 2] = "";
    replace_x(funcInput, b, exprB);
    char *pb = exprB;
    fxb = parse_expr(&pb);
    sum = (fxa + fxb) / (2.0);

    double h = (double) (b-a)/n;
    int i;
    for ( i = 1; i < n; i++) {
        double x = a + i * h;
        char exprX[MAX_LEN * 2] = "";
        replace_x(funcInput, x, exprX);
        char *pX = exprX;
        double fX = parse_expr(&pX);
        sum = sum + fX;
    }
    sum = sum * h;
    printf("Integral Result: %.10lf\n", sum);
}

void choleskyMethod() {
    int n, i, j, k;
    printf("Enter matrix size (n x n): ");
    scanf("%d", &n);

    double **A = allocate_matrix(n);
    double **L = allocate_matrix(n);
    double *C = (double *)malloc(n * sizeof(double));
    double *Y = (double *)malloc(n * sizeof(double));
    double *X = (double *)malloc(n * sizeof(double));

    if (!A || !L || !C || !Y || !X) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter matrix [A] (row by row): \n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("Enter vector [C] (%d elements):\n", n);
    for (i = 0; i < n; i++)
        scanf("%lf", &C[i]);

    // Cholesky Decomposition
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            double sum = 0.0;
            for (k = 0; k < j; k++)
                sum += L[i][k] * L[j][k];

            if (i == j)
                L[i][j] = sqrt(A[i][i] - sum);
            else
                L[i][j] = (1.0 / L[j][j]) * (A[i][j] - sum);
        }
    }

    // Forward Substitution L * Y = C
    for (i = 0; i < n; i++) {
        double sum = 0.0;
        for (j = 0; j < i; j++)
            sum += L[i][j] * Y[j];
        Y[i] = (C[i] - sum) / L[i][i];
    }

    // Backward Substitution L^T * X = Y
    for (i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (j = i + 1; j < n; j++)
            sum += L[j][i] * X[j];  
        X[i] = (Y[i] - sum) / L[i][i];
    }

    printf("Lower Triangular Matrix L:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++)
            printf("%lf ", L[i][j]);
        for (j = i + 1; j < n; j++)
            printf("0.000000 ");
        printf("\n");
    }

    printf("[Y] vector:\n");
    for (i = 0; i < n; i++)
        printf("Y[%d] = %lf\n", i, Y[i]);

    printf("Solution vector [X]:\n");
    for (i = 0; i < n; i++)
        printf("X[%d] = %.6lf\n", i, X[i]);

    free_matrix(A, n);
    free_matrix(L, n);
    free(C);
    free(Y);
    free(X);
}

void swap_rows(double **A, double *C, int row1, int row2, int n) {
    int j;
    double temp;
    for (j = 0; j < n; j++) {
        temp = A[row1][j];
        A[row1][j] = A[row2][j];
        A[row2][j] = temp;
    }
    temp = C[row1];
    C[row1] = C[row2];
    C[row2] = temp;
}

int isRowDiagonallyDominant(double *row, int diagIndex, int n) {
    int j;
    double diag = fabs(row[diagIndex]);
    double sum = 0.0;
    for (j = 0; j < n; j++) {
        if (j != diagIndex)
            sum += fabs(row[j]);
    }
    return diag >= sum;
}

void performPivoting(double **A, double *C, int n) {
    int i, j, found, bestRow;

    for (i = 0; i < n; i++) {
        found = 0;
        bestRow = -1;

        for (j = i; j < n && !found; j++) {
            if (isRowDiagonallyDominant(A[j], i, n)) {
                bestRow = j;
                found = 1;
            }
        }

        if (found && bestRow != i) {
            swap_rows(A, C, i, bestRow, n);
        } else if (!found) {
            printf("Warning: Diagonal dominance could not be established for row %d!\n", i + 1);
        }
    }
}

void gaussSeidelMethod() {
    int i, j, k, n, iteration, maxIter;
    double tol, error, maxError;

    printf("Enter matrix size (n x n): ");
    scanf("%d", &n);

    double **A = allocate_matrix(n);
    double *C = (double *)malloc(n * sizeof(double));
    double *X = (double *)malloc(n * sizeof(double));
    double *oldX = (double *)malloc(n * sizeof(double));

    printf("Enter matrix [A] (row by row): \n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("Enter vector [C] (%d elements):\n", n);
    for (i = 0; i < n; i++)
        scanf("%lf", &C[i]);

    printf("Enter error tolerance: ");
    scanf("%lf", &tol);
    printf("Enter max iterations: ");
    scanf("%d", &maxIter);

    performPivoting(A, C, n);

    for (i = 0; i < n; i++)
        X[i] = 0.0;

    iteration = 0;
    while (iteration < maxIter) {
        for (i = 0; i < n; i++)
            oldX[i] = X[i];

        for (i = 0; i < n; i++) {
            double sum = 0.0;
            for (j = 0; j < n; j++) {
                if (j != i)
                    sum += A[i][j] * X[j];
            }
            X[i] = (C[i] - sum) / A[i][i];
        }

        maxError = 0.0;
        for (i = 0; i < n; i++) {
            error = fabs(X[i] - oldX[i]);
            if (error > maxError)
                maxError = error;
        }

        if (maxError < tol) {
            iteration = maxIter; 
        } else {
            iteration++;
        }
    }

    printf("Solution vector X:\n");
    for (i = 0; i < n; i++)
        printf("X[%d] = %.6lf\n", i, X[i]);

    free_matrix(A, n);
    free(C);
    free(X);
    free(oldX);
}

void simpsonMethod() {
    char funcInput[MAX_LEN];
    double a, b;
    int n, selection;

    printf("Enter the function: ");
    fgets(funcInput, MAX_LEN, stdin);
    funcInput[strcspn(funcInput, "\n")] = '\0'; 

    printf("Enter lower bound: ");
    scanf("%lf", &a);

    printf("Enter upper bound: ");
    scanf("%lf", &b);

    printf("For [Simpson 1/3] press (1), for [Simpson 3/8] press (2): ");
    scanf("%d", &selection);
    
    printf("Enter n value: ");
    scanf("%d", &n);

    double integral_1_3 = 0.0;
    double integral_3_8 = 0.0;

    while(selection == 1){
        double x;
        double fx;
        double h = (b - a) / n;
        for (x = a; x <= b; x += h) {
            char exprBuf[MAX_LEN * 2]="";
            replace_x(funcInput, x, exprBuf);  
            char *ptr = exprBuf; 
            fx = parse_expr(&ptr); 

            printf("Calculated x: %lf, f(x) = %lf\n", x, fx);  

            if (x == a || x == b) {
                integral_1_3 += fx;
            } else if (fmod(x / h, 2) == 0) {
                integral_1_3 += 2 * fx;
            } else {
                integral_1_3 += 4 * fx;
            }
        }

        integral_1_3 *= h / 3;
        selection = 0;   
        printf("Simpson 1/3 rule result: %.6f\n", integral_1_3);
    }

    while(selection == 2){
        double x;
        double fx;
        n *= 3;
        double h = (b - a) / n;
        for (x = a; x <= b; x += h) {
            char exprBuf[MAX_LEN * 2]="";
            replace_x(funcInput, x, exprBuf);
            char *ptr = exprBuf;
            fx = parse_expr(&ptr);

            printf("Calculated x: %lf, f(x) = %lf\n", x, fx);  

            if (x == a || x == b) {
                integral_3_8 += fx;
            } else if (fmod(x / h, 3) == 0 && x!=b) {
                integral_3_8 += 2 * fx;
            } else {
                integral_3_8 += 3 * fx;
            }
        }

        integral_3_8 *= ((3*h)/8);
        selection = 0;
        printf("Simpson 3/8 rule result: %.6f\n", integral_3_8);    
    }
}

double factorial(int n) {
    double f = 1.0;
    int i;
    for (i = 1; i <= n; i++)
        f *= i;
    return f;
}

void gregoryNewtonCalculate(double xValues[], double yValues[], int n, double xInterp) {
    double diffTable[10][10];
    double h, u, result;
    int i, j;

    for (i = 0; i < n; i++)
        diffTable[i][0] = yValues[i];

    for (j = 1; j < n; j++) {
        for (i = 0; i < n - j; i++) {
            diffTable[i][j] = diffTable[i + 1][j - 1] - diffTable[i][j - 1];
        }
    }
    
    h = xValues[1] - xValues[0];
    u = (xInterp - xValues[0]) / h;

    result = yValues[0]; 

    double term = 1.0;
    for (i = 1; i < n; i++) {
        term *= (u - (i - 1));
        result += (term * diffTable[0][i]) / factorial(i);
    }

    printf("Interpolation Result: %.6lf\n", result);
}

int gregoryNewtonMethod() {
    double x[10], y[10];
    int n, i;
    double xInterp;

    printf("Enter number of data points: ");
    scanf("%d", &n);

    printf("Enter X values:\n");
    for (i = 0; i < n; i++)
        scanf("%lf", &x[i]);

    printf("Enter Y values:\n");
    for (i = 0; i < n; i++)
        scanf("%lf", &y[i]);

    printf("Enter x value to interpolate: ");
    scanf("%lf", &xInterp);

    gregoryNewtonCalculate(x, y, n, xInterp);

    return 0;
}