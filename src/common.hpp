#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <queue>
#include <map>

using std::map;
using std::pair;
using std::vector;
using std::queue;
using std::wstring;
using std::string;
using std::move;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

struct Size {
    size_t height, width;
    Size() : height(0), width(0) {}
    Size(size_t h, size_t w) : height(h), width(w) {}
};

struct Point {
	size_t x, y;
	// TODO
};

struct Vector {
    ptrdiff_t dx, dy;
    Vector() : dx(0), dy(0) {}
    Vector(ptrdiff_t dx, ptrdiff_t dy) : dx(dx), dy(dy) {}
};

struct Rect {
	Point origin;
	Size size;
	// TODO
};
