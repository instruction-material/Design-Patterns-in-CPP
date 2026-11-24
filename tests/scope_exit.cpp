#include "../DPC7-RAII-Resource-Manager/solution/scope_exit.hpp"

#include <type_traits>
#include <utility>

static_assert(!std::is_copy_constructible_v<ScopeExit>);
static_assert(!std::is_copy_assignable_v<ScopeExit>);
static_assert(std::is_nothrow_move_constructible_v<ScopeExit>);
static_assert(!std::is_move_assignable_v<ScopeExit>);

struct LeaveScope {};

int main() {
    int calls = 0;
    {
        ScopeExit first([&calls]() noexcept { ++calls; });
        try {
            ScopeExit owner(std::move(first));
            throw LeaveScope{};
        } catch (const LeaveScope&) {
            if (calls != 1) return 1;
        }
    }
    if (calls != 1) return 1;
    { ScopeExit ordinary([&calls]() noexcept { ++calls; }); }
    return calls == 2 ? 0 : 1;
}
