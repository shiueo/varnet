#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include "vulkan_var.h"

void createLogicalDevice(VkDevice& device, VkPhysicalDevice& physicalDevice, VkQueue& graphicsQueue, bool enableValidationLayers);