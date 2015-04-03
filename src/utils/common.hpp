#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <queue>
#include <map>
#include <algorithm>

#include <boost/program_options/variables_map.hpp>

using std::map;
using std::pair;
using std::vector;
using std::queue;
using std::wstring;
using std::string;
using std::move;
using std::shared_ptr;
using std::unique_ptr;
using std::make_pair;
using std::make_shared;
using std::make_unique;
using std::dynamic_pointer_cast;

struct Size {
    size_t height, width;
    Size() : height(0), width(0) {}
    Size(size_t h, size_t w) : height(h), width(w) {}
    bool operator ==(const Size &b) const {
        return height == b.height && width == b.width;
    }
};

struct Vector {
    ptrdiff_t x, y;
    Vector() : x(0), y(0) {}
    Vector(ptrdiff_t x, ptrdiff_t y) : x(x), y(y) {}
    Vector operator+(const Vector &rhs) {
        return Vector(x + rhs.x, y + rhs.y);
    }
    Vector operator-(const Vector &rhs) {
        return Vector(x - rhs.x, y - rhs.y);
    }
};

struct Point {
    ptrdiff_t x, y;
    Point() : x(0), y(0) {}
    Point(ptrdiff_t x, ptrdiff_t y) : x(x), y(y) {}
    Point operator+(const Vector &rhs) {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Vector &rhs) {
        return Point(x - rhs.x, y - rhs.y);
    }
};


inline Vector operator-(const Vector &lhs, const Vector &rhs)
{
    return Vector(lhs.x - rhs.x, lhs.y - rhs.y);
}

struct Rect {
	Point origin;
	Size size;
    Rect() : origin(), size() {}
    Rect(size_t x1, size_t x2, size_t y1, size_t y2) :
        origin(x1, y1), size(x2-x1, y2-y1) {}
    Rect(Point o, Size s) : origin(o), size(s) {}
    size_t x1() { return origin.x; }
    size_t x2() { return origin.x + size.height; }
    size_t y1() { return origin.y; }
    size_t y2() { return origin.y + size.width; }
    size_t height() { return size.height; }
    size_t width() { return size.width; }
    Rect &operator+=(const Vector &rhs) {
        origin = origin + rhs; // todo
        return *this;
    }
};

#include "utils/logger.hpp"
