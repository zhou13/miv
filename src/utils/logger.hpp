#pragma once

#include "utils/common.hpp"
#include "utils/spdlog/spdlog.h"

#include <boost/current_function.hpp>

/* Usage (with increasing priority):
 *     mlog->debug("1 + 1 = {}", 2);
 *     mlog->debug("1 + 1 = %d", 2);
 *     mlog->debug() << "1 + 1 =" << 3;
 *     mlog->info();
 *     mlog->notice();
 *     mlog->warn();
 *     mlog->err();
 *     mlog->critical();
 *     mlog->alert();
 *     mlog->emerg();
 */
extern std::shared_ptr<spdlog::logger> mlog;
extern std::string log_funcname;

#define DEFINE_SCOPE_LOGGER ScopeLogger scope_logger(BOOST_CURRENT_FUNCTION)
class ScopeLogger {
public:
    ScopeLogger(string funcname) {
        m_old_funcname = log_funcname;
        log_funcname = funcname;
        if (mlog) {
            set_pattern();
            mlog->debug("Entering function");
        }
    }

    ~ScopeLogger() {
        log_funcname = m_old_funcname;
        if (mlog) {
            mlog->debug("Leaving function");
            set_pattern();
        }
    }

private:
    string m_old_funcname;

    void set_pattern() {
        mlog->set_pattern(
                    "[%Y-%m-%d %H:%M:%S.%e][%l] " + log_funcname + ": %v");
    }
};
