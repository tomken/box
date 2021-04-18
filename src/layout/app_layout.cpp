
#include "app_layout.h"

namespace app {
    
    namespace layout {
        
        class Node;
        class Link {
        public:
            Node*    _node;
            Anchor   _from;
            Anchor   _to;
            float    _offsetX;
            float    _offsetY;
        };
        
        class Node {
        public:
            Node() {
                x = y = w = h = 0;
            }
            
            Node(float w_, float h_) {
                w = w_;
                h = h_;
                x = y = 0;
            }
            
            Node(float x_, float y_, float w_, float h_) {
                x = x_;
                y = y_;
                w = w_;
                h = h_;
            }
            
        public:
            std::string        key;
            std::vector<Link*> links;
            LayoutCallback     cb;
            
        public:
            float    x;
            float    y;
            float    w;
            float    h;
        };
        
        Layout::Layout() : _root(NULL), _minX(0.f), _minY(0.f), _maxX(0.f), _maxY(0.f) {
            _root = new Node();
            _root->key = "root";
            _nodes["root"] = _root;
        }
        
        Layout::Layout(float x, float y) {
            _root = new Node();
            _root->key = "root";
            _root->x = x;
            _root->y = y;
            _nodes["root"] = _root;
        }
        
        Layout::~Layout() {
            _nodes.clear();
        }
        
        bool Layout::add(const std::string& name, float w, float h, LayoutCallback cb) {
            Node* node = new Node(w, h);
            node->cb = cb;
            node->key = name;
            
            bool ret = _nodes.insert(std::pair<std::string, Node*>(name, node)).second;
            
            if (!ret) {
                delete node;
            }
            
            return ret;
        }
        
        bool Layout::link(const std::string& fromKey,
                          Anchor fromAnchor,
                          const std::string& toKey,
                          Anchor toAnchor,
                          float offsetX,
                          float offsetY) {
            Node* fn = find(fromKey);
            Node* tn = find(toKey);
            if (!fn || !tn)
                return false;
            Link* link = new Link();
            link->_from = fromAnchor;
            link->_to   = toAnchor;
            link->_offsetX = offsetX;
            link->_offsetY = offsetY;
            link->_node    = fn;
            
            tn->links.push_back(link);
            
            return true;
        }
        
        void Layout::calc(Node* node) {
            std::vector<Link*>& link = node->links;
            std::vector<Link*>::iterator it;
            for (it = link.begin(); it != link.end(); ++it) {
                Link* sub = (*it);
                float x = 0;
                float y = 0;
                get(node, sub->_to, x, y);
                set(sub->_node, sub->_from, x, y);
                
                sub->_node->x += sub->_offsetX;
                sub->_node->y += sub->_offsetY;
                         
                calc(sub->_node);
            }
            
            _minX = std::min(_minX, node->x);
            _maxX = std::max(_maxX, node->x + node->w);
            _minY = std::min(_minY, node->y);
            _maxY = std::max(_maxY, node->y + node->h);
        }
    
        void Layout::notify(Node* node, bool originCoordinate) {
            std::vector<Link*>& link = node->links;
            std::vector<Link*>::iterator it;
            for (it = link.begin(); it != link.end(); ++it) {
                Link* sub = (*it);
                notify(sub->_node, originCoordinate);
            }
            if (!node->cb.isNull()) {
                Result result;
                result.key = node->key;
                result.x = originCoordinate ? (node->x - _minX) : node->x;
                result.y = originCoordinate ? (node->y - _minY) : node->y;
                result.w = node->w;
                result.h = node->h;
                node->cb(result);
            }
        }
        
        void Layout::layout() {
            calc(_root);
            notify(_root, false);
        }
        
        void Layout::layoutForOriginCoordinate() {
            calc(_root);
            notify(_root, true);
        }
        
        float Layout::width() {
            return _maxX - _minX;
        }
        
        float Layout::height() {
            return _maxY - _minY;
        }
    
        void Layout::get(Node* node, Anchor anchor, float& x, float& y) {
            x = node->x + node->w * anchor.wRange;
            y = node->y + node->h * anchor.hRange;
        }
        
        void Layout::set(Node* node, Anchor anchor, float x, float y) {
            node->x = x - node->w * anchor.wRange;
            node->y = y - node->h * anchor.hRange;
        }
        
        Node* Layout::find(const std::string& key) {
            std::map<std::string, Node*>::iterator it;
            it = _nodes.find(key);
            if (it != _nodes.end())
                return it->second;
            
            return NULL;
        }
        
        const Anchor AnchorTL(0.0f, 0.0f);
        const Anchor AnchorTC(0.5f, 0.0f);
        const Anchor AnchorTR(1.0f, 0.0f);
        const Anchor AnchorCL(0.0f, 0.5f);
        const Anchor AnchorCC(0.5f, 0.5f);
        const Anchor AnchorCR(1.0f, 0.5f);
        const Anchor AnchorBL(0.0f, 1.0f);
        const Anchor AnchorBC(0.5f, 1.0f);
        const Anchor AnchorBR(1.0f, 1.0f);
        
    }
    
}
