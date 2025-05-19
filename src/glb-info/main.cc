#include <CLI/CLI.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

struct Chunk
{
    uint32_t length;
    uint32_t type;
    std::vector<uint8_t> content;
};

void readGLBFile(const std::string &filename, std::vector<Chunk> &chunks, bool silent, bool &isJsonFormat, bool &isBinFormat)
{
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file.");
    }

    // Read the magic value and version
    char magic[4];
    uint32_t version;
    uint32_t length;
    file.read(magic, 4);
    file.read(reinterpret_cast<char *>(&version), sizeof(version));
    file.read(reinterpret_cast<char *>(&length), sizeof(length));

    // Check for magic value "glTF"
    if (std::strncmp(magic, "glTF", 4) != 0)
    {
        throw std::runtime_error("Not a valid glTF file.");
    }

    if (!silent)
    {

        std::cout << "Format: glTF\n";
        std::cout << "Version: " << version << "\n";
        std::cout << "Length: " << length << " bytes\n\n";
    }

    // Read chunks
    while (file)
    {
        uint32_t chunkLength;
        uint32_t chunkType;

        file.read(reinterpret_cast<char *>(&chunkLength), sizeof(chunkLength));
        file.read(reinterpret_cast<char *>(&chunkType), sizeof(chunkType));

        if (!file)
            break;

        Chunk chunk;
        chunk.length = chunkLength;
        chunk.type = chunkType;
        chunk.content.resize(chunkLength);
        file.read(reinterpret_cast<char *>(chunk.content.data()), chunkLength);

        chunks.push_back(chunk);

        if (!silent)
        {
            std::cout << "Chunk #" << chunks.size() - 1 << ":\n";
            std::cout << "  Type: " << (chunkType == 0x4E4F534A ? "JSON" : "BIN") << "\n";
            std::cout << "  Length: " << chunkLength << "\n";
            std::cout << "  Chunk data read into memory.\n\n";
        }

        // Optionally handle other chunk types (e.g., JSON and BIN)
        if (chunkType == 0x4E4F534A)
        {
            isJsonFormat = true; // JSON chunk
        }
        else if (chunkType == 0x004E4942)
        {
            isBinFormat = true; // BIN chunk
        }
    }
}

// Function to output the JSON chunk to the console
void outputJsonChunk(const Chunk &jsonChunk)
{
    std::string jsonData(jsonChunk.content.begin(), jsonChunk.content.end());
    std::cout << jsonData << std::endl;
}

// Function to output the BIN chunk to the console
void outputBinChunk(const Chunk &binChunk)
{
    std::cout.write(reinterpret_cast<const char *>(binChunk.content.data()), binChunk.content.size());
}

int main(int argc, char **argv)
{
    CLI::App app{"glb-info: A tool for extracting and printing GLB file contents"};

    // Input file
    std::string filename;
    app.add_option("file", filename, "Path to the GLB file")->required();

    // Output format flag (json or bin)
    std::string output = "default";
    app.add_option("-o,--output", output, "Output format (json or bin)")->default_val("default");

    CLI11_PARSE(app, argc, argv);

    std::vector<Chunk> chunks;
    bool isJsonFormat = false;
    bool isBinFormat = false;

    try
    {
        // Read the GLB file and extract chunks
        readGLBFile(filename, chunks, output != "default", isJsonFormat, isBinFormat);

        // If the output is json, print the JSON chunk
        if (output == "json" && isJsonFormat)
        {
            outputJsonChunk(chunks[0]);
        }
        // If the output is bin, print the BIN chunk
        else if (output == "bin" && isBinFormat)
        {
            outputBinChunk(chunks[1]);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
