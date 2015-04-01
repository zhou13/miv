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
};

struct Point {
    size_t x, y;
    Point() : x(0), y(0) {}
    Point(size_t x, size_t y) : x(x), y(y) {}
};

struct Vector {
    ptrdiff_t dx, dy;
    Vector() : dx(0), dy(0) {}
    Vector(ptrdiff_t dx, ptrdiff_t dy) : dx(dx), dy(dy) {}
};

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
};
