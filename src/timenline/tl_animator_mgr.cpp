
#include "tl_animator_mgr.h"
#include "tl_animator_chain.h"
#include "tl_animator_color.h"
#include "tl_animator_line.h"
#include "tl_animator_quad.h"
#include "tl_animator_bezier.h"
#include "tl_animator_map.h"

#include "app_path.h"

namespace tl {
    
    AnimatorManager::AnimatorManager(IAnimatorEventListener* listener) : _root(new AnimatorChain()), _listener(listener), _needVSync(false), _minDelay(0) {
    }
    
    AnimatorManager::~AnimatorManager() {
        delete _root;
        _root = 0;
    }

    void AnimatorManager::play() {
        _root->start();
    }

    void AnimatorManager::run() {
        _needVSync = false;
        _minDelay = 0;
        std::map<std::string, AnimatorBase*>::iterator  animIt;
        for (animIt = _animators.begin(); animIt != _animators.end(); animIt++) {
            AnimatorBase* ab = animIt->second;
            bool isFinish = ab->isFinished();
            if (!isFinish) {
                animIt->second->run();
            }
//            if (!animIt->second->isFinished()) animIt->second->run();
        }
        if (_needVSync && _listener) {
            _listener->requestVSync(_minDelay);
        }
    }

    void AnimatorManager::stop() {
        _root->stop();
    }

    void AnimatorManager::stopAll() {
        _root->stop();
        std::map<std::string, AnimatorChain*>::iterator chainIt;
        for (chainIt = _eventChain.begin(); chainIt != _eventChain.end(); chainIt++) {
            chainIt->second->stop();
        }
    }

    uint32_t AnimatorManager::nextTime() const {
        return 0;
    }

    void AnimatorManager::onEvent(const std::string& eventTag) {
        std::map<std::string, AnimatorChain*>::iterator it = _eventChain.find(eventTag);
        if (it != _eventChain.end()) {
            it->second->start();
        }
    }
    
//    void AnimatorManager::onEvent(const std::string& elementTag, EventType type) {
//        std::string event_key;
//        char temp[8] = {0};
//        snprintf(temp, sizeof(temp), "%d", type);
//        event_key.append(elementTag).append("_").append(temp);
//        std::map<std::string, AnimatorChain*>::iterator it = _eventChain.find(event_key);
//        if (it != _eventChain.end()) {
//            it->second->start();
//        }
//    }

//    void AnimatorManager::cancelEvent(std::string elementTag, EventType type) {
//        std::string event_key;
//        char temp[8] = {0};
//        snprintf(temp, sizeof(temp), "%d", type);
//        event_key.append(elementTag).append("_").append(temp);
//        std::map<std::string, AnimatorChain*>::iterator it = _eventChain.find(event_key);
//        if (it != _eventChain.end()) {
//            it->second->stop();
//        }
//    }
    
    void AnimatorManager::makeAnimator(UUID uuid, const json& obj) {
        std::string tag = obj["tag"].get<std::string>();
        if (tag.empty())
            return;

        AnimatorBase* a = createAnimator(obj);
        a->setUuid(uuid);
        _animators[tag] = a;
        std::string target;
        
        if (!obj["width"].empty()) {
            target = obj.at("width").get<std::string>();
            if (_eventChain.find(target) != _eventChain.end()) {//in eventChain
                _eventChain[target]->add(a, AnimatorChain::AnimatorRelateWith, _animators[target]);
            } else {
                _root->add(a, AnimatorChain::AnimatorRelateWith, _animators[target]);
            }
        } else if (!obj["after"].empty()) {
            target = obj["after"].get<std::string>();
            if (_eventChain.find(target) != _eventChain.end()) {//in eventChain
                _eventChain[target]->add(a, AnimatorChain::AnimatorRelateAfter, _animators[target]);
            } else {
                _root->add(a, AnimatorChain::AnimatorRelateAfter, _animators[target]);
            }
        } else if (!obj["event"].empty()) {
            assert(_eventChain.find(tag) == _eventChain.end());
            _eventChain[tag] = new AnimatorChain();
            _eventChain[tag]->add(a);
        } else {
            _root->add(a);
        }
    }
    
    void AnimatorManager::clear() {
        _root->clear();
        
        std::map<std::string, AnimatorChain*>::iterator chainIt;
        for (chainIt = _eventChain.begin(); chainIt != _eventChain.end(); chainIt++) {
            chainIt->second->clear();
            delete chainIt->second;
        }
        _eventChain.clear();
        
        std::map<std::string, AnimatorBase*>::iterator  animIt;
        for (animIt = _animators.begin(); animIt != _animators.end(); animIt++) {
            delete animIt->second;
        }
        _animators.clear();
    }

    void AnimatorManager::dump(std::string& result) {
        _root->dump(result);
    }

    AnimatorBase* AnimatorManager::createAnimator(const json& obj) {
        std::string animationType = obj["type"].get<std::string>();
        AnimationType eType = AnimationUtil::covertStrToType(animationType);
        if(eType == AnimationTypeUnknown) {
            // LMK_WARNING("ani", "animation type error. %s", data.c_str());
        }
        AnimatorBase* ani = NULL;
        if (eType == AnimationTypeColor) {
            AnimatorColor* base = new AnimatorColor();
            int32_t fromInt = obj["from"].get<int>();
            int32_t toInt   = obj["to"].get<int>();
            app::Color from(fromInt);
            app::Color to(toInt);
            base->setValues(from, to);
            ani = base;
        } else if (eType == AnimationTypePath) {
            std::string p = obj["path"].get<std::string>();
            app::StringSlice path(p.c_str());
            
            app::Point from, to;

            from.x = obj["from_x"].get<float>();
            from.y = obj["from_y"].get<float>();
            
            to.x = obj["to_x"].get<float>();
            to.y = obj["to_x"].get<float>();
            
            AnimatorLine* line;
            if (path == "quad") {
                AnimatorQuad* quad = new AnimatorQuad();
                app::Point ctr;
                ctr.x = obj["c_x"].get<float>();
                ctr.y = obj["c_y"].get<float>();

                quad->setControlPoint(ctr);
                line = quad;
            } else if (path == "bezier") {
                AnimatorBezier* bezier = new AnimatorBezier();
                app::Point ctr1, ctr2;
                
                ctr1.x = obj["c1_x"].get<float>();
                ctr1.y = obj["c1_y"].get<float>();
                
                ctr2.x = obj["c2_x"].get<float>();
                ctr2.y = obj["c2_y"].get<float>();
                
                bezier->setControlPoint(ctr1, ctr2);
                line = bezier;
            } else {
                line = new AnimatorLine();
            }
            
            line->setValues(from, to);

            ani = line;
        } else if (eType == AnimationTypeMap) {
//            AnimatorMap* base = new AnimatorMap();
//            int32_t fromInt = obj.getAttr(key::FROM);
//            int32_t toInt = obj.getAttr(key::TO);
//            Color from(fromInt);
//            Color to(toInt);
//            base->setValues(from, to);
//            ani = base;
        } else {
            AnimatorDefault* base = new AnimatorDefault();
            float from = obj["from"].get<float>();
            float to   = obj["to"].get<float>();
            base->setValues(from, to);
            ani = base;
        }
        
        ani->setType((AnimationType)eType);
        ani->addObserver(this);
        ani->setVSyncRequester(this);
        
        if (!obj["delay"].empty()) {
            ani->setDelay(obj["delay"].get<int>());
        }
        
        if (!obj["repeatCount"].empty()) {
            ani->setRepeatCount(obj["repeatCount"].get<int>());
        }

        ani->setDuration(obj["duration"].get<int>());
        return ani;
    }

    void AnimatorManager::onAnimatorRangeChange(AnimatorBase* ani, float range) {
//        Element* element = (Element*)ani->uuid().data();
//        switch (ani->type()) {
//            case tl::AnimationTypeTranslateX: {
//                Animator<float>* a = (Animator<float>*)ani;
//                element->matrixTranslateX(a->getCurrent());
//                break;
//            }
//            case tl::AnimationTypeTranslateY: {
//                Animator<float>* a = (Animator<float>*)ani;
//                element->matrixTranslateY(a->getCurrent());
//                break;
//            }
//            case tl::AnimationTypeAlpha: {
//                Animator<float>* a = (Animator<float>*)ani;
//                element->matrixAlpha(a->getCurrent());
//                break;
//            }
//            case tl::AnimationTypeRotation: {
//                Animator<float>* a = (Animator<float>*)ani;
//                element->matrixRotation(a->getCurrent());
//                break;
//            }
//            case tl::AnimationTypeScale: {
//                Animator<float>* a = (Animator<float>*)ani;
//                element->matrixScale(a->getCurrent());
//                break;
//            }
//            case tl::AnimationTypeColor: {
//                Animator<app::Color>* a = (Animator<app::Color>*)ani;
//                element->matrixColor(a->getCurrent().toARGBInt());
//                break;;
//            }
//            case tl::AnimationTypePath: {
//                Animator<app::Point>* a = (Animator<app::Point>*)ani;
//                element->matrixTranslateX(a->getCurrent().x);
//                element->matrixTranslateY(a->getCurrent().y);
//                break;;
//            }
//            default:
//                break;
//        }
    }

    void AnimatorManager::requestVSync(int32_t delay) {
        _needVSync = true;
        if (_minDelay == 0 || delay < _minDelay) {
            _minDelay = delay;
        }
    }

}

