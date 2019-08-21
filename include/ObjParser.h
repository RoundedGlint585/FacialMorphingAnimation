//
// Created by roundedglint585 on 8/3/19.
//

#ifndef OPENGL_OBJPARSER_H
#define OPENGL_OBJPARSER_H

#include <vector>
#include <tuple>
#include <cstdint>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include "Logger.h"
#include "Mesh.h"

namespace objParser {
    namespace details {
        std::array<std::vector<uint32_t>, 3> parseFaceString(std::string_view str) {
            std::array<std::vector<uint32_t>, 3> result = {}; // vertexIndex/textureIndex/normalIndex
            enum typeOfIndex {
                vertexIndex,
                textureIndex,
                normalIndex
            };
            std::string num;
            uint32_t type = 0;
            for (auto &i: str) {
                if (i >= '0' && i <= '9') {
                    num += i;
                } else if (i == '/' || type == 2) {
                    if (type == 0) {
                        result[vertexIndex].emplace_back(std::stoi(num));
                        type++;
                    } else if (type == 1) {
                        result[textureIndex].emplace_back(std::stoi(num));
                        type++;
                    } else if (type == 2) {
                        result[normalIndex].emplace_back(std::stoi(num));
                        type = 0;
                    }
                    num = "";
                }
            }
            if(!num.empty()){
                result[normalIndex].emplace_back(std::stoi(num));
            }
            return result;
        }


        template<class T> class PairHash;

        template<>
        class PairHash<std::pair<glm::vec3, glm::vec3>> {
        public:
            size_t operator()(const std::pair<glm::vec3, glm::vec3> &pair) const {
                size_t h1 = std::hash<float>{}(pair.first.x);
                size_t h2 = std::hash<float>{}(pair.second.x);
                return h1 ^ (h2 << 1u);
            }
        };

    }



    [[nodiscard]] inline std::tuple<std::vector<Mesh::Vertex>, std::vector<uint32_t>> parseFile(std::string_view path) {
        std::ifstream file(&path.front());
        std::vector<glm::vec3> vertices, normals;
        std::vector<std::pair<glm::vec3, glm::vec3>> preMeshVertex;
        std::vector<uint32_t> indices = {};
        std::unordered_map<std::pair<glm::vec3, glm::vec3>, uint32_t, details::PairHash<std::pair<glm::vec3,glm::vec3>>> fromDataToIndex;

        std::string token;
        while (file >> token) {
            if (token == "v") {
                float x, y, z;
                file >> x >> y >> z;
                vertices.emplace_back(x, y, z);
            } else if (token == "vn") {
                float x, y, z;
                file >> x >> y >> z;
                normals.emplace_back(x, y, z);
            } else if (token == "f") { // todo: generate face as we should with indexed geometry
                std::string toParse;
                std::getline(file, toParse);
                auto result = details::parseFaceString(toParse);
                std::vector<uint32_t> parsedVertices = result[0];
                std::vector<uint32_t> parsedNormals = result[2];
                auto findOrInsertPair = [&](uint32_t index){
                    auto possibleIndex = fromDataToIndex.find(
                            {vertices[parsedVertices[index] - 1], normals[parsedNormals[index] - 1]});
                    if (possibleIndex == fromDataToIndex.end()) {
                        fromDataToIndex.insert({{vertices[parsedVertices[index] - 1], normals[parsedNormals[index] - 1]},
                                                preMeshVertex.size()});
                        indices.emplace_back(preMeshVertex.size());
                        preMeshVertex.emplace_back(vertices[parsedVertices[index] - 1], normals[parsedNormals[index] - 1]);

                    } else {
                        indices.emplace_back((*possibleIndex).second);
                    }
                };
                for (size_t i = 0; i < 3; i++) {
                    findOrInsertPair(i);
                }
                if (parsedVertices.size() == 4) {
                    findOrInsertPair(0);
                    findOrInsertPair(2);
                    findOrInsertPair(3);
                }
            } else if (token == "vt") {
                continue; //todo: ad textures
            } else if (token == "usemtl") {
                continue; //todo: add materials
            } else if (token == "mtllib") {
                continue; //todo: materials
            } else if (token == "o") {
                file >> token;
                INFO("Reading file: " + token);
            } else if (token == "g") {
                continue; //todo: object group parsing
            } else {
                continue;
            }
        }

        std::vector<Mesh::Vertex> verticesResult(preMeshVertex.size());
        for (size_t i = 0; i < preMeshVertex.size(); i++) {
            verticesResult[i] = {preMeshVertex[i].first, preMeshVertex[i].second};
        }
        return std::make_tuple(verticesResult, indices);
    }
}


#endif //OPENGL_OBJPARSER_H
