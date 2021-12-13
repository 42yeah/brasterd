#pragma once

#include <iostream>


template<typename T>
struct tvec4 {
    T x;
    T y;
    T z;
    T w;

    tvec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
    }
};

typedef tvec4<unsigned char> u8vec4;

template<typename T>
struct tvec3 {
    T x;
    T y;
    T z;

    tvec3(T x, T y, T z) : x(x), y(y), z(z) {
    }
};

typedef tvec3<float> vec3;
typedef tvec3<double> dvec3;

template<typename T>
struct tvec2 {
    T x;
    T y;

    tvec2(T x, T y) : x(x), y(y) {
    }
};

typedef tvec2<int> ivec2;

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
