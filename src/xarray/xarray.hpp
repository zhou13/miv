#pragma once
#include <string>

// maintain an array of char: S[0..n-1]
class XArray {
	std::wstring m_str;
public:
	XArray(const std::wstring &init_value);
	~XArray();

	// length
	size_t size() const;

	// insert $value before S[$pos]
	// - $pos in [0, n]
	void insert(size_t pos, const std::wstring &value);

	// delete elements [$pos, $pos+$len)
	// - $pos in [0, size-$len]
	void erase(size_t pos, size_t len);

	// find the $k-th newline starting from pos; return size if none
	size_t find_newline(size_t pos, size_t k);
};
