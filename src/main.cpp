#include <iostream>
#include "utils/common.hpp"
#include "ui/ncurses.hpp"

int main() {
    std::cout << "Hello World!" << std::endl;

    unique_ptr<UI> ui = make_unique<NcursesUI>();
    ui->run();


	return 0;
}
