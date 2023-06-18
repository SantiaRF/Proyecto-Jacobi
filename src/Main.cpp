#include <iostream>
#include <iomanip>
#include <cmath>
#include <Jacobiperron.hpp>

int main() {
    int size;
    double tol = 1e-6;
    int maxIter = 100;

    std::cout << "Ingrese el tamano de la matriz (2-5): ";
    std::cin >> size;

    // Verificar tamaño válido
    if (size < 2 || size > 5) {
        std::cout << "Tamano de matriz invalido." << std::endl;
        return 1;
    }

    Jacobiperron solver(size, tol, maxIter);

    // Ingresar coeficientes de la matriz
    std::cout << "Ingrese los coeficientes de la matriz A:" << std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double value;
            std::cout << "A[" << i << "][" << j << "]: ";
            std::cin >> value;
            solver.setMatrixCoefficient(i, j, value);
        }
    }

    // Ingresar valores del vector b
    std::cout << "Ingrese los valores del vector b:" << std::endl;
    for (int i = 0; i < size; ++i) {
        double value;
        std::cout << "b[" << i << "]: ";
        std::cin >> value;
        solver.setVectorValue(i, value);
    }

    // Ingresar valores iniciales de x
    std::cout << "Ingrese los valores iniciales de x:" << std::endl;
    for (int i = 0; i < size; ++i) {
        double value;
        std::cout << "x[" << i << "]: ";
        std::cin >> value;
        solver.setInitialGuess(i, value);
    }

    // Imprimir matriz original
    std::cout << std::endl << "Matriz original A:" << std::endl;
    solver.printMatrix();

    // Resolver el sistema de ecuaciones utilizando el método de Jacobi
    solver.solve();

    return 0;
}