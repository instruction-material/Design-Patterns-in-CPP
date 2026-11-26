#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Entry {
  public:
    virtual ~Entry() = default;
    virtual unsigned totalSeconds() const = 0;
};

class Track final : public Entry {
    std::string name_;
    unsigned duration_;
  public:
    Track(std::string name, unsigned duration)
        : name_(std::move(name)), duration_(duration) {}
    const std::string& name() const { return name_; }
    unsigned totalSeconds() const override { return duration_; }
};

class Playlist final : public Entry {
    std::vector<std::unique_ptr<Entry>> entries_;
  public:
    void add(std::unique_ptr<Entry> entry) {
        entries_.push_back(std::move(entry));
    }
    unsigned totalSeconds() const override {
        unsigned total = 0;
        for (const auto& part : entries_) total += part->totalSeconds();
        return total;
    }
};

int main() {
    Playlist mix;
    mix.add(std::make_unique<Track>("Intro", 120));
    auto set = std::make_unique<Playlist>();
    set->add(std::make_unique<Track>("Part A", 90));
    set->add(std::make_unique<Track>("Part B", 45));
    mix.add(std::move(set));
    mix.add(std::make_unique<Playlist>());
    std::cout << mix.totalSeconds() << '\n';
}
