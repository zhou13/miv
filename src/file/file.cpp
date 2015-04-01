#include "file/file.hpp"


File::File(string filename)
{
    m_filename = filename;
}

File::~File()
{

}

wstring File::read() const
{
    std::string s("Hello World!\n Yes?");
    return wstring(s.begin(), s.end());
}
