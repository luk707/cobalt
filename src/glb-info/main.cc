#include "glb.hh"
#include <CLI/CLI.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

int main(int argc, char **argv)
{
    CLI::App app{"glb-info: A tool for extracting and printing GLB file contents"};

    std::string filename;
    app.add_option("file", filename, "Path to the GLB file")
        ->required();

    std::string output = "default";
    app.add_option("-o,--output", output, "Output format (json or bin)")
        ->default_val("default");

    CLI11_PARSE(app, argc, argv);

    try
    {
        std::ifstream stream(filename, std::ios::binary);
        glb::File file = glb::readFile(stream);

        auto chunkType = glb::strToChunkType(output);

        if (!chunkType.has_value() && output != "default")
        {
            throw std::runtime_error("Invalid output format");
        }

        if (!chunkType.has_value())
        {
            std::cout << "Format: glTF\n";
            std::cout << "Version: " << file.header.version << "\n";
            std::cout << "Length: " << file.header.length << " bytes\n\n";

            int index = 0;
            for (glb::Chunk chunk : file.chunks)
            {
                std::cout << "Chunk #" << index << ":\n";
                std::cout << "  Type: " << glb::glbChunkTypeToStr(chunk.type) << "\n";
                std::cout << "  Length: " << chunk.length << "\n\n";
                ++index;
            }

            return 0;
        }

        const glb::Chunk *chunk = glb::glbGetFirstChunkOfType(file, static_cast<uint32_t>(chunkType.value()));

        switch (chunkType.value())
        {
        case glb::ChunkType::JSON:
        {
            std::string jsonData(chunk->content.begin(), chunk->content.end());
            std::cout << jsonData << std::endl;
            break;
        }
        case glb::ChunkType::BIN:
            std::cout.write(reinterpret_cast<const char *>(chunk->content.data()), chunk->content.size());
            break;
        }

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
