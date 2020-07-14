#pragma once;

#include <iostream>
#include "scene.h"
#include "../include/tinygltf/tiny_gltf.h"
//#include 
namespace toy {
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

			scene.addBuffer(gltf_buffer.data.data());
		}
		//

	};
}
