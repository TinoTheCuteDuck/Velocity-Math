#include "math/matrices/mat2.hpp"
#include "math/matrices/mat3.hpp"
#include "math/matrices/mat4.hpp"

#include "math/vectors/vector2.hpp"
#include "math/vectors/vector3.hpp"
#include "math/vectors/vector4.hpp"

#include <cmath>
#include <iostream>

int main() {
    Vector4 point = Vector4(Vector3(1, 0, -1), 1);
    Vector3 cameraPosition = Vector3(1, 0, 0);
    Mat4 view = Mat4::lookAt(cameraPosition, cameraPosition + Vector3::right, Vector3::up);
    Vector4 transformed = view * point;

    std::cout << transformed << std::endl;

    return 0;
}