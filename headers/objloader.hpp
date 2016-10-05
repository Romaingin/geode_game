#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

bool ObjLoader(const char * path,
    std::vector< glm::vec3 > & outVertices,
    std::vector< unsigned int> & outIndices);

#endif