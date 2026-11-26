#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct Catalog {
    std::map<std::string, int, std::less<>> tracks;
    mutable int lookups = 0;

    std::optional<int> find(std::string_view stop) const {
        ++lookups;
        const auto entry = tracks.find(stop);
        if (entry == tracks.end()) return std::nullopt;
        return entry->second;
    }
};

struct Player {
    std::vector<std::pair<int, int>> starts;

    void play(int track, int volume) {
        starts.emplace_back(track, volume);
    }
};

enum class Launch { InvalidVolume, UnknownStop, Started };

class AudioGuide {
public:
    AudioGuide(const Catalog& catalog, Player& player)
        : catalog_(catalog), player_(player) {}

    Launch start(std::string_view stop, int volume) {
        // TODO: Validate volume, then look up a track and start the player.
        (void)stop;
        (void)volume;
        return Launch::UnknownStop;
    }

private:
    [[maybe_unused]] const Catalog& catalog_;
    [[maybe_unused]] Player& player_;
};

int main() {
    const Catalog catalog{{{"garden", 7}}};
    Player player;
    AudioGuide guide(catalog, player);
    for (const auto& [stop, volume] : std::vector<std::pair<std::string, int>>{
             {"garden", 50}, {"missing", 50}, {"garden", 110}}) {
        const auto result = guide.start(stop, volume);
        switch (result) {
        case Launch::Started: std::cout << "Started\n"; break;
        case Launch::UnknownStop: std::cout << "Unknown stop\n"; break;
        case Launch::InvalidVolume: std::cout << "Invalid volume\n"; break;
        }
    }
    std::cout << "Player starts: " << player.starts.size() << '\n';
}
