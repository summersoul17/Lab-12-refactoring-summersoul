// Copyright 2020 Your Name <your_email>

#include <histogram.hpp>

void histogram::on_data_load(const std::vector<item> &,
                             const std::vector<item> & new_items) {
    for (const auto& new_item : new_items) {
        _average += static_cast<float>(new_item.score);
    }
    _average /= static_cast<float>(new_items.size());

    log_t::get_instance()->write("Average: " + std::to_string(_average) +
                                 " Thrown: " + std::to_string(_thrown));
    _thrown = 0;
}
