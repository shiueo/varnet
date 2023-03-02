#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept>

#include "vulkan_createinstance.h"
#include "vulkan_validation_layers.h"
#include "vulkan_physical_device.h"
#include "vulkan_create_logical_device.h"


#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

class VARNET {
public:
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanUp();
	}
private:
	GLFWwindow* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;
	VkSurfaceKHR surface;

	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "VARNET", nullptr, nullptr);
		std::cout << "glfw_window created" << std::endl;
	}
	void initVulkan() {
		createInstance(instance, enableValidationLayers);
		setupDebugMessenger(instance, debugMessenger, enableValidationLayers);
		pickPhysicalDevice(instance, physicalDevice);
		createLogicalDevice(device, physicalDevice, graphicsQueue, enableValidationLayers);
	}
	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}
	void cleanUp() {
		vkDestroyDevice(device, nullptr);
		std::cout << "vulkan_device destroyed" << std::endl;
		if (enableValidationLayers) {
			DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
		}
		vkDestroyInstance(instance, nullptr);
		std::cout << "vulkan_instance destroyed" << std::endl;
		glfwDestroyWindow(window);
		std::cout << "glfw_window destroyed" << std::endl;
		glfwTerminate();
	}
};

int main() {
	VARNET VARNET_APPLICATION{};

	try {
		VARNET_APPLICATION.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}