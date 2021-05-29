//
// Created by summersoul on 29.05.2021.
//

#ifndef INCLUDE_STAT_SENDER_HPP_
#define INCLUDE_STAT_SENDER_HPP_

#include <common.hpp>
#include <log.hpp>
#include <i_observer.hpp>
#include <string>
#include <vector>

class stat_sender : public i_observer {
public:
    stat_sender() = default;
    virtual ~stat_sender() = default;

public:
    void on_data_load(const std::vector<item>&,
                      const std::vector<item>& new_items) override;
    void on_skipped(const item& item = {-1, "inc", -1}) override;
    void on_raw_data_load(const std::vector<std::string>&,
                          const std::vector<std::string>&) override {}

protected:
    virtual void async_send(const std::vector<item>&,
                            std::string_view);

private:
    std::ofstream _out_file{"network", std::ios::binary};
};
#endif  // INCLUDE_STAT_SENDER_HPP_
