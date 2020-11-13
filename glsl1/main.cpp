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

	void create_plane(
		toy::Mesh* mesh,
		const int32_t u_dir, const int32_t v_dir,
		const int32_t width, const int32_t height, const int32_t depth,
		const int32_t grid_x, const int32_t grid_y, const int32_t plane_idx
	) {

		const int32_t segment_width = width / grid_x;
		const int32_t segment_height = height / grid_y;

		const int32_t half_width = width / 2;
		const int32_t half_height = height / 2;
		const int32_t half_depth = depth / 2;

		const int32_t length_x = grid_x + 1;
		const int32_t length_y = grid_y + 1;

		int32_t vertex_counter = 0;

		int32_t number_vertces = 0;
		for (size_t i = 0; i < length_y; i++)
		{
			const int32_t y = i * segment_height - half_height;
			for (size_t j = 0; j < length_x; j++)
			{
				const int32_t x = j * segment_width - half_width;

				toy::float3 t_vector;
				switch (plane_idx)
				{
				case 0:
					t_vector = toy::make_float3(
						half_depth,
						y * v_dir,
						x * u_dir
					);
					break;
				case 1:
					t_vector = toy::make_float3(
						x * u_dir,
						half_depth,
						y * v_dir
					);
					break;
				case 2:
					t_vector = toy::make_float3(
						x * u_dir,
						y * v_dir,
						half_depth
					);
					break;
				default:
					break;
				}
				/*Matrix4x4 t_m = Quaternion(
					static_cast<float>(0.924),
					static_cast<float>(0),
					static_cast<float>(0.383),
					static_cast<float>(0)
				).rotationMatrix();
				t_vector = make_float3(t_m * make_float4(t_vector, 1.0));*/

				mesh->verticesArray.push_back(t_vector);
				toy::float3 t_normal;
				switch (plane_idx)
				{
				case 2:
					t_normal = toy::make_float3(
						depth > 0 ? -1 : 1,
						0,
						0
					);
					break;
				case 1:
					t_normal = toy::make_float3(
						0,
						depth > 0 ? -1 : 1,
						0
					);
					break;
				case 0:
					t_normal = toy::make_float3(
						0,
						0,
						depth > 0 ? -1 : 1
					);
					break;
				default:
					break;
				}
				mesh->normalsArray.push_back(t_normal);
				vertex_counter += 1;
			}
		}
		// indices

			// 1. you need three indices to draw a single face
			// 2. a single segment consists of two faces
			// 3. so we need to generate six (2*3) indices per segment

		for (size_t i = 0; i < grid_y; i++) {

			for (size_t j = 0; j < grid_x; j++) {

				const int32_t a = number_vertces + j + length_x * i;
				const int32_t b = number_vertces + j + length_x * (i + 1);
				const int32_t c = number_vertces + (j + 1) + length_x * (i + 1);
				const int32_t d = number_vertces + (j + 1) + length_x * i;

				// faces

				mesh->indicesArray.push_back(toy::make_int3(a, b, d));
				mesh->indicesArray.push_back(toy::make_int3(b, c, d));

			}

		}

	}
	void create_box(
		const int32_t width, const int32_t height, const int32_t depth,
		const int32_t widthSegments, const int32_t heightSegments, const int32_t depthSegments,
		toy::Mesh* mesh
	) {
		int32_t width_segments = std::floor(widthSegments) || 1;
		int32_t height_segments = std::floor(heightSegments) || 1;
		int32_t depth_segments = std::floor(depthSegments) || 1;
		create_plane(mesh, -1, -1, depth, height, width, depthSegments, heightSegments, 0); // px
		create_plane(mesh, 1, -1, depth, height, -width, depthSegments, heightSegments, 0); // nx
		create_plane(mesh, 1, 1, width, depth, height, widthSegments, depthSegments, 1); // py
		create_plane(mesh, 1, -1, width, depth, -height, widthSegments, depthSegments, 1); // ny
		create_plane(mesh, 1, -1, width, height, depth, widthSegments, heightSegments, 2); // pz
		create_plane(mesh, -1, -1, width, height, -depth, widthSegments, heightSegments, 2); // nz
		mesh->transform = mesh->transform.identity();
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
			auto v = iy / (float)heightSegments;
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
				auto temp = toy::normalize(vertex);
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
	//toy::loadScene(gltfFilename, &scene);
	toy::Camera camera;
	toy::Mesh mesh;
	//create_sphere(1, 128, 128, &mesh);
	create_box(2, 2, 2, 5, 5, 5, &mesh);
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

	//unsigned int indices[] = { // ע��������0��ʼ! 
	//	0, 1, 2 // ��һ��������
	//};
	std::vector<float> vertices;
	std::vector<int> indices;
	for (size_t i = 0; i < mesh.verticesArray.size(); i++)
	{
		vertices.push_back(mesh.verticesArray[i].x/2);
		vertices.push_back(mesh.verticesArray[i].y/2);
		vertices.push_back(mesh.verticesArray[i].z/2);
	}
	for (size_t i = 0; i < mesh.indicesArray.size(); i++)
	{
		indices.push_back(mesh.indicesArray[i].x);
		indices.push_back(mesh.indicesArray[i].y);
		indices.push_back(mesh.indicesArray[i].z);
	}

	//float vertices[] = {
	//	0.0f, 0.7f, 0.0f,   // ���Ͻ�
	//	-0.7f, -0.7f, 0.0f,  // ���½�
	//	0.7f, -0.7f, 0.0f, // ���½�
	//};
	//float colors[] = {
	//	1.0f, 0.0f, 0.0f,   // ���Ͻ�
	//	0.0f,0.0f, 1.0f,  // ���½�
	//	0.0f, 1.0f, 0.0f,  // ���½�
	//};

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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//������


	//����ebo����������
	{
		//����ebo 
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//渲染
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// render
		// ------
		// bind to framebuffer and draw scene as we normally would to color texture 
		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

								 // make sure we clear the framebuffer's content
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0,600);
		glBindVertexArray(0);

		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due

		//fshaderProgram.use();
		//// clear all relevant buffers
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		//glClear(GL_COLOR_BUFFER_BIT);
		//glBindVertexArray(quadVAO);
		//glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//交换缓存
		glfwSwapBuffers(window);
		//�¼���ѯ
		glfwPollEvents();
	}
	//关闭glfw
	glfwTerminate();
	return 0;
}