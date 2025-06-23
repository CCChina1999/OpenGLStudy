#include <iostream>	
/*
请确认是在包含GLFW的头文件之前包含了GLAD的头文件。GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD。
*/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/**
 * @brief 程序入口点，初始化OpenGL环境并执行主循环。
 * 
 * @param argc 命令行参数数量
 * @param argv 命令行参数数组
 * @return int 程序退出码
 */
int main(int argc, char** argv) {
	std::cout << "Hello, OpenGL!" << std::endl;
	// 初始化OpenGL上下文
	// 设置窗口、着色器、缓冲区等
	// 主循环
	// 清理资源并退出
	
	glfwInit();
	// 设置OpenGL版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// 设置OpenGL版本为3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 设置OpenGL核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1; 
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// 初始化GLAD以管理OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// 设置视口
	glViewport(0, 0, 800, 600);

	// 主循环
	while (!glfwWindowShouldClose(window))
	{
		//清空颜色后设置的屏幕颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//执行清空屏幕缓冲区颜色操作
		glClear(GL_COLOR_BUFFER_BIT);

		//输入
		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 清理资源
	glfwTerminate();
	return 0;

	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}