//
// Created by summersoul on 29.05.2021.
//

#include <stat_sender.hpp>

void stat_sender::on_data_load(const std::vector<item>&,
                               const std::vector<item>& new_items){
    log_t::get_instance()->write_debug("stat_sender::on_loaded");
    async_send(new_items, "/items/loaded");
    log_t::get_instance()->write_debug("stat_sender::on_loaded");
}
void stat_sender::on_skipped(const item& item) {
    log_t::get_instance()->write_debug("stat_sender::on_skipped");
    async_send({item}, "/items/skipped");
    log_t::get_instance()->write_debug("stat_sender::on_skipped");
}
void stat_sender::async_send(const std::vector<item>& items,
                             std::string_view path) {
    auto log = log_t::get_instance();

    log->write(path);
    log->write("send stat " + std::to_string(items.size()));

    for (auto const& item : items) {
        log->write_debug("send: " + std::to_string(item.id));
        // ... some code
        _out_file << item.id << item.name << item.score;
        _out_file.flush();
    }
}
