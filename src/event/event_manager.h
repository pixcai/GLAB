#pragma once

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace glab {

struct EventState {
    bool connected{true};
};

template <typename EventT>
struct EventConnection {
    EventConnection(const std::shared_ptr<EventT>& state, std::function<void()> on_disconnect)
        : m_state(state), m_on_disconnect(std::move(on_disconnect)) {}

    void Unsubscribe() const {
        if (auto state = m_state.lock()) {
            if (state->connected) {
                state->connected = false;
                m_on_disconnect();
            }
        }
    }

private:
    std::weak_ptr<EventState> m_state;
    std::function<void()> m_on_disconnect;
};

struct IEventListener {
    virtual ~IEventListener() = default;
};

template <typename EventT>
using EventCallback = std::function<void(const EventT& event)>;

template <typename EventT>
struct EventListener : public IEventListener {
    std::shared_ptr<EventState> state;
    EventCallback<EventT> callback;
};

class EventManager {
public:
    template <typename EventT>
    EventConnection<EventT> Subscribe(EventCallback<EventT> callback) {
        auto state = std::make_shared<EventState>();
        auto listener = std::make_shared<EventListener<EventT>>(
            state, [callback = std::move(callback)](const EventT& event) { callback(event); });

        m_listeners.emplace(typeid(EventT), listener);
        return {state, [&, listener = std::move(listener)]() { RemoveListener<EventT>(listener); }};
    }

    template <typename EventT>
    void Dispatch(const EventT& event) {
        auto [first, last] = m_listeners.equal_range(typeid(EventT));

        for (auto it = first; it != last; ++it) {
            auto listener = static_cast<EventListener<EventT>*>(it->second.get());

            if (listener->state->connected) {
                listener->callback(event);
            }
        }
    }

private:
    template <typename EventT>
    void RemoveListener(std::shared_ptr<EventListener<EventT>> listener) {
        auto [first, last] = m_listeners.equal_range(typeid(EventT));

        for (auto it = first; it != last; ++it) {
            if (it->second == listener) {
                m_listeners.erase(listener);
                break;
            }
        }
    }

    std::unordered_multimap<std::type_index, std::shared_ptr<IEventListener>> m_listeners;
};

inline static EventManager event_manager;

}  // namespace glab
