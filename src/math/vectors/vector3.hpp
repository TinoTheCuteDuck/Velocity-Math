#pragma once

#include "math/defines.hpp"
#include "math/vectors/vector2.hpp"

struct Vector3 {
    // Members
    union { float x, r, s; };
    union { float y, g, t; };
    union { float z, b, p; };

    VELOCITY_MATH_SWIZZLE_VECTOR3

    // Constructors
    constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr Vector3(const float xyz) : x(xyz), y(xyz), z(xyz) {}
    constexpr Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    constexpr Vector3(const Vector2& other, const float z) : x(other.x), y(other.y), z(z) {}
    constexpr Vector3(const float x, const Vector2& other) : x(x), y(other.x), z(other.y) {}
    constexpr Vector3(const float values[3]) : x(values[0]), y(values[1]), z(values[2]) {}

    // Static members
    static Vector3 zero;
    static Vector3 one;
    static Vector3 up;
    static Vector3 right;
    static Vector3 forward;

    // Compound vector assignment
    constexpr Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    constexpr Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    constexpr Vector3& operator*=(const Vector3& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }
    constexpr Vector3& operator/=(const Vector3& other) {
        if (std::abs(other.x) < VELOCITY_MATH_EPSILON || std::abs(other.y) < VELOCITY_MATH_EPSILON || std::abs(other.z) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector3 by zero");
            return *this;
        }

        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    // Arithmetic vector operators
    constexpr Vector3 operator+(const Vector3& other) const {
        return {
            x + other.x,
            y + other.y,
            z + other.z
        };
    }
    constexpr Vector3 operator-(const Vector3& other) const {
        return {
            x - other.x,
            y - other.y,
            z - other.z
        };
    }
    constexpr Vector3 operator*(const Vector3& other) const {
        return {
            x * other.x,
            y * other.y,
            z * other.z
        };
    }
    constexpr Vector3 operator/(const Vector3& other) const {
        if (std::abs(other.x) < VELOCITY_MATH_EPSILON || std::abs(other.y) < VELOCITY_MATH_EPSILON || std::abs(other.z) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector3 by zero");
            return *this;
        }

        return {
            x / other.x,
            y / other.y,
            z / other.z
        };
    }

    // Compound scalar assignment
    constexpr Vector3& operator+=(const float scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }
    constexpr Vector3& operator-=(const float scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }
    constexpr Vector3& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    constexpr Vector3& operator/=(const float scalar) {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector3 by zero");
            return *this;
        }

        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Arithmetic scalar operators
    constexpr Vector3 operator+(const float scalar) const {
        return {
            x + scalar,
            y + scalar,
            z + scalar
        };
    }
    constexpr Vector3 operator-(const float scalar) const {
        return {
            x - scalar,
            y - scalar,
            z - scalar
        };
    }
    constexpr Vector3 operator*(const float scalar) const {
        return {
            x * scalar,
            y * scalar,
            z * scalar
        };
    }
    constexpr Vector3 operator/(const float scalar) const {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector3 by zero");
            return *this;
        }

        return {
            x / scalar,
            y / scalar,
            z / scalar
        };
    }

    // Increment operators
    constexpr Vector3& operator++() {
        ++x;
        ++y;
        ++z;
        return *this;
    }
    constexpr Vector3& operator--() {
        --x;
        --y;
        --z;
        return *this;
    }
    constexpr Vector3 operator++(int) {
        const Vector3 old = *this;
        ++*this;
        return old;
    }
    constexpr Vector3 operator--(int) {
        const Vector3 old = *this;
        --*this;
        return old;
    }

    // Miscellaneous
    friend constexpr Vector3 operator*(const float scalar, const Vector3& vector) {
        return vector * scalar;
    }
    constexpr float& operator[](const size_t index) {
        if (index >= 3) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector3");
            return x;
        }

        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default:
                VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector3");
                return x;
        }
    }
    constexpr const float& operator[](const size_t index) const {
        if (index >= 3) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector3");
            return x;
        }

        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default:
                VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector3");
                return x;
        }
    }
    constexpr bool operator==(const Vector3& other) const {
        return std::abs(x - other.x) < VELOCITY_MATH_EPSILON &&
               std::abs(y - other.y) < VELOCITY_MATH_EPSILON &&
               std::abs(z - other.z) < VELOCITY_MATH_EPSILON;
    }
    constexpr bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }
    constexpr Vector3 operator-() const {
        return {
            -x,
            -y,
            -z
        };
    }
    [[nodiscard]] constexpr Vector3 reciprocal() const {
        return {
            1.0f / x,
            1.0f / y,
            1.0f / z
        };
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
        os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
        return os;
    }

    [[nodiscard]] constexpr float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    [[nodiscard]] constexpr float lengthSquared() const {
        return x * x + y * y + z * z;
    }
    static constexpr float distance(const Vector3& a, const Vector3& b) {
        return (a - b).length();
    }
    static constexpr float distanceSquared(const Vector3& a, const Vector3& b) {
        return (a - b).lengthSquared();
    }
    static constexpr float angle(const Vector3& a, const Vector3& b) {
        return std::acos(std::clamp(dot(a.normalized(), b.normalized()), -1.0f, 1.0f));
    }

    constexpr Vector3& normalize() {
        const float len = length();
        if (std::abs(len) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to normalize Vector3 with length zero");
            return zero;
        }

        x /= len;
        y /= len;
        z /= len;
        return *this;
    }
    [[nodiscard]] constexpr Vector3 normalized() const {
        const float len = length();
        if (std::abs(len) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to normalize Vector3 with length zero");
            return {};
        }

        return {x / len, y / len, z / len};
    }

    static constexpr float dot(const Vector3& vec1, const Vector3& vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }
    static constexpr Vector3 cross(const Vector3& a, const Vector3& b) {
        return {
            a.y * b.z - b.y * a.z,
            b.x * a.z - a.x * b.z,
            a.x * b.y - b.x * a.y
        };
    }
    static constexpr Vector3 reflect(const Vector3& incident, const Vector3& normal) {
        // normal vector must be normalized
        const Vector3 projected = dot(incident, normal) * normal;
        const Vector3 tangential = incident - projected;
        const Vector3 reflected = tangential - projected;
        return reflected;
    }
    static constexpr Vector3 refract(const Vector3& incident, const Vector3& normal, const float eta) {
        // normal and incident vector must be normalized
        const Vector3 incidentPerpendicular = dot(incident, normal) * normal;
        const Vector3 incidentParallel = incident - incidentPerpendicular;
        const Vector3 refractedParallel = incidentParallel * eta;

        if (refractedParallel.lengthSquared() > 1) {
            return {};
        }

        const Vector3 refractedPerpendicular = std::sqrt(std::max(0.0f, 1.0f - refractedParallel.lengthSquared())) * -normal;
        const Vector3 refracted = refractedParallel + refractedPerpendicular;
        return refracted;
    }

    static constexpr Vector3 min(const Vector3& a, const Vector3& b) {
        return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
    }
    static constexpr Vector3 max(const Vector3& a, const Vector3& b) {
        return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
    }
    static constexpr Vector3 abs(const Vector3& v) {
        return {
            std::abs(v.x),
            std::abs(v.y),
            std::abs(v.z)
        };
    }
    static constexpr Vector3 clamp(const Vector3& v, const Vector3& min, const Vector3& max) {
        return {
            std::clamp(v.x, min.x, max.x),
            std::clamp(v.y, min.y, max.y),
            std::clamp(v.z, min.z, max.z)
        };
    }

    static constexpr Vector3 lerp(const Vector3& a, const Vector3& b, const float t) {
        return a + t * (b - a);
    }
    template <typename Easing>
    static constexpr Vector3 lerp(const Vector3& a, const Vector3& b, const float t, Easing&& easing) {
        return a + easing(t) * (b - a);
    }
};

inline Vector3 Vector3::zero = Vector3();
inline Vector3 Vector3::one = Vector3(1);
inline Vector3 Vector3::up = Vector3(0, 1, 0);
inline Vector3 Vector3::right = Vector3(1, 0, 0);
inline Vector3 Vector3::forward = Vector3(0, 0, -1);