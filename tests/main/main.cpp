#include "math/matrices/mat2.hpp"
#include "math/matrices/mat3.hpp"
#include "math/matrices/mat4.hpp"

#include "math/vectors/vector2.hpp"
#include "math/vectors/vector3.hpp"
#include "math/vectors/vector4.hpp"

#include <cmath>
#include <iostream>

int main() {
    Vector3 incident = Vector3(1, -1, 0).normalize();
    Vector3 normal = Vector3::up;

    Mat4 a = Mat4(2, 41,121,421,241,421,4,41,134,1,631,123,67,3,78,5);

    std::cout << "Mat: \n" << a << std::endl;
    std::cout << "Inverse: \n" << a.inverse()  << std::endl;
    std::cout << "Identity: \n" << a * a.inverse() << std::endl;

    return 0;
}