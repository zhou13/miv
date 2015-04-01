#pragma once

#include "common.hpp"


class File {
public:
    File(string filename);
    ~File();
    wstring read() const;
private:
    string m_filename;
};
