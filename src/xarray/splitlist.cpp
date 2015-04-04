#include "xarray/splitlist.hpp"


SplitList::SplitList()
{

}

SplitList::~SplitList()
{

}

void SplitList::assign(const wstring &str)
{
    m_str = str;
}

num SplitList::size() const
{
    return (num)m_str.size();
}

num SplitList::count_newline() const
{
    return (num)count(m_str.begin(), m_str.end(), '\n');
}

num SplitList::count_newline(num begin, num end) const
{
    return (num)count(m_str.begin() + begin, m_str.begin() + end, '\n');
}

wstring SplitList::get(num begin, num end) const
{
    return m_str.substr(begin, end - begin);
}

void SplitList::insert(num pos, const std::wstring &value)
{
    m_str.insert(pos, value);
}

void SplitList::erase(num pos, num len)
{
    m_str.erase(pos, len);
}

num SplitList::find_kth_newline(num k) const
{
    num cur = 0;
    for (num i = 0; i < (num)m_str.size(); ++i) {
        if (m_str[i] == '\n') {
            if (cur == k)
                return i;
            ++cur;
        }
    }
    return size();
}
