export module cmoon.html.attributes;

import std.core;

namespace cmoon::html
{
    export
    namespace attributes
    {
        export
        struct accesskey
        {
            template<char C>
            struct constant
            {
                using parent_type = accesskey;

                friend std::ostream& operator<<(std::ostream& os, const constant&)
                {
                    return os << "accesskey=\""
                              << C
                              << '"';
                }

                static constexpr char value {C};
            };

            friend std::ostream& operator<<(std::ostream& os, const accesskey& a)
            {
                return os << "accesskey=\""
                          << a.value
                          << '"';
            }

            char value;
        };

        export
        struct async
        {
            friend std::ostream& operator<<(std::ostream& os, const async&)
            {
                return os << "async";
            }
        };
    }
}