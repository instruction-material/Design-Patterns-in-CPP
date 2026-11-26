#include <iostream>
#include <string>
#include <string_view>
#include <vector>

enum class Delivery { Accepted, Rejected };

class NoticeSink {
public:
    virtual ~NoticeSink() = default;
    virtual Delivery deliver(std::string_view line) = 0;
};

class NonemptySink final : public NoticeSink {
public:
    Delivery deliver(std::string_view line) override {
        return line.empty() ? Delivery::Rejected : Delivery::Accepted;
    }
};

class TracingSink final : public NoticeSink {
public:
    TracingSink(NoticeSink& sink, std::vector<Delivery>& trace)
        : sink_(sink), trace_(trace) {}

    Delivery deliver(std::string_view line) override {
        // TODO: Record the result as well as returning it.
        return sink_.deliver(line);
    }

private:
    NoticeSink& sink_;
    [[maybe_unused]] std::vector<Delivery>& trace_;
};

int main() {
    NonemptySink sink;
    std::vector<Delivery> trace;
    TracingSink decorated(sink, trace);
    for (const auto note : {"Room ready", ""}) {
        std::cout << (decorated.deliver(note) == Delivery::Accepted ? "accepted" : "rejected") << '\n';
    }
    std::cout << "Trace entries: " << trace.size() << '\n';
}
