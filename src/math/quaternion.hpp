#pragma once

#include "defines.hpp"
#include "math/vectors/vector2.hpp"
#include "math/vectors/vector3.hpp"
#include "math/vectors/vector4.hpp"

#include <cmath>
#include <iostream>

struct Quaternion {
    // Members
    float x, y, z, w;

    VELOCITY_MATH_SWIZZLE_QUATERNION

    // Constructors
    constexpr Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    constexpr Quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    constexpr Quaternion(const Vector2& vec, const float z, const float w) : x(vec.x), y(vec.y), z(z), w(w) {}
    constexpr Quaternion(const float x, const Vector2& vec, const float w) : x(x), y(vec.x), z(vec.y), w(w) {}
    constexpr Quaternion(const float x, const float y, const Vector2& vec) : x(x), y(y), z(vec.x), w(vec.y) {}
    constexpr Quaternion(const Vector2& vec1, const Vector2& vec2) : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) {}
    constexpr Quaternion(const Vector3& vec, const float scalar) : x(vec.x), y(vec.y), z(vec.z), w(scalar) {}
    constexpr Quaternion(const float scalar, const Vector3& vec) : x(scalar), y(vec.x), z(vec.y), w(vec.z) {}
    constexpr Quaternion(const Vector4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

    // Static constants
    static const Quaternion zero;
    static const Quaternion identity;

    // Compound quaternion assignment
    constexpr Quaternion& operator+=(const Quaternion& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }
    constexpr Quaternion& operator-=(const Quaternion& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }
    constexpr Quaternion& operator*=(const Quaternion& other) {
        *this = {
            x * other.w + y * other.z - z * other.y + w * other.x,
            -x * other.z + y * other.w + z * other.x + w * other.y,
            x * other.y - y * other.x + z * other.w + w * other.z,
            -x * other.x - y * other.y - z * other.z + w * other.w
        };

        return *this;
    }
    constexpr Quaternion& operator/=(const Quaternion& other) {
        *this = *this * other.inverse();

        return *this;
    }

    // Arithmetic quaternion operators
    constexpr Quaternion operator+(const Quaternion& other) const {
        return {
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w
        };
    }
    constexpr Quaternion operator-(const Quaternion& other) const {
        return {
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w
        };
    }
    constexpr Quaternion operator*(const Quaternion& other) const {
        return {
            x * other.w + y * other.z - z * other.y + w * other.x,
            -x * other.z + y * other.w + z * other.x + w * other.y,
            x * other.y - y * other.x + z * other.w + w * other.z,
            -x * other.x - y * other.y - z * other.z + w * other.w
        };
    }
    constexpr Quaternion operator/(const Quaternion& other) const {
        return *this * other.inverse();
    }

    // Compound scalar assignment
    constexpr Quaternion& operator+=(const float scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;

        return *this;
    }
    constexpr Quaternion& operator-=(const float scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;

        return *this;
    }
    constexpr Quaternion& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;

        return *this;
    }
    constexpr Quaternion& operator/=(const float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;

        return *this;
    }

    // Arithmetic scalar operators
    constexpr Quaternion operator+(const float scalar) const {
        return {
            x + scalar,
            y + scalar,
            z + scalar,
            w + scalar
        };
    }
    constexpr Quaternion operator-(const float scalar) const {
        return {
            x - scalar,
            y - scalar,
            z - scalar,
            w - scalar
        };
    }
    constexpr Quaternion operator*(const float scalar) const {
        return {
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        };
    }
    constexpr Quaternion operator/(const float scalar) const {
        return {
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar
        };
    }

    // Miscellaneous operators
    constexpr Vector3 operator*(const Vector3& vector) const {
        const Quaternion vq = {vector, 0.0f};
        const Quaternion result = *this * vq * conjugated();

        return result.xyz();
    }
    constexpr Quaternion operator-() const {
        return {-x, -y, -z, -w};
    }
    constexpr float& operator[](const size_t index) {
        if (index >= 4) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Quaternion");
            return x;
        }

        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Quaternion");
            return x;
        }
    }
    constexpr const float& operator[](const size_t index) const {
        if (index >= 4) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Quaternion");
            return x;
        }

        switch (index) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Quaternion");
            return x;
        }
    }
    constexpr bool operator==(const Quaternion& other) const {
        return (std::abs(x - other.x) < VELOCITY_MATH_EPSILON &&
                std::abs(y - other.y) < VELOCITY_MATH_EPSILON &&
                std::abs(z - other.z) < VELOCITY_MATH_EPSILON &&
                std::abs(w - other.w) < VELOCITY_MATH_EPSILON) ||

               (std::abs(-x - other.x) < VELOCITY_MATH_EPSILON &&
                std::abs(-y - other.y) < VELOCITY_MATH_EPSILON &&
                std::abs(-z - other.z) < VELOCITY_MATH_EPSILON &&
                std::abs(-w - other.w) < VELOCITY_MATH_EPSILON);
    }
    constexpr bool operator!=(const Quaternion& other) const {
        return !(*this == other);
    }
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion) {
        os << "("
           << (std::abs(quaternion.x) > VELOCITY_MATH_EPSILON ? quaternion.x : 0.0f) << "i, "
           << (std::abs(quaternion.y) > VELOCITY_MATH_EPSILON ? quaternion.y : 0.0f) << "j, "
           << (std::abs(quaternion.z) > VELOCITY_MATH_EPSILON ? quaternion.z : 0.0f) << "k, "
           << (std::abs(quaternion.w) > VELOCITY_MATH_EPSILON ? quaternion.w : 0.0f)
           << ")";
        return os;
    }

    // Member methods
    constexpr Quaternion& normalize() {
        const float mag = magnitude();
        if (std::abs(mag) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Attempted to normalize Quaternion with magnitude zero");
            return *this;
        }

        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
        return *this;
    }
    [[nodiscard]] Quaternion normalized() const {
        const float mag = magnitude();
        if (std::abs(mag) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Attempted to normalize Quaternion with magnitude zero");
            return *this;
        }

        return {
            x / mag,
            y / mag,
            z / mag,
            w / mag
        };
    }
    constexpr Quaternion& conjugate() {
        x = -x;
        y = -y;
        z = -z;

        return *this;
    }
    [[nodiscard]] constexpr Quaternion conjugated() const {
        return {-x, -y, -z, w};
    }
    constexpr Quaternion& invert() {
        conjugate() /= magnitudeSquared();

        return *this;
    }
    [[nodiscard]] constexpr Quaternion inverse() const {
        return conjugated() / magnitudeSquared();
    }

    [[nodiscard]] constexpr float magnitude() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    [[nodiscard]] constexpr float magnitudeSquared() const {
        return x * x + y * y + z * z + w * w;
    }

    [[nodiscard]] constexpr Vector3 toEuler() const {

        return {};
    }
    [[nodiscard]] constexpr Vector4 toAxis() const {
        const float angle = std::acos(w);
        const float multiplier = 1 / std::sin(angle);
        const Vector3 vector = xyz() * multiplier;

        return {vector, angle * 2};
    }

    // Static methods
    static constexpr float dot(const Quaternion& a, const Quaternion& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    static constexpr Quaternion fromEuler(const float pitch, const float yaw, const float roll) {
        const Quaternion qx = {std::sin(pitch * 0.5f) * 1.0f, 0.0f, 0.0f, std::cos(pitch * 0.5f)};
        const Quaternion qy = {0.0f, std::sin(yaw * 0.5f) * 1.0f, 0.0f, std::cos(yaw * 0.5f)};
        const Quaternion qz = {0.0f, 0.0f, std::sin(roll * 0.5f) * 1.0f, std::cos(roll * 0.5f)};

        return qx * qy * qz;
    }
    static constexpr Quaternion fromEuler(const Vector3& rotation) {
        const Quaternion qx = {std::sin(rotation.x * 0.5f), 0.0f, 0.0f, std::cos(rotation.x * 0.5f)};
        const Quaternion qy = {0.0f, std::sin(rotation.y * 0.5f), 0.0f, std::cos(rotation.y * 0.5f)};
        const Quaternion qz = {0.0f, 0.0f, std::sin(rotation.z * 0.5f), std::cos(rotation.z * 0.5f)};

        return qx * qy * qz;
    }
    static constexpr Quaternion fromAxis(const float x, const float y, const float z, const float angle) {
        const float multiplier = std::sin(angle * 0.5f);
        const float scalar = std::cos(angle * 0.5f);
        const Vector3 vec = Vector3(x, y, z) * multiplier;

        return {vec, scalar};
    }
    static constexpr Quaternion fromAxis(const Vector3& vector, const float angle) {
        const float multiplier = std::sin(angle * 0.5f);
        const float scalar = std::cos(angle * 0.5f);
        const Vector3 vec = vector * multiplier;

        return {vec, scalar};
    }
};

constexpr Quaternion Quaternion::zero = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
constexpr Quaternion Quaternion::identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);