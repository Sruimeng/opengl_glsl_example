#pragma once


#include <vector>
#include "optix/optixu/optixu_aabb_namespace.h"
#include "optix/optixu/optixu_math_namespace.h"
using namespace optix;
namespace uautil {
	struct MeshBound
	{
		float3 g_min;//glb����ʱ����Сֵ
		float3 g_max;//glb����ʱ�����ֵ
		float m_min;//ģ�ͼ��غ����ݵ���Сֵ
		float m_max;//ģ�ͼ��غ����ݵ����ֵ
	};

	struct Mesh
	{
		std::vector<int3> trianglesArray; //�������±�����
		std::vector<float3> verticesArray;	//�����ε������
		std::vector<float3> normalsArray;  //������������
		std::vector<float2> texcoordsArray; //UV0��������

		std::string                       name;
		Matrix4x4 transform;
		std::vector<int32_t>              material_idx;
		int32_t             num_triangles;  // Number of triangles
		int32_t             num_vertices;   // Number of triangle vertices
		float               bbox_min[3];    // Scene BBox
		float               bbox_max[3];    //
		float extra_samples_offset{};
		Aabb                              object_aabb;
		Aabb                              world_aabb;

		MeshBound        meshBound[3];
	};

	class Scene
	{
	public:
		std::vector<unsigned char>			m_data;
		std::vector<Mesh>   m_meshes;
		float               bbox_min[3];    // Scene BBox
		float               bbox_max[3];    //
		std::size_t				 m_num_meshes;
		Aabb                          m_scene_aabb;
		private:
	
	};
	
	void loadScene(const std::string& filename, Scene* scene);
}

//namespace uautil {
//	
//	struct MeshBound
//	{
//		float3 g_min;//glb����ʱ����Сֵ
//		float3 g_max;//glb����ʱ�����ֵ
//		float m_min;//ģ�ͼ��غ����ݵ���Сֵ
//		float m_max;//ģ�ͼ��غ����ݵ����ֵ
//	};
//
//	struct Mesh
//	{
//		std::vector<int3> trianglesArray; //�������±�����
//		std::vector<float3> verticesArray;	//�����ε������
//		std::vector<float3> normalsArray;  //������������
//		std::vector<float2> texcoordsArray; //UV��������
//

//		int32_t             num_triangles;  // Number of triangles
//		int32_t             num_vertices;   // Number of triangle vertices
//		float               bbox_min[3];    // Scene BBox
//		float               bbox_max[3];    //
//		float extra_samples_offset{};
//		Aabb                              object_aabb;
//		Aabb                              world_aabb;
//
//		meshBound        meshBound[3];
//	};
//
//	class Scene
//	{
//	public:
//		std::vector<unsigned char>			m_data;
//		std::vector<Mesh>   m_meshes;
//		float               bbox_min[3];    // Scene BBox
//		float               bbox_max[3];    //
//		std::size_t				 m_num_meshes;
//		Aabb                          m_scene_aabb;
//	private:
//
//	};
//
//	void loadScene(const std::string& filename, Scene* scene);
//}

