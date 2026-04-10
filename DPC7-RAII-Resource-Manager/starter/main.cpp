#include <iostream>
#include <memory>
#include <string>
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
	std::vector<TextureHandle> textures;
};

PreviewRenderer::PreviewRenderer() : impl_(std::make_unique<Impl>()) {}
PreviewRenderer::~PreviewRenderer() = default;

void PreviewRenderer::addTexture(const std::string& label) {
	impl_->textures.emplace_back(label);
}

void PreviewRenderer::draw() const {
	std::cout << "textures:";
	for (const auto& texture : impl_->textures) {
		std::cout << ' ' << texture.label() << '#' << texture.id();
	}
	std::cout << '\n';
}

int main() {
	PreviewRenderer renderer;
	renderer.addTexture("terrain");
	renderer.addTexture("player");
	renderer.draw();
	std::cout << "\nTODO: add a scoped cleanup helper or a small cache around the move-only handles.\n";
}
