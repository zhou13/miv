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
    num size, width, n_newline, n_tab, cw;
    SplitListBlock *next;

    SplitListBlock() : size(0), width(0), n_newline(0), n_tab(0), cw(0) {}
    ~SplitListBlock() {
        if (next != nullptr)
            delete next;
    }
    void update() {
        width = (num)std::accumulate(w, w + size, (num)0);
        n_newline = (num)std::count(a, a + size, '\n');
        n_tab = (num)std::count(a, a + size, '\t');
        if (n_newline == 0)
            cw = width;
        else {
            num i = size - 1;
            while (a[i] != '\n') --i;
            cw = (num)std::accumulate(w + i + 1, w + size, (num)0);
        }
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
    m_head = _make_list(str, 0, m_size, 0);
}

void SplitList::set_tab_width(num width)
{
    assert(width > 0);
    m_tab_width = width;
    m_head = _resize_tabs(m_head, 0);
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
    num le = 0, ri = 0;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        le = ri, ri += cur->size;
        if (begin <= le && ri <= end) {
            ans += cur->n_newline;
            continue;
        }
        num s = max(begin, le) - le;
        num t = min(end, ri) - le;
        if (s < t) {
            ans += (num)std::count(cur->a + s, cur->a + t, '\n');
        }
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
        if (tot + cur->n_newline > k) {
            for (num i = 0; i < cur->size; ++i)
                if (cur->a[i] == '\n') {
                    if (tot == k)
                        return offset + i;
                    ++tot;
                }
            DIE("unexcepted error (not enough newlines in block)");
            break;
        }
        tot += cur->n_newline;
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
    SplitListBlock *tmp = _make_list(value, 0, (num)value.size(), 0);
    SplitListBlock *tail;
    m_head = _split(m_head, pos, tail);
    m_head = _concat(m_head, tmp, 0);
    m_head = _concat(m_head, tail, 0);

    m_size += (num)value.size();
}

/*!
    Erase.
*/
void SplitList::erase(num begin, num end)
{
    SplitListBlock *tail, *middle;
    m_head = _split(m_head, end, tail);
    m_head = _split(m_head, begin, middle);
    m_head = _concat(m_head, tail, 0);
    delete middle;

    m_size -= end - begin;
}

vector<pair<wchar_t, num>> SplitList::D_dump() const
{
    vector<pair<wchar_t, num>> ans;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        for (num i = 0; i < cur->size; ++i) {
            ans.push_back(make_pair(cur->a[i], cur->w[i]));
        }
    }
    return ans;
}

string SplitList::D_test() const
{
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        if (cur->size <= 0)
            return string("invalid size (<0)");
        if (cur->size > BLOCK_SIZE)
            return string("invalid size (>BLOCK_SIZE)");
        num w = 0, n = 0, t = 0, cw = 0;
        for (num i = 0; i < cur->size; ++i) {
            w += cur->w[i];
            if (cur->a[i] == '\n') ++n;
            if (cur->a[i] == '\t') ++t;
            if (cur->a[i] == '\n')
                cw = 0;
            else
                cw += cur->w[i];
        }
        if (w != cur->width)
            return string("wrong width");
        if (n != cur->n_newline)
            return string("wrong newline count");
        if (t != cur->n_tab)
            return string("wrong tab count");
        if (cw != cur->cw)
            return string("wrong cw (width after last newline)");
    }
    return string("");
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
    num le = 0, ri = 0;
    for (auto cur = m_head; cur != nullptr; cur = cur->next) {
        le = ri, ri += cur->size;
        if (begin <= le && ri <= end) {
            ans += cur->width;
            continue;
        }
        num s = max(begin, le) - le;
        num t = min(end, le) - le;
        if (s < t) {
            ans += std::accumulate(cur->w + s, cur->w + t, 0);
        }
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

SplitListBlock * SplitList::_resize_tabs(SplitListBlock *cur, num cw) const
{
    if (cur == nullptr)
        return nullptr;
    bool changed = false;
    for (num i = 0; i < cur->size; ++i) {
        if (cur->a[i] == '\t') {
            cur->w[i] = m_tab_width - cw;
            changed = true;
        }
        if (cur->a[i] == '\n') {
            cw = 0;
        }
        else {
            cw = (cw + cur->w[i]) % m_tab_width;
        }
    }
    if (changed)
        cur->update();
    cur->next = _resize_tabs(cur->next, cw);
    return cur;
}

SplitListBlock * SplitList::_resize_single_tab(SplitListBlock *cur, num cw) const
{
    if (cur == nullptr)
        return nullptr;

    if (cur->n_tab > 0) {
        num i = 0;
        while (cur->a[i] != '\t' && cur->a[i] != '\n') {
            cw = (cw + cur->w[i]) % m_tab_width;
            ++i;
        }
        if (cur->a[i] == '\t') {
            cur->w[i] = m_tab_width - cw;
            cur->update();
        }
        return cur;
    }
    else {
        if (cur->n_newline > 0)
            return cur;
        cw = (cw + cur->width) % m_tab_width;
        cur->next = _resize_single_tab(cur->next, cw);
        return cur;
    }
}

SplitListBlock *SplitList::_make_list(const wstring &str, num begin, num end, num cw) const
{
    if (begin >= end)
        return nullptr;
    num p = min(begin + BLOCK_SIZE, end);
    SplitListBlock *cur = new SplitListBlock();

    cur->size = p - begin;
    std::copy(str.begin() + begin, str.begin() + p, cur->a);
    for (num i = 0; i < cur->size; ++i) {
        if (cur->a[i] == '\t') {
            cur->w[i] = m_tab_width - cw;
        } 
        else {
            cur->w[i] = char_width(cur->a[i]);
        }
        if (cur->a[i] == '\n') {
            cw = 0;
        }
        else {
            cw = (cw + cur->w[i]) % m_tab_width;
        }
    }
    cur->update();

    cur->next = _make_list(str, p, end, cw);
    return cur;
}

SplitListBlock *SplitList::_split(SplitListBlock *cur, num pos, SplitListBlock *&tmp) const
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
        std::copy(cur->w + pos, cur->w + cur->size, tmp->w);
        tmp->update();
        _try_merge(tmp);

        tmp = _resize_single_tab(tmp, 0);

        cur->next = nullptr;
        cur->size = pos;
        cur->update();
        return cur;
    }
    cur->next = _split(cur->next, pos - cur->size, tmp);
    return cur;
}

SplitListBlock *SplitList::_concat(SplitListBlock *cur, SplitListBlock *tmp, num cw) const
{
    if (cur == nullptr) {
        assert(cw == 0);
        return tmp;
    }

    if (cur->n_newline == 0) {
        cw = (cw + cur->width) % m_tab_width;
    }
    else {
        cw = cur->cw % m_tab_width;
    }

    if (cur->next == nullptr) {
        _resize_single_tab(tmp, cw);
        cur->next = tmp;
        cur = _try_merge(cur);
    }
    else {
        cur->next = _concat(cur->next, tmp, cw);
    }
    return cur;
}

SplitListBlock *SplitList::_try_merge(SplitListBlock *cur) const
{
    if (cur->next == nullptr)
        return cur;
    if (cur->size + cur->next->size > BLOCK_SIZE)
        return cur;
    auto tmp = cur->next;
    std::copy(tmp->a, tmp->a + tmp->size, cur->a + cur->size);
    std::copy(tmp->w, tmp->w + tmp->size, cur->w + cur->size);
    cur->size += tmp->size;
    cur->next = tmp->next;
    cur->update();

    tmp->next = nullptr;
    delete tmp;

    return cur;
}


