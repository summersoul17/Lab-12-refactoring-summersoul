//
// Created by summersoul on 29.05.2021.
//

#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_

#include <common.hpp>

class log_t {
public:
    static log_t* get_instance();
    void set_log_level(size_t level) { _level = level; }

public:
    void write(std::string_view) const;
    void write_debug(std::string_view) const;

private:
    log_t():_output{&std::cout}{}

private:
    size_t _level = 0;
    mutable std::ostream* _output;
};

#endif  // INCLUDE_LOG_HPP_
