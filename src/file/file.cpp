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
    std::string s("Hello World!\nHello!\nWorld!\nU\nP\nTTTT\nT_T\nThis is the last line\nThis is really the \n last \n LINE\n!");
    m_array->assign(wstring(s.begin(), s.end()));
}


void File::write()
{
    // do nothing
}
