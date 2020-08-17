#include "Shader.h"

#include "../support/glad/glad.h"
#include "GLFW/glfw3.h"
#include "../toy/scene.h"
#include <iostream>
#define GET_ARRAY_SIZE(array,length){length = (sizeof(array) / sizeof(array[0]));}
#define PI 3.1415926
namespace {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow* window)
	{
		//��esc�˳�
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void openglInit(int major, int minor) {
		//glfw��ʼ��
		glfwInit();
		//�������������ð汾��GLFW_CONTEXT_VERSION_MAJOR->���汾 GLFW_CONTEXT_VERSION_MINOR->С�汾
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		//����ʹ�ú���ģʽ
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}

	void create_sphere(int radius, int widthSegments, int heightSegments, toy::Mesh* mesh) {
		int ix, iy;

		int index = 0;
		std::vector<std::vector<int>> grid;
		float phiStart = 0;
		float phiLength = PI * 2;

		float thetaStart = 0;
		float thetaLength = PI;
		float thetaEnd = PI;
		for (iy = 0; iy <= heightSegments; iy++)
		{
			std::vector<int> verticesRow;
			int v = iy / (float)heightSegments;
			int uOffset = 0;

			if (iy == 0) {

				uOffset = 0.5 / widthSegments;

			}
			else if (iy == heightSegments) {

				uOffset = -0.5 / widthSegments;

			}

			for (ix = 0; ix <= widthSegments; ix++) {

				auto u = ix / (float)widthSegments;
				toy::float3 vertex;
				auto a = std::cos(phiStart + u * phiLength);
				auto b = std::sin(thetaStart + v * thetaLength);
				vertex.x = -radius * std::cos(phiStart + u * phiLength) * std::sin(thetaStart + v * thetaLength);
				vertex.y = radius * std::cos(thetaStart + v * thetaLength);
				vertex.z = radius * std::sin(phiStart + u * phiLength) * std::sin(thetaStart + v * thetaLength);
				mesh->verticesArray.push_back(vertex);

				toy::float3 normal;
				auto temp = uautil::normalize(vertex);
				normal.x = -temp.x;
				normal.y = -temp.y;
				normal.z = -temp.z;
				mesh->normalsArray.push_back(normal);
				verticesRow.push_back(index++);
			}
			grid.push_back(verticesRow);
		}
		// indices

		for (iy = 0; iy < heightSegments; iy++) {

			for (ix = 0; ix < widthSegments; ix++) {

				int a = grid[iy][ix + 1];
				int b = grid[iy][ix];
				int c = grid[iy + 1][ix];
				int d = grid[iy + 1][ix + 1];
				toy::int3 index1;
				index1.x = a;
				index1.y = b;
				index1.z = d;
				toy::int3 index2;
				index2.x = b;
				index2.y = c;
				index2.z = d;
				if (iy != 0 || thetaStart > 0) mesh->indicesArray.push_back(index1);
				if (iy != heightSegments - 1 || thetaEnd < PI) mesh->indicesArray.push_back(index2);

			}

		}
	};
}


int main()
{

	const std::string filename = "D:/project/atlas/models/";
	std::string gltfFilename = filename + "/199.glb";
	toy::Scene scene;
	toy::loadScene(gltfFilename, &scene);
	toy::Camera camera;

	////opengl 初始化
	openglInit(4, 3);

	//新建窗口
	GLFWwindow* window = glfwCreateWindow(1000, 800, "glsl example", NULL, NULL);
	//创建上下文
	glfwMakeContextCurrent(window);
	//glad初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//判断Windows状态
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//设置缩放
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	////�����ζ�������
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};
	////���������� ��ͨ��Ⱦ��ʽ
	//float vertices[] = {
	//	// ��һ��������
	//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
	//	0.5f, -0.5f, 0.0f,  // ���½�
	//	-0.5f, 0.5f, 0.0f,  // ���Ͻ�
	//	// �ڶ���������
	//	0.5f, -0.5f, 0.0f,  // ���½�
	//	-0.5f, -0.5f, 0.0f, // ���½�
	//	-0.5f, 0.5f, 0.0f   // ���Ͻ�
	//};

	unsigned int indices[] = { // ע��������0��ʼ! 
		0, 1, 2 // ��һ��������
	};
	float vertices[] = {
		0.0f, 0.7f, 0.0f,   // ���Ͻ�
		-0.7f, -0.7f, 0.0f,  // ���½�
		0.7f, -0.7f, 0.0f, // ���½�
	};
	float colors[] = {
		1.0f, 0.0f, 0.0f,   // ���Ͻ�
		0.0f,0.0f, 1.0f,  // ���½�
		0.0f, 1.0f, 0.0f,  // ���½�
	};

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	int verticesLength;
	int	indicesLength;
	GET_ARRAY_SIZE(vertices, verticesLength);
	GET_ARRAY_SIZE(indices, indicesLength);

	// screen quad VAO
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));



	//����vbo
	unsigned int VBO[2];
	glGenBuffers(2, VBO);
	//�½�vao
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//��VAO
	glBindVertexArray(VAO);
	//��vbo ע��˳��
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	//������


	//����ebo����������
	{
		//����ebo 
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	//shader的文件导入
	Shader fsShader("../../../glsl1/shader.fs");
	Shader vsShader("../../../glsl1/shader.vs");
	ShaderProgram shaderProgram(vsShader.code, fsShader.code);
	shaderProgram.use();

	Shader ffsShader("../../../glsl1/screen.fs");
	Shader fvsShader("../../../glsl1/screen.vs");
	ShaderProgram fshaderProgram(fvsShader.code, ffsShader.code);
	fshaderProgram.use();
	//glUniform1i(glGetUniformLocation(fshaderProgram.ID, "uv"), 1);
	fshaderProgram.setInt("screenTexture", 0);
	// framebuffer configuration
	// -------------------------
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1024, 1024); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
																								  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//渲染
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// render
		// ------
		// bind to framebuffer and draw scene as we normally would to color texture 
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

								 // make sure we clear the framebuffer's content
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due

		fshaderProgram.use();
		// clear all relevant buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(quadVAO);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//交换缓存
		glfwSwapBuffers(window);
		//�¼���ѯ
		glfwPollEvents();
	}
	//关闭glfw
	glfwTerminate();
	return 0;
}