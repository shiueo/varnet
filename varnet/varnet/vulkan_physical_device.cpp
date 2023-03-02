#include "vulkan_physical_device.h"


bool isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.isComplete();
}

int rateDeviceSuitability(VkPhysicalDevice device, VkPhysicalDeviceProperties deviceProperties, VkPhysicalDeviceFeatures deviceFeatures) {
    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader) {
        return 0;
    }

    std::cout << deviceProperties.deviceName << " = " << score << std::endl;

    return score;
}

void pickPhysicalDevice(VkInstance& instance, VkPhysicalDevice& physicalDevice) {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    for (const auto& device : devices) {
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        int score = rateDeviceSuitability(device, deviceProperties, deviceFeatures);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        physicalDevice = candidates.rbegin()->second;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
        std::cout << deviceProperties.deviceName << " selected" << std::endl;
    }
    else {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}