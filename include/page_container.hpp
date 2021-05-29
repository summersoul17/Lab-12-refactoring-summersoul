//
// Created by summersoul on 29.05.2021.
//

#ifndef INCLUDE_PAGE_CONTAINER_HPP_
#define INCLUDE_PAGE_CONTAINER_HPP_

#include <common.hpp>
#include <log.hpp>
#include <used_memory.hpp>
#include <histogram.hpp>
#include <stat_sender.hpp>
#include <set>
#include <vector>
#include <string>
#include <utility>

template <class stat_sender_t = stat_sender>
class page_container {
public:
    explicit page_container(used_memory* counter = new used_memory(),
                            stat_sender_t* sender = new stat_sender_t()) {
        attach(counter);
        attach(sender);
    }
    ~page_container() {
        for (auto observer : _observers){
            delete observer;
        }
    }

    void attach(i_observer* observer) { _observers.emplace_back(observer); }

public:
    void load_raw_data(std::istream& is) {
        std::vector<std::string> raw_data;
        auto log = log_t::get_instance();

        if (!is) {
            throw std::runtime_error{"unable to open file"};
        }

        log->write("opening file");
        while (!is.eof()) {
            std::string line;
            std::getline(is, line, '\n');
            raw_data.push_back(std::move(line));
        }

        if (raw_data.size() < MIN_LINES) {
            throw std::runtime_error("too small input stream");
        }

        on_raw_data_load(raw_data);
        _raw_data = std::move(raw_data);
    }
    void load_data(int threshold) {
        std::vector<item> data;
        std::set<int> ids;
        for (const auto& line : _raw_data) {
            std::stringstream stream(line);

            item i;
            stream >> i;

            if (auto&& [_, inserted] = ids.insert(i.id); !inserted) {
                throw std::runtime_error("already seen");
            }

            if (i.score > threshold && i.valid()) {
                data.push_back(std::move(i));
            } else {
                on_skipped(i);
            }
        }

        if (data.size() < MIN_LINES) {
            throw std::runtime_error("oops");
        }

        on_data_load(data);
        _data = std::move(data);
    }

    const item& operator[](size_t i) const { return _data[i]; }
    const item& operator[](const std::string& id) const {
        auto it = std::find_if(_data.begin(), _data.end(), [&id](auto const& i) {
            return atoi(id.c_str()) == i.id;
        });
        return *it;
    }

    void on_data_load(const std::vector<item>& new_data) {
        for (auto& observer : _observers) {
            observer->on_data_load(_data, new_data);
        }
    }
    void on_raw_data_load(const std::vector<std::string>& new_data) {
        for (auto& observer : _observers) {
            observer->on_raw_data_load(_raw_data, new_data);
        }
    }
    void on_skipped(const item& i) {
        for (auto& observer : _observers) {
            observer->on_skipped(i);
        }
    }

    [[nodiscard]] size_t data_size() const { return _data.size(); }

private:
    std::vector<i_observer*> _observers;
    std::vector<item> _data;
    std::vector<std::string> _raw_data;
};

#endif  // INCLUDE_PAGE_CONTAINER_HPP_
