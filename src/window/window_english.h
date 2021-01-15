
#ifndef __ENGLISH_H__
#define __ENGLISH_H__

#include "app/app.h"

#include <vector>

using namespace app;

namespace english {
    
    class Game : public Window {
    public:
        Game();
        ~Game();
        
    public:
        virtual void onCreate();
        
    private:
        void onClick(Button* btn);
        
    private:
        void loadWordsFile();
        void doTest();
        void playWord();
        int random(int min, int max);
        int findWorng();
        void updateTips();
        
    private:
        std::vector<std::string>   _words;
        std::map<int, std::string> _chinese;
        
    private:
        Label*    _title;
        Label*    _tips;
        
        Image*    _rightImage;
        Image*    _wrongImage;
        
        Button*   _daan1;
        Button*   _daan2;
        Button*   _daan3;
        Button*   _daan4;
        
        Button*   _continue;
        
        bool      _off;
    private:
        int                _wordIndex;
        int                _rightIndex;
        std::vector<int>   _result;
        int                _count;
        int                _right;
        
        Audio*             _audio;
    };
    
}

#endif // __ENGLISH_H__

