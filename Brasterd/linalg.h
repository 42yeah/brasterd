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

typedef pmat<float, 2, 1> vec2;
typedef pmat<float, 3, 1> vec3;
typedef pmat<float, 4, 1> vec4;

typedef pmat<int, 2, 1> ivec2;
typedef pmat<int, 3, 1> ivec3;
typedef pmat<int, 4, 1> ivec4;

typedef pmat<unsigned char, 2, 1> u8vec2;
typedef pmat<unsigned char, 3, 1> u8vec3;
typedef pmat<unsigned char, 4, 1> u8vec4;

template<typename T>
void swoop(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
