#include "splitlist-tester.hpp"
#include <random>
#include <iostream>

class SplitList2
{
public:
    SplitList2() : tw(4) {}
    ~SplitList2() {}
    void assign(const wstring &str) { m_str = str; }
    void set_tab_width(num width) { tw = width; }
    num tab_width() const { return tw; }
    num size() const { return (num)m_str.size(); }
    wstring get(num begin, num end) const { return m_str.substr(begin, end - begin); }
    num count_newline() const { return (num)std::count(m_str.begin(), m_str.end(), '\n'); }
    num count_newline(num begin, num end) const { 
        return (num)std::count(m_str.begin() + begin, m_str.begin() + end, '\n');
    }
    num find_kth_newline(num k) const {
        if (k < 0) return -1;
        num cnt = 0;
        for (num i = 0; i < size(); ++i) {
            if (m_str[i] == '\n') {
                if (cnt == k) return i;
                ++cnt;
            }
        }
        if (cnt == k)
            return size();
        assert(false);
        return -1;
    }
    num width() const { return width(0, size()); }
    num width(num begin, num end) const {
        num cw = 0, ans = 0;
        for (num i = begin; i < end; ++i) {
            wchar_t ch = m_str[i];
            num w = char_width(ch);
            if (ch == '\t') w = tw - cw;
            cw = (cw + w) % tw;
            if (ch == '\n') cw = 0;
            ans += w;
        }
        return ans;
    }
    num find_visual_pos(num i, num w) const {
        num j = i;
        while (width(i, j + 1) <= w)
            ++j;
        return j;
    }
    void insert(num pos, const wstring &value) {
        m_str.insert(pos, value);
    }
    void erase(num begin, num end) {
        m_str.erase(begin, end - begin);
    }
    vector<pair<wchar_t, num>> D_dump() const {
        vector<pair<wchar_t, num>> ans;
        num cw = 0;
        for (auto &ch : m_str) {
            num w = char_width(ch);
            if (ch == '\t') w = tw - cw;
            cw = (cw + w) % tw;
            if (ch == '\n') cw = 0;
            ans.push_back(make_pair(ch, w));
        }
        return ans;
    }
private:
    wstring m_str;
    num tw;
};

SplitListTester::SplitListTester()
{
    obj = make_unique<SplitList>();
    ref = make_unique<SplitList2>();
    settings.clear();
    config("N0", 10);
    config("N_insert", 2);
    config("N_erase", 2);
    config("operations", 100000);
    std::cout << "SplitListTester created" << std::endl;
}

SplitListTester::~SplitListTester()
{
    std::cout << "SplitListTester destroyed" << std::endl;
}

void SplitListTester::config(string ind, num val)
{
    settings[ind] = val;
}

static wstring rand_seq(std::default_random_engine &gen, num len)
{
    static wstring alphabet;
    if (alphabet.empty()) {
        for (wchar_t ch = 'a'; ch <= 'z'; ++ch)
            alphabet += ch;
        for (wchar_t ch = 'A'; ch <= 'Z'; ++ch)
            alphabet += ch;
        alphabet += wchar_t('\t');
        alphabet += wchar_t('\n');
        alphabet += wchar_t(' ');
    }
    static std::uniform_int_distribution<size_t> distribution(0, alphabet.size() - 1);
    wstring ans;
    for (num p = 0; p < len; ++p) {
        size_t i = distribution(gen);
        ans += alphabet[i];
    }
    return ans;
}

static char p_ch(wchar_t ch) {
    if (ch == '\t') return '_';
    if (ch == '\n') return '\\';
    return char(ch);
}

static string p_str(const wstring &str) {
    string s;
    for (auto c : str) s += p_ch(c);
    return s;
}

static std::ostream& operator <<(std::ostream& os, const wstring& str)
{
    string s = p_str(str);
    os << s;
    return os;
}

static num random(std::default_random_engine &gen, num n) {
    std::uniform_int_distribution<num> distribution(0, n - 1);
    return distribution(gen);
}

static void bad(string msg, string details = "") {
    std::cout << "bad [" << msg << "]" << std::endl;
    std::cout << details;
    system("pause");
    exit(1);
}

void SplitListTester::run()
{
    std::default_random_engine gen;

    num n0 = get_setting("N0");
    wstring s0 = rand_seq(gen, n0 + random(gen, n0));
    obj->assign(s0);
    ref->assign(s0);

    num operations = get_setting("operations");
    for (num cur = 0; cur < operations; ++cur) {
        std::cout << "Op #" << cur + 1 << ": ";
        num n = ref->size();

        switch (random(gen, 3)) {
        case 0: // modification
            if (random(gen, 100) == 0) { // assign
                std::cout << "(assign) ";
                wstring s0 = rand_seq(gen, n0 + random(gen, n0));
                obj->assign(s0);
                ref->assign(s0);
            }
            else if (random(gen, 20) == 0) { // set tab width
                std::cout << "(set_tw) ";
                num w = 1 + random(gen, 20);
                obj->set_tab_width(w);
                ref->set_tab_width(w);
            }
            else if (random(gen, 2) == 0) { // insert
                std::cout << "(insert) ";
                num n1 = get_setting("N_insert");
                wstring s = rand_seq(gen, 1 + random(gen, n1));
                num pos = random(gen, n + 1);
                obj->insert(pos, s);
                ref->insert(pos, s);
            }
            else if (n > 0) { // erase
                std::cout << "(erase) ";
                num n1 = get_setting("N_erase");
                num len = random(gen, min(n, n1)) + 1;
                num pos = random(gen, n - len + 1);
                std::cout << "pos=" << pos << " len=" << len << " ";
                obj->erase(pos, pos + len);
                ref->erase(pos, pos + len);
            }
            break;

        case 1: // query
            break;

        case 2: // test
            std::cout << "(!test) ";
            string test_result = obj->D_test();
            if (test_result != "") {
                bad("@D_test " + test_result);
            }
            if (obj->D_dump() != ref->D_dump()) {
                std::stringstream sout;
                auto dump_obj = obj->D_dump();
                auto dump_ref = ref->D_dump();
                sout << "  tab_width: " << ref->tab_width() << std::endl;
                sout << "  obj: "; for (auto x : dump_obj) sout << p_ch(x.first); sout << std::endl;
                sout << "  ref: "; for (auto x : dump_ref) sout << p_ch(x.first); sout << std::endl;
                sout << "  obj_w: "; for (auto x : dump_obj) sout << x.second << " "; sout << std::endl;
                sout << "  ref_w: "; for (auto x : dump_ref) sout << x.second << " "; sout << std::endl;
                /*
                sout << "ref: ";
                for (auto x : dump_ref)
                    sout << "(" << (char)x.first << ", " << x.second << ") ";
                sout << std::endl;
                */
                bad("@D_dump", sout.str());
            }
            std::cout << "ok | tw=" << ref->tab_width() << " n=" << n;
            break;
        }
        std::cout << std::endl;
    }
    //std::cout << rand_seq(gen, 10) << std::endl;
    //std::cout << rand_seq(gen, 10) << std::endl;
}

num SplitListTester::get_setting(string ind) const
{
    auto it = settings.find(ind);
    if (it == settings.end()) {
        std::cout << "DAMN: cannot find setting '" << ind << "'" << std::endl;
        exit(1);
    }
    return it->second;
}
