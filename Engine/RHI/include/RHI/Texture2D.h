// Engine/RHI/include/RHI/Texture2D.h

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

// Never include <GL/gl.h> here.
namespace Valinor::RHI {

// Enum for supported texture formats
enum class TextureFormat : uint8_t {
	RGBA8, RGB8, Depth24Stencil8
};

// Structure describing texture properties
struct TextureDescription {
	uint32_t        width        = 1; // Texture width (default 1)
	uint32_t        height       = 1; // Texture height (default 1)
	TextureFormat   format       = TextureFormat::RGBA8; // Texture format
	bool            generateMips = false; // Generate mipmaps flag
	std::string_view debugName; // Optional debug name
};

// Abstract base class for 2D textures
class Texture2D {
public:
	virtual ~Texture2D() = default;

	Texture2D(const Texture2D&)            = delete; // Disable copy constructor
	Texture2D& operator=(const Texture2D&) = delete; // Disable copy assignment

	[[nodiscard]] virtual uint32_t GetWidth()  const  noexcept = 0;  // Get texture width
	[[nodiscard]] virtual uint32_t GetHeight() const  noexcept = 0;  // Get texture height

	// Get API-specific texture handle
	[[nodiscard]] virtual uint64_t GetHandle() const  noexcept = 0;

	virtual void SetData(const void* data, uint32_t size) = 0; // Set texture data

	// Factory method to create a Texture2D instance
	[[nodiscard]]
	static std::unique_ptr<Texture2D>
		Create(const TextureDescription& desc);

protected:
	explicit Texture2D(const TextureDescription& d) : m_Desc(d) {} // Protected constructor
	TextureDescription m_Desc; // Texture description
};

} // namespace Valinor::RHI

