//
// Created by summersoul on 29.05.2021.
//

#ifndef INCLUDE_I_OBSERVER_HPP_
#define INCLUDE_I_OBSERVER_HPP_

#include <common.hpp>
#include <string>
#include <vector>

class i_observer {
public:
    i_observer() = default;
    virtual ~i_observer() = default;
    virtual void on_data_load(const std::vector<item>&,
                              const std::vector<item>&) = 0;
    virtual void on_raw_data_load(const std::vector<std::string>&,
                                  const std::vector<std::string>&) = 0;
    virtual void on_skipped(const item&) = 0;
};
#endif  // INCLUDE_I_OBSERVER_HPP_
