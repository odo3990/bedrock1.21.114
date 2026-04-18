#include "semita/client/client.h"

#include <chrono>
#include <thread>
#include <windows.h>

namespace semita::internal {
    DWORD WINAPI entry_thread(LPVOID lp_parameter) {
        const auto& instance = client::get();
        while (instance.running()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        logger::shutdown();
        FreeLibraryAndExitThread(static_cast<HMODULE>(lp_parameter), 0);
    }
}

BOOL APIENTRY DllMain(const HMODULE module, const DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module);
        CreateThread(nullptr, 0, semita::internal::entry_thread, module, 0, nullptr);
    }

    return true;
}
