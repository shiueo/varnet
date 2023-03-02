#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "vulkan_var.h"
#include "vulkan_validation_layers.h"

void createInstance(VkInstance& instance, bool enableValidationLayers);