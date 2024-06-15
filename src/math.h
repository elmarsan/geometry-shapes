#pragma once

#include <cmath>
#include <math.h>
#include <random>

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

    float &operator[](const int i);
    const float &operator[](const int i) const;

    // Friend operators
    friend vec3 operator*(const float &lhs, const vec3 &rhs) { return vec3{rhs.x * lhs, rhs.y * lhs, rhs.z * lhs}; }
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
    vec4(const float val);
    vec4(const float x, const float y, const float z, const float w);

    float dot(const vec4 rhs) const;

    // Operators
    vec4 operator*(const vec4 rhs) const;

    vec4 operator+(const vec4 &rhs) const;
    
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

/////////////////////////// vec2 ////////////////////////////////
inline vec2::vec2() : x(0), y(0) {}

inline vec2::vec2(const float x, const float y) : x(x), y(y) {}
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

inline float &vec3::operator[](const int i) { return (&x)[i]; }

inline const float &vec3::operator[](const int i) const { return (&x)[i]; }
////////////////////////////////////////////////////////////////

/////////////////////////// vec4 ////////////////////////////////
inline vec4::vec4() : x(0), y(0), z(0), w(0) {}

inline vec4::vec4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}

inline vec4::vec4(const float val): x(val), y(val), z(val), w(val) {}

inline float &vec4::operator[](const int i) { return (&x)[i]; }

inline const float &vec4::operator[](const int i) const { return (&x)[i]; }

inline vec4 vec4::operator*(const vec4 rhs) const { return vec4{x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w}; }

inline vec4 vec4::operator+(const vec4 &rhs) const { return vec4{x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w}; }

inline bool vec4::operator==(const vec4 &rhs) const 
{
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

inline float vec4::dot(const vec4 rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }
////////////////////////////////////////////////////////////////

struct mat4
{
    mat4() = default;
    mat4(const float diagonal)
        : col0{diagonal, 0.0f, 0.0f, 0.0f},
          col1{0.0f, diagonal, 0.0f, 0.0f},
          col2{0.0f, 0.0f, diagonal, 0.0f},
          col3{0.0f, 0.0f, 0.0f, diagonal}
    {
    }
    mat4(const mat4 &r) : col0(r.col0), col1(r.col1), col2(r.col2), col3(r.col3) {}
    mat4(const float v00, const float v01);

    mat4(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
         const float m12, const float m13, const float m20, const float m21, const float m22, const float m23,
         const float m30, const float m31, const float m32, const float m33)
        : col0(m00, m01, m02, m03), col1(m10, m11, m12, m13), col2(m20, m21, m22, m23), col3(m30, m31, m32, m33)
    {
    }

    vec4 &operator[](const int i) { return (&col0)[i]; }
    const vec4 &operator[](const int i) const { return (&col0)[i]; }

    mat4 operator*(const mat4 &r)
    {
        mat4 m{};

        const vec4 row0{col0.x, col1.x, col2.x, col3.x};
        const vec4 row1{col0.y, col1.y, col2.y, col3.y};
        const vec4 row2{col0.z, col1.z, col2.z, col3.z};
        const vec4 row3{col0.w, col1.w, col2.w, col3.w};

        m[0][0] = row0.dot(r.col0);
        m[1][0] = row0.dot(r.col1);
        m[2][0] = row0.dot(r.col2);
        m[3][0] = row0.dot(r.col3);

        m[0][1] = row1.dot(r.col0);
        m[1][1] = row1.dot(r.col1);
        m[2][1] = row1.dot(r.col2);
        m[3][1] = row1.dot(r.col3);

        m[0][2] = row2.dot(r.col0);
        m[1][2] = row2.dot(r.col1);
        m[2][2] = row2.dot(r.col2);
        m[3][2] = row2.dot(r.col3);

        m[0][3] = row3.dot(r.col0);
        m[1][3] = row3.dot(r.col1);
        m[2][3] = row3.dot(r.col2);
        m[3][3] = row3.dot(r.col3);

        return m;
    }

    vec4 col0;
    vec4 col1;
    vec4 col2;
    vec4 col3;
};

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
