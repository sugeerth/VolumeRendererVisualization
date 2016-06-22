#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <limits>

template<typename T>
struct Vec2
{
public:
    T x, y;

public:
    Vec2()
    {
        x = T(0);
        y = T(0);
    }

    Vec2(T s)
    {
        this->x = s;
        this->y = s;
    }

    template<typename _T>
    Vec2(const Vec2<_T> &v)
    {
        this->x = T(v.x);
        this->y = T(v.y);
    }

    Vec2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    template<typename _T>
    Vec2(_T x, _T y)
    {
        this->x = T(x);
        this->y = T(y);
    }

    Vec2<T> &operator=(T s)
    {
        this->x = s;
        this->y = s;
        return *this;
    }

    Vec2<T> &operator=(const Vec2<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
        return *this;
    }

    Vec2<T> &operator+=(const Vec2<T> &v)
    {
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vec2<T> &operator-=(const Vec2<T> &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vec2<T> &operator*=(T s)
    {
        this->x *= s;
        this->y *= s;
        return *this;
    }

    Vec2<T> &operator*=(const Vec2<T> &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        return *this;
    }

    T dot(const Vec2<T> &v1) const
    {
        return x * v1.x + y * v1.y;
    }

    T norm() const
    {
        return std::sqrt(x * x + y * y);
    }

    T norm2() const
    {
        return x * x + y * y;
    }

    Vec2<T> unit() const
    {
        T inorm = T(1) / norm();
        return Vec2<T>(x * inorm, y * inorm);
    }

    static Vec2<T> unitX()
    {
        return Vec2<T>(T(1), T(0));
    }

    static Vec2<T> unitY()
    {
        return Vec2<T>(T(0), T(1));
    }

    static Vec2<T> zero()
    {
        return Vec2<T>(T(0), T(0));
    }
};

template<typename T>
struct Vec3
{
public:
    T x, y, z;

public:
    Vec3()
    {
        this->x = T(0);
        this->y = T(0);
        this->z = T(0);
    }

    Vec3(T s)
    {
        this->x = s;
        this->y = s;
        this->z = s;
    }

    template<typename _T>
    Vec3(const Vec3<_T> &v)
    {
        this->x = T(v.x);
        this->y = T(v.y);
        this->z = T(v.z);
    }

    Vec3(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template<typename _T>
    Vec3(_T x, _T y, _T z)
    {
        this->x = T(x);
        this->y = T(y);
        this->z = T(z);
    }

    Vec3<T> &operator=(T s)
    {
        this->x = s;
        this->y = s;
        this->z = s;
        return *this;
    }

    Vec3<T> &operator=(const Vec3<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }

    Vec3<T> &operator+=(const Vec3<T> &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    Vec3<T> &operator-=(const Vec3<T> &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    Vec3<T> &operator*=(T s)
    {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        return *this;
    }

    Vec3<T> &operator*=(const Vec3<T> &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }

    Vec3<T> cross(Vec3<T> v1)
    {
        Vec3<T> v;
        v.x = y * v1.z - z * v1.y;
        v.y = z * v1.x - x * v1.z;
        v.z = x * v1.y - y * v1.x;
        return v;
    }

    T dot(const Vec3<T> &v1) const
    {
        return x * v1.x + y * v1.y + z * v1.z;
    }

    T norm() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    T norm2() const
    {
        return x * x + y * y + z * z;
    }

    Vec3<T> unit() const
    {
        T inorm = T(1) / norm();
        return Vec3<T>(x * inorm, y * inorm, z * inorm);
    }

    static Vec3<T> unitX()
    {
        return Vec3<T>(T(1), T(0), T(0));
    }

    static Vec3<T> unitY()
    {
        return Vec3<T>(T(0), T(1), T(0));
    }

    static Vec3<T> unitZ()
    {
        return Vec3<T>(T(0), T(0), T(1));
    }

    static Vec3<T> zero()
    {
        return Vec3<T>(T(0), T(0), T(0));
    }

    static Vec3<T> one()
    {
        return Vec3<T>(T(1), T(1), T(1));
    }

    static Vec3<T> min()
    {
        T sMin = std::numeric_limits<T>::min();
        return Vec3<T>(sMin, sMin, sMin);
    }

    static Vec3<T> max()
    {
        T sMax = std::numeric_limits<T>::max();
        return Vec3<T>(sMax, sMax, sMax);
    }
};

template<typename T>
struct Vec4
{
public:
    T x, y, z, w;

public:
    Vec4()
    {
        this->x = T(0);
        this->y = T(0);
        this->z = T(0);
        this->w = T(0);
    }

    Vec4(T s)
    {
        this->x = s;
        this->y = s;
        this->z = s;
        this->w = s;
    }

    Vec4(T x, T y, T z, T w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Vec4(const Vec3<T> &v, T w)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = w;
    }

    Vec4<T> &operator=(T s)
    {
        this->x = s;
        this->y = s;
        this->z = s;
        this->w = s;
        return *this;
    }

    Vec4<T> &operator=(const Vec4<T> &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
        return *this;
    }

    Vec4<T> &operator+=(const Vec4<T> &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;
        return *this;
    }

    Vec4<T> &operator-=(const Vec4<T> &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;
        return *this;
    }

    Vec4<T> &operator*=(T s)
    {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        this->w *= s;
        return *this;
    }

    Vec4<T> &operator*=(const Vec4<T> &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
        return *this;
    }

    T dot(const Vec4<T> &v1) const
    {
        return x * v1.x + y * v1.y + z * v1.z + w * v1.w;
    }

    T norm() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    T norm2() const
    {
        return x * x + y * y + z * z + w * w;
    }

    Vec4<T> unit() const
    {
        T inorm = T(1) / norm();
        return Vec4<T>(x * inorm, y * inorm, z * inorm, w * inorm);
    }

    Vec3<T> xyz() const
    {
        return Vec3<T>(x, y, z);
    }

    static Vec4<T> unitX()
    {
        return Vec4<T>(T(1), T(0), T(0), T(0));
    }

    static Vec4<T> unitY()
    {
        return Vec4<T>(T(0), T(1), T(0), T(0));
    }

    static Vec4<T> unitZ()
    {
        return Vec4<T>(T(0), T(0), T(1), T(0));
    }

    static Vec4<T> unitW()
    {
        return Vec4<T>(T(0), T(0), T(0), T(1));
    }

    static Vec4<T> zero()
    {
        return Vec4<T>(T(0), T(0), T(0), T(0));
    }
};

template<typename T>
T clamp(T v, T vMin, T vMax)
{
    T vOut;
    vOut = std::min(std::max(v, vMin), vMax);
    return vOut;
}

template<typename T>
Vec2<T> operator+(const Vec2<T> &v1, T s1)
{
    Vec2<T> v;
    v.x = v1.x + s1;
    v.y = v1.y + s1;
    return v;
}

template<typename T>
Vec2<T> operator+(const Vec2<T> &v1, const Vec2<T> &v2)
{
    Vec2<T> v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

template<typename T>
Vec2<T> operator-(const Vec2<T> &v1)
{
    return Vec2<T>(-v1.x, -v1.y);
}

template<typename T>
Vec2<T> operator-(const Vec2<T> &v1, T s1)
{
    Vec2<T> v;
    v.x = v1.x - s1;
    v.y = v1.y - s1;
    return v;
}

template<typename T>
Vec2<T> operator-(const Vec2<T> &v1, const Vec2<T> &v2)
{
    Vec2<T> v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

template<typename T>
Vec2<T> operator*(const Vec2<T> &v1, T s1)
{
    Vec2<T> v;
    v.x = v1.x * s1;
    v.y = v1.y * s1;
    return v;
}

template<typename T>
Vec2<T> operator*(T s1, const Vec2<T> &v1)
{
    Vec2<T> v;
    v.x = s1 * v1.x;
    v.y = s1 * v1.y;
    return v;
}

template<typename T>
Vec2<T> operator*(const Vec2<T> &v1, const Vec2<T> &v2)
{
    Vec2<T> v;
    v.x = v1.x * v2.x;
    v.y = v1.y * v2.y;
    return v;
}

template<typename T>
Vec2<T> operator/(const Vec2<T> &v1, T s1)
{
    Vec2<T> v;
    v.x = v1.x / s1;
    v.y = v1.y / s1;
    return v;
}

template<typename T>
Vec2<T> operator/(const Vec2<T> &v1, const Vec2<T> &v2)
{
    Vec2<T> v;
    v.x = v1.x / v2.x;
    v.y = v1.y / v2.y;
    return v;
}

template<typename T>
Vec2<T> clamp(const Vec2<T> &v, const Vec2<T> &vMin, const Vec2<T> &vMax)
{
    Vec2<T> vOut;
    vOut.x = std::min(std::max(v.x, vMin.x), vMax.x);
    vOut.y = std::min(std::max(v.y, vMin.y), vMax.y);
    return vOut;
}

template<typename T>
Vec2<T> lerp(const Vec2<T> &v1, const Vec2<T> &v2, T t)
{
    Vec2<T> vOut;
    vOut.x = v1.x * (T(1) - t) + v2.x * t;
    vOut.y = v1.y * (T(1) - t) + v2.y * t;
    return vOut;
}

template<typename T>
Vec2<T> abs(const Vec2<T> &v)
{
    Vec2<T> vOut;
    vOut.x = std::abs(v.x);
    vOut.y = std::abs(v.y);
    return vOut;
}

template<typename T>
Vec2<T> min(const Vec2<T> &v1, const Vec2<T> &v2)
{
    Vec2<T> vOut;
    vOut.x = std::min(v1.x, v2.x);
    vOut.y = std::min(v1.y, v2.y);
    return vOut;
}

template<typename T>
Vec2<T> max(const Vec2<T> &v1, const Vec2<T> &v2)
{
    Vec2<T> vOut;
    vOut.x = std::max(v1.x, v2.x);
    vOut.y = std::max(v1.y, v2.y);
    return vOut;
}

template<typename T>
Vec3<T> operator+(const Vec3<T> &v1, T s1)
{
    Vec3<T> v;
    v.x = v1.x + s1;
    v.y = v1.y + s1;
    v.z = v1.z + s1;
    return v;
}

template<typename T>
Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2)
{
    Vec3<T> v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}

template<typename T>
Vec3<T> operator-(const Vec3<T> &v1)
{
    return Vec3<T>(-v1.x, -v1.y, -v1.z);
}

template<typename T>
Vec3<T> operator-(const Vec3<T> &v1, T s1)
{
    Vec3<T> v;
    v.x = v1.x - s1;
    v.y = v1.y - s1;
    v.z = v1.z - s1;
    return v;
}

template<typename T>
Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2)
{
    Vec3<T> v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}

template<typename T>
Vec3<T> operator*(const Vec3<T> &v1, T s1)
{
    Vec3<T> v;
    v.x = v1.x * s1;
    v.y = v1.y * s1;
    v.z = v1.z * s1;
    return v;
}

template<typename T>
Vec3<T> operator*(T s1, const Vec3<T> &v1)
{
    Vec3<T> v;
    v.x = s1 * v1.x;
    v.y = s1 * v1.y;
    v.z = s1 * v1.z;
    return v;
}

template<typename T>
Vec3<T> operator*(const Vec3<T> &v1, const Vec3<T> &v2)
{
    Vec3<T> v;
    v.x = v1.x * v2.x;
    v.y = v1.y * v2.y;
    v.z = v1.z * v2.z;
    return v;
}

template<typename T>
Vec3<T> operator/(const Vec3<T> &v1, T s1)
{
    Vec3<T> v;
    v.x = v1.x / s1;
    v.y = v1.y / s1;
    v.z = v1.z / s1;
    return v;
}

template<typename T>
Vec3<T> operator/(const Vec3<T> &v1, const Vec3<T> &v2)
{
    Vec3<T> v;
    v.x = v1.x / v2.x;
    v.y = v1.y / v2.y;
    v.z = v1.z / v2.z;
    return v;
}

template<typename T>
Vec3<T> clamp(const Vec3<T> &v, const Vec3<T> &vMin, const Vec3<T> &vMax)
{
    Vec3<T> vOut;
    vOut.x = std::min(std::max(v.x, vMin.x), vMax.x);
    vOut.y = std::min(std::max(v.y, vMin.y), vMax.y);
    vOut.z = std::min(std::max(v.z, vMin.z), vMax.z);
    return vOut;
}

template<typename T>
Vec3<T> lerp(const Vec3<T> &v1, const Vec3<T> &v2, T t)
{
    Vec3<T> vOut;
    vOut.x = v1.x * (T(1) - t) + v2.x * t;
    vOut.y = v1.y * (T(1) - t) + v2.y * t;
    vOut.z = v1.z * (T(1) - t) + v2.z * t;
    return vOut;
}

template<typename T>
Vec3<T> abs(const Vec3<T> &v)
{
    Vec3<T> vOut;
    vOut.x = std::abs(v.x);
    vOut.y = std::abs(v.y);
    vOut.z = std::abs(v.z);
    return vOut;
}

template<typename T>
Vec3<T> min(const Vec3<T> &v1, const Vec3<T> &v2)
{
    Vec3<T> vOut;
    vOut.x = std::min(v1.x, v2.x);
    vOut.y = std::min(v1.y, v2.y);
    vOut.z = std::min(v1.z, v2.z);
    return vOut;
}

template<typename T>
Vec3<T> max(const Vec3<T> &v1, const Vec3<T> &v2)
{
    Vec3<T> vOut;
    vOut.x = std::max(v1.x, v2.x);
    vOut.y = std::max(v1.y, v2.y);
    vOut.z = std::max(v1.z, v2.z);
    return vOut;
}

template<typename T>
Vec4<T> operator+(const Vec4<T> &v1, T s1)
{
    Vec4<T> v;
    v.x = v1.x + s1;
    v.y = v1.y + s1;
    v.z = v1.z + s1;
    v.w = v1.w + s1;
    return v;
}

template<typename T>
Vec4<T> operator+(const Vec4<T> &v1, const Vec4<T> &v2)
{
    Vec4<T> v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    v.w = v1.w + v2.w;
    return v;
}

template<typename T>
Vec4<T> operator-(const Vec4<T> &v1)
{
    return Vec4<T>(-v1.x, -v1.y, -v1.z, -v1.w);
}

template<typename T>
Vec4<T> operator-(const Vec4<T> &v1, T s1)
{
    Vec4<T> v;
    v.x = v1.x - s1;
    v.y = v1.y - s1;
    v.z = v1.z - s1;
    v.w = v1.w - s1;
    return v;
}

template<typename T>
Vec4<T> operator-(const Vec4<T> &v1, const Vec4<T> &v2)
{
    Vec4<T> v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    v.w = v1.w - v2.w;
    return v;
}

template<typename T>
Vec4<T> operator*(const Vec4<T> &v1, T s1)
{
    Vec4<T> v;
    v.x = v1.x * s1;
    v.y = v1.y * s1;
    v.z = v1.z * s1;
    v.w = v1.w * s1;
    return v;
}

template<typename T>
Vec4<T> operator*(T s1, const Vec4<T> &v1)
{
    Vec4<T> v;
    v.x = s1 * v1.x;
    v.y = s1 * v1.y;
    v.z = s1 * v1.z;
    v.w = s1 * v1.w;
    return v;
}

template<typename T>
Vec4<T> operator*(const Vec4<T> &v1, const Vec4<T> &v2)
{
    Vec4<T> v;
    v.x = v1.x * v2.x;
    v.y = v1.y * v2.y;
    v.z = v1.z * v2.z;
    v.w = v1.w * v2.w;
    return v;
}

template<typename T>
Vec4<T> operator/(const Vec4<T> &v1, T s1)
{
    Vec4<T> v;
    v.x = v1.x / s1;
    v.y = v1.y / s1;
    v.z = v1.z / s1;
    v.w = v1.w / s1;
    return v;
}

template<typename T>
Vec4<T> operator/(const Vec4<T> &v1, const Vec4<T> &v2)
{
    Vec4<T> v;
    v.x = v1.x / v2.x;
    v.y = v1.y / v2.y;
    v.z = v1.z / v2.z;
    v.w = v1.w / v2.w;
    return v;
}

template<typename T>
Vec4<T> clamp(const Vec4<T> &v, const Vec4<T> &vMin, const Vec4<T> &vMax)
{
    Vec4<T> vOut;
    vOut.x = std::min(std::max(v.x, vMin.x), vMax.x);
    vOut.y = std::min(std::max(v.y, vMin.y), vMax.y);
    vOut.z = std::min(std::max(v.z, vMin.z), vMax.z);
    vOut.w = std::min(std::max(v.w, vMin.w), vMax.w);
    return vOut;
}

template<typename T>
Vec4<T> lerp(const Vec4<T> &v1, const Vec4<T> &v2, T t)
{
    Vec4<T> vOut;
    vOut.x = v1.x * (T(1) - t) + v2.x * t;
    vOut.y = v1.y * (T(1) - t) + v2.y * t;
    vOut.z = v1.z * (T(1) - t) + v2.z * t;
    vOut.w = v1.w * (T(1) - t) + v2.w * t;
    return vOut;
}

template<typename T>
Vec4<T> abs(const Vec4<T> &v)
{
    Vec4<T> vOut;
    vOut.x = std::abs(v.x);
    vOut.y = std::abs(v.y);
    vOut.z = std::abs(v.z);
    vOut.w = std::abs(v.w);
    return vOut;
}

template<typename T>
Vec4<T> min(const Vec4<T> &v1, const Vec4<T> &v2)
{
    Vec4<T> vOut;
    vOut.x = std::min(v1.x, v2.x);
    vOut.y = std::min(v1.y, v2.y);
    vOut.z = std::min(v1.z, v2.z);
    vOut.w = std::min(v1.w, v2.w);
    return vOut;
}

template<typename T>
Vec4<T> max(const Vec4<T> &v1, const Vec4<T> &v2)
{
    Vec4<T> vOut;
    vOut.x = std::max(v1.x, v2.x);
    vOut.y = std::max(v1.y, v2.y);
    vOut.z = std::max(v1.z, v2.z);
    vOut.w = std::max(v1.w, v2.w);
    return vOut;
}

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;

inline Vec3i index3D(int index, Vec3i dim)
{
    Vec3i index3D;
    index3D.z = index / (dim.x * dim.y);
    index -= index3D.z * (dim.x * dim.y);
    index3D.y = index / dim.x;
    index -= index3D.y * dim.x;
    index3D.x = index;
    return index3D;
}

#endif // VEC_H
