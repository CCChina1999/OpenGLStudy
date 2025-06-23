#include <iostream>	
/*
��ȷ�����ڰ���GLFW��ͷ�ļ�֮ǰ������GLAD��ͷ�ļ���GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD��
*/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/**
 * @brief ������ڵ㣬��ʼ��OpenGL������ִ����ѭ����
 * 
 * @param argc �����в�������
 * @param argv �����в�������
 * @return int �����˳���
 */
int main(int argc, char** argv) {
	std::cout << "Hello, OpenGL!" << std::endl;
	// ��ʼ��OpenGL������
	// ���ô��ڡ���ɫ������������
	// ��ѭ��
	// ������Դ���˳�
	
	glfwInit();
	// ����OpenGL�汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// ����OpenGL�汾Ϊ3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ����OpenGL����ģʽ
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


	// ��ʼ��GLAD�Թ���OpenGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// �����ӿ�
	glViewport(0, 0, 800, 600);

	// ��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����ɫ�����õ���Ļ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//ִ�������Ļ��������ɫ����
		glClear(GL_COLOR_BUFFER_BIT);

		//����
		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ������Դ
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