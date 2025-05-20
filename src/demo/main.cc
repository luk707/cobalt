#include "app.hh"

class TriangleApp : public VulkanApp
{
protected:
    void initVulkan() override
    {
        VulkanApp::initVulkan();
        // Add pipeline, render pass, etc. here later
    }

    void mainLoop() override
    {
        bool running = true;
        SDL_Event event;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    running = false;
            }
            SDL_Delay(16); // render later
        }
    }

    void cleanup() override
    {
        // destroy pipeline, render pass, etc. later
        VulkanApp::cleanup();
    }
};

int main()
{
    try
    {
        TriangleApp app;
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
