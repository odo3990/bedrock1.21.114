#pragma once

#include <string_view>

namespace semita::text_format {
    namespace detail {
        template <char color_code>
        inline constexpr char color_code_bytes[4] = { '\xC2', '\xA7', color_code, '\0' };
    }

    enum class color_code : char {
        black = '0',
        dark_blue = '1',
        dark_green = '2',
        dark_aqua = '3',
        dark_red = '4',
        dark_purple = '5',
        gold = '6',
        gray = '7',
        dark_gray = '8',
        blue = '9',
        green = 'a',
        aqua = 'b',
        red = 'c',
        light_purple = 'd',
        yellow = 'e',
        white = 'f',
        obfuscated = 'k',
        bold = 'l',
        strikethrough = 'm',
        underline = 'n',
        italic = 'o',
        reset = 'r'
    };

    template <color_code C>
    inline constexpr std::string_view color{detail::color_code_bytes<static_cast<char>(C)>, 3};

    static constexpr auto black          = color<color_code::black>;
    static constexpr auto dark_blue      = color<color_code::dark_blue>;
    static constexpr auto dark_green     = color<color_code::dark_green>;
    static constexpr auto dark_aqua      = color<color_code::dark_aqua>;
    static constexpr auto dark_red       = color<color_code::dark_red>;
    static constexpr auto dark_purple    = color<color_code::dark_purple>;
    static constexpr auto gold           = color<color_code::gold>;
    static constexpr auto gray           = color<color_code::gray>;
    static constexpr auto dark_gray      = color<color_code::dark_gray>;
    static constexpr auto blue           = color<color_code::blue>;
    static constexpr auto green          = color<color_code::green>;
    static constexpr auto aqua           = color<color_code::aqua>;
    static constexpr auto red            = color<color_code::red>;
    static constexpr auto light_purple   = color<color_code::light_purple>;
    static constexpr auto yellow         = color<color_code::yellow>;
    static constexpr auto white          = color<color_code::white>;
    static constexpr auto reset          = color<color_code::reset>;
    static constexpr auto bold           = color<color_code::bold>;
    static constexpr auto italic         = color<color_code::italic>;
    static constexpr auto underline      = color<color_code::underline>;
    static constexpr auto strikethrough  = color<color_code::strikethrough>;
    static constexpr auto obfuscated     = color<color_code::obfuscated>;
}
