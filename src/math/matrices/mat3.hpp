#pragma once

#include "math/defines.hpp"
#include "math/vectors/vector3.hpp"

struct Mat3 {
  private:
    float m[3][3]; // Column major [column][row]

  public:
    // Constructors
    constexpr Mat3() : m({1, 0, 0}, {0, 1, 0}, {0, 0, 1}) {}
    constexpr Mat3(const float scale) : m({scale, 0, 0}, {0, scale, 0}, {0, 0, scale}) {}
    constexpr Mat3(const float values[9]) : m() {
        for (size_t col = 0; col < 3; col++) {
            for (size_t row = 0; row < 3; row++) {
                m[col][row] = values[col * 3 + row];
            }
        }
    }
    constexpr Mat3(const Vector3& column0, const Vector3& column1, const Vector3& column2) : m({column0.x, column0.y, column0.z}, {column1.x, column1.y, column1.z}, {column2.x, column2.y, column2.z}) {}
    constexpr Mat3(const float c0r0, const float c0r1, const float c0r2, const float c1r0, const float c1r1, const float c1r2, const float c2r0, const float c2r1, const float c2r2) : m({c0r0, c0r1, c0r2}, {c1r0, c1r1, c1r2}, {c2r0, c2r1, c2r2}) {}

    // Static members
    static Mat3 zero;
    static Mat3 identity;

    // Compound matrix assignment
    constexpr Mat3& operator+=(const Mat3& other) {
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                m[col][row] += other[col][row];
            }
        }

        return *this;
    }
    constexpr Mat3& operator-=(const Mat3& other) {
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                m[col][row] -= other[col][row];
            }
        }

        return *this;
    }
    constexpr Mat3& operator*=(const Mat3& other) {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                for (int k = 0; k < 3; k++) {
                    result[col][row] += other[col][k] * m[k][row];
                }
            }
        }

        *this = result;
        return *this;
    }

    // Arithmetic matrix operators
    constexpr Mat3 operator+(const Mat3& other) const {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = m[col][row] + other[col][row];
            }
        }

        return result;
    }
    constexpr Mat3 operator-(const Mat3& other) const {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = m[col][row] - other[col][row];
            }
        }

        return result;
    }
    constexpr Mat3 operator*(const Mat3& other) const {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                for (int k = 0; k < 3; k++) {
                    result[col][row] += other[col][k] * m[k][row];
                }
            }
        }

        return result;
    }

    // Compound scalar assignment
    constexpr Mat3& operator+=(const float scalar) {
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                m[col][row] += scalar;
            }
        }

        return *this;
    }
    constexpr Mat3& operator-=(const float scalar) {
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                m[col][row] -= scalar;
            }
        }

        return *this;
    }
    constexpr Mat3& operator*=(const float scalar) {
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                m[col][row] *= scalar;
            }
        }

        return *this;
    }
    constexpr Mat3& operator/=(const float scalar) {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Mat3 by zero");
            return *this;
        }

        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                m[col][row] /= scalar;
            }
        }

        return *this;
    }

    // Arithmetic scalar operators
    constexpr Mat3 operator+(const float scalar) const {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = m[col][row] + scalar;
            }
        }

        return result;
    }
    constexpr Mat3 operator-(const float scalar) const {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = m[col][row] - scalar;
            }
        }

        return result;
    }
    constexpr Mat3 operator*(const float scalar) const {
        Mat3 mat = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                mat[col][row] = m[col][row] * scalar;
            }
        }

        return mat;
    }
    constexpr Mat3 operator/(const float scalar) const {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Mat3 by zero");
            return *this;
        }

        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
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
    constexpr bool operator==(const Mat3& other) const {
        Mat3 diff = abs(*this - other);
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                if (diff[col][row] > VELOCITY_MATH_EPSILON)
                    return false;
            }
        }

        return true;
    }
    constexpr bool operator!=(const Mat3& other) const {
        return !(*this == other);
    }

    constexpr Mat3 operator-() const {
        return *this * -1.0f;
    }
    friend std::ostream& operator<<(std::ostream& os, const Mat3& mat) {
        for (int row = 0; row < 3; row++) {
            os << '[';
            for (int col = 0; col < 3; col++) {
                os << (std::abs(mat[col][row]) > VELOCITY_MATH_EPSILON ? mat[col][row] : 0.0f);

                if (col != 2) {
                    os << ", ";
                }
            }
            os << "]\n";
        }

        return os;
    }
    friend Vector3 operator*(const Mat3& mat, const Vector3& vector) {
        Vector3 result = Vector3::zero;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                result[row] += vector[col] * mat[col][row];
            }
        }

        return result;
    }
    [[nodiscard]] constexpr Vector3 column(const size_t index) const {
        return {
            m[index][0],
            m[index][1],
            m[index][2]
        };
    }
    [[nodiscard]] constexpr Vector3 row(const size_t index) const {
        return {
            m[0][index],
            m[1][index],
            m[2][index]
        };
    }

    [[nodiscard]] constexpr float determinant() const {
        return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
            m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
            m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
    }
    constexpr Mat3& transpose() {
        std::swap(m[0][1], m[1][0]);
        std::swap(m[0][2], m[2][0]);
        std::swap(m[1][2], m[2][1]);
        return *this;
    }
    [[nodiscard]] constexpr Mat3 transposed() const {
        return {
            m[0][0],
            m[1][0],
            m[2][0],

            m[0][1],
            m[1][1],
            m[2][1],

            m[0][2],
            m[1][2],
            m[2][2]
        };
    }
    constexpr Mat3& invert() {
        *this = inverse();
        return *this;
    }
    [[nodiscard]] constexpr Mat3 inverse() const {
        const float det = determinant();
        if (std::abs(det) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to get inverse of a matrix where the determinant is zero");
            return *this;
        }

        const float invDet = 1 / det;
        Mat3 result {
            (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invDet,
            -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invDet,
            (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet,

            -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invDet,
            (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invDet,
            -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invDet,

            (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invDet,
            -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invDet,
            (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet
        };

        std::swap(result[0][1], result[1][0]);
        std::swap(result[0][2], result[2][0]);
        std::swap(result[1][2], result[2][1]);

        return result;
    }

    static constexpr Mat3 abs(const Mat3& mat) {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = std::abs(mat[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat3 clamp(const Mat3& mat, const Mat3& min, const Mat3& max) {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = std::clamp(mat[col][row], min[col][row], max[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat3 min(const Mat3& a, const Mat3& b) {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = std::min(a[col][row], b[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat3 max(const Mat3& a, const Mat3& b) {
        Mat3 result = zero;
        for (int col = 0; col < 3; col++) {
            for (int row = 0; row < 3; row++) {
                result[col][row] = std::max(a[col][row], b[col][row]);
            }
        }

        return result;
    }
};

inline Mat3 Mat3::zero = Mat3(0.0f);
inline Mat3 Mat3::identity = Mat3(1.0f);