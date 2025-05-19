#include "glb.hh"

std::optional<glb::ChunkType> glb::strToChunkType(const std::string &chunkTypeStr)
{
    static const std::unordered_map<std::string, glb::ChunkType> chunkTypeMap = {
        {"json", glb::ChunkType::JSON},
        {"bin", glb::ChunkType::BIN},
    };

    auto it = chunkTypeMap.find(chunkTypeStr);
    if (it != chunkTypeMap.end())
    {
        return it->second;
    }
    return std::nullopt;
}

glb::File glb::readFile(std::istream &stream)
{
    glb::File file;

    uint32_t magic = 0;
    stream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
    if (magic != glb::GLTF_HEADER_MAGIC_CONSTANT)
    {
        throw std::runtime_error("Invalid GLB header");
    }

    stream.read(reinterpret_cast<char *>(&file.header.version), sizeof(uint32_t));
    stream.read(reinterpret_cast<char *>(&file.header.length), sizeof(uint32_t));

    while (stream.tellg() < file.header.length)
    {
        glb::Chunk chunk;

        stream.read(reinterpret_cast<char *>(&chunk.length), sizeof(uint32_t));
        stream.read(reinterpret_cast<char *>(&chunk.type), sizeof(uint32_t));

        chunk.content.resize(chunk.length);
        stream.read(reinterpret_cast<char *>(chunk.content.data()), chunk.length);

        file.chunks.push_back(std::move(chunk));
    }

    return file;
}

const glb::Chunk *glb::glbGetFirstChunkOfType(const glb::File &file, uint32_t type)
{
    for (const auto &chunk : file.chunks)
    {
        if (chunk.type == type)
        {
            return &chunk;
        }
    }
    return nullptr;
}
