#pragma once

#include <cmath>
#include <math.h>
#include <random>
#include <iostream>

/////////////////////////// Utils ///////////////////////////////
inline float radians(const float deg) { return deg * M_PI / 180; }
inline float degress(const float radians) { return radians * 180 / M_PI; }

inline float randomFloat(const float min, const float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
////////////////////////////////////////////////////////////////

struct mat4;

struct vec2
{
    union
    {
        float x, r, u;
    };

    union
    {
        float y, g, v;
    };

    vec2();
    vec2(const float x, const float y);

    // Operators
    float &operator[](const int i);
    const float &operator[](const int i) const;

    vec2 operator/(const float rhs) const;

    vec2 operator*(const vec2 &rhs) const;

    bool operator==(const vec2 &rhs) const;
    bool operator!=(const vec2 &rhs) const;
};

struct vec3
{
    union
    {
        float x, r;
    };

    union
    {
        float y, g;
    };

    union
    {
        float z, b;
    };

    vec3();
    vec3(const float x, const float y, const float z);
    vec3(const float val);

    vec3 cross(const vec3 &rhs) const;
    float dot(const vec3 &r) const;
    vec3 normalize() const;
    float magnitude() const;

    // Operators
    vec3 operator*(const float &rhs) const;
    vec3 operator*(const vec3 &rhs) const;
    void operator*=(const float &rhs);
    void operator*=(const vec3 &rhs);

    vec3 operator-(const vec3 &rhs) const;
    void operator-=(const vec3 &rhs);
    vec3 operator+(const vec3 &rhs) const;
    void operator+=(const vec3 &rhs);

    vec3 operator/(const float &rhs) const;

    bool operator!=(const vec3 &rhs) const;
    bool operator==(const vec3 &rhs) const;

    float &operator[](const int i);
    const float &operator[](const int i) const;

    // Friend operators
    friend vec3 operator*(const float &lhs, const vec3 &rhs) { return vec3{rhs.x * lhs, rhs.y * lhs, rhs.z * lhs}; }
    friend std::ostream &operator<<(std::ostream &os, const vec3 &v3);
};

struct vec4
{
    union
    {
        float x, r;
    };

    union
    {
        float y, g;
    };

    union
    {
        float z, b;
    };

    union
    {
        float w, a;
    };

    vec4();
    vec4(const float x, const float y, const float z, const float w);

    float dot(const vec4 &rhs) const;

    // Operators
    vec4 operator*(const vec4 &rhs) const;

    vec4 operator+(const vec4 &rhs) const;

    vec4 operator/(const float rhs) const;

    bool operator==(const vec4 &rhs) const;

    float &operator[](const int i);
    const float &operator[](const int i) const;

    // Friend operators
    friend vec4 operator*(const float lhs, const vec4 &rhs)
    {
        return vec4{rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs};
    }

    friend vec4 operator*(const vec4 &lhs, const float rhs)
    {
        return vec4{rhs * lhs.x, rhs * lhs.y, rhs * lhs.z, rhs * lhs.w};
    }
};

struct mat2
{
    mat2() = default;
    mat2(const float diagonal);
    mat2(const vec2 col0, const vec2 col1);
    mat2(const float m00, const float m01, const float m10, const float m11);

    float determinant() const;

    mat2 transpose() const;
    mat2 minor() const;
    mat2 cofactor() const;
    mat2 adjugate() const;
    mat2 inverse() const;

    vec2 row0() const;
    vec2 row1() const;

    // Operators
    vec2 &operator[](const int i);
    const vec2 &operator[](const int i) const;

    mat2 operator/(const float rhs) const;

    mat2 operator*(const mat2 &rhs) const;
    void operator*=(const float rhs);

    bool operator==(const mat2 &rhs) const;

    // Friend operators
    friend std::ostream &operator<<(std::ostream &os, const mat2 &m2);

    vec2 col0;
    vec2 col1;
};

struct mat3
{
    mat3() = default;
    mat3(const float diagonal);
    mat3(const vec3 col0, const vec3 col1, const vec3 col2);
    mat3(const float m00, const float m01, const float m02, const float m10, const float m11, const float m12,
         const float m20, const float m21, const float m22);
    mat3(const mat4 &m4);

    float determinant() const;

    mat3 transpose() const;
    mat3 minor() const;
    mat3 cofactor() const;
    mat3 adjugate() const;
    mat3 inverse() const;

    vec3 row0() const;
    vec3 row1() const;
    vec3 row2() const;

    // Operators
    vec3 &operator[](const int i);
    const vec3 &operator[](const int i) const;

    mat3 operator/(const float rhs) const;

    mat3 operator*(const float rhs) const;
    mat3 operator*(const mat3 &rhs) const;

    bool operator==(const mat3 &rhs) const;

    // Friend operators
    friend std::ostream &operator<<(std::ostream &os, const mat3 &m3);

    vec3 col0;
    vec3 col1;
    vec3 col2;
};

struct mat4
{
    mat4() = default;
    mat4(const float diagonal);
    mat4(const mat4 &rhs);

    mat4(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
         const float m12, const float m13, const float m20, const float m21, const float m22, const float m23,
         const float m30, const float m31, const float m32, const float m33);

    float determinant() const;

    /* mat4 transpose() const; */
    /* mat4 adjugate() const; */
    /* mat4 inverse() const; */

    // Operators
    vec4 &operator[](const int i);
    const vec4 &operator[](const int i) const;

    bool operator==(const mat4 &rhs) const;

    mat4 operator*(const mat4 &rhs);

    mat4 operator/(const float rhs) const;

    // Friend operators
    friend std::ostream &operator<<(std::ostream &os, const mat4 &m4);

    vec4 col0;
    vec4 col1;
    vec4 col2;
    vec4 col3;
};

/////////////////////////// vec2 ////////////////////////////////
inline vec2::vec2() : x(0), y(0) {}

inline vec2::vec2(const float x, const float y) : x(x), y(y) {}

inline float &vec2::operator[](const int i) { return (&x)[i]; }

inline const float &vec2::operator[](const int i) const { return (&x)[i]; }

inline vec2 vec2::operator/(const float rhs) const { return vec2{x / rhs, y / rhs}; }

inline vec2 vec2::operator*(const vec2 &rhs) const { return vec2{x * rhs.x, y * rhs.y}; }

inline bool vec2::operator==(const vec2 &rhs) const { return x == rhs.x && y == rhs.y; }
inline bool vec2::operator!=(const vec2 &rhs) const { return x != rhs.x || y != rhs.y; }
/////////////////////////////////////////////////////////////////

/////////////////////////// vec3 ////////////////////////////////
inline vec3::vec3() : x(0), y(0), z(0) {}

inline vec3::vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

inline vec3::vec3(const float val) : x(val), y(val), z(val) {}

inline vec3 vec3::cross(const vec3 &rhs) const
{
    return vec3{
        (y * rhs.z) - (z * rhs.y),
        (z * rhs.x) - (x * rhs.z),
        (x * rhs.y) - (y * rhs.x),
    };
}

inline float vec3::dot(const vec3 &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

inline vec3 vec3::normalize() const { return *this / magnitude(); }

inline float vec3::magnitude() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

inline vec3 vec3::operator*(const float &rhs) const { return vec3{x * rhs, y * rhs, z * rhs}; }

inline void vec3::operator*=(const float &rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
}

inline vec3 vec3::operator*(const vec3 &rhs) const { return vec3{x * rhs.x, y * rhs.y, z * rhs.z}; }

inline void vec3::operator*=(const vec3 &rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
}

inline vec3 vec3::operator-(const vec3 &rhs) const { return vec3{x - rhs.x, y - rhs.y, z - rhs.z}; }

inline void vec3::operator-=(const vec3 &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
}

inline vec3 vec3::operator+(const vec3 &rhs) const { return vec3{x + rhs.x, y + rhs.y, z + rhs.z}; }

inline void vec3::operator+=(const vec3 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

inline vec3 vec3::operator/(const float &rhs) const { return vec3{x / rhs, y / rhs, z / rhs}; }

inline bool vec3::operator!=(const vec3 &rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

inline bool vec3::operator==(const vec3 &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

inline float &vec3::operator[](const int i) { return (&x)[i]; }

inline const float &vec3::operator[](const int i) const { return (&x)[i]; }

inline std::ostream &operator<<(std::ostream &os, const vec3 &v3)
{
    os << "[ " << v3.x << " " << v3.y << " " << v3.z << " ]";
    return os;
}
////////////////////////////////////////////////////////////////

/////////////////////////// vec4 ////////////////////////////////
inline vec4::vec4() : x(0), y(0), z(0), w(0) {}

inline vec4::vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

inline float &vec4::operator[](const int i) { return (&x)[i]; }

inline const float &vec4::operator[](const int i) const { return (&x)[i]; }

inline vec4 vec4::operator*(const vec4 &rhs) const { return vec4{x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w}; }

inline vec4 vec4::operator+(const vec4 &rhs) const { return vec4{x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w}; }

inline vec4 vec4::operator/(const float rhs) const { return vec4{x / rhs, y / rhs, z / rhs, w / rhs}; }

inline bool vec4::operator==(const vec4 &rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }

inline float vec4::dot(const vec4 &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }
/////////////////////////////////////////////////////////////////

/////////////////////////// mat2 ////////////////////////////////

inline mat2::mat2(const float diagonal) : col0(diagonal, 0), col1(0, diagonal) {}

inline mat2::mat2(const vec2 col0, const vec2 col1) : col0(col0), col1(col1) {}

inline mat2::mat2(const float m00, const float m01, const float m10, const float m11) : col0(m00, m01), col1(m10, m11)
{
}

inline float mat2::determinant() const { return col0[0] * col1[1] - col0[1] * col1[0]; }

inline mat2 mat2::transpose() const
{
    const auto r0 = row0();
    const auto r1 = row1();

    return mat2{r0, r1};
}

inline mat2 mat2::minor() const
{
    return mat2{
        (*this)[1][1], (*this)[1][0],  // Col 0
        (*this)[0][1], (*this)[0][0],  // Col 1
    };
}

inline mat2 mat2::cofactor() const
{
    mat2 m = minor();
    m[0][1] *= -1;
    m[1][0] *= -1;
    return m;
}

inline mat2 mat2::adjugate() const { return cofactor().transpose(); }

inline mat2 mat2::inverse() const { return adjugate() / determinant(); }

inline vec2 mat2::row0() const { return vec2{(*this)[0][0], (*this)[1][0]}; }

inline vec2 mat2::row1() const { return vec2{(*this)[0][1], (*this)[1][1]}; }

// Write matrix in row major on the ostream.
inline std::ostream &operator<<(std::ostream &os, const mat2 &m2)
{
    os << "[" << m2[0][0] << " " << m2[1][0] << "]\n";
    os << "[" << m2[0][1] << " " << m2[1][1] << "]\n";
    return os;
}

inline vec2 &mat2::operator[](const int i) { return (&col0)[i]; }
inline const vec2 &mat2::operator[](const int i) const { return (&col0)[i]; }

inline mat2 mat2::operator/(const float rhs) const
{
    return mat2{
        (*this)[0] / rhs,  // Col 0
        (*this)[1] / rhs,  // Col 1
    };
}

inline mat2 mat2::operator*(const mat2 &rhs) const
{
    return mat2{
        (*this)[0][0] * rhs[0][0] + (*this)[1][0] * rhs[0][1],
        (*this)[0][1] * rhs[0][0] + (*this)[1][1] * rhs[0][1],  // Col 0
        (*this)[0][0] * rhs[1][0] + (*this)[1][0] * rhs[1][1],
        (*this)[0][1] * rhs[1][0] + (*this)[1][1] * rhs[1][1],  // Col 1
    };
}

inline void mat2::operator*=(const float rhs)
{
    (*this)[0][0] *= rhs;
    (*this)[0][1] *= rhs;
    (*this)[1][0] *= rhs;
    (*this)[1][1] *= rhs;
}

inline bool mat2::operator==(const mat2 &rhs) const { return (*this)[0] == rhs[0] && (*this)[1] == rhs[1]; }
/////////////////////////////////////////////////////////////////

/////////////////////////// mat3 ////////////////////////////////
inline mat3::mat3(const float diagonal)
    : col0{diagonal, 0.0f, 0.0f}, col1{0.0f, diagonal, 0.0f}, col2{0.0f, 0.0f, diagonal}
{
}

inline mat3::mat3(const vec3 col0, const vec3 col1, const vec3 col2) : col0(col0), col1(col1), col2(col2) {}

inline mat3::mat3(const float m00, const float m01, const float m02, const float m10, const float m11, const float m12,
                  const float m20, const float m21, const float m22)
    : col0(m00, m01, m02), col1(m10, m11, m12), col2(m20, m21, m22)
{
}

inline mat3::mat3(const mat4 &m4)
    : col0(m4[0].x, m4[0].y, m4[0].z), col1(m4[1].x, m4[1].y, m4[1].z), col2(m4[2].x, m4[2].y, m4[2].z)
{
}

inline float mat3::determinant() const
{
    const mat2 a{
        (*this)[1][1], (*this)[1][2],  // col 0
        (*this)[2][1], (*this)[2][2],  // col 1
    };

    const mat2 b{
        (*this)[0][1], (*this)[0][2],  // col 0
        (*this)[2][1], (*this)[2][2],  // col 1
    };

    const mat2 c{
        (*this)[0][1], (*this)[0][2],  // col 0
        (*this)[1][1], (*this)[1][2],  // col 1
    };

    const auto aPivot = (*this)[0][0];
    const auto bPivot = (*this)[1][0];
    const auto cPivot = (*this)[2][0];

    return aPivot * a.determinant() - bPivot * b.determinant() + cPivot * c.determinant();
}

inline mat3 mat3::minor() const
{
    mat3 m;

    m[0][0] = mat2{(*this)[1][1], (*this)[1][2], (*this)[2][1], (*this)[2][2]}.determinant();
    m[0][1] = mat2{(*this)[1][0], (*this)[1][2], (*this)[2][0], (*this)[2][2]}.determinant();
    m[0][2] = mat2{(*this)[1][0], (*this)[1][1], (*this)[2][0], (*this)[2][1]}.determinant();

    m[1][0] = mat2{(*this)[0][1], (*this)[0][2], (*this)[2][1], (*this)[2][2]}.determinant();
    m[1][1] = mat2{(*this)[0][0], (*this)[0][2], (*this)[2][0], (*this)[2][2]}.determinant();
    m[1][2] = mat2{(*this)[0][0], (*this)[0][1], (*this)[2][0], (*this)[2][1]}.determinant();

    m[2][0] = mat2{(*this)[0][1], (*this)[0][2], (*this)[1][1], (*this)[1][2]}.determinant();
    m[2][1] = mat2{(*this)[0][0], (*this)[0][2], (*this)[1][0], (*this)[1][2]}.determinant();
    m[2][2] = mat2{(*this)[0][0], (*this)[0][1], (*this)[1][0], (*this)[1][1]}.determinant();

    return m;
}

inline mat3 mat3::cofactor() const
{
    mat3 c = minor();
    c[0][1] *= -1;
    c[1][0] *= -1;
    c[1][2] *= -1;
    c[2][1] *= -1;
    return c;
}

inline mat3 mat3::transpose() const
{
    const auto r0 = row0();
    const auto r1 = row1();
    const auto r2 = row2();

    return mat3{r0, r1, r2};
}

inline mat3 mat3::adjugate() const { return cofactor().transpose(); }

inline mat3 mat3::inverse() const { return adjugate() / determinant(); }

inline vec3 mat3::row0() const { return vec3{(*this)[0][0], (*this)[1][0], (*this)[2][0]}; }

inline vec3 mat3::row1() const { return vec3{(*this)[0][1], (*this)[1][1], (*this)[2][1]}; }

inline vec3 mat3::row2() const { return vec3{(*this)[0][2], (*this)[1][2], (*this)[2][2]}; }

inline vec3 &mat3::operator[](const int i) { return (&col0)[i]; }
inline const vec3 &mat3::operator[](const int i) const { return (&col0)[i]; }

inline mat3 mat3::operator/(const float rhs) const
{
    return mat3{
        (*this)[0] / rhs,
        (*this)[1] / rhs,
        (*this)[2] / rhs,
    };
}

inline mat3 mat3::operator*(const float rhs) const
{
    return mat3{
        (*this)[0] * rhs,
        (*this)[1] * rhs,
        (*this)[2] * rhs,
    };
}

inline mat3 mat3::operator*(const mat3 &rhs) const
{
    mat3 r;

    const vec3 lhsRow0{(*this)[0][0], (*this)[1][0], (*this)[2][0]};
    const vec3 lhsRow1{(*this)[0][1], (*this)[1][1], (*this)[2][1]};
    const vec3 lhsRow2{(*this)[0][2], (*this)[1][2], (*this)[2][2]};

    r[0][0] = lhsRow0.dot(rhs[0]);
    r[1][0] = lhsRow0.dot(rhs[1]);
    r[2][0] = lhsRow0.dot(rhs[2]);

    r[0][1] = lhsRow1.dot(rhs[0]);
    r[1][1] = lhsRow1.dot(rhs[1]);
    r[2][1] = lhsRow1.dot(rhs[2]);

    r[0][2] = lhsRow2.dot(rhs[0]);
    r[1][2] = lhsRow2.dot(rhs[1]);
    r[2][2] = lhsRow2.dot(rhs[2]);

    return r;
}

inline bool mat3::operator==(const mat3 &rhs) const
{
    return (*this)[0] == rhs[0] && (*this)[1] == rhs[1] && (*this)[2] == rhs[2];
}

// Write matrix in row major on the ostream.
inline std::ostream &operator<<(std::ostream &os, const mat3 &m3)
{
    os << "[ " << m3[0][0] << " " << m3[1][0] << " " << m3[2][0] << " ]\n";
    os << "[ " << m3[0][1] << " " << m3[1][1] << " " << m3[2][1] << " ]\n";
    os << "[ " << m3[0][2] << " " << m3[1][2] << " " << m3[2][2] << " ]\n";
    return os;
}
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////

/////////////////////////// mat4 ////////////////////////////////
inline mat4::mat4(const float diagonal)
    : col0{diagonal, 0.0f, 0.0f, 0.0f},
      col1{0.0f, diagonal, 0.0f, 0.0f},
      col2{0.0f, 0.0f, diagonal, 0.0f},
      col3{0.0f, 0.0f, 0.0f, diagonal}
{
}
inline mat4::mat4(const mat4 &r) : col0(r.col0), col1(r.col1), col2(r.col2), col3(r.col3) {}

inline mat4::mat4(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
                  const float m12, const float m13, const float m20, const float m21, const float m22, const float m23,
                  const float m30, const float m31, const float m32, const float m33)
    : col0(m00, m01, m02, m03), col1(m10, m11, m12, m13), col2(m20, m21, m22, m23), col3(m30, m31, m32, m33)
{
}

inline float mat4::determinant() const
{
    const mat3 a{
        (*this)[1][1], (*this)[1][2], (*this)[1][3],  // col 0
        (*this)[2][1], (*this)[2][2], (*this)[2][3],  // col 1
        (*this)[3][1], (*this)[3][2], (*this)[3][3],  // col 2
    };

    const mat3 b{
        (*this)[0][1], (*this)[0][2], (*this)[0][3],  // col 0
        (*this)[2][1], (*this)[2][2], (*this)[2][3],  // col 1
        (*this)[3][1], (*this)[3][2], (*this)[3][3],  // col 2
    };

    const mat3 c{
        (*this)[0][1], (*this)[0][2], (*this)[0][3],  // col 0
        (*this)[1][1], (*this)[1][2], (*this)[1][3],  // col 1
        (*this)[3][1], (*this)[3][2], (*this)[3][3],  // col 2
    };

    const mat3 d{
        (*this)[0][1], (*this)[0][2], (*this)[0][3],  // col 0
        (*this)[1][1], (*this)[1][2], (*this)[1][3],  // col 1
        (*this)[2][1], (*this)[2][2], (*this)[2][3],  // col 2
    };

    const auto aPivot = (*this)[0][0];
    const auto bPivot = (*this)[1][0];
    const auto cPivot = (*this)[2][0];
    const auto dPivot = (*this)[3][0];

    return aPivot * a.determinant() - bPivot * b.determinant() + cPivot * c.determinant() - dPivot * d.determinant();

    return 0.0f;
}

/* inline mat4 mat4::transpose() const */
/* { */
/*     mat4 t; */

/*     t[0][0] = (*this)[0][0]; */
/*     t[1][0] = (*this)[0][1]; */
/*     t[2][0] = (*this)[0][2]; */
/*     t[3][0] = (*this)[0][3]; */

/*     t[0][1] = (*this)[1][0]; */
/*     t[1][1] = (*this)[1][1]; */
/*     t[2][1] = (*this)[1][2]; */
/*     t[3][1] = (*this)[1][3]; */

/*     t[0][2] = (*this)[2][0]; */
/*     t[1][2] = (*this)[2][1]; */
/*     t[2][2] = (*this)[2][2]; */
/*     t[3][2] = (*this)[2][3]; */

/*     t[0][3] = (*this)[3][0]; */
/*     t[1][3] = (*this)[3][1]; */
/*     t[2][3] = (*this)[3][2]; */
/*     t[3][3] = (*this)[3][3]; */

/*     return t; */
/* } */

/* inline mat4 mat4::adjugate() const */
/* { */
/*     mat4 c; */

/*     // Col0 */
/*     c[0][0] = */
/*         mat3{ */
/*             (*this)[1][1], (*this)[1][2], (*this)[1][3],  // Col0 */
/*             (*this)[2][1], (*this)[2][2], (*this)[2][3],  // Col1 */
/*             (*this)[3][1], (*this)[3][2], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant(); */
/*     c[0][1] = */
/*         -mat3{ */
/*             (*this)[1][0], (*this)[1][2], (*this)[1][3],  // Col0 */
/*             (*this)[2][0], (*this)[2][2], (*this)[2][3],  // Col1 */
/*             (*this)[3][0], (*this)[3][2], (*this)[3][3],  // Col2 */
/*         } */
/*              .determinant(); */
/*     c[0][2] = */
/*         mat3{ */
/*             (*this)[1][0], (*this)[1][1], (*this)[1][3],  // Col0 */
/*             (*this)[2][0], (*this)[2][1], (*this)[2][3],  // Col1 */
/*             (*this)[3][0], (*this)[3][1], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant(); */
/*     c[0][3] = */
/*         mat3{ */
/*             (*this)[1][0], (*this)[1][1], (*this)[1][2],  // Col0 */
/*             (*this)[2][0], (*this)[2][1], (*this)[2][2],  // Col1 */
/*             (*this)[3][0], (*this)[3][1], (*this)[3][2],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */

/*     // Col 1 */
/*     c[1][0] = */
/*         mat3{ */
/*             (*this)[0][1], (*this)[0][2], (*this)[0][3],  // Col0 */
/*             (*this)[2][1], (*this)[2][2], (*this)[2][3],  // Col1 */
/*             (*this)[3][1], (*this)[3][2], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */
/*     c[1][1] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][2], (*this)[0][3],  // Col0 */
/*             (*this)[2][0], (*this)[2][2], (*this)[2][3],  // Col1 */
/*             (*this)[3][0], (*this)[3][2], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant(); */
/*     c[1][2] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][1], (*this)[0][3],  // Col0 */
/*             (*this)[2][0], (*this)[2][1], (*this)[2][3],  // Col1 */
/*             (*this)[3][0], (*this)[3][1], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */
/*     c[1][3] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][1], (*this)[0][2],  // Col0 */
/*             (*this)[2][0], (*this)[2][1], (*this)[2][2],  // Col1 */
/*             (*this)[3][0], (*this)[3][1], (*this)[3][2],  // Col2 */
/*         } */
/*             .determinant(); */

/*     // Col 2 */
/*     c[2][0] = */
/*         mat3{ */
/*             (*this)[0][1], (*this)[0][2], (*this)[0][3],  // Col0 */
/*             (*this)[1][1], (*this)[1][2], (*this)[1][3],  // Col1 */
/*             (*this)[3][1], (*this)[3][2], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant(); */
/*     c[2][1] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][2], (*this)[0][3],  // Col0 */
/*             (*this)[1][0], (*this)[1][2], (*this)[1][3],  // Col1 */
/*             (*this)[3][0], (*this)[3][2], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */
/*     c[2][2] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][1], (*this)[0][3],  // Col0 */
/*             (*this)[1][0], (*this)[1][1], (*this)[1][3],  // Col1 */
/*             (*this)[3][0], (*this)[3][1], (*this)[3][3],  // Col2 */
/*         } */
/*             .determinant(); */
/*     c[2][3] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][1], (*this)[0][2],  // Col0 */
/*             (*this)[1][0], (*this)[1][1], (*this)[1][2],  // Col1 */
/*             (*this)[3][0], (*this)[3][1], (*this)[3][2],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */

/*     // Col 3 */
/*     c[3][0] = */
/*         mat3{ */
/*             (*this)[0][1], (*this)[0][2], (*this)[0][3],  // Col0 */
/*             (*this)[1][1], (*this)[1][2], (*this)[1][3],  // Col1 */
/*             (*this)[2][1], (*this)[2][2], (*this)[2][3],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */
/*     c[3][1] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][2], (*this)[0][3],  // Col0 */
/*             (*this)[1][0], (*this)[1][2], (*this)[1][3],  // Col1 */
/*             (*this)[2][0], (*this)[2][2], (*this)[2][3],  // Col2 */
/*         } */
/*             .determinant(); */
/*     c[3][2] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][1], (*this)[0][3],  // Col0 */
/*             (*this)[1][0], (*this)[1][1], (*this)[1][3],  // Col1 */
/*             (*this)[2][0], (*this)[2][1], (*this)[2][3],  // Col2 */
/*         } */
/*             .determinant() * */
/*         -1; */
/*     c[3][3] = */
/*         mat3{ */
/*             (*this)[0][0], (*this)[0][1], (*this)[0][2],  // Col0 */
/*             (*this)[1][0], (*this)[1][1], (*this)[1][2],  // Col1 */
/*             (*this)[2][0], (*this)[2][1], (*this)[2][2],  // Col2 */
/*         } */
/*             .determinant(); */

/*     return c; */
/* } */

/* inline mat4 mat4::inverse() const { return adjugate() / determinant(); } */

inline vec4 &mat4::operator[](const int i) { return (&col0)[i]; }
inline const vec4 &mat4::operator[](const int i) const { return (&col0)[i]; }

inline bool mat4::operator==(const mat4 &rhs) const
{
    return (*this)[0] == rhs[0] && (*this)[1] == rhs[1] && (*this)[2] == rhs[2] && (*this)[3] == rhs[3];
}

inline mat4 mat4::operator*(const mat4 &rhs)
{
    mat4 m{};

    const vec4 lhsRow0{(*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0]};
    const vec4 lhsRow1{(*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1]};
    const vec4 lhsRow2{(*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2]};
    const vec4 lhsRow4{(*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3]};

    m[0][0] = lhsRow0.dot(rhs[0]);
    m[1][0] = lhsRow0.dot(rhs[1]);
    m[2][0] = lhsRow0.dot(rhs[2]);
    m[3][0] = lhsRow0.dot(rhs[3]);

    m[0][1] = lhsRow1.dot(rhs[0]);
    m[1][1] = lhsRow1.dot(rhs[1]);
    m[2][1] = lhsRow1.dot(rhs[2]);
    m[3][1] = lhsRow1.dot(rhs[3]);

    m[0][2] = lhsRow2.dot(rhs[0]);
    m[1][2] = lhsRow2.dot(rhs[1]);
    m[2][2] = lhsRow2.dot(rhs[2]);
    m[3][2] = lhsRow2.dot(rhs[3]);

    m[0][3] = lhsRow4.dot(rhs[0]);
    m[1][3] = lhsRow4.dot(rhs[1]);
    m[2][3] = lhsRow4.dot(rhs[2]);
    m[3][3] = lhsRow4.dot(rhs[3]);

    return m;
}

inline mat4 mat4::operator/(const float rhs) const
{
    mat4 m;
    m[0] = (*this)[0] / rhs;
    m[1] = (*this)[1] / rhs;
    m[2] = (*this)[2] / rhs;
    m[3] = (*this)[3] / rhs;
    return m;
}

// Write matrix in row major on the ostream.
inline std::ostream &operator<<(std::ostream &os, const mat4 &m4)
{
    os << "[" << m4[0][0] << " " << m4[1][0] << " " << m4[2][0] << " " << m4[3][0] << "]\n";
    os << "[" << m4[0][1] << " " << m4[1][1] << " " << m4[2][1] << " " << m4[3][1] << "]\n";
    os << "[" << m4[0][2] << " " << m4[1][2] << " " << m4[2][2] << " " << m4[3][2] << "]\n";
    os << "[" << m4[0][3] << " " << m4[1][3] << " " << m4[2][3] << " " << m4[3][3] << "]\n";
    return os;
}
////////////////////////////////////////////////////////////////

inline mat4 translate(const mat4 &m, const vec3 &v)
{
    mat4 t{m};
    t[3][0] = v.x;
    t[3][1] = v.y;
    t[3][2] = v.z;
    return t;
}

inline mat4 rotate(const mat4 &m, const float &a, const vec3 &v)
{
    const auto c = cos(a);
    const auto s = sin(a);

    const auto r = v.normalize();
    const auto x = r.x;
    const auto y = r.y;
    const auto z = r.z;

    mat4 rot;

    rot[0][0] = (1 - c) * pow(x, 2) + c;
    rot[0][1] = (1 - c) * x * y + s * z;
    rot[0][2] = (1 - c) * x * z - s * y;

    rot[1][0] = (1 - c) * x * y - s * z;
    rot[1][1] = (1 - c) * pow(y, 2) + c;
    rot[1][2] = (1 - c) * y * z + s * x;

    rot[2][0] = (1 - c) * x * z + s * y;
    rot[2][1] = (1 - c) * y * z - s * x;
    rot[2][2] = (1 - c) * pow(z, 2) + c;

    mat4 res;
    res[0] = rot[0][0] * m[0] + rot[0][1] * m[1] + rot[0][2] * m[2];
    res[1] = rot[1][0] * m[0] + rot[1][1] * m[1] + rot[1][2] * m[2];
    res[2] = rot[2][0] * m[0] + rot[2][1] * m[1] + rot[2][2] * m[2];
    res[3] = m[3];

    return res;
}

inline mat4 perspective(const float &fov, const float &aspectRatio, const float &zNear, const float &zFar)
{
    mat4 p{0};

    const auto tanHalfFov = tan(fov / 2);

    p[0][0] = 1 / (aspectRatio * tanHalfFov);
    p[1][1] = 1 / tanHalfFov;
    p[2][2] = -(zFar + zNear) / (zFar - zNear);
    p[2][3] = -1;
    p[3][2] = -(2 * zFar * zNear) / (zFar - zNear);

    return p;
}

inline mat4 lookAt(const vec3 &eye, const vec3 &target, const vec3 &worldUp)
{
    const auto forward = (eye - target).normalize();
    const auto left = worldUp.cross(forward).normalize();
    const auto up = forward.cross(left);

    mat4 lookAtm{1.0f};

    lookAtm[0][0] = left.x;
    lookAtm[0][1] = up.x;
    lookAtm[0][2] = forward.x;

    lookAtm[1][0] = left.y;
    lookAtm[1][1] = up.y;
    lookAtm[1][2] = forward.y;

    lookAtm[2][0] = left.z;
    lookAtm[2][1] = up.z;
    lookAtm[2][2] = forward.z;

    lookAtm[3][0] = -left.x * eye.x - left.y * eye.y - left.z * eye.z;
    lookAtm[3][1] = -up.x * eye.x - up.y * eye.y - up.z * eye.z;
    lookAtm[3][2] = -forward.x * eye.x - forward.y * eye.y - forward.z * eye.z;

    return lookAtm;
}

inline mat4 scale(const mat4 &m, const vec3 &v)
{
    mat4 s{};
    s[0] = v.x * m[0];
    s[1] = v.y * m[1];
    s[2] = v.z * m[2];
    s[3] = m[3];
    return s;
}
