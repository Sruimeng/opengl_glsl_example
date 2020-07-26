#pragma once


#include <vector>
#include <iostream>
#include "vector.h"
#include "aabb.h"
#include "matrix.h"
#include "camera.h"
namespace toy {

	struct Mesh
	{
		std::vector<int3>	indicesArray; //三角形下标数组
		std::vector<float3> verticesArray;	//三角形顶点数组
		std::vector<float3> normalsArray;  //法线数组
		std::vector<float2> texcoordsArray; //UV0通道数组

		std::string                       name;
		Matrix4x4 transform;				//矩阵
		std::vector<int32_t>              material_idx;//使用的材质iD
		int32_t             num_triangles;  // Number of triangles
		int32_t             num_vertices;   // Number of triangle vertices
		Aabb                              object_aabb;
		Aabb                              world_aabb;
	};

	class Scene
	{
	public:
		void addCamera(const Camera& camera) { m_cameras.push_back(camera); };
		void addMesh(const Mesh& mesh) {
			m_meshes.push_back(mesh);
			m_num_meshes++;
		};
		void addBuffer(const std::vector<unsigned char> data) {
			m_data = data;
		};
		
	private:
		std::vector<unsigned char>			m_data;
		std::vector<Mesh>   m_meshes;
		std::vector<Camera> m_cameras;
		std::size_t				 m_num_meshes;
		Aabb                          m_scene_aabb;

	};
	void loadScene(const std::string& filename, Scene* scene);
	void loadGLTF(const std::string& filename, Scene& scene, const std::string& model_type);
	
}


