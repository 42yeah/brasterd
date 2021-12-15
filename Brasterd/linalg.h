#pragma once

#include <string>
#include <iostream>


// COLUMN-FIRST specification of the PRIMORDIAL matrix.
template<typename T, int r, int c>
struct pmat {
    // Getting element from row a and column b
    T &operator()(int a, int b) {
        // Debug boundary check
        if (a < 0 || a >= r || b < 0 || b >= c) {
            throw "NOPE! Bad matrix access: " + std::to_string(a) + ", " + std::to_string(b);
        }
        return data[b * c + a];
    }

    // PRIMORDIAL matrix element-wise copy
    pmat<T, r, c> &operator=(const pmat<T, r, c> &a) {
        for (int i = 0; i < r * c; i++) {
            data[i] = a.data[i];
        }
        return *this;
    }

    T data[r * c];
};

// Primordial matrix multiplication.
template<typename T, int r, int c, int l>
pmat<T, r, l> operator*(pmat<T, r, c> mat1, pmat<T, c, l> mat2) {
    pmat<T, r, l> ret;
    // For each row of ret...
    for (int i = 0; i < r; i++) {
        // For each column of ret...
        for (int j = 0; j < l; j++) {
            float result = 0.0f;
            // The result is the multiplicative sum of mat1's row i and mat2's column j
            for (int a = 0; a < c; a++) {
                result += mat1(i, a) * mat2(a, j);
            }
            ret(i, j) = result;
        }
    }
    return ret;
}

// PRIMORDIAL matrix element-wise add.
template<typename T, int r, int c>
pmat<T, r, c> operator+(pmat<T, r, c> a, pmat<T, r, c> b) {
    pmat<T, r, c> ret;
    for (int i = 0; i < r * c; i++) {
        ret.data[i] = a.data[i] + b.data[i];
    }
    return ret;
}

// PRIMORDIAL matrix element-wise subtract.
template<typename T, int r, int c>
pmat<T, r, c> operator-(pmat<T, r, c> a, pmat<T, r, c> b) {
    pmat<T, r, c> ret;
    for (int i = 0; i < r * c; i++) {
        ret.data[i] = a.data[i] - b.data[i];
    }
    return ret;
}

// PRIMORDIAL matrix element-wise negate.
template<typename T, int r, int c>
pmat<T, r, c> operator-(pmat<T, r, c> a) {
    pmat<T, r, c> ret;
    for (int i = 0; i < r * c; i++) {
        ret.data[i] = -a.data[i];
    }
    return ret;
}


template<int r, int c>
struct mat : public pmat<float, r, c> {
};

template<typename T>
struct tvec2 : public pmat<T, 2, 1> {
    tvec2(const pmat<T, 2, 1> mat) {
        this->operator=(mat);
    }

    tvec2(T x, T y) {
        this->data[0] = x;
        this->data[1] = y;
    }

    tvec2 &operator=(const tvec2& a) {
        x = a.x;
        y = a.y;
        return *this;
    }

    T &x = this->data[0];
    T &y = this->data[1];
};

template<typename T>
struct tvec3 : public pmat<T, 3, 1> {
    tvec3(const pmat<T, 3, 1> mat) {
        this->operator=(mat);
    }

    tvec3(T x, T y, T z) {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }

    tvec3 &operator=(const tvec3& a) {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }

    T &x = this->data[0];
    T &y = this->data[1];
    T &z = this->data[2];
};

template<typename T>
struct tvec4 : public pmat<T, 4, 1> {
    tvec4(const pmat<T, 4, 1> mat) {
        this->operator=(mat);
    }

    tvec4(T x, T y, T z, T w) {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
    }

    tvec4 &operator=(const tvec4& a) {
        this->data[0] = a.x;
        this->data[1] = a.y;
        this->data[2] = a.z;
        this->data[3] = a.w;
        return *this;
    }

    T &x = this->data[0];
    T &y = this->data[1];
    T &z = this->data[2];
    T &w = this->data[3];
};

typedef tvec2<float> vec2;
typedef tvec3<float> vec3;
typedef tvec4<float> vec4;

typedef tvec2<int> ivec2;
typedef tvec3<int> ivec3;
typedef tvec4<int> ivec4;

typedef tvec2<unsigned char> u8vec2;
typedef tvec3<unsigned char> u8vec3;
typedef tvec4<unsigned char> u8vec4;


template<typename T>
void swoop(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
