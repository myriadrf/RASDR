#ifndef GEOM_H
#define GEOM_H


struct Point {
    double x, y;
};



struct Vec {
    double x, y, z;
};



// Basic arithmetic:

inline Vec operator+(const Vec & a, const Vec & b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
inline Vec operator+=(Vec & a, const Vec & b) {
    return (a = a + b);
}

inline Vec operator-(const Vec & a, const Vec & b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
inline Vec operator-=(Vec & a, const Vec & b) {
    return (a = a - b);
}

inline Vec operator*(const Vec & a, double scalar) {
    return {a.x * scalar, a.y * scalar, a.z * scalar};
}
inline Vec operator*(double scalar, const Vec & a) {
    return {a.x * scalar, a.y * scalar, a.z * scalar};
}
inline Vec operator*=(Vec & a, double scalar) {
    return (a = a * scalar);
}

inline Vec operator/(const Vec & a, double scalar) {
    return {a.x / scalar, a.y / scalar, a.z / scalar};
}
inline Vec operator/(double scalar, const Vec & a) {
    return {a.x / scalar, a.y / scalar, a.z / scalar};
}
inline Vec operator/=(Vec & a, double scalar) {
    return (a = a / scalar);
}

inline Vec cross(const Vec & a, const Vec & b) {
    return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}

#endif // GEOM_H
