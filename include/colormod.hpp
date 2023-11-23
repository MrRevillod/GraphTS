
#ifndef COLORMOD_HPP
#define COLORMOD_HPP

#include <iostream>

namespace Color {
    inline std::ostream &red(std::ostream &s) {
        return s << "\033[31m";
    }

    inline std::ostream &green(std::ostream &s) {
        return s << "\033[32m";
    }

    inline std::ostream &blue(std::ostream &s) {
        return s << "\033[34m";
    }

    inline std::ostream &def(std::ostream &s) {
        return s << "\033[39m";
    }
}

#endif
