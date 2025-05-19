#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <istream>
#include <optional>

namespace glb
{
    constexpr uint32_t GLTF_HEADER_MAGIC_CONSTANT = 0x46546C67;

    enum class ChunkType : uint32_t
    {
        JSON = 0x4E4F534A,
        BIN = 0x004E4942
    };

    struct Header
    {
        std::string format;
        uint32_t version;
        uint32_t length;
    };

    struct Chunk
    {
        uint32_t length;
        uint32_t type;
        std::vector<uint8_t> content;
    };

    struct File
    {
        Header header;
        std::vector<Chunk> chunks;
    };

    inline const char *glbChunkTypeToStr(uint32_t type)
    {
        static char buf[5]{};
        std::memcpy(buf, &type, 4);
        buf[4] = '\0';
        return buf;
    }

    std::optional<ChunkType> strToChunkType(const std::string &chunkType);

    File readFile(std::istream &stream);

    const Chunk *glbGetFirstChunkOfType(const File &, uint32_t type);
}
