#pragma once

#include <functional>
#include <utility>

class ScopeExit {
  public:
    explicit ScopeExit(std::function<void()> action)
        : action_(std::move(action)) {
    }
    ScopeExit(const ScopeExit&) = delete;
    ScopeExit& operator=(const ScopeExit&) = delete;
    ScopeExit(ScopeExit&& other) noexcept
        : action_(std::exchange(other.action_, {})) {}
    ScopeExit& operator=(ScopeExit&&) = delete;

    ~ScopeExit() noexcept {
        if (action_) {
            action_();
        }
    }

  private:
    std::function<void()> action_;
};
