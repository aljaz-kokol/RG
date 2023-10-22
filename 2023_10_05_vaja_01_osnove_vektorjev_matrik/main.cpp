#include <iostream>
#include <glm/glm.hpp>

int main() {
    int n = 0;
    std::cout << "Enter \"n\": ";
    std::cin >> n;

    std::cout << std::endl << "========== First formula ==========" << std::endl;
    glm::mat4 firstFormulaMatrix = glm::mat4(
            glm::vec4(glm::cos(glm::radians(30.0f)), 0, 0, 0), glm::vec4(0, 1, glm::sin(glm::radians(30.0f)), 0),
            glm::vec4(0, -glm::sin(glm::radians(30.0f)), glm::cos(glm::radians(30.0f)), 0), glm::vec4(0, 0, 0, 1)
            );

    glm::vec4 firstFormulaResult = glm::vec4(0.5, 0.7, 0.9, 1) * firstFormulaMatrix;
    firstFormulaResult *= n;

    std::cout << "Result : [ ";
    for (int i = 0; i < 4; i++) {
        std::cout << firstFormulaResult[i] << (i < 3 ? ", " : " ");
    }
    std::cout << "]" << std::endl;

    std::cout << std::endl << "========== Second formula ==========" << std::endl;
    glm::vec4 secondFormulaVec1 = glm::vec4(2 * n, 4 * n, 8 * n, 16 * n);
    glm::mat4 secondFormulaMatrix1 = glm::mat4(0);

    for (uint32_t a = 1; a <= glm::pow(n, 4); a++) {
        secondFormulaMatrix1 += glm::mat4(
                glm::vec4(0.5, 0, 0, 0), glm::vec4(0, a, 0, 0),
                glm::vec4(a, 0, glm::pow(a, 2), 0), glm::vec4(0, 0, 0, 1)
                );
    }

    glm::mat4 secondFormulaMatrix2 = glm::mat4(0);
    glm::mat4 secondFormulaMatrix3 = glm::mat4(1); // Create identity matrix
    glm::vec4 secondFormulaVector2 = glm::vec4 (glm::pow(n, 3), glm::pow(n, 2), n, 1);

    for (uint32_t a = 1; a <= glm::pow(n, 2); a++) {
        secondFormulaMatrix2 += glm::inverse(glm::mat4(
                glm::vec4(1, 0, 0, 0), glm::vec4(0, a, 0, 0),
                glm::vec4(a, glm::pow(a, 4), glm::pow(a, 2), 0), glm::vec4(0, 0, 0, 1)
        ));
    }

    for (uint32_t a = 1; a <= n; a++) {
        secondFormulaMatrix3 *= glm::mat4(
                glm::vec4(0, 0, 0, 0), glm::vec4(a, a, 0, a),
                glm::vec4(0, 0, glm::pow(a, 2), 0), glm::vec4(0, 0, 0, glm::pow(a, 3))
        );
    }

    double result = glm::dot(secondFormulaVec1 * secondFormulaMatrix1, (secondFormulaMatrix2 + secondFormulaMatrix3) * secondFormulaVector2);
    std::cout << "Result : " << result;
    return 0;
}
