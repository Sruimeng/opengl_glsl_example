#pragma once;
#include "scene.h"
namespace toy {
	void loadScene(const std::string& filename, Scene* scene) {
		const std::string model_type = filename.substr(filename.find_last_of('.') + 1);
		if (model_type == "glb" || model_type == "gltf") {
			void loadGLTF(const std::string & filename, Scene & scene, const std::string & model_type);
		}

	};
}

//
//
//
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
//#include "optix/optixu/optixu_matrix_namespace.h"
//#include "Quaternion.h"
//#include "scene.h"
//// Define these only in *one* .cc file.
//#define TINYGLTF_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
//#include "include/tinygltf/tiny_gltf.h"
//namespace uautil {
//	namespace {
//		float makeFinalNumber(float x, float max, float min) {
//			if (min+max>0) {
//				return x  * (max - min) + min;
//			}
//			else if (max+min == 0) {
//				if (x < 0) {
//					return -x ;
//				}
//				else
//				{
//					return x ;
//				}
//				
//			}
//			else
//			{
//				if (max > 0) {
//					return (x ) * (max - min) + min;
//				}
//				else if(max<0)
//				{
//					return (x ) * min - max;
//				}
//				else
//				{
//					return (x ) * (max - min);
//				}
//				
//			}
//			
//		}
//
//		float normalizeNumber(float num, float max, float min, float box_max, float box_min) {
//			if ((max + min) > 0){
//				auto temp = (max - min) / (box_max - box_min);
//				auto flag = max - temp;
//				return (num - flag) / temp;
//			}
//		}
//
//		float makeMeshMin(float x, float y, float z,float m) {
//			return std::fmaxf(std::fmaxf(x,z),std::fmaxf(y,m));
//		}
//
//		float makeMeshMax(float x, float y, float z, float m) {
//			return std::fminf(std::fminf(x, z), std::fminf(y, m));
//		}
//
//		float makeMeshFloat2Min(float x, float y,  float m) {
//			return std::fminf(x, std::fminf(y, m));
//		}
//
//		float makeMeshFloat2Max(float x, float y,  float m) {
//			return std::fmaxf(x, std::fmaxf(y, m));
//		}
//
//		float3 make_float3_from_double(double x, double y, double z)
//		{
//			return make_float3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
//		}
//
//
//		float4 make_float4_from_double(double x, double y, double z, double w)
//		{
//			return make_float4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w));
//		}
//
//		union Convert
//		{
//			unsigned char byte[4];
//			float real;
//		};
//
//		float makeRealFolat(unsigned char x, unsigned char y, unsigned char z, unsigned char w) {
//			Convert convert;
//			convert.byte[0] = x;
//			convert.byte[1] = y;
//			convert.byte[2] = z;
//			convert.byte[3] = w;
//			return convert.real;
//		}
//	}
//
//	void bufferViewFromGLTF(const tinygltf::Model& model, Scene* scene, const int32_t accessor_idx, const int32_t type, Mesh* mesh)
//	{
//		if (accessor_idx == -1)
//			std::cerr << "glTF accessor_idx is -1;" << "'\n";
//
//		const auto& gltf_accessor = model.accessors[accessor_idx];
//		const auto& gltf_buffer_view = model.bufferViews[gltf_accessor.bufferView];
//
//		const int32_t elmt_byte_size =
//			gltf_accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT ? 2 :
//			gltf_accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT ? 4 :
//			gltf_accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT ? 4 :
//			0;
//		if (!elmt_byte_size)
//			std::cerr << "gltf accessor component type not supported;" << "'\n";
//		if (type != 0) {//������������ζ���
//			if (gltf_accessor.minValues.size() != 0) {
//				if (type == 3) {
//					mesh->meshBound[type - 1].g_min.x = gltf_accessor.minValues[0];
//					mesh->meshBound[type - 1].g_min.y = gltf_accessor.minValues[1];
//						
//					mesh->meshBound[type - 1].g_max.x = gltf_accessor.maxValues[0];
//					mesh->meshBound[type - 1].g_max.y = gltf_accessor.maxValues[1];
//				}
//				else
//				{
//					mesh->meshBound[type - 1].g_min = make_float3_from_double(gltf_accessor.minValues[0],
//						gltf_accessor.minValues[1],
//						gltf_accessor.minValues[2]);
//					mesh->meshBound[type - 1].g_max = make_float3_from_double(gltf_accessor.maxValues[0],
//						gltf_accessor.maxValues[1],
//						gltf_accessor.maxValues[2]);
//				}
//				
//			}
//			else
//			{
//				mesh->meshBound[type - 1].g_max = make_float3(1.0, 1.0, 1.0);
//				if (type == 3) {
//					mesh->meshBound[type - 1].g_min = make_float3(0.0, 0.0, 0.0);
//				}
//				else
//				{
//					mesh->meshBound[type - 1].g_min = make_float3(-1.0, -1.0, -1.0);
//				}
//			}
//			
//			mesh->meshBound[type - 1].m_min = 0;
//			mesh->meshBound[type - 1].m_max = 0;
//		}
//		std::vector<unsigned char>::const_iterator begin;
//		std::vector<unsigned char>::const_iterator end;
//
//		if (gltf_buffer_view.byteOffset != 0) {
//			begin = scene->m_data.begin() + gltf_buffer_view.byteOffset;
//			end = scene->m_data.begin() + gltf_buffer_view.byteOffset + gltf_buffer_view.byteLength;
//		}
//		else
//		{
//			begin = scene->m_data.begin();
//			end = scene->m_data.begin() + gltf_buffer_view.byteLength;
//		}
//		std::vector<unsigned char> index(begin, end);
//		int byte = elmt_byte_size * 3;
//		auto length = index.size() / byte;
//		switch (type)
//		{
//		case 0:
//			
//			for (size_t i = 0; i < length; i++)
//			{
//				int3 inde;
//				inde.x = index[byte * i]+ index[byte * i+1]*256;
//				inde.y = index[byte * i + elmt_byte_size]+ index[byte * i + elmt_byte_size + 1] * 256;
//				inde.z = index[byte * i + elmt_byte_size * 2]+ index[byte * i + elmt_byte_size *2 + 1] * 256;;
//				
//				mesh->trianglesArray.push_back(inde);
//			}
//			break;
//		case 1:
//			
//			for (size_t i = 0; i < length; i++)
//			{
//				float3 point;
//				//point.x = index[byte * i];
//				//point.y = index[byte * i + elmt_byte_size];
//				//point.z = index[byte * i + elmt_byte_size * 2];
//				point.x = makeRealFolat(index[byte * i], index[byte * i + 1], index[byte * i + 2] , index[byte * i + 3]);
//
//				point.y = makeRealFolat(index[byte * i+ elmt_byte_size], index[byte * i + elmt_byte_size + 1], index[byte * i + elmt_byte_size + 2], index[byte * i + elmt_byte_size + 3]);
//
//				point.z = makeRealFolat(index[byte * i + elmt_byte_size * 2], index[byte * i + 1+ elmt_byte_size * 2], index[byte * i + 2 + elmt_byte_size * 2], index[byte * i + 3+ elmt_byte_size * 2]);
//
//
//				/*point.x = makeFinalNumber(static_cast<float>(index[byte * i]),mesh->meshBound[type-1].g_max.x, mesh->meshBound[type - 1].g_min.x);
//				point.y = makeFinalNumber(static_cast<float>(index[byte * i+ elmt_byte_size]), mesh->meshBound[type - 1].g_max.y, mesh->meshBound[type - 1].g_min.y);
//				point.z = makeFinalNumber(static_cast<float>(index[byte * i + elmt_byte_size * 2]), mesh->meshBound[type - 1].g_max.z, mesh->meshBound[type - 1].g_min.z);
//				mesh->meshBound[type - 1].m_min = makeMeshMin(mesh->meshBound[type - 1].m_min, point.x, point.y, point.z);
//				mesh->meshBound[type - 1].m_max = makeMeshMax(mesh->meshBound[type - 1].m_max, point.x, point.y, point.z);*/
//				mesh->verticesArray.push_back(point);
//			}
//			break;
//		case 2:
//			for (size_t i = 0; i < length; i++)
//			{
//				float3 normal;
//				normal.x = makeRealFolat(index[byte * i], index[byte * i + 1], index[byte * i + 2], index[byte * i + 3]);
//
//				normal.y = makeRealFolat(index[byte * i + elmt_byte_size], index[byte * i + elmt_byte_size + 1], index[byte * i + elmt_byte_size + 2], index[byte * i + elmt_byte_size + 3]);
//
//				normal.z = makeRealFolat(index[byte * i + elmt_byte_size * 2], index[byte * i + 1 + elmt_byte_size * 2], index[byte * i + 2 + elmt_byte_size * 2], index[byte * i + 3 + elmt_byte_size * 2]);
//				mesh->meshBound[type - 1].m_min = makeMeshMin(mesh->meshBound[type - 1].m_min, normal.x, normal.y, normal.z);
//				mesh->meshBound[type - 1].m_max = makeMeshMax(mesh->meshBound[type - 1].m_max, normal.x, normal.y, normal.z);
//				mesh->normalsArray.push_back(normal);
//			}
//			std::cout << "mesh normal max:" << mesh->meshBound[type - 1].m_max << std::endl;
//			std::cout << "mesh normal min:" << mesh->meshBound[type - 1].m_min << std::endl;
//			/*for (size_t i = 0; i < mesh->normalsArray.size(); i++)
//			{
//				mesh->normalsArray[i].x = mesh->normalsArray[i].x / 2.56;
//				mesh->normalsArray[i].y = mesh->normalsArray[i].y / 2.56;
//				mesh->normalsArray[i].z = mesh->normalsArray[i].z / 2.56;
//			}*/
//			break;
//		case 3:
//			int texcoordsByte = elmt_byte_size * 2;
//			auto texcoordslength = index.size() / texcoordsByte;
//			for (size_t i = 0; i < texcoordslength; i++)
//			{
//				float2 texcoords;
//
//				texcoords.x = makeRealFolat(index[texcoordsByte * i], index[texcoordsByte * i + 1], index[texcoordsByte * i + 2], index[texcoordsByte * i + 3]);
//
//				texcoords.y = makeRealFolat(index[texcoordsByte * i + elmt_byte_size], index[texcoordsByte * i + elmt_byte_size + 1], index[texcoordsByte * i + elmt_byte_size + 2], index[texcoordsByte * i + elmt_byte_size + 3]);
//
//				texcoords.x = makeFinalNumber(texcoords.x, mesh->meshBound[type - 1].g_max.x, mesh->meshBound[type - 1].g_min.x);
//				texcoords.y = makeFinalNumber(texcoords.y, mesh->meshBound[type - 1].g_max.y, mesh->meshBound[type - 1].g_min.y);
//				mesh->meshBound[type - 1].m_min = makeMeshFloat2Min(mesh->meshBound[type - 1].m_min, texcoords.x, texcoords.y);
//				mesh->meshBound[type - 1].m_max = makeMeshFloat2Max(mesh->meshBound[type - 1].m_max, texcoords.x, texcoords.y);
//				mesh->texcoordsArray.push_back(texcoords);
//			}
//			auto max1 = mesh->meshBound[type - 1].m_min;
//			auto min1 = mesh->meshBound[type - 1].m_max;
//			std::cout << "mesh uv max:" << max1 << std::endl;
//			std::cout << "mesh uv min:" << min1 << std::endl;
//
//			/*if (std::abs(max - 1.0) >= 0.05 || std::abs(min - 0.0) >= 0.05) {
//				for (size_t i = 0; i < mesh->texcoordsArray.size(); i++)
//				{
//					mesh->texcoordsArray[i].x=normalizeNumber(mesh->texcoordsArray[i].x,max,min, mesh->meshBound[type - 1].g_max.x, mesh->meshBound[type - 1].g_min.x);
//					mesh->texcoordsArray[i].y = normalizeNumber(mesh->texcoordsArray[i].y, max, min, mesh->meshBound[type - 1].g_max.y, mesh->meshBound[type - 1].g_min.y);
//				}
//			}
//			else
//			{
//				for (size_t i = 0; i < mesh->texcoordsArray.size(); i++)
//				{
//					mesh->texcoordsArray[i].x = mesh->texcoordsArray[i].x*max;
//					mesh->texcoordsArray[i].y = mesh->texcoordsArray[i].y*max;
//				}
//			}*/
//			
//			break;
//		}
//	}
//
//
//	void processGLTFNode(
//		Scene* scene,
//		const tinygltf::Model& model,
//		const tinygltf::Node& gltf_node,
//		const Matrix4x4& parent_matrix
//	)
//	{
//		const Matrix4x4 translation = gltf_node.translation.empty() ?
//			Matrix4x4::identity() :
//			Matrix4x4::translate(make_float3_from_double(
//				gltf_node.translation[0],
//				gltf_node.translation[1],
//				gltf_node.translation[2]
//			));
//
//		const Matrix4x4 rotation = gltf_node.rotation.empty() ?
//			Matrix4x4::identity() :
//			Quaternion(
//				static_cast<float>(gltf_node.rotation[3]),
//				static_cast<float>(gltf_node.rotation[0]),
//				static_cast<float>(gltf_node.rotation[1]),
//				static_cast<float>(gltf_node.rotation[2])
//			).rotationMatrix();
//
//		const Matrix4x4 scale = gltf_node.scale.empty() ?
//			Matrix4x4::identity() :
//			Matrix4x4::scale(make_float3_from_double(
//				gltf_node.scale[0],
//				gltf_node.scale[1],
//				gltf_node.scale[2]
//			));
//
//		std::vector<float> gltf_matrix;
//		for (double x : gltf_node.matrix)
//			gltf_matrix.push_back(static_cast<float>(x));
//		const Matrix4x4 matrix = gltf_node.matrix.empty() ?
//			Matrix4x4::identity() :
//			Matrix4x4(reinterpret_cast<float*>(gltf_matrix.data())).transpose();
//
//		Matrix4x4 node_xform = parent_matrix * matrix * translation * rotation * scale;
//
//		/*if (gltf_node.camera != -1)
//		{
//			const auto& gltf_camera = model.cameras[gltf_node.camera];
//			std::cerr << "Processing camera '" << gltf_camera.name << "'\n"
//				<< "\ttype: " << gltf_camera.type << "\n";
//			if (gltf_camera.type != "perspective")
//			{
//				std::cerr << "\tskipping non-perpective camera\n";
//				return;
//			}
//
//			const float3 eye = make_float3(node_xform*make_float4_from_double(0.0f, 0.0f, 0.0f, 1.0f));
//			const float3 up = make_float3(node_xform*make_float4_from_double(0.0f, 1.0f, 0.0f, 0.0f));
//			const float  yfov = static_cast<float>(gltf_camera.perspective.yfov) * 180.0f / static_cast<float>(M_PI);
//
//			std::cerr << "\teye   : " << eye.x << ", " << eye.y << ", " << eye.z << std::endl;
//			std::cerr << "\tup    : " << up.x << ", " << up.y << ", " << up.z << std::endl;
//			std::cerr << "\tfov   : " << yfov << std::endl;
//			std::cerr << "\taspect: " << gltf_camera.perspective.aspectRatio << std::endl;
//
//			Camera camera;
//			camera.setFovY(yfov);
//			camera.setAspectRatio(static_cast<float>(gltf_camera.perspective.aspectRatio));
//			camera.setEye(eye);
//			camera.setUp(up);
//			scene.addCamera(camera);
//		}*/
//		if (gltf_node.mesh != -1)
//		{
//			const auto& gltf_mesh = model.meshes[gltf_node.mesh];
//			std::cerr << "Processing glTF mesh: '" << gltf_mesh.name << "'\n";
//			std::cerr << "\tNum mesh primitive groups: " << gltf_mesh.primitives.size() << std::endl;
//			for (auto& gltf_primitive : gltf_mesh.primitives)
//			{
//				if (gltf_primitive.mode != TINYGLTF_MODE_TRIANGLES) // Ignore non-triangle meshes
//				{
//					std::cerr << "\tNon-triangle primitive: skipping\n";
//					continue;
//				}
//
//				Mesh mesh;
//				
//
//
//				mesh.name = gltf_mesh.name;
//				
//				bufferViewFromGLTF(model, scene, gltf_primitive.indices, 0, &mesh);
//				mesh.material_idx.push_back(gltf_primitive.material);
//				mesh.transform = node_xform;
//				mesh.num_triangles = mesh.trianglesArray.size();
//				std::cerr << "\t\tNum triangles: " << mesh.num_triangles << std::endl;
//
//				assert(gltf_primitive.attributes.find("POSITION") != gltf_primitive.attributes.end());
//				const int32_t pos_accessor_idx = gltf_primitive.attributes.at("POSITION");
//				bufferViewFromGLTF(model, scene, pos_accessor_idx, 1, &mesh);
//				mesh.num_vertices = mesh.verticesArray.size();
//				std::cerr << "\t\tNum vertices: " << mesh.num_vertices << std::endl;
//				const auto& pos_gltf_accessor = model.accessors[pos_accessor_idx];
//				mesh.object_aabb = Aabb(
//					make_float3_from_double(
//						pos_gltf_accessor.minValues[0],
//						pos_gltf_accessor.minValues[1],
//						pos_gltf_accessor.minValues[2]
//					),
//					make_float3_from_double(
//						pos_gltf_accessor.maxValues[0],
//						pos_gltf_accessor.maxValues[1],
//						pos_gltf_accessor.maxValues[2]
//					));
//				mesh.world_aabb = mesh.object_aabb;
//				mesh.world_aabb.transform(node_xform);
//				mesh.bbox_min[0]= pos_gltf_accessor.minValues[0];
//				mesh.bbox_min[1] = pos_gltf_accessor.minValues[1];
//				mesh.bbox_min[2] = pos_gltf_accessor.minValues[2];
//				mesh.bbox_max[0] = pos_gltf_accessor.maxValues[0];
//				mesh.bbox_max[1] = pos_gltf_accessor.maxValues[1];
//				mesh.bbox_max[2] = pos_gltf_accessor.maxValues[2];
//
//
//				
//
//				auto normal_accessor_iter = gltf_primitive.attributes.find("NORMAL");
//				if (normal_accessor_iter != gltf_primitive.attributes.end())
//				{
//					std::cerr << "\t\tHas vertex normals: true\n";
//					bufferViewFromGLTF(model, scene, normal_accessor_iter->second, 2, &mesh);
//				}
//				else
//				{
//					std::cerr << "\t\tHas vertex normals: false\n";
//					bufferViewFromGLTF(model, scene, -1, 2, &mesh);
//				}
//
//				auto texcoord_accessor_iter = gltf_primitive.attributes.find("TEXCOORD_0");
//				if (texcoord_accessor_iter != gltf_primitive.attributes.end())
//				{
//					std::cerr << "\t\tHas texcoords: true\n";
//					bufferViewFromGLTF(model, scene, texcoord_accessor_iter->second, 3, &mesh);
//				}
//				else
//				{
//					std::cerr << "\t\tHas texcoords: false\n";
//					bufferViewFromGLTF(model, scene, -1, 3, &mesh);
//				}
//
//
//				scene->m_meshes.push_back(mesh);
//			}
//
//		}
//		else if (!gltf_node.children.empty())
//		{
//			for (int32_t child : gltf_node.children)
//			{
//				processGLTFNode(scene, model, model.nodes[child], node_xform);
//			}
//		}
//
//
//	}
//void loadScene(const std::string& filename, uautil::Scene* scene) {
//	tinygltf::Model model;
//	tinygltf::TinyGLTF loader;
//	std::string err;
//	std::string warn;
//
//	bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
//	if (!warn.empty())
//		std::cerr << "glTF WARNING: " << warn << std::endl;
//	if (!ret)
//	{
//		std::cerr << "Failed to load GLTF scene '" << filename << "': " << err << std::endl;
//	}
//
//	//
//	// Process buffer data first -- buffer views will reference this list
//	//
//	for (const auto& gltf_buffer : model.buffers)
//	{
//		const uint64_t buf_size = gltf_buffer.data.size();
//		std::cerr << "Processing glTF buffer '" << gltf_buffer.name << "'\n"
//			<< "\tbyte size: " << buf_size << "\n"
//			<< "\turi      : " << gltf_buffer.uri << std::endl;
//		auto data = gltf_buffer.data;
//		scene->m_data = gltf_buffer.data;
//	}
//	//����ע��Ϊ��������ļ��أ����������Ҫ��ȥ����
//	/*//
//	// Images -- just load all up front for simplicity
//	//
//	for (const auto& gltf_image : model.images)
//	{
//		std::cerr << "Processing image '" << gltf_image.name << "'\n"
//			<< "\t(" << gltf_image.width << "x" << gltf_image.height << ")x" << gltf_image.component << "\n"
//			<< "\tbits: " << gltf_image.bits << std::endl;
//
//		assert(gltf_image.component == 4);
//		assert(gltf_image.bits == 8 || gltf_image.bits == 16);
//
//		scene.addImage(
//			gltf_image.width,
//			gltf_image.height,
//			gltf_image.bits,
//			gltf_image.component,
//			gltf_image.image.data()
//		);
//	}
//
//	//
//	// Textures -- refer to previously loaded images
//	//
//	for (const auto& gltf_texture : model.textures)
//	{
//		if (gltf_texture.sampler == -1)
//		{
//			scene.addSampler(cudaAddressModeWrap, cudaAddressModeWrap, cudaFilterModeLinear, gltf_texture.source);
//			continue;
//		}
//
//		const auto& gltf_sampler = model.samplers[gltf_texture.sampler];
//
//		const cudaTextureAddressMode address_s = gltf_sampler.wrapS == GL_CLAMP_TO_EDGE ? cudaAddressModeClamp :
//			gltf_sampler.wrapS == GL_MIRRORED_REPEAT ? cudaAddressModeMirror :
//			cudaAddressModeWrap;
//		const cudaTextureAddressMode address_t = gltf_sampler.wrapT == GL_CLAMP_TO_EDGE ? cudaAddressModeClamp :
//			gltf_sampler.wrapT == GL_MIRRORED_REPEAT ? cudaAddressModeMirror :
//			cudaAddressModeWrap;
//		const cudaTextureFilterMode  filter = gltf_sampler.minFilter == GL_NEAREST ? cudaFilterModePoint :
//			cudaFilterModeLinear;
//		scene.addSampler(address_s, address_t, filter, gltf_texture.source);
//	}
//
//	//
//	// Materials
//	//
//	for (auto& gltf_material : model.materials)
//	{
//		std::cerr << "Processing glTF material: '" << gltf_material.name << "'\n";
//		MaterialData::Pbr mtl;
//
//		{
//			const auto base_color_it = gltf_material.values.find("baseColorFactor");
//			if (base_color_it != gltf_material.values.end())
//			{
//				const tinygltf::ColorValue c = base_color_it->second.ColorFactor();
//				mtl.base_color = make_float4_from_double(c[0], c[1], c[2], c[3]);
//				std::cerr
//					<< "\tBase color: ("
//					<< mtl.base_color.x << ", "
//					<< mtl.base_color.y << ", "
//					<< mtl.base_color.z << ")\n";
//			}
//			else
//			{
//				std::cerr << "\tUsing default base color factor\n";
//			}
//		}
//
//		{
//			const auto base_color_it = gltf_material.values.find("baseColorTexture");
//			if (base_color_it != gltf_material.values.end())
//			{
//				std::cerr << "\tFound base color tex: " << base_color_it->second.TextureIndex() << "\n";
//				mtl.base_color_tex = scene.getSampler(base_color_it->second.TextureIndex());
//			}
//			else
//			{
//				std::cerr << "\tNo base color tex\n";
//			}
//		}
//
//		{
//			const auto roughness_it = gltf_material.values.find("roughnessFactor");
//			if (roughness_it != gltf_material.values.end())
//			{
//				mtl.roughness = static_cast<float>(roughness_it->second.Factor());
//				std::cerr << "\tRougness:  " << mtl.roughness << "\n";
//			}
//			else
//			{
//				std::cerr << "\tUsing default roughness factor\n";
//			}
//		}
//
//		{
//			const auto metallic_it = gltf_material.values.find("metallicFactor");
//			if (metallic_it != gltf_material.values.end())
//			{
//				mtl.metallic = static_cast<float>(metallic_it->second.Factor());
//				std::cerr << "\tMetallic:  " << mtl.metallic << "\n";
//			}
//			else
//			{
//				std::cerr << "\tUsing default metallic factor\n";
//			}
//		}
//
//		{
//			const auto metallic_roughness_it = gltf_material.values.find("metallicRoughnessTexture");
//			if (metallic_roughness_it != gltf_material.values.end())
//			{
//				std::cerr << "\tFound metallic roughness tex: " << metallic_roughness_it->second.TextureIndex() << "\n";
//				mtl.metallic_roughness_tex = scene.getSampler(metallic_roughness_it->second.TextureIndex());
//			}
//			else
//			{
//				std::cerr << "\tNo metallic roughness tex\n";
//			}
//		}
//
//		{
//			const auto normal_it = gltf_material.additionalValues.find("normalTexture");
//			if (normal_it != gltf_material.additionalValues.end())
//			{
//				std::cerr << "\tFound normal color tex: " << normal_it->second.TextureIndex() << "\n";
//				mtl.normal_tex = scene.getSampler(normal_it->second.TextureIndex());
//			}
//			else
//			{
//				std::cerr << "\tNo normal tex\n";
//			}
//		}
//
//		scene.addMaterial(mtl);
//	}*/
//
//	//
//	// Process nodes
//	//
//	std::vector<int32_t> root_nodes(model.nodes.size(), 1);
//	for (auto& gltf_node : model.nodes)
//		for (int32_t child : gltf_node.children)
//			root_nodes[child] = 0;
//
//	for (size_t i = 0; i < root_nodes.size(); ++i)
//	{	
//		if (!root_nodes[i])
//			continue;
//		auto& gltf_node = model.nodes[i];
//		processGLTFNode(scene, model, gltf_node, Matrix4x4::identity());
//	}
//	scene->m_num_meshes = scene->m_meshes.size();
//	scene->m_scene_aabb.invalidate();
//	for (const auto mesh : scene->m_meshes)
//		scene->m_scene_aabb.include(mesh.object_aabb);
//	scene->bbox_min[0] = scene->m_scene_aabb.m_min.x;
//	scene->bbox_min[1] = scene->m_scene_aabb.m_min.y;
//	scene->bbox_min[2] = scene->m_scene_aabb.m_min.z;
//	scene->bbox_max[0] = scene->m_scene_aabb.m_max.x;
//	scene->bbox_max[1] = scene->m_scene_aabb.m_max.y;
//	scene->bbox_max[2] = scene->m_scene_aabb.m_max.z;
//}
//
//
//}
