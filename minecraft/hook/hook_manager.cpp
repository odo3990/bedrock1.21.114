#include "hook_manager.h"

#include "../signature/scanner.h"
#include "util/tuple.h"

#include <Minhook.h>

namespace semita {
    hook_manager::hook_manager() {
        scanner::initialize();
        MH_Initialize();

        tuple_for_each(m_hooks, [this](auto&& hook) {
            initialize(hook);
        });

        constexpr auto standalone_hook_count = std::tuple_size_v<standalone_hook_types>;
        initialize_standalone_hooks<standalone_hook_types>(std::make_index_sequence<standalone_hook_count>{});
    }

    hook_manager::~hook_manager() {
        constexpr auto standalone_hook_count = std::tuple_size_v<standalone_hook_types>;
        shutdown_standalone_hooks<standalone_hook_types>(std::make_index_sequence<standalone_hook_count>{});

        tuple_for_each(m_hooks, [this](auto&& hook) {
            shutdown(hook);
        });

        MH_Uninitialize();
    }
}
