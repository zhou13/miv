#include "file/file.hpp"
#include "xarray/xarray.hpp"

File::File(Miv *miv, XArray *array, std::string filename) :
    m_miv(miv), m_array(array), m_filename(filename)
{
}

File::~File()
{
}

void File::read()
{
    std::string s("Hello World!\n"
                  "Hello!\n"
                  "World!\n"
                  "U\n"
                  "P\n"
                  "TTTT\n"
                  "T_T\n"
                  "This is the last line\n"
                  "This is really the last LINE!");
    m_array->assign(wstring(s.begin(), s.end()));
}


void File::write()
{
    // do nothing
}
