#pragma once

#include "minecraft/event/event.h"
#include "minecraft/sdk/client/client_instance.h"

namespace semita {
    class tick_event : public event {
    public:
        explicit tick_event(client_instance* instance)
        : m_client_instance(instance) {}

        [[nodiscard]] client_instance* get_client_instance() const {
            return m_client_instance;
        }

    private:
        client_instance* m_client_instance{ nullptr };
    };
}
