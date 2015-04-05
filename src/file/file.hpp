#pragma once

#include "utils/utils.hpp"

class Miv;
class XArray;

class File {
public:
    File(Miv *m_miv, XArray *array, string filename);
    ~File();
    void read();
    void write();

private:
    Miv *m_miv;
    XArray *m_array;
    string m_filename;
};
