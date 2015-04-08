#include "xarray/splitlist.hpp"

/*!
    \class SplitList
    \ingroup datastruct

    \brief The SplitList class provides supports for the XArray class
        by implementing a split list (functional?!).

    Use SplitList to maintain an array of wchar_t.

    \sa XArray
*/

static const int BLOCK_SIZE = 5;

class SplitListBlock {
public:
    wchar_t a[BLOCK_SIZE];
    uint8_t w[BLOCK_SIZE];
    num size, width, newlines;
    num first_tab;
    SplitListBlock *next;
    SplitListBlock() : size(0), width(0), newlines(0), first_tab(0) {}
    void update() {
        newlines = (num)std::count(a, a + size, '\n');
        width = (num)std::accumulate(w, w + size, (num)0);
        num it = (num)(std::find(a, a + size, '\t') - a);
        num in = (num)(std::find(a, a + size, '\n') - a);
        first_tab = min(it, in);
    }
};
static struct Iterator {
    SplitListBlock *cur;
    num begin, end;
    Iterator(SplitListBlock *cur, num begin, num end) :
        cur(cur), begin(begin), end(end) {}
    bool ok() const {
        return cur != nullptr;
    }
    void go() {
        begin -= cur->size;
        end -= cur->size;
        cur = cur->next;
    }
};

/*!
    Construct with empty string.
*/
SplitList::SplitList()
{
    m_head = nullptr;
    m_size = 0;
    m_tab_width = 4;
}

/*!
    Free.
*/
SplitList::~SplitList()
{
    if (m_head != nullptr)
        delete m_head;
}

/*!
    Free previous data and assign.
    \param[in] str
*/
void SplitList::assign(const wstring &str)
{
    if (m_head != nullptr)
        delete m_head;
    m_size = (num)str.size();
    m_head = _make_list(str, 0, m_size);
}

void SplitList::set_tab_width(num width)
{
    assert(width > 0);
    m_tab_width = width;
    // TODO
}

/*!
    \return Guarantee \f$size \ge 0\f$.
*/
num SplitList::size() const
{
    return m_size;
}

/*!
    Count newline symbols among the whole string.
*/
num SplitList::count_newline() const
{
    return count_newline(0, size());
}

/*!
    \param[in] begin Must have \f$0 \le begin\f$.
    \param[in] end Must have \f$begin \le end \le size\f$.
    \return Guarantee \f$count \ge 0\f$.
*/
num SplitList::count_newline(num begin, num end) const
{
    num ans = 0;
    for (auto it = Iterator(m_head, begin, end); it.ok(); it.go()) {
        if (begin <= 0 && it.cur->size <= end) {
            ans += it.cur->newlines;
            continue;
        }
        num s = max(begin, (num)0), t = min(end, it.cur->size);
        ans += std::count(it.cur->a + s, it.cur->a + t, '\n');
    }
    return ans;
}

/*!
    \param[in] k Must have \f$-1 \le 0 \le num\f$ where \f$num\f$ is the 
        total number of new lines.
    \return If \f$k = -1\f$, return 0; if \f$k = num\f$, return \f$size\f$;
        otherwise return the index of the \f$k\f$-th newline symbol.
*/
num SplitList::find_kth_newline(num k) const
{
    if (k == -1) {
        return -1;
    }
    num tot = 0, offset = 0;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        if (tot + cur->newlines > k) {
            for (num i = 0; i < cur->size; ++i)
                if (cur->a[i] == '\n') {
                    if (tot == k)
                        return offset + i;
                    ++tot;
                }
            DIE("unexcepted error (not enough newlines in block)");
            break;
        }
        tot += cur->newlines;
        offset += cur->size;
    }
    if (tot == k) {
        return size();
    }
    DIE("cannot found");
    return -1;
}

/*!
    Get.
*/
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

/*!
    Insert before.
*/
void SplitList::insert(num pos, const std::wstring &value)
{
    SplitListBlock *tmp = _make_list(value, 0, (num)value.size());
    SplitListBlock *tail;
    m_head = _split(m_head, pos, tail);
    m_head = _concat(m_head, tmp);
    m_head = _concat(m_head, tail);

    m_size += (num)value.size();
}

/*!
    Erase.
*/
void SplitList::erase(num pos, num len)
{
    SplitListBlock *tail, *middle;
    m_head = _split(m_head, pos + len, tail);
    m_head = _split(m_head, pos, middle);
    m_head = _concat(m_head, tail);
    delete middle;

    m_size -= len;
}

/*!
    Width.
*/
num SplitList::width() const
{
    return width(0, size());
}

/*!
    Width.
*/
num SplitList::width(num begin, num end) const
{
    num ans = 0;
    for (auto it = Iterator(m_head, begin, end); it.ok(); it.go()) {
        if (begin <= 0 && it.cur->size <= end) {
            ans += it.cur->width;
            continue;
        }
        num s = max(begin, (num)0), t = min(end, it.cur->size);
        ans += std::accumulate(it.cur->w + s, it.cur->w + t, 0);
    }
    return ans;
}

/*!
    Find first position \f$j\f$ that \f$width(i,j+1)>w\f$.
*/
num SplitList::find_visual_pos(num i, num w) const
{
    num begin = 0, end;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        end = begin + cur->size;
        if (end <= i)
            continue;
        num cur_width = 0;
        if (i <= begin) {
            cur_width = cur->width;
        }
        else {
            num x = i - begin, y = cur->size;
            cur_width = (num)std::accumulate(cur->w + x, cur->w + y, (num)0);
        }
        if (w < cur_width) {
            // inside this block
            for (num j = i;; ++j) {
                if (j - begin >= cur->size)
                    DIE("unexcepted out of bound");
                w -= cur->w[j - begin];
                if (w < 0)
                    return j;
            }
        }
        w -= cur_width;
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


