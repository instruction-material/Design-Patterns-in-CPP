#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

int acquireHandle(const std::string& label) {
	static int nextHandle = 1;
	const int handle = nextHandle++;
	std::cout << "acquire " << label << " -> " << handle << '\n';
	return handle;
}

void releaseHandle(int handle, const std::string& label) {
	std::cout << "release " << label << " -> " << handle << '\n';
}

class ScopeExit {
public:
	explicit ScopeExit(std::function<void()> action) : action_(std::move(action)) {}
	~ScopeExit() {
		if (action_) {
			action_();
		}
	}

private:
	std::function<void()> action_;
};

class TextureHandle {
public:
	explicit TextureHandle(std::string label)
		: label_(std::move(label)), handle_(acquireHandle(label_)) {}

	TextureHandle(const TextureHandle&) = delete;
	TextureHandle& operator=(const TextureHandle&) = delete;

	TextureHandle(TextureHandle&& other) noexcept
		: label_(std::move(other.label_)), handle_(std::exchange(other.handle_, -1)) {}

	TextureHandle& operator=(TextureHandle&& other) noexcept {
		if (this != &other) {
			reset();
			label_ = std::move(other.label_);
			handle_ = std::exchange(other.handle_, -1);
		}
		return *this;
	}

	~TextureHandle() {
		reset();
	}

	int id() const { return handle_; }
	const std::string& label() const { return label_; }

private:
	void reset() {
		if (handle_ != -1) {
			releaseHandle(handle_, label_);
			handle_ = -1;
		}
	}

	std::string label_;
	int handle_;
};

class PreviewRenderer {
public:
	PreviewRenderer();
	~PreviewRenderer();

	void addTexture(const std::string& label);
	void draw() const;

private:
	struct Impl;
	std::unique_ptr<Impl> impl_;
};

struct PreviewRenderer::Impl {
	std::vector<std::shared_ptr<TextureHandle>> textures;
	std::unordered_map<std::string, std::shared_ptr<TextureHandle>> cache;
};

PreviewRenderer::PreviewRenderer() : impl_(std::make_unique<Impl>()) {}
PreviewRenderer::~PreviewRenderer() = default;

void PreviewRenderer::addTexture(const std::string& label) {
	const auto it = impl_->cache.find(label);
	if (it != impl_->cache.end()) {
		impl_->textures.push_back(it->second);
		return;
	}

	auto texture = std::make_shared<TextureHandle>(label);
	impl_->cache.emplace(label, texture);
	impl_->textures.push_back(std::move(texture));
}

void PreviewRenderer::draw() const {
	ScopeExit marker([] { std::cout << "[scope-exit] draw finished\n"; });
	std::cout << "textures:";
	for (const auto& texture : impl_->textures) {
		std::cout << ' ' << texture->label() << '#' << texture->id();
	}
	std::cout << '\n';
}

int main() {
	PreviewRenderer renderer;
	renderer.addTexture("terrain");
	renderer.addTexture("player");
	renderer.addTexture("terrain");
	renderer.draw();
}
