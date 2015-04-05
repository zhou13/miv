#include <iostream>

#include "utils/utils.hpp"
#include "ui/ncurses.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

shared_ptr<spdlog::logger> mlog;
string log_funcname;

void help() {
    std::cout << "desc" << std::endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    // TODO change with program_options
    mlog = spdlog::rotating_logger_mt(
                "file_logger", "debug", 1048576 * 5, 3, true);
    mlog->set_level(spdlog::level::info);
#ifdef DEBUG
    mlog->set_level(spdlog::level::debug);
#endif

    DEFINE_SCOPE_LOGGER;

#ifdef WITH_NCURSES_UI
    unique_ptr<UI> ui = make_unique<NcursesUI>();
#endif
    ui->run();

	return 0;
}
