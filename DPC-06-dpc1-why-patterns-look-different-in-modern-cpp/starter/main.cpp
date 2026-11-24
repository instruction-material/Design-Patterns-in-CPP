#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Settings {
    int exposure = 1;
    std::vector<std::string> effects;
};

class Preset {
public:
    void setExposure(int value) { settings_->exposure = value; }
    int exposure() const { return settings_->exposure; }
    void addEffect(const std::string& effect) { settings_->effects.push_back(effect); }
    const std::vector<std::string>& effects() const { return settings_->effects; }
private:
    // TODO: copying a preset must give the copy independent settings.
    std::shared_ptr<Settings> settings_ = std::make_shared<Settings>();
};

bool check(const char* label, bool observed) {
    std::cout << label << ": observed " << (observed ? "pass" : "fail") << ", expected pass" << '\n';
    return observed;
}
int main() {
    Preset base;
    base.addEffect("grain");
    Preset night = base;
    night.setExposure(3);
    night.addEffect("blue");
    bool ok = check("original exposure", base.exposure() == 1);
    ok &= check("original effects", base.effects() == std::vector<std::string>{"grain"});
    ok &= check("variant", night.exposure() == 3 &&
                night.effects() == std::vector<std::string>{"grain", "blue"});
    Preset copy;
    copy = night;
    night.addEffect("glow");
    ok &= check("copy assignment", copy.effects().size() == 2);
    return ok ? 0 : 1;
}
