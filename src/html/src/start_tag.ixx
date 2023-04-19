export module cmoon.html.start_tag;

namespace cmoon::html
{
    export
    struct start_tag
    {
        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return true;
        }
    };
}