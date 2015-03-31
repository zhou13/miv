#include <iostream>
#include "common.hpp"
#include "ui/ncurses.hpp"

int main() {
	std::cout << "Hello World!" << std::endl;
    UI *ui = new NcursesUI();
    ui->run();
	return 0;
}
