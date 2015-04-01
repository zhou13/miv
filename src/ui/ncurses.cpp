#include "miv/miv.hpp"
#include "ui/ncurses.hpp"
#include <ncurses.h>

NcursesUI::NcursesUI()
{
    printf("NcursesUI.constructor\n");
    initscr();
    noecho();
}


NcursesUI::~NcursesUI()
{
    printf("NcursesUI.destructor\n");
    endwin();
}


void NcursesUI::run()
{
    printf("NcursesUI.start_run\n");
    m_miv->init();
    m_miv->redraw();
    while (1) {
        char ch = getch();
        if (ch == 'q')
            break;
        mvprintw(50, 0, "");
        m_miv->key_press(KeyCombo(ch));
    }
    printf("NcursesUI.stop_run\n");
}


void NcursesUI::paint(int frame_id, const Screen &screen)
{
    (void)frame_id; // TODO: add more frames

    const int x = (int)screen.cursor.x;
    const int y = (int)screen.cursor.y;

    int cur_line = 10, first_line = cur_line;
    mvprintw(cur_line++, 0, "#------#");
    for (auto &x: screen.cells) {
        string str = "";
        for (auto &y: x) {
            char ch = (char)y.ch;
            if (ch == '\0')
                ch = ' ';
            str += ch;
        }
        while (str.size() < 60) str += ' ';
        mvprintw(cur_line++, 0, "|%s|", str.c_str());
    }
    mvprintw(cur_line++, 0, "#------#");
    mvprintw(first_line + 1 + x, y + 1, "");
}


Size NcursesUI::ask_size(int frame_id,
                         const vector<ScreenCell> &gutter_sample)
{
    (void)frame_id;
    (void)gutter_sample;
    return Size(8, 60);
}
