
#ifndef __APP_PARTICLE_PARSER_H__
#define __APP_PARTICLE_PARSER_H__

#include "app_particle_description.h"

namespace app {
    
    class ParticleParser {
    public:
        ParticleParser();
        ~ParticleParser();
        
    public:
//        bool parseFromObj(asl::dyobj::Dyobj obj);
        bool parseFromPlist(const char* data);
        bool parseFromPex(const char* data);
        
        const ParticleDescription& description() {
            return _desc;
        }
        
    private:
        ParticleDescription _desc;
    };
    
}

#endif // __APP_PARTICLE_PARSER_H__
