#pragma once
#include <iostream>
#include <vector>

#include "vector_type.h"
#include "matrix.h"
namespace uautil {

	struct Mesh
	{
		std::vector<int3> trianglesArray; //三角形下标数组
		std::vector<float3> verticesArray;	//点的数组
		std::vector<float3> normalsArray;  //法线
		std::vector<float2> texcoordsArray; //UV
		std::vector<float> positions;
		std::vector<unsigned int> indices;
		std::string                       name;

		//Matrix4x4							mat;//模型的矩阵

		int32_t             num_triangles;  // Number of triangles
		int32_t             num_vertices;   // Number of triangle vertices
		float               bbox_min[3];    // Scene BBox
		float               bbox_max[3];    //


	};

	class Scene
	{
	public:
		std::vector<unsigned char>			m_data;
		std::vector<Mesh>   m_meshes;
		float               bbox_min[3];    // Scene BBox
		float               bbox_max[3];    //
		std::size_t				 m_num_meshes;
	private:

	};

	void loadScene(const std::string& filename, Scene* scene);
}