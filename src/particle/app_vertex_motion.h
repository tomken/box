
#ifndef __APP_VERTEX_MOTION_H__
#define __APP_VERTEX_MOTION_H__

#include <string>
#include <vector>
#include <map>

namespace app {
    
    enum BlendFactor {
        BF_ZERO                 = 0,
        BF_ONE                  = 1,
        BF_SRC_COLOR            = 2,
        BF_INV_SRC_COLOR        = 3,
        BF_SRC_ALPHA            = 4,
        BF_INV_SRC_ALPHA        = 5,
        BF_DEST_ALPHA           = 6,
        BF_INV_DEST_ALPHA       = 7,
        BF_DEST_COLOR           = 8,
        BF_INV_DEST_COLOR       = 9,
        BF_SRC_ALPHA_SAT        = 10,
        BF_SRC_BLEND_FACTOR     = 11,
        BF_INV_BLEND_FACTOR     = 12,
        BF_SRC1_COLOR           = 13,
        BF_INV_SRC1_COLOR       = 14,
        BF_SRC1_ALPHA           = 15,
        BF_INV_SRC1_ALPHA       = 16,
        BF_FORCE_DWORD          = 0xffffffff,
    };
    
    enum BlendOp {
        BO_ADD            = 0,
        BO_SUB            = 1,
        BO_REV_SUB        = 2,
        BO_MIN            = 3,
        BO_MAX            = 4,
    };
    
    struct BlendSeparateDesc {
        BlendSeparateDesc() {
            blendEnable = true;
            blendOp = BO_ADD;
            srcBlend = BF_SRC_ALPHA;
            dstBlend = BF_INV_SRC_ALPHA;
            blendOpAlpha = BO_ADD;
            srcBlendAlpha = BF_ONE;
            dstBlendAlpha = BF_ZERO;
        }
        
        bool            blendEnable;
        BlendOp         blendOp;           // 融合rgb运算参数，默认值为BF_ADD
        BlendFactor     srcBlend;          // 融合源rgb颜色函数参数，默认值为BF_ONE
        BlendFactor     dstBlend;          // 融合目标rgb颜色函数参数，默认值为BF_ZERO
        
        BlendOp         blendOpAlpha;      // 融合alpha运算参数，默认值为BF_ADD
        BlendFactor     srcBlendAlpha;     // 融合源alpha颜色函数参数，默认值为BF_ONE
        BlendFactor     dstBlendAlpha;     // 融合目标alpha颜色函数参数，默认值为BF_ZERO
    };

    
    enum VertexType {
        VertexTypeTriangles = 0,
        VertexTypeTrianglesTrip,
    };
    
    class Vertex {
    public:
        float x, y, z;
        uint32_t  diffuse;
        float u, v;
    };
    
    typedef struct {
        int32_t count;
    } TextureConfig;
    
    class VertexRenderData {
    public:
        VertexType          vertexType;
        std::vector<Vertex> vertexs;
        std::vector<short>  indexes;
        
        TextureConfig       config;
    };
    
    class VertexMotion {
    public:
        VertexMotion();
        virtual ~VertexMotion();
        
    public:
        virtual void run() = 0;
        
    public:
        const std::map<std::string, VertexRenderData*>& getVertexDataMap() const;
        void setVertexType(VertexType type) {
            _vertexType = type;
        }
        
        VertexType getVertexType() const {
            return _vertexType;
        }
        
//        void setBlendDesc(asl::dyobj::Dyobj& obj);
        
        const BlendSeparateDesc& getBlendDesc() const {
            return _blendDesc;
        }
        
//        sgi::vector<Vertex>& getVertex() {
//            return _vertexs;
//        }
        
    protected:
        void clearData();
        void addVertexData(const std::string& tag, VertexRenderData* data);
        VertexRenderData* getVertexData(const std::string& tag);
        
    protected:
        std::map<std::string, VertexRenderData*>    _vertexMap;
        VertexType          _vertexType;
        BlendSeparateDesc   _blendDesc;
//        sgi::vector<Vertex> _vertexs;
//        sgi::vector<short>  _indexes;
    };

}

#endif // __APP_VERTEX_MOTION_H__
