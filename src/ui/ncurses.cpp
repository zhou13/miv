#include "miv/miv.hpp"
#include "ui/ncurses.hpp"
#include <ncurses.h>

static const int W = 20;
static const int H = 10;

#if 0
#undef initscr
#define initscr(agrs...)
#undef noecho
#define noecho(args...)
#undef mvprintw
#define mvprintw(x, y, args...) printf(args), printf("\n")
#endif

NcursesUI::NcursesUI()
{
    //DEFINE_SCOPE_LOGGER;

    initscr();
    noecho();

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_YELLOW);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
}


NcursesUI::~NcursesUI()
{
    //DEFINE_SCOPE_LOGGER;

    endwin();
}


void NcursesUI::run()
{
    //DEFINE_SCOPE_LOGGER;

    m_miv->init();
    m_miv->redraw();
    while (1) {
        char ch = getch();
        if (ch == '`')
            break;
        m_miv->key_press(KeyCombo(string(1, ch)));
    }
}


void NcursesUI::paint(int frame_id, const Screen &screen)
{
    (void)frame_id; // TODO: add more frames

    const int x = (int)screen.cursor.x;
    const int y = (int)screen.cursor.y;

    int cur_line = 0, first_line = cur_line;
    int gutter_width = 0;
    for (auto &line: screen.cells) {
        string str1 = "", str2 = "";
        for (auto &cell: line) {
            if (cell.type == ScreenCellType::TEXT) {
                char ch = (char)cell.ch;
                if (ch == '\0')
                    ch = ' ';
                str2 += ch;
            }
            if (cell.type == ScreenCellType::LINE_NUMBER) {
                string tmp = "";
                if (cell.enabled) {
                    num x = cell.line_number;
                    bool neg = false;
                    if (x < 0) {
                        x = -x;
                        neg = true;
                    }
                    for (; x > 0; x /= 10)
                        tmp = string() + (char)(x % 10 + '0') + tmp;
                    if (neg) {
                        tmp = "-" + tmp;
                    }
                    if (tmp.size() == 0)
                       tmp = "0";
                }
                while ((num)tmp.size() < cell.width)
                    tmp = " " + tmp;
                str1 += tmp + " ";
            }
        }
        gutter_width = (int)str1.size();
        while (str1.size() + str2.size() < W) str2 += ' ';

        attron(COLOR_PAIR(1));
        mvprintw(cur_line, 0, "%s", str1.c_str());
        if (cur_line == first_line + x) {
            attron(COLOR_PAIR(3));
        }
        else {
            attron(COLOR_PAIR(2));
        }
        printw("%s", str2.c_str());
        attron(COLOR_PAIR(4));
        printw("|");
        cur_line += 1;
    }
    string str(W + 1, '-');
    attron(COLOR_PAIR(4));
    mvprintw(cur_line, 0, "%s", str.c_str());
    mvprintw(first_line + x, gutter_width + y, "");
}


Size NcursesUI::ask_size(int frame_id,
                         const vector<ScreenCell> &gutter_sample)
{
    (void)frame_id;
    num height = H, width = W;
    for (auto &cell: gutter_sample) {
        if (cell.type == ScreenCellType::TEXT)
            width -= 1;
        if (cell.type == ScreenCellType::LINE_NUMBER)
            width -= cell.width + 1;
    }
    return Size(height, width);
}
