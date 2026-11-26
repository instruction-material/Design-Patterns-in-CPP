#include <iostream>

class OutputChannel {
public:
    bool tryOpen() noexcept {
        if (open_) return false;
        open_ = true;
        return true;
    }

    void close() noexcept {
        open_ = false;
        ++closes_;
    }

    bool isOpen() const noexcept { return open_; }
    int closeCalls() const noexcept { return closes_; }

private:
    bool open_ = false;
    int closes_ = 0;
};

class ChannelLease {
public:
    explicit ChannelLease(OutputChannel& channel) noexcept
        : channel_(channel), acquired_(channel.tryOpen()) {}

    ChannelLease(const ChannelLease&) = delete;
    ChannelLease& operator=(const ChannelLease&) = delete;

    ~ChannelLease() {
        if (acquired_) channel_.close();
    }

    bool acquired() const noexcept { return acquired_; }

private:
    [[maybe_unused]] OutputChannel& channel_;
    bool acquired_;
};

int main() {
    OutputChannel channel;
    std::cout << std::boolalpha;
    {
        const ChannelLease first(channel);
        {
            const ChannelLease denied(channel);
            std::cout << first.acquired() << ' ' << denied.acquired() << '\n';
        }
        std::cout << "Open after denial: " << channel.isOpen() << '\n';
    }
    std::cout << "Open after owner: " << channel.isOpen() << '\n';
    std::cout << "Close calls: " << channel.closeCalls() << '\n';
}
