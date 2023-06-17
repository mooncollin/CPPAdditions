export module cmoon.html:end_tag;

namespace cmoon::html
{
    export
    struct end_tag
    {
        [[nodiscard]] static constexpr bool is_self_closing() noexcept
        {
            return false;
        }
    };
}