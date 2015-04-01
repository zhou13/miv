#include "miv/miv.hpp"
#include "ui/ncurses.hpp"

NcursesUI::NcursesUI()
{
    printf("NcursesUI.constructor\n");
}


NcursesUI::~NcursesUI()
{
    printf("NcursesUI.destructor\n");
}


void NcursesUI::run()
{
    printf("NcursesUI.start_run\n");
    m_miv->init();
    m_miv->redraw();
    while (1) {
        char buf[99];
        char ch;
        scanf("%s", buf);
        ch = buf[0];
        if (ch == 'q')
            break;
        m_miv->key_press(KeyCombo(ch));
    }
    printf("NcursesUI.stop_run\n");
}


void NcursesUI::paint(int frame_id, const Screen &screen)
{
    (void)frame_id; // TODO: add more frames
    int x = (int)screen.cursor.x;
    int y = (int)screen.cursor.y;
    printf("NcursesUI.paint; cursor=(%d, %d)\n", x, y);
    for (auto &x: screen.cells) {
        for (auto &y: x) {
            printf("%c", (char)y.ch);
        }
        printf("\n");
    }
    printf("--------------------\n");
}


Size NcursesUI::ask_size(int frame_id,
                         const vector<ScreenCell> &gutter_sample)
{
    (void)frame_id;
    (void)gutter_sample;
    return Size(8, 6);
}
