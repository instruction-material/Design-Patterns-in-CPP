#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Request {
    std::string id;
    bool urgent;
};

class Desk {
public:
    bool submit(Request request) {
        if (std::ranges::any_of(queue_, [&](const Request& queued) {
            return queued.id == request.id;
        })) return false;
        if (request.urgent) {
            const auto firstOrdinary = std::ranges::find_if(queue_, [](const Request& row) {
                return !row.urgent;
            });
            queue_.insert(firstOrdinary, std::move(request));
        } else {
            queue_.push_back(std::move(request));
        }
        return true;
    }

    const std::vector<Request>& queue() const { return queue_; }

private:
    std::vector<Request> queue_;
};

int main() {
    Desk desk;
    desk.submit({"A", false});
    desk.submit({"B", true});
    desk.submit({"C", false});
    desk.submit({"D", true});
    std::cout << std::boolalpha << desk.submit({"A", true}) << '\n';
    for (const auto& request : desk.queue()) std::cout << request.id << '\n';
}
