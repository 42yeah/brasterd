#pragma once

#include <iostream>


template<typename T>
struct tvec4 {
    T x;
    T y;
    T z;
    T w;

    tvec4() : x(0), y(0), z(0), w(0) {
    }

    tvec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
    }
};

typedef tvec4<unsigned char> u8vec4;
typedef tvec4<float> vec4;

template<typename T>
struct tvec3 {
    T x;
    T y;
    T z;

    tvec3() : x((T) 0), y(0), z(0) {
    }

    tvec3(T x, T y, T z) : x(x), y(y), z(z) {
    }
};

typedef tvec3<float> vec3;
typedef tvec3<double> dvec3;

template<typename T>
struct tvec2 {
    T x;
    T y;

    tvec2() : x(0), y(0) {
    }

    tvec2(T x, T y) : x(x), y(y) {
    }
};

typedef tvec2<int> ivec2;
typedef tvec2<float> vec2;

template<typename T>
std::ostream& operator<<(std::ostream& o, tvec4<T> what) {
    o << "vec4(" << what.x << ", " << what.y << ", " << what.z << ", " << what.w << ")";
    return o;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, tvec3<T> what) {
    o << "vec3(" << what.x << ", " << what.y << ", " << what.z << ")";
    return o;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, tvec2<T> what) {
    o << "vec2(" << what.x << ", " << what.y << ")";
    return o;
}

template<typename T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}


template<template<typename> typename T, typename U>
T<U> operator-(T<U> a) {
    U *a_raw = (U *) &a;
    T<U> ret;
    U *c_raw = (U *) &ret;
    for (int i = 0; i < sizeof(T<U>) / sizeof(U); i++) {
        c_raw[i] = -a_raw[i];
    }
    return ret;
}

template<template<typename> typename T, typename U>
T<U> operator+(T<U> a, T<U> b) {
    U *a_raw = (U *) &a;
    U *b_raw = (U *) &b;
    T<U> ret;
    U *c_raw = (U *) &ret;
    for (int i = 0; i < sizeof(T<U>) / sizeof(U); i++) {
        c_raw[i] = a_raw[i] + b_raw[i];
    }
    return ret;
}

template<template<typename> typename T, typename U>
T<U> operator-(T<U> a, T<U> b) {
    U *a_raw = (U *) &a;
    U *b_raw = (U *) &b;
    T<U> ret;
    U *c_raw = (U *) &ret;
    for (int i = 0; i < sizeof(T<U>) / sizeof(U); i++) {
        c_raw[i] = a_raw[i] - b_raw[i];
    }
    return ret;
}
