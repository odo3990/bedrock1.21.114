#include "client.h"

namespace semita {
    void client::eject() {
        m_running = false;
    }

    bool client::running() const {
        return m_running;
    }

    client& client::get() {
        static client instance;
        return instance;
    }
}
