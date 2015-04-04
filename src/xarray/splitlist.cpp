#include "xarray/splitlist.hpp"

static const int BLOCK_SIZE = 5;

struct SplitListBlock {
    wchar_t a[BLOCK_SIZE];
    num size;
    num newline_count;
    SplitListBlock *next;
    void update() {
        newline_count = (num)std::count(a, a + size, '\n');
    }
};


SplitList::SplitList()
{
    m_head = nullptr;
    m_size = 0;
}

SplitList::~SplitList()
{
    if (m_head != nullptr)
        delete m_head;
}

void SplitList::assign(const wstring &str)
{
    if (m_head != nullptr)
        delete m_head;
    m_size = (num)str.size();
    m_head = _make_list(str, 0, m_size);
}

num SplitList::size() const
{
    return m_size;
}

num SplitList::count_newline() const
{
    return count_newline(0, size());
}

num SplitList::count_newline(num begin, num end) const
{
    num ans = 0;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        if (begin <= 0 && cur->size <= end) {
            ans += cur->newline_count;
            goto __L1;
        }
        if (begin >= cur->size)
            goto __L1;
        if (end <= 0)
            goto __L1;
        {
        num s = max(begin, (num)0), t = min(end, cur->size);
        ans += std::count(cur->a + s, cur->a + t, '\n');
        }
    __L1:
        begin -= cur->size;
        end -= cur->size;
    }
    return ans;
}

wstring SplitList::get(num begin, num end) const
{
    wstring ans;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        for (num i = max(begin, (num)0); i < min(end, cur->size); ++i) {
            ans += cur->a[i];
        }
        begin -= cur->size;
        end -= cur->size;
    }
    return ans;
}

void SplitList::insert(num pos, const std::wstring &value)
{
    SplitListBlock *tmp = _make_list(value, 0, (num)value.size());
    SplitListBlock *tail;
    m_head = _split(m_head, pos, tail);
    m_head = _concat(m_head, tmp);
    m_head = _concat(m_head, tail);

    m_size += (num)value.size();
}

void SplitList::erase(num pos, num len)
{
    SplitListBlock *tail, *middle;
    m_head = _split(m_head, pos + len, tail);
    m_head = _split(m_head, pos, middle);
    m_head = _concat(m_head, tail);
    delete middle;

    m_size -= len;
}

num SplitList::find_kth_newline(num k) const
{
    num tot = 0, offset = 0;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        if (tot + cur->newline_count > k) {
            for (num i = 0; i < cur->size; ++i)
                if (cur->a[i] == '\n') {
                    if (tot == k)
                        return offset + i;
                    ++tot;
                }
            DIE("unexcepted error (not enough newlines in block)");
            break;
        }
        tot += cur->newline_count;
        offset += cur->size;
    }
    return size();
}

SplitListBlock *SplitList::_make_list(const wstring &str, num begin, num end)
{
    if (begin >= end)
        return nullptr;
    num p = min(begin + BLOCK_SIZE, end);
    SplitListBlock *cur = new SplitListBlock();

    cur->next = _make_list(str, p, end);
    cur->size = p - begin;
    std::copy(str.begin() + begin, str.begin() + p, cur->a);
    cur->update();
    return cur;
}

SplitListBlock *SplitList::_split(SplitListBlock *cur, num pos, SplitListBlock *&tmp)
{
    if (pos == 0) {
        tmp = cur;
        return nullptr;
    }
    if (pos < cur->size) {
        // split the block $cur, at position $pos
        tmp = new SplitListBlock();
        tmp->next = cur->next;
        tmp->size = cur->size - pos;
        std::copy(cur->a + pos, cur->a + cur->size, tmp->a);
        tmp->update();
        _try_merge(tmp);

        cur->next = nullptr;
        cur->size = pos;
        cur->update();
        return cur;
    }
    cur->next = _split(cur->next, pos - cur->size, tmp);
    return cur;
}

SplitListBlock *SplitList::_concat(SplitListBlock *cur, SplitListBlock *tmp)
{
    if (cur == nullptr) {
        return tmp;
    }
    if (cur->next == nullptr) {
        cur->next = tmp;
        cur = _try_merge(cur);
        return cur;
    }
    cur->next = _concat(cur->next, tmp);
    return cur;
}

SplitListBlock *SplitList::_try_merge(SplitListBlock *cur)
{
    if (cur->next == nullptr)
        return cur;
    if (cur->size + cur->next->size > BLOCK_SIZE)
        return cur;
    auto *tmp = cur->next;
    std::copy(tmp->a, tmp->a + tmp->size, cur->a + cur->size);
    cur->size += tmp->size;
    cur->next = tmp->next;
    cur->update();
    delete tmp;
    return cur;
}


