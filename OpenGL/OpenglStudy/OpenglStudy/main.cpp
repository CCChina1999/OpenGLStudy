#include <iostream>	
/*
��ȷ�����ڰ���GLFW��ͷ�ļ�֮ǰ������GLAD��ͷ�ļ���GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD��
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
 * @brief ������ڵ㣬��ʼ��OpenGL������ִ����ѭ����
 * 
 * @param argc �����в�������
 * @param argv �����в�������
 * @return int �����˳���
 */
int main(int argc, char** argv) {
	std::cout << "Hello, OpenGL!" << std::endl;

	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	0.5f, -0.5f, 0.0f,  // ���½�
	-0.5f, -0.5f, 0.0f, // ���½�
	-0.5f, 0.5f, 0.0f   // ���Ͻ�
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
		// ע��������0��ʼ! 
		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
		// �����������±��������ϳɾ���

		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
	
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

	//���ö�����ɫ����Ƭ����ɫ��
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
	//��������ɫ����Ƭ����ɫ���󶨵���ɫ������������ɫ������
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

	//1����VAO -- VAO����һ�����ü�¼�����԰�VBO�Ĳ�������¼��������Ⱦʱ��ֱ�Ӱ�VAO���������ڰ��˶�����ɫ��
	glBindVertexArray(VAO);
	//2����VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//3����EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//3�����ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//3.1�����ö�������λ��Ϊ0λ�ÿ�ʼ�ĵĶ�����ɫ��
	glEnableVertexAttribArray(0);

	//�����VBO  ---  VAO������Ϊ�����VBO�󣬾Ͳ���¼VBO�Ĳ����ˣ���Ҫԭ��Ӧ����VAOû��¼VBO��glBindBuffer����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//�����EBO  ---  VAO���¼EBO��glBindBuffer������Ҳ���¼��󶨵Ĳ���������ֻ����ȷ�ϲ�ʹ��EBO��VAO���ܽ����
	//������һ��ԭ������ΪEBO��洢��VAO��
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//�����VAO
	glBindVertexArray(0);

	glBindVertexArray(VA01);
	glBindBuffer(GL_ARRAY_BUFFER, VB01);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//3.1�����ö�������λ��Ϊ0λ�ÿ�ʼ�ĵĶ�����ɫ��
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VA02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//3.1�����ö�������λ��Ϊ0λ�ÿ�ʼ�ĵĶ�����ɫ��
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// ��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����ɫ�����õ���Ļ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//ִ�������Ļ��������ɫ����
		glClear(GL_COLOR_BUFFER_BIT);
		//����
		processInput(window);

		//�����ݲ���ʾ

		//ʹ����ɫ������
		//glUseProgram(shaderProgram);
		//��VAO
		//glBindVertexArray(VAO);
		glUseProgram(shaderProgram_1);
		glBindVertexArray(VA01);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(0);

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VA02);
		//��������
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//�����߿�ģʽ
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glUseProgram(0);
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