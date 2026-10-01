#include "math/matrices/mat2.hpp"

#include <cmath>
#include <iostream>

#include "math/vectors/vector2.hpp"
#include "math/vectors/vector3.hpp"
#include "math/vectors/vector4.hpp"

int main() {
    Vector3 incident = Vector3(1, -1, 0).normalize();
    Vector3 normal = Vector3::up;

    Mat2 a = Mat2(1, 2, 3, 4);
    Mat2 invA = a.inverse();
    Mat2 shouldIdentity = a * invA;


    return 0;
}