#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};


VkResult CreateDebugUtilsMessengerEXT(VkInstance& instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
bool checkValidationLayerSupport();
void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
std::vector<const char*> getRequiredExtensions(bool enableValidationLayers);


void setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger, bool enableValidationLayers);
void DestroyDebugUtilsMessengerEXT(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger, const VkAllocationCallbacks* pAllocator);
