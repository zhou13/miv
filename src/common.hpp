#pragma once
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <queue>

using std::vector;
using std::queue;
using std::wstring;
using std::unique_ptr;
using std::shared_ptr;

struct Size {
	size_t width, height;
	// TODO
};

struct Point {
	size_t x, y;
	// TODO
};

struct Vector {
	ptrdiff_t dx, dy;
	// TODO
};

struct Rect {
	Point origin;
	Size size;
	// TODO
};
