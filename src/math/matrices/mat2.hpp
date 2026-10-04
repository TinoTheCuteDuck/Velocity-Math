#pragma once

#include "math/defines.hpp"
#include "math/vectors/vector2.hpp"

struct Mat2 {
  private:
    float m[2][2]; // Column major [column][row]

  public:
    // Constructors
    constexpr Mat2() : m({1, 0}, {0, 1}) {}
    constexpr Mat2(const float scale) : m({scale, 0}, {0, scale}) {}
    constexpr Mat2(const float values[4]) : m() {
        for (size_t col = 0; col < 2; col++) {
            for (size_t row = 0; row < 2; row++) {
                m[col][row] = values[col * 2 + row];
            }
        }
    }
    constexpr Mat2(const Vector2& column0, const Vector2& column1) : m({column0.x, column0.y}, {column1.x, column1.y}) {}
    constexpr Mat2(const float c0r0, const float c0r1, const float c1r0, const float c1r1) : m({c0r0, c0r1}, {c1r0, c1r1}) {}

    // Static members
    static Mat2 zero;
    static Mat2 identity;

    // Compound matrix assignment
    constexpr Mat2& operator+=(const Mat2& other) {
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                m[col][row] += other[col][row];
            }
        }

        return *this;
    }
    constexpr Mat2& operator-=(const Mat2& other) {
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                m[col][row] -= other[col][row];
            }
        }

        return *this;
    }
    constexpr Mat2& operator*=(const Mat2& other) {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                for (int k = 0; k < 2; k++) {
                    result[col][row] += other[col][k] * m[k][row];
                }
            }
        }

        *this = result;
        return *this;
    }

    // Arithmetic matrix operators
    constexpr Mat2 operator+(const Mat2& other) const {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = m[col][row] + other[col][row];
            }
        }

        return result;
    }
    constexpr Mat2 operator-(const Mat2& other) const {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = m[col][row] - other[col][row];
            }
        }

        return result;
    }
    constexpr Mat2 operator*(const Mat2& other) const {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                for (int k = 0; k < 2; k++) {
                    result[col][row] += other[col][k] * m[k][row];
                }
            }
        }

        return result;
    }

    // Compound scalar assignment
    constexpr Mat2& operator+=(const float scalar) {
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                m[col][row] += scalar;
            }
        }

        return *this;
    }
    constexpr Mat2& operator-=(const float scalar) {
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                m[col][row] -= scalar;
            }
        }

        return *this;
    }
    constexpr Mat2& operator*=(const float scalar) {
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                m[col][row] *= scalar;
            }
        }

        return *this;
    }
    constexpr Mat2& operator/=(const float scalar) {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Mat2 by zero");
            return *this;
        }

        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                m[col][row] /= scalar;
            }
        }

        return *this;
    }

    // Arithmetic scalar operators
    constexpr Mat2 operator+(const float scalar) const {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = m[col][row] + scalar;
            }
        }

        return result;
    }
    constexpr Mat2 operator-(const float scalar) const {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = m[col][row] - scalar;
            }
        }

        return result;
    }
    constexpr Mat2 operator*(const float scalar) const {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = m[col][row] * scalar;
            }
        }

        return result;
    }
    constexpr Mat2 operator/(const float scalar) const {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Mat2 by zero");
            return *this;
        }

        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = m[col][row] / scalar;
            }
        }

        return result;
    }

    // Miscellaneous
    constexpr float* operator[](const size_t column) {
        return m[column];
    }
    constexpr const float* operator[](const size_t column) const {
        return m[column];
    }
    constexpr bool operator==(const Mat2& other) const {
        Mat2 diff = abs(*this - other);
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                if (diff[col][row] > VELOCITY_MATH_EPSILON)
                    return false;
            }
        }

        return true;
    }
    constexpr bool operator!=(const Mat2& other) const {
        return !(*this == other);
    }

    constexpr Mat2 operator-() const {
        return *this * -1.0f;
    }
    friend std::ostream& operator<<(std::ostream& os, const Mat2& mat) {
        for (int row = 0; row < 2; row++) {
            os << '[';
            for (int col = 0; col < 2; col++) {
                os << (std::abs(mat[col][row]) > VELOCITY_MATH_EPSILON ? mat[col][row] : 0.0f);

                if (col != 1) {
                    os << ", ";
                }
            }
            os << "]\n";
        }

        return os;
    }
    friend Vector2 operator*(const Mat2& mat, const Vector2& vector) {
        Vector2 result = Vector2::zero;
        for (int row = 0; row < 2; row++) {
            for (int col = 0; col < 2; col++) {
                result[row] += vector[col] * mat[col][row];
            }
        }

        return result;
    }
    [[nodiscard]] constexpr Vector2 column(const size_t index) const {
        return {
            m[index][0],
            m[index][1]
        };
    }
    [[nodiscard]] constexpr Vector2 row(const size_t index) const {
        return {
            m[0][index],
            m[1][index]
        };
    }

    [[nodiscard]] constexpr float determinant() const {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }
    constexpr Mat2& transpose() {
        std::swap(m[0][1], m[1][0]);
        return *this;
    }
    [[nodiscard]] constexpr Mat2 transposed() const {
        return {
            m[0][0],
            m[1][0],
            m[0][1],
            m[1][1]
        };
    }
    constexpr Mat2& invert() {
        *this = inverse();
        return *this;
    }
    [[nodiscard]] constexpr Mat2 inverse() const {
        const float det = determinant();
        if (std::abs(det) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to get inverse of a matrix where the determinant is zero");
            return *this;
        }

        const float invDet = 1 / det;

        return {
            m[1][1] * invDet,
            -m[0][1] * invDet,
            -m[1][0] * invDet,
            m[0][0] * invDet
        };
    }

    static constexpr Mat2 abs(const Mat2& mat) {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = std::abs(mat[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat2 clamp(const Mat2& mat, const Mat2& min, const Mat2& max) {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = std::clamp(mat[col][row], min[col][row], max[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat2 min(const Mat2& a, const Mat2& b) {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = std::min(a[col][row], b[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat2 max(const Mat2& a, const Mat2& b) {
        Mat2 result = zero;
        for (int col = 0; col < 2; col++) {
            for (int row = 0; row < 2; row++) {
                result[col][row] = std::max(a[col][row], b[col][row]);
            }
        }

        return result;
    }
};

inline Mat2 Mat2::zero = Mat2(0.0f);
inline Mat2 Mat2::identity = Mat2(1.0f);