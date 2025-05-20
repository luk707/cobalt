#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

class VulkanApp
{
public:
    void run();

protected:
    virtual void initVulkan();
    virtual void mainLoop() = 0;
    virtual void cleanup();

    void initWindow();
    void createInstance();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    std::vector<char> readFile(const std::string &filename);
    VkShaderModule createShaderModule(const std::vector<char> &code);

protected:
    SDL_Window *window = nullptr;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
};
