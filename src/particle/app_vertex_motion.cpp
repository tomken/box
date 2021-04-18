#include "app_vertex_motion.h"

namespace app {
    
    VertexMotion::VertexMotion() {
    }
    
    VertexMotion::~VertexMotion() {
        std::map<std::string, VertexRenderData*>::iterator it = _vertexMap.begin();
        while (it != _vertexMap.begin()) {
            delete it->second;
            ++it;
        }
        _vertexMap.clear();
    }
    
    const std::map<std::string, VertexRenderData*>& VertexMotion::getVertexDataMap() const {
        return _vertexMap;
    }
    
    void VertexMotion::clearData() {
        std::map<std::string, VertexRenderData*>::iterator it = _vertexMap.begin();
        while (it != _vertexMap.end()) {
            it->second->vertexs.clear();
            it->second->indexes.clear();
            ++it;
        }
    }
    
    void VertexMotion::addVertexData(const std::string& tag, VertexRenderData* data) {
        _vertexMap[tag] = data;
    }
    
    VertexRenderData* VertexMotion::getVertexData(const std::string& tag) {
        std::map<std::string, VertexRenderData*>::iterator it = _vertexMap.find(tag);
        if (it != _vertexMap.end()) {
            return it->second;
        }
        return NULL;
    }
    
}
