#ifndef MAT_H
#define MAT_H

#include <algorithm>
#include <cmath>
#include "MathUtil.h"
#include "Vec.h"

template<typename T>
struct Mat3
{
public:
    T elem[3][3];   // row major

public:
    Mat3()
    {
        T *elemPtr = &elem[0][0];
        std::fill(elemPtr, elemPtr + 9, T(0));
    }

    Vec3<T> operator*(const Vec3<T> &v) const
    {
        Vec3<T> vOut;
        vOut.x = elem[0][0] * v.x + elem[0][1] * v.y + elem[0][2] * v.z;
        vOut.y = elem[1][0] * v.x + elem[1][1] * v.y + elem[1][2] * v.z;
        vOut.z = elem[2][0] * v.x + elem[2][1] * v.y + elem[2][2] * v.z;
        return vOut;
    }

    Mat3<T> operator*(const Mat3<T> &m) const
    {
        Mat3<T> mOut;

        for(int i = 0; i < 3; ++i) for(int j = 0; j < 3; ++j)
        {
            mOut.elem[i][j] = T(0);
            for(int k = 0; k < 3; ++k)
                mOut.elem[i][j] += elem[i][k] * m.elem[k][j];
        }

        return mOut;
    }

    Mat3<T> transpose() const
    {
        Mat3<T> mOut;
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                mOut.elem[i][j] = elem[j][i];
        return mOut;
    }

    void orthonormalize()
    {
        Vec3<T> v0 = Vec3<T>(elem[0][0], elem[0][1], elem[0][2]).unit();
        Vec3<T> v1 = Vec3<T>(elem[1][0], elem[1][1], elem[1][2]);
        v1 = (v1 - v0 * v1.dot(v0)).unit();
        Vec3<T> v2 = Vec3<T>(elem[2][0], elem[2][1], elem[2][2]);
        v2 = (v2 - v0 * v2.dot(v0) - v1 * v2.dot(v1)).unit();
        elem[0][0] = v0.x;
        elem[0][1] = v0.y;
        elem[0][2] = v0.z;
        elem[1][0] = v1.x;
        elem[1][1] = v1.y;
        elem[1][2] = v1.z;
        elem[2][0] = v2.x;
        elem[2][1] = v2.y;
        elem[2][2] = v2.z;
    }

    static Mat3<T> identity()
    {
        Mat3<T> mOut;
        T *elemPtr = &mOut.elem[0][0];
        std::fill(elemPtr, elemPtr + 9, T(0));
        mOut.elem[0][0] = T(1);
        mOut.elem[1][1] = T(1);
        mOut.elem[2][2] = T(1);
        return mOut;
    }

    static Mat3<T> zero()
    {
        Mat3<T> mOut;
        T *elemPtr = &mOut.elem[0][0];
        std::fill(elemPtr, elemPtr + 9, T(0));
        return mOut;
    }

    static Mat3<T> fromAxisAngle(const Vec3<T> &axis, T angle)
    {
        Mat3<T> mOut;
        T cost = std::cos(angle);
        T sint = std::sin(angle);
        T omct = T(1) - cost;
        T xx = axis.x * axis.x;
        T yy = axis.y * axis.y;
        T zz = axis.z * axis.z;
        T xy = axis.x * axis.y;
        T yz = axis.y * axis.z;
        T zx = axis.z * axis.x;
        mOut.elem[0][0] = cost + xx * omct;
        mOut.elem[0][1] = xy * omct - axis.z * sint;
        mOut.elem[0][2] = zx * omct + axis.y * sint;
        mOut.elem[1][0] = xy * omct + axis.z * sint;
        mOut.elem[1][1] = cost + yy * omct;
        mOut.elem[1][2] = yz * omct - axis.x * sint;
        mOut.elem[2][0] = zx * omct - axis.y * sint;
        mOut.elem[2][1] = yz * omct + axis.x * sint;
        mOut.elem[2][2] = cost + zz * omct;
        return mOut;
    }
};

typedef Mat3<float> Mat3f;

template<typename T>
struct Mat4
{
public:
    T elem[4][4];   // row major

public:
    Mat4()
    {
        T *elemPtr = &elem[0][0];
        std::fill(elemPtr, elemPtr + 16, T(0));
    }

    Mat4(const Mat3<T> &m, const Vec3<T> &v)
    {
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                elem[i][j] = m.elem[i][j];
        elem[0][3] = v.x;
        elem[1][3] = v.y;
        elem[2][3] = v.z;
        elem[3][0] = T(0);
        elem[3][1] = T(0);
        elem[3][2] = T(0);
        elem[3][3] = T(1);
    }

    Vec4<T> operator*(const Vec4<T> &v) const
    {
        Vec4<T> vOut;
        vOut.x = elem[0][0] * v.x + elem[0][1] * v.y + elem[0][2] * v.z + elem[0][3] * v.w;
        vOut.y = elem[1][0] * v.x + elem[1][1] * v.y + elem[1][2] * v.z + elem[1][3] * v.w;
        vOut.z = elem[2][0] * v.x + elem[2][1] * v.y + elem[2][2] * v.z + elem[2][3] * v.w;
        vOut.w = elem[3][0] * v.x + elem[3][1] * v.y + elem[3][2] * v.z + elem[3][3] * v.w;
        return vOut;
    }

    Mat4<T> operator*(const Mat4<T> &m) const
    {
        Mat4<T> mOut;

        for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j)
        {
            mOut.elem[i][j] = T(0);
            for(int k = 0; k < 4; ++k)
                mOut.elem[i][j] += elem[i][k] * m.elem[k][j];
        }

        return mOut;
    }

    Mat4<T> inverse() const
    {
        // Inversion by Cramer's rule.
        Mat4<T> mOut;
        T tmp[12]; // temp array for pairs
        T src[16]; // array of transpose source matrix

        // transpose matrix
        for(int i = 0; i < 4; i++)
        {
            src[i+0] = elem[i][0];
            src[i+4] = elem[i][1];
            src[i+8] = elem[i][2];
            src[i+12] = elem[i][3];
        }

        // calculate pairs for first 8 elements (cofactors)
        tmp[0] = src[10] * src[15];
        tmp[1] = src[11] * src[14];
        tmp[2] = src[9] * src[15];
        tmp[3] = src[11] * src[13];
        tmp[4] = src[9] * src[14];
        tmp[5] = src[10] * src[13];
        tmp[6] = src[8] * src[15];
        tmp[7] = src[11] * src[12];
        tmp[8] = src[8] * src[14];
        tmp[9] = src[10] * src[12];
        tmp[10] = src[8] * src[13];
        tmp[11] = src[9] * src[12];

        // calculate first 8 elements (cofactors)
        mOut.elem[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
        mOut.elem[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
        mOut.elem[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
        mOut.elem[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
        mOut.elem[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
        mOut.elem[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
        mOut.elem[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
        mOut.elem[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
        mOut.elem[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
        mOut.elem[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
        mOut.elem[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
        mOut.elem[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
        mOut.elem[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
        mOut.elem[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
        mOut.elem[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
        mOut.elem[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

        // calculate pairs for second 8 elements (cofactors)
        tmp[0] = src[2] * src[7];
        tmp[1] = src[3] * src[6];
        tmp[2] = src[1] * src[7];
        tmp[3] = src[3] * src[5];
        tmp[4] = src[1] * src[6];
        tmp[5] = src[2] * src[5];
        tmp[6] = src[0] * src[7];
        tmp[7] = src[3] * src[4];
        tmp[8] = src[0] * src[6];
        tmp[9] = src[2] * src[4];
        tmp[10] = src[0] * src[5];
        tmp[11] = src[1] * src[4];

        // calculate second 8 elements (cofactors)
        mOut.elem[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
        mOut.elem[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
        mOut.elem[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
        mOut.elem[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
        mOut.elem[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
        mOut.elem[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
        mOut.elem[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
        mOut.elem[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
        mOut.elem[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
        mOut.elem[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
        mOut.elem[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
        mOut.elem[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
        mOut.elem[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
        mOut.elem[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
        mOut.elem[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
        mOut.elem[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

        // calculate determinant
        T det = src[0] * mOut.elem[0][0] + src[1] * mOut.elem[0][1] + src[2] * mOut.elem[0][2] + src[3] * mOut.elem[0][3];

        // we don't check singularity here because it is easier for debug
        //if(std::abs(det) == T(0))
        //    return zero();

        // calculate inverse matrix
        T invdet = T(1) / det;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                mOut.elem[i][j] *= invdet;
        return mOut;
    }

    Mat4<T> transpose() const
    {
        Mat4<T> mOut;
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                mOut.elem[i][j] = elem[j][i];
        return mOut;
    }

    static Mat4<T> identity()
    {
        Mat4<T> mOut;
        T *elemPtr = &mOut.elem[0][0];
        std::fill(elemPtr, elemPtr + 16, T(0));
        mOut.elem[0][0] = T(1);
        mOut.elem[1][1] = T(1);
        mOut.elem[2][2] = T(1);
        mOut.elem[3][3] = T(1);
        return mOut;
    }

    static Mat4<T> zero()
    {
        Mat4<T> mOut;
        T *elemPtr = &mOut.elem[0][0];
        std::fill(elemPtr, elemPtr + 16, T(0));
        return mOut;
    }

    static Mat4<T> ortho(T left, T right, T bottom, T top, T zNear, T zFar)
    {
        Mat4<T> mOut;
        T *elemPtr = &mOut.elem[0][0];
        std::fill(elemPtr, elemPtr + 16, T(0));
        mOut.elem[0][0] = T(2) / (right - left);
        mOut.elem[0][3] = (right + left) / (left - right);
        mOut.elem[1][1] = T(2) / (top - bottom);
        mOut.elem[1][3] = (top + bottom) / (bottom - top);
        mOut.elem[2][2] = T(2) / (zNear - zFar);
        mOut.elem[2][3] = (zNear + zFar) / (zNear - zFar);
        mOut.elem[3][3] = T(1);
        return mOut;
    }

    static Mat4<T> perspective(T fovy, T aspect, T zNear, T zFar)
    {
        Mat4<T> mOut;
        T *elemPtr = &mOut.elem[0][0];
        std::fill(elemPtr, elemPtr + 16, T(0));
        T f = std::tan(Math::pi_2<T>() - fovy * T(0.5));
        mOut.elem[0][0] = f / aspect;
        mOut.elem[1][1] = f;
        mOut.elem[2][2] = (zNear + zFar) / (zNear - zFar);
        mOut.elem[2][3] = T(2) * zNear * zFar / (zNear - zFar);
        mOut.elem[3][2] = T(-1);
        return mOut;
    }
};

typedef Mat4<float> Mat4f;

#endif // MAT_H
