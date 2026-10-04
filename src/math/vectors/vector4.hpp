#pragma once

#include "math/defines.hpp"
#include "math/vectors/vector2.hpp"
#include "math/vectors/vector3.hpp"

struct Vector4 {
    // Members
    union { float x, r, s; };
    union { float y, g, t; };
    union { float z, b, p; };
    union { float w, a, q; };

    VELOCITY_MATH_SWIZZLE_VECTOR4

    // Constructors
    constexpr Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr Vector4(const float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
    constexpr Vector4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
    constexpr Vector4(const Vector2& vec, const float z, const float w) : x(vec.x), y(vec.y), z(z), w(w) {}
    constexpr Vector4(const float x, const Vector2& vec, const float w) : x(x), y(vec.x), z(vec.y), w(w) {}
    constexpr Vector4(const float x, const float y, const Vector2& vec) : x(x), y(y), z(vec.x), w(vec.y) {}
    constexpr Vector4(const Vector2& vec1, const Vector2& vec2) : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) {}
    constexpr Vector4(const Vector3& vec, const float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}
    constexpr Vector4(const float x, const Vector3& vec) : x(x), y(vec.x), z(vec.y), w(vec.z) {}
    constexpr Vector4(const float values[4]) : x(values[0]), y(values[1]), z(values[2]), w(values[3]) {}

    // Static members
    static Vector4 zero;
    static Vector4 one;

    // Compound vector assignment
    constexpr Vector4& operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }
    constexpr Vector4& operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }
    constexpr Vector4& operator*=(const Vector4& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }
    constexpr Vector4& operator/=(const Vector4& other) {
        if (std::abs(other.x) < VELOCITY_MATH_EPSILON || std::abs(other.y) < VELOCITY_MATH_EPSILON || std::abs(other.z) < VELOCITY_MATH_EPSILON || std::abs(other.w) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector4 by zero");
            return *this;
        }

        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    }

    // Arithmetic vector operators
    constexpr Vector4 operator+(const Vector4& other) const {
        return {
            x + other.x,
            y + other.y,
            z + other.z,
            w + other.w
        };
    }
    constexpr Vector4 operator-(const Vector4& other) const {
        return {
            x - other.x,
            y - other.y,
            z - other.z,
            w - other.w
        };
    }
    constexpr Vector4 operator*(const Vector4& other) const {
        return {
            x * other.x,
            y * other.y,
            z * other.z,
            w * other.w
        };
    }
    constexpr Vector4 operator/(const Vector4& other) const {
        if (std::abs(other.x) < VELOCITY_MATH_EPSILON || std::abs(other.y) < VELOCITY_MATH_EPSILON || std::abs(other.z) < VELOCITY_MATH_EPSILON || std::abs(other.w) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector4 by zero");
            return *this;
        }

        return {
            x / other.x,
            y / other.y,
            z / other.z,
            w / other.w
        };
    }

    // Compound scalar assignment
    constexpr Vector4& operator+=(const float scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }
    constexpr Vector4& operator-=(const float scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }
    constexpr Vector4& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }
    constexpr Vector4& operator/=(const float scalar) {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector4 by zero");
            return *this;
        }

        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    // Arithmetic scalar operators
    constexpr Vector4 operator+(const float scalar) const {
        return {
            x + scalar,
            y + scalar,
            z + scalar,
            w + scalar
        };
    }
    constexpr Vector4 operator-(const float scalar) const {
        return {
            x - scalar,
            y - scalar,
            z - scalar,
            w - scalar
        };
    }
    constexpr Vector4 operator*(const float scalar) const {
        return {
            x * scalar,
            y * scalar,
            z * scalar,
            w * scalar
        };
    }
    constexpr Vector4 operator/(const float scalar) const {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector4 by zero");
            return *this;
        }

        return {
            x / scalar,
            y / scalar,
            z / scalar,
            w / scalar
        };
    }

    // Increment operators
    constexpr Vector4& operator++() {
        ++x;
        ++y;
        ++z;
        ++w;
        return *this;
    }
    constexpr Vector4& operator--() {
        --x;
        --y;
        --z;
        --w;
        return *this;
    }
    constexpr Vector4 operator++(int) {
        const Vector4 old = *this;
        ++*this;
        return old;
    }
    constexpr Vector4 operator--(int) {
        const Vector4 old = *this;
        --*this;
        return old;
    }

    // Miscellaneous
    friend constexpr Vector4 operator*(const float scalar, const Vector4 &vector) {
        return vector * scalar;
    }
    constexpr float& operator[](const size_t index) {
        if (index >= 4) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector4");
            return x;
        }

        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default:
                VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector4");
                return x;
        }
    }
    constexpr const float& operator[](const size_t index) const {
        if (index >= 4) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector4");
            return x;
        }

        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            case 3: return w;
            default:
                VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector4");
                return x;
        }
    }
    constexpr bool operator==(const Vector4& other) const {
        return std::abs(x - other.x) < VELOCITY_MATH_EPSILON &&
               std::abs(y - other.y) < VELOCITY_MATH_EPSILON &&
               std::abs(z - other.z) < VELOCITY_MATH_EPSILON &&
               std::abs(w - other.w) < VELOCITY_MATH_EPSILON;
    }
    constexpr bool operator!=(const Vector4& other) const {
        return !(*this == other);
    }
    constexpr Vector4 operator-() const {
        return {
            -x,
            -y,
            -z,
            -w
        };
    }
    [[nodiscard]] constexpr Vector4 reciprocal() const {
        return {
            1.0f / x,
            1.0f / y,
            1.0f / z,
            1.0f / w
        };
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vector) {
        os << "("
            << (std::abs(vector.x) > VELOCITY_MATH_EPSILON ? vector.x : 0.0f)<< ", "
            << (std::abs(vector.y) > VELOCITY_MATH_EPSILON ? vector.y : 0.0f) << ", "
            << (std::abs(vector.z) > VELOCITY_MATH_EPSILON ? vector.z : 0.0f) << ", "
            << (std::abs(vector.w) > VELOCITY_MATH_EPSILON ? vector.w : 0.0f)
        << ")";
        return os;
    }

    [[nodiscard]] constexpr float length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }
    [[nodiscard]] constexpr float lengthSquared() const {
        return x * x + y * y + z * z + w * w;
    }
    static constexpr float distance(const Vector4& a, const Vector4& b) {
        return (a - b).length();
    }
    static constexpr float distanceSquared(const Vector4& a, const Vector4& b) {
        return (a - b).lengthSquared();
    }
    static constexpr float angle(const Vector4& a, const Vector4& b) {
        return std::acos(std::clamp(dot(a.normalized(), b.normalized()), -1.0f, 1.0f));
    }

    constexpr Vector4& normalize() {
        const float len = length();
        if (std::abs(len) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to normalize Vector4 with length zero");
            return zero;
        }

        x /= len;
        y /= len;
        z /= len;
        w /= len;
        return *this;
    }
    [[nodiscard]] constexpr Vector4 normalized() const {
        const float len = length();
        if (std::abs(len) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to normalize Vector4 with length zero");
            return {};
        }

        return {x / len, y / len, z / len, w / len};
    }

    static constexpr float dot(const Vector4& a, const Vector4& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }
    static constexpr Vector4 reflect(const Vector4& incident, const Vector4& normal) {
        // normal vector must be normalized
        const Vector4 projected = dot(incident, normal) * normal;
        const Vector4 tangential = incident - projected;
        const Vector4 reflected = tangential - projected;
        return reflected;
    }
    static constexpr Vector4 refract(const Vector4& incident, const Vector4& normal, const float eta) {
        // normal and incident vector must be normalized
        const Vector4 incidentPerpendicular = dot(incident, normal) * normal;
        const Vector4 incidentParallel = incident - incidentPerpendicular;
        const Vector4 refractedParallel = incidentParallel * eta;

        if (refractedParallel.lengthSquared() > 1) {
            return {};
        }

        const Vector4 refractedPerpendicular = std::sqrt(std::max(0.0f, 1.0f - refractedParallel.lengthSquared())) * -normal;
        const Vector4 refracted = refractedParallel + refractedPerpendicular;
        return refracted;
    }

    static constexpr Vector4 min(const Vector4& a, const Vector4& b) {
        return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)};
    }
    static constexpr Vector4 max(const Vector4& a, const Vector4& b) {
        return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)};
    }
    static constexpr Vector4 abs(const Vector4& vector) {
        return {
            std::abs(vector.x),
            std::abs(vector.y),
            std::abs(vector.z),
            std::abs(vector.w)
        };
    }
    static constexpr Vector4 clamp(const Vector4& vector, const Vector4& min, const Vector4& max) {
        return {
            std::clamp(vector.x, min.x, max.x),
            std::clamp(vector.y, min.y, max.y),
            std::clamp(vector.z, min.z, max.z),
            std::clamp(vector.w, min.w, max.w)
        };
    }

    static constexpr Vector4 lerp(const Vector4& a, const Vector4& b, const float t) {
        return a + t * (b - a);
    }
    template <typename Easing>
    static constexpr Vector4 lerp(const Vector4& a, const Vector4& b, const float t, Easing&& easing) {
        return a + easing(t) * (b - a);
    }
};

inline Vector4 Vector4::zero = Vector4(0.0f);
inline Vector4 Vector4::one = Vector4(1.0f);