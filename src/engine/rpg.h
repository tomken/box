
#ifndef __RPG_H__
#define __RPG_H__

typedef typename app::Callable<void(const MapInfo&)> DarkInitCb;

class Dark {
public:
    Dark();
    ~Dark();
    
public:
    void save(const char* path);
    void load(const char* path);
    void start();
    
public:
    void setLevel(int level);
    void showEquip();
    void showState();
    
    
};


#endif // __RPG_H__


