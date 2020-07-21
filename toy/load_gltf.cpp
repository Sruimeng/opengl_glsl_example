#pragma once;

#include <iostream>
#include "scene.h"
#include "../include/tinygltf/tiny_gltf.h"
//#include 
namespace toy {


	//void processGLTFNode(
	//	Scene* scene,
	//	const tinygltf::Model& model,
	//	const tinygltf::Node& gltf_node,
	//	const Matrix4x4& parent_matrix
	//)
	//{
	//	const Matrix4x4 translation = gltf_node.translation.empty() ?
	//		Matrix4x4::identity() :
	//		Matrix4x4::translate(make_float3_from_double(
	//			gltf_node.translation[0],
	//			gltf_node.translation[1],
	//			gltf_node.translation[2]
	//		));

	//	const Matrix4x4 rotation = gltf_node.rotation.empty() ?
	//		Matrix4x4::identity() :
	//		Quaternion(
	//			static_cast<float>(gltf_node.rotation[3]),
	//			static_cast<float>(gltf_node.rotation[0]),
	//			static_cast<float>(gltf_node.rotation[1]),
	//			static_cast<float>(gltf_node.rotation[2])
	//		).rotationMatrix();

	//	const Matrix4x4 scale = gltf_node.scale.empty() ?
	//		Matrix4x4::identity() :
	//		Matrix4x4::scale(make_float3_from_double(
	//			gltf_node.scale[0],
	//			gltf_node.scale[1],
	//			gltf_node.scale[2]
	//		));

	//	std::vector<float> gltf_matrix;
	//	for (double x : gltf_node.matrix)
	//		gltf_matrix.push_back(static_cast<float>(x));
	//	const Matrix4x4 matrix = gltf_node.matrix.empty() ?
	//		Matrix4x4::identity() :
	//		Matrix4x4(reinterpret_cast<float*>(gltf_matrix.data())).transpose();

	//	Matrix4x4 node_xform = parent_matrix * matrix * translation * rotation * scale;

	//	/*if (gltf_node.camera != -1)
	//	{
	//		const auto& gltf_camera = model.cameras[gltf_node.camera];
	//		std::cerr << "Processing camera '" << gltf_camera.name << "'\n"
	//			<< "\ttype: " << gltf_camera.type << "\n";
	//		if (gltf_camera.type != "perspective")
	//		{
	//			std::cerr << "\tskipping non-perpective camera\n";
	//			return;
	//		}

	//		const float3 eye = make_float3(node_xform*make_float4_from_double(0.0f, 0.0f, 0.0f, 1.0f));
	//		const float3 up = make_float3(node_xform*make_float4_from_double(0.0f, 1.0f, 0.0f, 0.0f));
	//		const float  yfov = static_cast<float>(gltf_camera.perspective.yfov) * 180.0f / static_cast<float>(M_PI);

	//		std::cerr << "\teye   : " << eye.x << ", " << eye.y << ", " << eye.z << std::endl;
	//		std::cerr << "\tup    : " << up.x << ", " << up.y << ", " << up.z << std::endl;
	//		std::cerr << "\tfov   : " << yfov << std::endl;
	//		std::cerr << "\taspect: " << gltf_camera.perspective.aspectRatio << std::endl;

	//		Camera camera;
	//		camera.setFovY(yfov);
	//		camera.setAspectRatio(static_cast<float>(gltf_camera.perspective.aspectRatio));
	//		camera.setEye(eye);
	//		camera.setUp(up);
	//		scene.addCamera(camera);
	//	}*/
	//	if (gltf_node.mesh != -1)
	//	{
	//		const auto& gltf_mesh = model.meshes[gltf_node.mesh];
	//		std::cerr << "Processing glTF mesh: '" << gltf_mesh.name << "'\n";
	//		std::cerr << "\tNum mesh primitive groups: " << gltf_mesh.primitives.size() << std::endl;
	//		for (auto& gltf_primitive : gltf_mesh.primitives)
	//		{
	//			if (gltf_primitive.mode != TINYGLTF_MODE_TRIANGLES) // Ignore non-triangle meshes
	//			{
	//				std::cerr << "\tNon-triangle primitive: skipping\n";
	//				continue;
	//			}

	//			Mesh mesh;



	//			mesh.name = gltf_mesh.name;

	//			bufferViewFromGLTF(model, scene, gltf_primitive.indices, 0, &mesh);
	//			mesh.material_idx.push_back(gltf_primitive.material);
	//			mesh.transform = node_xform;
	//			mesh.num_triangles = mesh.trianglesArray.size();
	//			std::cerr << "\t\tNum triangles: " << mesh.num_triangles << std::endl;

	//			assert(gltf_primitive.attributes.find("POSITION") != gltf_primitive.attributes.end());
	//			const int32_t pos_accessor_idx = gltf_primitive.attributes.at("POSITION");
	//			bufferViewFromGLTF(model, scene, pos_accessor_idx, 1, &mesh);
	//			mesh.num_vertices = mesh.verticesArray.size();
	//			std::cerr << "\t\tNum vertices: " << mesh.num_vertices << std::endl;
	//			const auto& pos_gltf_accessor = model.accessors[pos_accessor_idx];
	//			mesh.object_aabb = Aabb(
	//				make_float3_from_double(
	//					pos_gltf_accessor.minValues[0],
	//					pos_gltf_accessor.minValues[1],
	//					pos_gltf_accessor.minValues[2]
	//				),
	//				make_float3_from_double(
	//					pos_gltf_accessor.maxValues[0],
	//					pos_gltf_accessor.maxValues[1],
	//					pos_gltf_accessor.maxValues[2]
	//				));
	//			mesh.world_aabb = mesh.object_aabb;
	//			mesh.world_aabb.transform(node_xform);
	//			mesh.bbox_min[0] = pos_gltf_accessor.minValues[0];
	//			mesh.bbox_min[1] = pos_gltf_accessor.minValues[1];
	//			mesh.bbox_min[2] = pos_gltf_accessor.minValues[2];
	//			mesh.bbox_max[0] = pos_gltf_accessor.maxValues[0];
	//			mesh.bbox_max[1] = pos_gltf_accessor.maxValues[1];
	//			mesh.bbox_max[2] = pos_gltf_accessor.maxValues[2];




	//			auto normal_accessor_iter = gltf_primitive.attributes.find("NORMAL");
	//			if (normal_accessor_iter != gltf_primitive.attributes.end())
	//			{
	//				std::cerr << "\t\tHas vertex normals: true\n";
	//				bufferViewFromGLTF(model, scene, normal_accessor_iter->second, 2, &mesh);
	//			}
	//			else
	//			{
	//				std::cerr << "\t\tHas vertex normals: false\n";
	//				bufferViewFromGLTF(model, scene, -1, 2, &mesh);
	//			}

	//			auto texcoord_accessor_iter = gltf_primitive.attributes.find("TEXCOORD_0");
	//			if (texcoord_accessor_iter != gltf_primitive.attributes.end())
	//			{
	//				std::cerr << "\t\tHas texcoords: true\n";
	//				bufferViewFromGLTF(model, scene, texcoord_accessor_iter->second, 3, &mesh);
	//			}
	//			else
	//			{
	//				std::cerr << "\t\tHas texcoords: false\n";
	//				bufferViewFromGLTF(model, scene, -1, 3, &mesh);
	//			}


	//			scene.push_back(mesh);
	//		}

	//	}
	//	else if (!gltf_node.children.empty())
	//	{
	//		for (int32_t child : gltf_node.children)
	//		{
	//			processGLTFNode(scene, model, model.nodes[child], node_xform);
	//		}
	//	}


	//}

	void loadGLTF(const std::string& filename, Scene& scene, const std::string& model_type) {
		tinygltf::Model model;
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		bool retur;
		if (model_type == "gltf") {
			retur = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
		}
		else if(model_type=="glb")
		{
			retur = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
		}
		if (!warn.empty())//打印警告
			std::cerr << "glTF WARNING: " << warn << std::endl;
		if (!retur)//打印错误
		{
			std::cerr << "Failed to load GLTF scene '" << filename << "': " << err << std::endl;
			throw err.c_str();
		}
		//添加数据
		for (const auto& gltf_buffer : model.buffers)
		{
			const uint64_t bufffer_size = gltf_buffer.data.size();
			std::cerr << "Processing glTF buffer '" << gltf_buffer.name << "'\n"
				<< "\tbyte size: " << bufffer_size << "\n"
				<< "\turi      : " << gltf_buffer.uri << std::endl;

			//scene.addBuffer(gltf_buffer.data.data());
		}
		//

	};
}
