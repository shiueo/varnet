#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include "vulkan_validation_layers.h"

void createInstance(VkInstance& instance, bool enableValidationLayers);