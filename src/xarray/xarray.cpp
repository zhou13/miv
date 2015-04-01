#include "xarray/xarray.hpp"


XArray::~XArray()
{

}


XArray::XArray(const std::wstring &init_value)
{
    (void)init_value;
}


size_t XArray::size() const
{
    return m_str.size();
}


void XArray::insert(size_t pos, const std::wstring &value)
{
    (void)pos, (void)value;
}


void XArray::erase(size_t pos, size_t len)
{
    (void)pos, (void)len;
}


size_t XArray::find_newline(size_t pos, size_t k)
{
    (void)pos, (void)k;
    return 0;
}
