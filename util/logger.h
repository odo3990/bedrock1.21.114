#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <cstdio>
#include <memory>
#include <windows.h>

namespace semita {
    class logger {
    public:
        static logger& instance() {
            static logger instance;
            return instance;
        }

        static spdlog::logger* get() {
            const auto& inst = instance();
            return inst.m_logger.get();
        }

        static void shutdown() {
            get()->info("Ejecting logger...");
            spdlog::shutdown();
            FreeConsole();
        }

    private:
        logger() {
            init_console();

            m_logger = spdlog::stdout_color_mt("Semita");
            spdlog::set_pattern("[%H:%M:%S] [%^Semita%$] %v");
            m_logger->set_level(spdlog::level::debug);
            m_logger->info("welcome to semita.\n");
        }

        static void init_console() {
            AllocConsole();

            FILE* f;
            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONOUT$", "w", stderr);
            freopen_s(&f, "CONIN$", "w", stdin);

            const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
               dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
               SetConsoleMode(hOut, dwMode);
            }

            SetConsoleTitleA("semita logger");
        }

        std::shared_ptr<spdlog::logger> m_logger{};
    };
}
