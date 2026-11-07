#include "math/matrices/mat4.hpp"
//
// #include "math/vectors/vector3.hpp"
// #include "math/vectors/vector4.hpp"
#include "math/quaternion.hpp"

#include <iostream>
#include <cmath>

constexpr float degreesToRadians = std::numbers::pi / 180;
constexpr float radiansToDegrees = 180 / std::numbers::pi;

int main() {
    Vector3 rotation = Vector3(23.4f * degreesToRadians, 68.6f * degreesToRadians, 41.3f * degreesToRadians);
    Quaternion q = Quaternion::fromEuler(rotation);

    std::cout << Vector4(0.71, 0.0, 0.0, 0.71).reciprocal() << std::endl;


    return 0;
}