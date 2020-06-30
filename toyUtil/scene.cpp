#include <iostream>
#include "../support/fbx/fbx.hpp"
#include "scene.h"
#include "vector_type.h"

namespace uautil {

	namespace {
        void printRecord(const Fbx::Record* record, size_t level = 0)
        {
            std::cout << std::string(level * 3, ' ') << "Rec: " << record->name() << std::endl;

            for (auto p : record->properties())
            {
                std::cout << std::string((level + 1) * 3, ' ') << "Prop - " << p->code() << ": " << p->string() << std::endl;
            }
            for (auto r : *record)
            {
                printRecord(r, level + 1);
            }
        }

	}

    void processFbxNode(Mesh& mesh, std::list<Fbx::Record*>::iterator list) {
        auto vertices =(*(*list)->find("Vertices"));
        if (vertices->properties().size() == 0) {
            throw "点数组长度为0,请检查模型";
        }
        auto verticesArray = vertices->properties().front()->array();
        //如果出现了其他类型再修改
        //auto verticesType = vertices->properties().front()->type();
        for (size_t i = 0; i < verticesArray.size() / 3; i++)
        {
            float3 temp;
            temp.x = verticesArray[3 * i].float64;
            temp.y = verticesArray[3 * i +1].float64;
            temp.z = verticesArray[3 * i +2].float64;
            mesh.positions.push_back(verticesArray[3 * i].float64);
            mesh.positions.push_back(verticesArray[3 * i+1].float64);
            mesh.positions.push_back(verticesArray[3 * i+2].float64);
            mesh.verticesArray.push_back(temp);
        }

        auto index = (*(*list)->find("PolygonVertexIndex"));
        if (index->properties().size() == 0) {
            throw "位置下标数组长度为0,请检查模型";
        }
        auto indexArray = index->properties().front()->array();
        for (size_t  i = 0; i < indexArray.size() / 3; i++)
        {
            int3 tempIndex;
            tempIndex.x = indexArray[3*i].integer32;
            tempIndex.y = indexArray[3 * i +1].integer32;
            mesh.indices.push_back(indexArray[3 * i].integer32);
            mesh.indices.push_back(indexArray[3 * i+1].integer32);
            if (indexArray[3 * i + 2].integer32 < 0) {
                tempIndex.z = std::abs(indexArray[3 * i + 2].integer32) - 1;
                mesh.indices.push_back(std::abs(indexArray[3 * i + 2].integer32) - 1);
            }
            mesh.trianglesArray.push_back(tempIndex);
        }
    }

    void loadFbx(const std::string& filename, uautil::Scene* scene) {
        Fbx::Record file;
        std::vector<Mesh> meshs;
        auto versionCheck = [](std::string magic, uint32_t version)
        {
            if (magic != "Kaydara FBX Binary  ")
            {
                throw std::runtime_error("Invalid magic string.");
            }
            if (version < 7100)
            {
                throw std::runtime_error("I'm not interested in version less than 7100.");
            }
        };

        file.read(filename);

        auto object =*file.find("Objects");
        
        for (auto i= object->begin();i!= object->end();i++)
        {
            std::cout << (*i)->name() << std::endl;
            if ((*i)->name() == "Geometry")
            {
                Mesh mesh;
                processFbxNode(mesh, i);
                scene->m_meshes.push_back(mesh);
                //loadNodeFromFbx
                //std::cout << object->size() << std::endl;
            }
        }
    }

	void loadScene(const std::string& filename, uautil::Scene* scene) {
        loadFbx(filename, scene);
	}
	
}