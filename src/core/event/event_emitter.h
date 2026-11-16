#pragma once

#include "event.h"

#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>

namespace glab::event {

class EventEmitter {
public:
    template <typename EventT>
    EventID On(const std::function<void(const EventT& event)>& callback) {
        auto id = m_next_id++;
        auto index = std::type_index(typeid(EventT));

        m_listeners.emplace(index, id, [callback = std::move(callback)](const std::any& event) {
            callback(std::any_cast<const EventT&>(event));
        });
        return id;
    }

    template <typename EventT>
    void Off(EventID id) {}

    template <typename EventT>
    void Emit(EventT&& event) {}

private:
    using Listener = std::pair<EventID, std::function<void(const std::any& event)>>;

    EventID m_next_id{};
    std::unordered_map<std::type_index, std::vector<Listener>> m_listeners;
};

}  // namespace glab::event
