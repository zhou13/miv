#pragma once

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>

#include <boost/program_options/variables_map.hpp>

typedef ptrdiff_t num;

using std::map;
using std::set;
using std::hash;
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
using std::unordered_map;

struct Size {
    num height, width;
    Size() : height(0), width(0) {}
    Size(num h, num w) : height(h), width(w) {}
    bool operator ==(const Size &b) const {
        return height == b.height && width == b.width;
    }
};

struct Vector {
    num x, y;
    Vector() : x(0), y(0) {}
    Vector(num x, num y) : x(x), y(y) {}
    Vector operator+(const Vector &rhs) {
        return Vector(x + rhs.x, y + rhs.y);
    }
    Vector operator-(const Vector &rhs) {
        return Vector(x - rhs.x, y - rhs.y);
    }
};

struct Point {
    num x, y;
    Point() : x(0), y(0) {}
    Point(num x, num y) : x(x), y(y) {}
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
    Rect(num x1, num x2, num y1, num y2) :
        origin(x1, y1), size(x2-x1, y2-y1) {}
    Rect(Point o, Size s) : origin(o), size(s) {}
    num x1() { return origin.x; }
    num x2() { return origin.x + size.height; }
    num y1() { return origin.y; }
    num y2() { return origin.y + size.width; }
    num height() { return size.height; }
    num width() { return size.width; }
    Rect &operator+=(const Vector &rhs) {
        origin = origin + rhs; // todo
        return *this;
    }
};

#include "utils/logger.hpp"
