#include <iostream>	
/*
请确认是在包含GLFW的头文件之前包含了GLAD的头文件。GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD。
*/
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
								"layout (location = 0) in vec3 aPos;\n"
								"void main()\n"
								"{\n"
								"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
									"}\0";

const char* fragmentShaderSource_1 = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
									"}\0";

const char* fragmentShaderSource_2 = "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
									"}\0";

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

	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
	};

	float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	
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

	//配置顶点着色器、片段着色器
	int success;
	char infoLog[512];

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader, fragmentShader_1, fragmentShader_2;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::memset(infoLog, 0, 512);
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_1, 1, &fragmentShaderSource_1, NULL);
	glCompileShader(fragmentShader_1);
	glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::memset(infoLog, 0, 512);
		glGetShaderInfoLog(fragmentShader_1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragmentShader_2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_2, 1, &fragmentShaderSource_2, NULL);
	glCompileShader(fragmentShader_2);
	glGetShaderiv(fragmentShader_2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::memset(infoLog, 0, 512);
		glGetShaderInfoLog(fragmentShader_2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//将顶点着色器、片段着色器绑定到着色器程序并启用着色器程序
	unsigned int shaderProgram, shaderProgram_1, shaderProgram_2;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	shaderProgram_1 = glCreateProgram();
	glAttachShader(shaderProgram_1, vertexShader);
	glAttachShader(shaderProgram_1, fragmentShader_1);
	glLinkProgram(shaderProgram_1);

	shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, vertexShader);
	glAttachShader(shaderProgram_2, fragmentShader_2);
	glLinkProgram(shaderProgram_2);







	unsigned int VAO,VA01,VA02;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VA01);
	glGenVertexArrays(1, &VA02);

	unsigned int VBO,VB01,VBO2;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VB01);
	glGenBuffers(1, &VBO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//1、绑定VAO -- VAO类似一个配置记录表，可以把VBO的操作都记录起来，渲染时，直接绑定VAO，就类似于绑定了顶点着色器
	glBindVertexArray(VAO);
	//2、绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//3、绑定EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//3、设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//3.1、启用顶点属性位置为0位置开始的的顶点着色器
	glEnableVertexAttribArray(0);

	//解除绑定VBO  ---  VAO不会因为解除绑定VBO后，就不记录VBO的操作了，主要原因应该是VAO没记录VBO的glBindBuffer操作
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//解除绑定EBO  ---  VAO会记录EBO的glBindBuffer操作，也会记录解绑定的操作，所以只能在确认不使用EBO后，VAO才能解除绑定
	//还看到一个原因，是因为EBO会存储在VAO中
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//解除绑定VAO
	glBindVertexArray(0);

	glBindVertexArray(VA01);
	glBindBuffer(GL_ARRAY_BUFFER, VB01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//3.1、启用顶点属性位置为0位置开始的的顶点着色器
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VA02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//3.1、启用顶点属性位置为0位置开始的的顶点着色器
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// 主循环
	while (!glfwWindowShouldClose(window))
	{
		//清空颜色后设置的屏幕颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//执行清空屏幕缓冲区颜色操作
		glClear(GL_COLOR_BUFFER_BIT);
		//输入
		processInput(window);

		//绑定数据并显示

		//使用着色器程序
		//glUseProgram(shaderProgram);
		//绑定VAO
		//glBindVertexArray(VAO);
		glUseProgram(shaderProgram_1);
		glBindVertexArray(VA01);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(0);

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VA02);
		//绘制物体
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//绘制线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glUseProgram(0);
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