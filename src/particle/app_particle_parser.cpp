
#include "app_particle_parser.h"

//#include "tinyxml/tinyxml.h"

#define GET_F(map, name) (map)[name]
#define GET_I(map, name) (map)[name]

//#define LONG_STRING_CONST(...) #__VA_ARGS__

namespace app {
    
    ParticleParser::ParticleParser() {
        
    }
    
    ParticleParser::~ParticleParser() {
        
    }
    
//    bool ParticleParser::parseFromObj(asl::dyobj::Dyobj obj) {
//        _desc.emitAngle     = GET_I(obj, "angle");
//        _desc.emitAngle     = 360 - _desc.emitAngle;
//        _desc.emitAngleVar  = GET_I(obj, "angleVariance");
//
//        _desc.emitSpeed     = GET_I(obj, "speed");
//        _desc.emitSpeedVar  = GET_I(obj, "speedVariance");
//
//        _desc.duration      = GET_F(obj, "duration");
//
//        int emitterType     = GET_I(obj, "emitterType");
//        if ( emitterType > 0 ) {
//            _desc.emitterType = EMITTER_TYPE_RADIUS;
//        } else {
//            _desc.emitterType = EMITTER_TYPE_GRAVITY;
//        }
//
//        _desc.particleCount = GET_F(obj, "maxParticles");
//        _desc.emitPosVar.set(GET_F(obj, "sourcePositionVarianceX"),
//                             GET_F(obj, "sourcePositionVarianceY"));
//
//        _desc.life    = GET_F(obj, "particleLifeSpan");
//        _desc.lifeVar = GET_F(obj, "particleLifespanVariance");
//
//        _desc.emitRate = _desc.particleCount / _desc.life;
//
//        _desc.beginColor.set(
//                    GET_F(obj, "startColorRed"),
//                    GET_F(obj, "startColorGreen"),
//                    GET_F(obj, "startColorBlue"),
//                    GET_F(obj, "startColorAlpha"));
//
//        _desc.beginColorVar.set(
//                    GET_F(obj, "startColorVarianceRed"),
//                    GET_F(obj, "startColorVarianceGreen"),
//                    GET_F(obj, "startColorVarianceBlue"),
//                    GET_F(obj, "startColorVarianceAlpha"));
//
//        _desc.endColor.set(
//                    GET_F(obj, "finishColorRed"),
//                    GET_F(obj, "finishColorGreen"),
//                    GET_F(obj, "finishColorBlue"),
//                    GET_F(obj, "finishColorAlpha"));
//
//        _desc.endColorVar.set(
//                    GET_F(obj, "finishColorVarianceRed"),
//                    GET_F(obj, "finishColorVarianceGreen"),
//                    GET_F(obj, "finishColorVarianceBlue"),
//                    GET_F(obj, "finishColorVarianceAlpha"));
//
//        _desc.beginSize     = GET_F(obj, "startParticleSize");
//        _desc.beginSizeVar  = GET_F(obj, "startParticleSizeVariance");
//        _desc.endSize       = GET_F(obj, "finishParticleSize");
//        _desc.endSizeVar    = GET_F(obj, "finishParticleSizeVariance");
//
//        _desc.beginSpin     = GET_F(obj, "rotationStart");
//        _desc.beginSpinVar  = GET_F(obj, "rotationStartVariance");
//        _desc.endSpin       = GET_F(obj, "rotationEnd");
//        _desc.endSpinVar    = GET_F(obj, "rotationEndVariance");
//
//        MotionMode motionModes[2] = {
//            MOTION_MODE_FREE,
//            MOTION_MODE_RELATIVE
//        };
//
//        int motionMode = GET_I(obj, "positionType");
//        _desc.motionMode = motionModes[motionMode];
//
//        _desc.gravityMode.gravity.set(GET_F(obj, "gravityX"), GET_F(obj, "gravityY"));
//        _desc.gravityMode.gravity.y = -_desc.gravityMode.gravity.y; // for particle editor
//
//        _desc.gravityMode.radialAccel     = GET_F(obj, "radialAcceleration");
//        _desc.gravityMode.radialAccelVar  = GET_F(obj, "radialAccelVariance");
//
//        _desc.gravityMode.tangentialAccel     = GET_F(obj, "tangentialAcceleration");
//        _desc.gravityMode.tangentialAccelVar  = GET_F(obj, "tangentialAccelVariance");
//
//        _desc.radiusMode.endRadius    = GET_F(obj, "minRadius");
//        _desc.radiusMode.endRadiusVar = GET_F(obj, "minRadiusVariance");
//
//        _desc.radiusMode.beginRadius    = GET_F(obj, "maxRadius");
//        _desc.radiusMode.beginRadiusVar = GET_F(obj, "maxRadiusVariance");
//
//        _desc.radiusMode.spinPerSecond    = GET_F(obj, "rotatePerSecond");
//        _desc.radiusMode.spinPerSecondVar = GET_F(obj, "rotatePerSecondVariance");
//
//        _desc.blendFuncSource = GET_I(obj, "blendFuncSource");
//        _desc.blendFuncDestination = GET_I(obj, "blendFuncDestination");
//
//        return true;
//    }
    
    bool ParticleParser::parseFromPlist(const char* data) {
//        asl::dyobj::Dyobj obj;
//
//        TiXmlDocument doc;
//        doc.Parse(data);
//
//        TiXmlElement* root = doc.RootElement();
//        TiXmlNode* dict = root->FirstChildElement("dict");
//        TiXmlElement* ele = dict->FirstChildElement();
//
//        const char* tmpstr1;
//        const char* tmpstr2;
//        while ( ele ) {
//            if ( ele->GetText() != NULL && strcmp("textureImageData", ele->GetText()) == 0 ) {
//                ele = ele->NextSiblingElement()->NextSiblingElement();
//            } else {
//                tmpstr1 = ele->GetText();
//                ele = ele->NextSiblingElement();
//                tmpstr2 = ele->GetText() == NULL ? "0" : ele->GetText();
//                ele = ele->NextSiblingElement();
//
//                obj[tmpstr1] = tmpstr2;
//            }
//        }
//
//        parseFromObj(obj);
        
        return true;
    }
    
    bool ParticleParser::parseFromPex(const char* data) {
//        asl::dyobj::Dyobj obj;
//        
//        TiXmlDocument doc;
//        doc.Parse(data);
//        
//        TiXmlElement* root = doc.RootElement();
//        TiXmlNode* dict = root->FirstChildElement("dict");
//        TiXmlElement* ele = dict->FirstChildElement();
//        
//        const char* tmpstr1;
//        const char* tmpstr2;
//        while ( ele ) {
//            if ( ele->GetText() != NULL && strcmp("textureImageData", ele->GetText()) == 0 ) {
//                ele = ele->NextSiblingElement()->NextSiblingElement();
//            } else {
//                tmpstr1 = ele->GetText();
//                ele = ele->NextSiblingElement();
//                tmpstr2 = ele->GetText() == NULL ? "0" : ele->GetText();
//                ele = ele->NextSiblingElement();
//
//                //  map.insert(make_pair(tmpstr1, tmpstr2));
//            }
//        }
//        
//        parseFromObj(obj);
        
        return true;
    }
    
}
