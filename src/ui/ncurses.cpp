#include "miv/miv.hpp"
#include "ui/ncurses.hpp"
#include <ncurses.h>

static const int W = 10;
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
    printf("NcursesUI.constructor\n");
    initscr();
    noecho();

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
}


NcursesUI::~NcursesUI()
{
    printf("NcursesUI.destructor\n");
    endwin();
}


void NcursesUI::run()
{
    printf("NcursesUI.start_run\n"); fflush(stdout);
    m_miv->init();
    m_miv->redraw();
    while (1) {
        char ch = getch();
        if (ch == 'q')
            break;
        //mvprintw(50, 0, "");
        m_miv->key_press(KeyCombo(ch));
    }
    printf("NcursesUI.stop_run\n");
}


void NcursesUI::paint(int frame_id, const Screen &screen)
{
    (void)frame_id; // TODO: add more frames

    const int x = (int)screen.cursor.x;
    const int y = (int)screen.cursor.y;

    //printf("NcursesUI.paint: screen.cells.size=%d\n", (int)screen.cells.size());
    //return;

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
            if (cell.type == ScreenCellType::LINENUMBER) {
                string tmp = "";
                if (cell.enabled) {
                    ptrdiff_t x = cell.line_number;
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
                while (tmp.size() < cell.width)
                    tmp = " " + tmp;
                str1 += tmp + " ";
            }
        }
        gutter_width = (int)str1.size();
        while (str1.size() + str2.size() < W) str2 += ' ';

        attron(COLOR_PAIR(1));
        mvprintw(cur_line, 0, "%s", str1.c_str());
        attron(COLOR_PAIR(2));
        printw("%s", str2.c_str());
        attron(COLOR_PAIR(3));
        printw(" ");
        cur_line += 1;
    }
    string str(W + 1, ' ');
    attron(COLOR_PAIR(3));
    mvprintw(cur_line, 0, "%s", str.c_str());
    mvprintw(first_line + x, gutter_width + y, "");
}


Size NcursesUI::ask_size(int frame_id,
                         const vector<ScreenCell> &gutter_sample)
{
    (void)frame_id;
    size_t height = H, width = W;
    for (auto &cell: gutter_sample) {
        if (cell.type == ScreenCellType::TEXT)
            width -= 1;
        if (cell.type == ScreenCellType::LINENUMBER)
            width -= cell.width + 1;
    }
    //printf("NcursesUI.ask_size: return\n"); fflush(stdout);
    return Size(height, width);
}
