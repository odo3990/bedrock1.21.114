#pragma once

#include "registry/signature_registry.h"
#include "util/timer.h"

#include <future>
#include <libhat/Scanner.hpp>

namespace semita {
    struct scanner {
        static void initialize() {
            constexpr auto size = std::tuple_size_v<signature_list>;
            scan_all(std::make_index_sequence<size>{});
        }

        template <size_t ...Is>
        static void scan_all(std::index_sequence<Is...>) {
            scan_all_impl<std::tuple_element_t<Is, signature_list>...>();
        }

        template <is_signature... sig_t>
        static void scan_all_impl() {
            logger::get()->debug("starting signature scan...");
            const timer timer;

            std::array<std::future<void>, sizeof...(sig_t)> futures = {
                std::async(std::launch::async, scan<sig_t>)...
            };

            for (const auto& f : futures) {
                f.wait();
            }

            const auto count = timer.count();
            logger::get()->debug("Finished scanning in {:.3f} ms\n", count);
        }

        template <is_signature sig>
        static void scan() {
            constexpr auto name = sig::name.to_view();
            constexpr auto pattern = hat::compile_signature<sig::fixed_pattern>();
            const auto result = hat::find_pattern(pattern, ".text");

            if (!result.has_result()) {
                logger::get()->error("failed to find signature: {}", name);
                return;
            }

            signature_result<signature_func_v<sig>>::value = result.get();
            logger::get()->info("found signature {}: {}", name, reinterpret_cast<uintptr_t>(result.get()));
        }
    };
}
