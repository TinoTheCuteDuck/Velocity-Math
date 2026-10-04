#pragma once

#include "math/defines.hpp"

struct Vector2 {
    // Members
    union { float x, r, s; };
    union { float y, g, t; };

    VELOCITY_MATH_SWIZZLE_VECTOR2

    // Constructors
    constexpr Vector2() : x(0.0f), y(0.0f) {}
    constexpr Vector2(const float xy) : x(xy), y(xy) {}
    constexpr Vector2(const float x, const float y) : x(x), y(y) {}
    constexpr Vector2(const float values[2]) : x(values[0]), y(values[1]) {}

    // Static members
    static Vector2 zero;
    static Vector2 one;
    static Vector2 up;
    static Vector2 right;

    // Compound vector assignment
    constexpr Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    constexpr Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    constexpr Vector2& operator/=(const Vector2& other) {
        if (std::abs(other.x) < VELOCITY_MATH_EPSILON || std::abs(other.y) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector2 by zero");
            return *this;
        }

        x /= other.x;
        y /= other.y;
        return *this;
    }

    // Arithmetic vector operators
    constexpr Vector2 operator+(const Vector2& other) const {
        return {
            x + other.x,
            y + other.y
        };
    }
    constexpr Vector2 operator-(const Vector2& other) const {
        return {
            x - other.x,
            y - other.y
        };
    }
    constexpr Vector2 operator*(const Vector2& other) const {
        return {
            x * other.x,
            y * other.y
        };
    }
    constexpr Vector2 operator/(const Vector2& other) const {
        if (std::abs(other.x) < VELOCITY_MATH_EPSILON || std::abs(other.y) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector2 by zero");
            return *this;
        }

        return {
            x / other.x,
            y / other.y
        };
    }

    // Compound scalar assignment
    constexpr Vector2& operator+=(const float scalar) {
        x += scalar;
        y += scalar;
        return *this;
    }
    constexpr Vector2& operator-=(const float scalar) {
        x -= scalar;
        y -= scalar;
        return *this;
    }
    constexpr Vector2& operator*=(const float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    constexpr Vector2& operator/=(const float scalar) {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector2 by zero");
            return *this;
        }

        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Arithmetic scalar operators
    constexpr Vector2 operator+(const float scalar) const {
        return {
            x + scalar,
            y + scalar};
    }
    constexpr Vector2 operator-(const float scalar) const {
        return {
            x - scalar,
            y - scalar
        };
    }
    constexpr Vector2 operator*(const float scalar) const {
        return {
            x * scalar,
            y * scalar
        };
    }
    constexpr Vector2 operator/(const float scalar) const {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Vector2 by zero");
            return *this;
        }

        return {
            x / scalar,
            y / scalar
        };
    }

    // Increment operators
    constexpr Vector2& operator++() {
        ++x;
        ++y;
        return *this;
    }
    constexpr Vector2& operator--() {
        --x;
        --y;
        return *this;
    }
    constexpr Vector2 operator++(int) {
        const Vector2 old = *this;
        ++*this;
        return old;
    }
    constexpr Vector2 operator--(int) {
        const Vector2 old = *this;
        --*this;
        return old;
    }

    // Miscellaneous
    friend constexpr Vector2 operator*(const float scalar, const Vector2& vector) {
        return vector * scalar;
    }
    constexpr float& operator[](const size_t index) {
        if (index >= 2) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector2");
            return x;
        }

        switch (index) {
            case 0: return x;
            case 1: return y;
            default:
                VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector2");
                return x;
        }
    }
    constexpr const float& operator[](const size_t index) const {
        if (index >= 2) {
            VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector2");
            return x;
        }

        switch (index) {
            case 0: return x;
            case 1: return y;
            default:
                VELOCITY_MATH_ERROR("Tried to access index out of bounds on Vector2");
                return x;
        }
    }
    constexpr bool operator==(const Vector2& other) const {
        return std::abs(x - other.x) < VELOCITY_MATH_EPSILON &&
               std::abs(y - other.y) < VELOCITY_MATH_EPSILON;
    }
    constexpr bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }
    constexpr Vector2 operator-() const {
        return {
            -x,
            -y
        };
    }
    [[nodiscard]] constexpr Vector2 reciprocal() const {
        return {
            1.0f / x,
            1.0f / y
        };
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        os << "(" << (std::abs(vector.x) > VELOCITY_MATH_EPSILON ? vector.x : 0.0f) << ", "
            << (std::abs(vector.y) > VELOCITY_MATH_EPSILON ? vector.y : 0.0f)
        << ")";
        return os;
    }

    [[nodiscard]] constexpr float length() const {
        return std::sqrt(x * x + y * y);
    }
    [[nodiscard]] constexpr float lengthSquared() const {
        return x * x + y * y;
    }
    static constexpr float distance(const Vector2& a, const Vector2& b) {
        return (a - b).length();
    }
    static constexpr float distanceSquared(const Vector2& a, const Vector2& b) {
        return (a - b).lengthSquared();
    }
    static constexpr float angle(const Vector2& a, const Vector2& b) {
        return std::acos(std::clamp(dot(a.normalized(), b.normalized()), -1.0f, 1.0f));
    }

    constexpr Vector2& normalize() {
        const float len = length();
        if (std::abs(len) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to normalize Vector2 with length zero");
            return zero;
        }

        x /= len;
        y /= len;
        return *this;
    }
    [[nodiscard]] constexpr Vector2 normalized() const {
        const float len = length();
        if (std::abs(len) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to normalize Vector2 with length zero");
            return {};
        }

        return {x / len, y / len};
    }

    static constexpr float dot(const Vector2& a, const Vector2& b) {
        return a.x * b.x + a.y * b.y;
    }
    static constexpr Vector2 reflect(const Vector2& incident, const Vector2& normal) {
        // normal vector must be normalized
        const Vector2 projected = dot(incident, normal) * normal;
        const Vector2 tangential = incident - projected;
        const Vector2 reflected = tangential - projected;
        return reflected;
    }
    static constexpr Vector2 refract(const Vector2& incident, const Vector2& normal, const float eta) {
        // normal and incident vector must be normalized
        const Vector2 incidentPerpendicular = dot(incident, normal) * normal;
        const Vector2 incidentParallel = incident - incidentPerpendicular;
        const Vector2 refractedParallel = incidentParallel * eta;

        if (refractedParallel.lengthSquared() > 1) {
            return {};
        }

        const Vector2 refractedPerpendicular = std::sqrt(std::max(0.0f, 1.0f - refractedParallel.lengthSquared())) * -normal;
        const Vector2 refracted = refractedParallel + refractedPerpendicular;
        return refracted;
    }

    static constexpr Vector2 min(const Vector2& a, const Vector2& b) {
        return {std::min(a.x, b.x), std::min(a.y, b.y)};
    }
    static constexpr Vector2 max(const Vector2& a, const Vector2& b) {
        return {std::max(a.x, b.x), std::max(a.y, b.y)};
    }
    static constexpr Vector2 abs(const Vector2& vector) {
        return {
            std::abs(vector.x),
            std::abs(vector.y)
        };
    }
    static constexpr Vector2 clamp(const Vector2& vector, const Vector2& min, const Vector2& max) {
        return {
            std::clamp(vector.x, min.x, max.x),
            std::clamp(vector.y, min.y, max.y)
        };
    }

    static constexpr Vector2 lerp(const Vector2& a, const Vector2& b, const float t) {
        return a + t * (b - a);
    }
    template <typename Easing>
    static constexpr Vector2 lerp(const Vector2& a, const Vector2& b, const float t, Easing&& easing) {
        return a + easing(t) * (b - a);
    }
};

inline Vector2 Vector2::zero = Vector2(0.0f);
inline Vector2 Vector2::one = Vector2(1.0f);
inline Vector2 Vector2::up = Vector2(0.0f, 1.0f);
inline Vector2 Vector2::right = Vector2(1.0f, 0.0f);