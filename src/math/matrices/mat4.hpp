#pragma once

#include "math/defines.hpp"
#include "math/vectors/vector4.hpp"

struct Mat4 {
  private:
    float m[4][4]; // Column major [column][row]

  public:
    // Constructors
    constexpr Mat4() : m({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}) {}
    constexpr Mat4(const float scale) : m({scale, 0, 0, 0}, {0, scale, 0, 0}, {0, 0, scale, 0}, {0, 0, 0, scale}) {}
    constexpr Mat4(const float values[16]) : m() {
        for (size_t col = 0; col < 4; col++) {
            for (size_t row = 0; row < 4; row++) {
                m[col][row] = values[col * 4 + row];
            }
        }
    }
    constexpr Mat4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3) : m(
        {column0.x, column0.y, column0.z, column0.w},
        {column1.x, column1.y, column1.z, column1.w},
        {column2.x, column2.y, column2.z, column2.w},
        {column3.x, column3.y, column3.z, column3.w}
    ) {}
    constexpr Mat4(
        const float c0r0, const float c0r1, const float c0r2, const float c0r3,
        const float c1r0, const float c1r1, const float c1r2, const float c1r3,
        const float c2r0, const float c2r1, const float c2r2, const float c2r3,
        const float c3r0, const float c3r1, const float c3r2, const float c3r3
    ) : m({c0r0, c0r1, c0r2, c0r3}, {c1r0, c1r1, c1r2, c1r3}, {c2r0, c2r1, c2r2, c2r3}, {c3r0, c3r1, c3r2, c3r3}) {}

    // Static members
    static Mat4 zero;
    static Mat4 identity;

    // Compound matrix assignment
    constexpr Mat4& operator+=(const Mat4& other) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                m[col][row] += other[col][row];
            }
        }

        return *this;
    }
    constexpr Mat4& operator-=(const Mat4& other) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                m[col][row] -= other[col][row];
            }
        }

        return *this;
    }
    constexpr Mat4& operator*=(const Mat4& other) {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                for (int k = 0; k < 4; k++) {
                    result[col][row] += other[col][k] * m[k][row];
                }
            }
        }

        *this = result;
        return *this;
    }

    // Arithmetic matrix operators
    constexpr Mat4 operator+(const Mat4& other) const {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = m[col][row] + other[col][row];
            }
        }

        return result;
    }
    constexpr Mat4 operator-(const Mat4& other) const {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = m[col][row] - other[col][row];
            }
        }

        return result;
    }
    constexpr Mat4 operator*(const Mat4& other) const {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                for (int k = 0; k < 4; k++) {
                    result[col][row] += other[col][k] * m[k][row];
                }
            }
        }

        return result;
    }

    // Compound scalar assignment
    constexpr Mat4& operator+=(const float scalar) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                m[col][row] += scalar;
            }
        }

        return *this;
    }
    constexpr Mat4& operator-=(const float scalar) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                m[col][row] -= scalar;
            }
        }

        return *this;
    }
    constexpr Mat4& operator*=(const float scalar) {
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                m[col][row] *= scalar;
            }
        }

        return *this;
    }
    constexpr Mat4& operator/=(const float scalar) {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Mat4 by zero");
            return *this;
        }

        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                m[col][row] /= scalar;
            }
        }

        return *this;
    }

    // Arithmetic scalar operators
    constexpr Mat4 operator+(const float scalar) const {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = m[col][row] + scalar;
            }
        }

        return result;
    }
    constexpr Mat4 operator-(const float scalar) const {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = m[col][row] - scalar;
            }
        }

        return result;
    }
    constexpr Mat4 operator*(const float scalar) const {
        Mat4 mat = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                mat[col][row] = m[col][row] * scalar;
            }
        }

        return mat;
    }
    constexpr Mat4 operator/(const float scalar) const {
        if (std::abs(scalar) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to divide Mat4 by zero");
            return *this;
        }

        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
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
    constexpr bool operator==(const Mat4& other) const {
        Mat4 diff = abs(*this - other);
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                if (diff[col][row] > VELOCITY_MATH_EPSILON)
                    return false;
            }
        }

        return true;
    }
    constexpr bool operator!=(const Mat4& other) const {
        return !(*this == other);
    }

    constexpr Mat4 operator-() const {
        return *this * -1.0f;
    }
    friend std::ostream& operator<<(std::ostream& os, const Mat4& mat) {
        for (int row = 0; row < 4; row++) {
            os << '[';
            for (int col = 0; col < 4; col++) {
                os << (std::abs(mat[col][row]) > VELOCITY_MATH_EPSILON ? mat[col][row] : 0.0f);

                if (col != 3) {
                    os << ", ";
                }
            }
            os << "]\n";
        }

        return os;
    }
    friend Vector4 operator*(const Mat4& mat, const Vector4& vector) {
        Vector4 result = Vector4::zero;
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                result[row] += vector[col] * mat[col][row];
            }
        }

        return result;
    }
    [[nodiscard]] constexpr Vector4 column(const size_t index) const {
        return {
            m[index][0],
            m[index][1],
            m[index][2],
            m[index][3]
        };
    }
    [[nodiscard]] constexpr Vector4 row(const size_t index) const {
        return {
            m[0][index],
            m[1][index],
            m[2][index],
            m[3][index]
        };
    }

    [[nodiscard]] constexpr float determinant() const {
        return m[0][0] * determinant3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]) -
            m[1][0] * determinant3x3(m[0][1], m[0][2], m[0][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]) +
            m[2][0] * determinant3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[3][1], m[3][2], m[3][3]) -
            m[3][0] * determinant3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3]);
    }
    constexpr Mat4& transpose() {
        std::swap(m[0][1], m[1][0]);
        std::swap(m[0][2], m[2][0]);
        std::swap(m[0][3], m[3][0]);
        std::swap(m[1][2], m[2][1]);
        std::swap(m[1][3], m[3][1]);
        std::swap(m[2][3], m[3][2]);
        return *this;
    }
    [[nodiscard]] constexpr Mat4 transposed() const {
        return {
            m[0][0],
            m[1][0],
            m[2][0],
            m[3][0],

            m[0][1],
            m[1][1],
            m[2][1],
            m[3][1],

            m[0][2],
            m[1][2],
            m[2][2],
            m[3][2],

            m[0][3],
            m[1][3],
            m[2][3],
            m[3][3],
        };
    }
    constexpr Mat4& invert() {
        *this = inverse();
        return *this;
    }
    [[nodiscard]] constexpr Mat4 inverse() const {
        const float det = determinant();
        if (std::abs(det) < VELOCITY_MATH_EPSILON) {
            VELOCITY_MATH_ERROR("Tried to get inverse of a matrix where the determinant is zero");
            return *this;
        }

        const float invDet = 1 / det;
        Mat4 result {
            determinant3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]) * invDet,
            -determinant3x3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]) * invDet,
            determinant3x3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]) * invDet,
            -determinant3x3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]) * invDet,

            -determinant3x3(m[0][1], m[0][2], m[0][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]) * invDet,
            determinant3x3(m[0][0], m[0][2], m[0][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]) * invDet,
            -determinant3x3(m[0][0], m[0][1], m[0][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]) * invDet,
            determinant3x3(m[0][0], m[0][1], m[0][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]) * invDet,

            determinant3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[3][1], m[3][2], m[3][3]) * invDet,
            -determinant3x3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[3][0], m[3][2], m[3][3]) * invDet,
            determinant3x3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[3][0], m[3][1], m[3][3]) * invDet,
            -determinant3x3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[3][0], m[3][1], m[3][2]) * invDet,

            -determinant3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3]) * invDet,
            determinant3x3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3]) * invDet,
            -determinant3x3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3]) * invDet,
            determinant3x3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]) * invDet
        };

        std::swap(result[0][1], result[1][0]);
        std::swap(result[0][2], result[2][0]);
        std::swap(result[0][3], result[3][0]);
        std::swap(result[1][2], result[2][1]);
        std::swap(result[1][3], result[3][1]);
        std::swap(result[2][3], result[3][2]);

        return result;
    }

    static constexpr Mat4 abs(const Mat4& mat) {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = std::abs(mat[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat4 clamp(const Mat4& mat, const Mat4& min, const Mat4& max) {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = std::clamp(mat[col][row], min[col][row], max[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat4 min(const Mat4& a, const Mat4& b) {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = std::min(a[col][row], b[col][row]);
            }
        }

        return result;
    }
    static constexpr Mat4 max(const Mat4& a, const Mat4& b) {
        Mat4 result = zero;
        for (int col = 0; col < 4; col++) {
            for (int row = 0; row < 4; row++) {
                result[col][row] = std::max(a[col][row], b[col][row]);
            }
        }

        return result;
    }

  private:
    static constexpr float determinant3x3(const float c0r0, const float c0r1, const float c0r2, const float c1r0, const float c1r1, const float c1r2, const float c2r0, const float c2r1, const float c2r2) {
        return c0r0 * (c1r1 * c2r2 - c2r1 * c1r2) -
            c1r0 * (c0r1 * c2r2 - c2r1 * c0r2) +
            c2r0 * (c0r1 * c1r2 - c1r1 * c0r2);
    }

};

inline Mat4 Mat4::zero = Mat4(0.0f);
inline Mat4 Mat4::identity = Mat4(1.0f);