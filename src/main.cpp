#include <vulkan/vulkan.h>

#include <cstdlib>
#include <iostream>
#include <vector>

int main()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Flux";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "Flux";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance = VK_NULL_HANDLE;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to create Vulkan instance: " << result << '\n';
        return EXIT_FAILURE;
    }

    uint32_t deviceCount = 0;

    result = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (result != VK_SUCCESS || deviceCount == 0)
    {
        std::cerr << "No Vulkan physical devices found.\n";
        vkDestroyInstance(instance, nullptr);
        return EXIT_FAILURE;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);

    result = vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to enumerate Vulkan devices.\n";
        vkDestroyInstance(instance, nullptr);
        return EXIT_FAILURE;
    }

    std::cout << "Flux initialized!\n";
    std::cout << "Available Vulkan devices:\n";

    for (const auto device : devices)
    {
        VkPhysicalDeviceProperties properties{};

        vkGetPhysicalDeviceProperties(device, &properties);

        std::cout << " - " << properties.deviceName << '\n';
        std::cout << "   Vulkan API: "
                  << VK_VERSION_MAJOR(properties.apiVersion)
                  << "."
                  << VK_VERSION_MINOR(properties.apiVersion)
                  << "."
                  << VK_VERSION_PATCH(properties.apiVersion)
                  << '\n';
    }

    vkDestroyInstance(instance, nullptr);

    return EXIT_SUCCESS;
}
