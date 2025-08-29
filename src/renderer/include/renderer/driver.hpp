#pragma once
#ifndef ENGINE_RENDERER_DRIVER_HPP_
#define ENGINE_RENDERER_DRIVER_HPP_

#include <filesystem>
#include <stdexcept>
#include <vector>

#include "tools/services/service_interface.hpp"

#include <vulkan/vulkan.h>

namespace Engine::Renderer
{
    struct Vertex
    {
        float position[3];
        float color[4];
    };

    class Driver : public Tools::Services::IService
    {
    public:
        Driver(const std::filesystem::path& shaderLocation);
        virtual ~Driver() = default;

        Driver(const Driver& other)             = delete;
        Driver(Driver&& other)                  = delete;
        Driver& operator=(const Driver& other)  = delete;
        Driver& operator=(const Driver&& other) = delete;

        void Init();
        void Release();
        void NewFrame();

    private:
        inline void throwIfFailed(VkResult rs, const char* message)
        {
            if (rs != VK_SUCCESS)
                throw std::runtime_error(std::string("VULKAN: ").append(message).c_str());
        }

        VkResult createInstance();
        VkResult createPhysicalDevice();
        VkResult createDevice();
        VkResult createSwapchain();
        VkResult createRenderPass();
        VkResult createPipeline();
        VkResult createBuffer();
        VkResult createCommandPool();
        VkResult createVertexBuffer();
        VkResult createCommandBuffers();
        VkResult recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        VkResult createSemaphore();
        VkResult createFence();
        VkResult createImguiDescriptorPool();
        VkResult initImgui();

        std::vector<char> readFile(const std::wstring& filename);
        uint32_t findMemoryType(VkPhysicalDevice& physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

        VkInstance m_instance                  = VK_NULL_HANDLE;
        VkSurfaceKHR m_surface                 = VK_NULL_HANDLE;
        VkPhysicalDevice m_physicalDevice      = VK_NULL_HANDLE;
        VkDevice m_device                      = VK_NULL_HANDLE;
        VkQueue m_queue                        = VK_NULL_HANDLE;
        VkSwapchainKHR m_swapchain             = VK_NULL_HANDLE;
        VkBuffer m_vertexBuffer                = VK_NULL_HANDLE;
        VkDeviceMemory m_vertexBufferMemory    = VK_NULL_HANDLE;
        VkRenderPass m_renderPass              = VK_NULL_HANDLE;
        VkPipeline m_pipeline                  = VK_NULL_HANDLE;
        VkPipelineLayout m_pipelineLayout      = VK_NULL_HANDLE;
        VkCommandPool m_commandPool            = VK_NULL_HANDLE;
        VkDescriptorPool m_imguiDescriptorPool = VK_NULL_HANDLE;

        uint32_t m_graphicsQueueIndex;
        VkExtent2D m_swapchainExtent;
        std::vector<VkImageView> m_swapchainImageViews;
        std::vector<VkFramebuffer> m_frameBuffers;
        std::vector<VkCommandBuffer> m_commandBuffers;
        std::vector<VkSemaphore> m_imgAvailSemaphores;
        std::vector<VkSemaphore> m_renderFinishedSemaphores;
        std::vector<VkFence> m_fences;

        VkClearValue m_clearColor = { 0.0f, 0.2f, 0.4f, 1.0f };

        const VkFormat m_swapchainImgFormat = VK_FORMAT_B8G8R8A8_UNORM;
        const int MAX_FRAMES_IN_FLIGHT = 2;

        std::filesystem::path m_shaderLocation = "";

        bool m_isInit = false;
    };
}

#endif // ENGINE_RENDERER_DRIVER_HPP_
