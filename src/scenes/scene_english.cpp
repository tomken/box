
#include "scene_english.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <stdlib.h>

const char* voice_path = "/Users/zy/peter/voice";

inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

namespace app {
    
    English::English() {
        _audio = 0;
        _count = 0;
        _right = 0;
        _off   = false;
        
        srand(time(0));
        loadWordsFile();
        initUi();
    }
    
    English::~English() {
        
    }
    
    void English::onEnter() {
        int w, h;
        context().requestSetBackgroundColor(Color::White);
        context().requestSetTitle("背单词 v1.0");
        context().requestGetWindowSize(w, h);
        
        _title->setPosition(0, 0);
        _title->setSize(w, 80);
        
        _daan1->setSize(200, 40);
        _daan1->setPosition(w/2 - 200 - 20, 100);
        
        _daan2->setSize(200, 40);
        _daan2->setPosition(w/2 + 20, 100);
        
        _daan3->setSize(200, 40);
        _daan3->setPosition(w/2 - 200 - 20, 160);
        
        _daan4->setSize(200, 40);
        _daan4->setPosition(w/2 + 20, 160);
        
        _tips->setPosition(0, h - 40 - 10);
        _tips->setSize(w - 200 - 10, 40);
        
        _continue->setSize(200, 40);
        _continue->setPosition(w - 200 - 10, h - 40 - 10);
        
        _rightImage->setSize(80, 80);
        _rightImage->setPosition(w*0.5f - 40, h*0.5f - 40);
        
        _wrongImage->setSize(80, 80);
        _wrongImage->setPosition(w*0.5f - 40, h*0.5f - 40);
        
        _back->setSize(50, 50);
        _back->setPosition(w - 50 - 10, 10);
        
        doTest();
    }
    
    void English::onLeave() {
        
    }
    
    void English::onClick(Button* btn) {
        if (btn == _continue) {
            _continue->setVisible(false);
            _wrongImage->fadeOut();
            doTest();
            _off = false;
            return;
        }
        
        if (btn == _back) {
            context().requestChangeScene("menu");
            return;
        }
        
        if (_off) {
            return;
        }
        
        _count++;
        
        bool isRight = false;
        if (btn == _daan1 && _rightIndex == 0) {
            isRight = true;
        } else if (btn == _daan2 && _rightIndex == 1) {
            isRight = true;
        } else if (btn == _daan3 && _rightIndex == 2) {
            isRight = true;
        } else if (btn == _daan4 && _rightIndex == 3) {
            isRight = true;
        }
        
        if (isRight) {
            _right++;
            _rightImage->setAlpha(1.0);
            _rightImage->setVisible(true);
            _rightImage->animate(tl::AnimationTypeAlpha, 1.0f, 0.f, 1200);
            doTest();
        } else {
            _wrongImage->setAlpha(1.0);
            _wrongImage->setVisible(true);
            
            _continue->setVisible(true);
            _off = true;
            char buff[512];
            int clickIndex = 0;
            if (btn == _daan1) {
                clickIndex = 1;
            } else if (btn == _daan2) {
                clickIndex = 2;
            } else if (btn == _daan3) {
                clickIndex = 3;
            } else if (btn == _daan4) {
                clickIndex = 4;
            }
            
            sprintf(buff, "你点的是第 %d 个，正确答案是第 %d 个！", clickIndex, _rightIndex+1);
            _tips->setText(buff);
        }
    }
    
    void English::loadWordsFile() {
        Path pp(ROOT_PATH);
        pp.join("english2.txt");
        const char* path = pp.toString().data();
        std::fstream f(path, std::ios::in);
        if (f) {
            // 有该文件
            std::string line;
            while (getline(f, line)) {
                std::stringstream input(line);
                
                std::string result;
                std::vector<std::string> ll;
                while (input>>result) {
                    ll.push_back(result);
                }
                
                if (ll.size() > 1) {
                    _chinese[_words.size()] = ll[1];
                    _words.push_back(ll[0]);
                }
            }
        }
    }
    
    void English::initUi() {
        Layer* layer = new Layer();
        
        _title = new Label();
        _title->setTag("title");
        _title->setPosition(100, 30);
        _title->setSize(500, 40);
        _title->setText("main");
        _title->setFontSize(48);
        _title->setFontName("sans-bold");
        _title->setTextColor(Color(50, 50, 50));
        layer->addNode(_title);
        
        _back = new ImageButton();
        _back->setTag("back");
        _back->setNormalImage("english/back_n.png");
        _back->setPressImage("english/back_p.png");
        _back->setClickCallback(app::bind(&English::onClick, this));
        layer->addNode(_back);
        
        _daan1 = new Button();
        _daan1->setTag("d1");
        _daan1->setText("Peter 出品1");
        _daan1->setFontName("sans-bold");
        _daan1->setTextColor(Color(187, 222, 251));
        _daan1->setNormalColor(Color(25, 118, 210));
        _daan1->setPressColor(Color(25, 118, 210, 200));
        _daan1->setClickCallback(app::bind(&English::onClick, this));
        layer->addNode(_daan1);
        
        _daan2 = new Button();
        _daan2->setTag("d2");
        _daan2->setPosition(400, 100);
        _daan2->setSize(200, 40);
        _daan2->setText("Peter 出品2");
        _daan2->setFontName("sans-bold");
        _daan2->setTextColor(Color(187, 222, 251));
        _daan2->setNormalColor(Color(25, 118, 210));
        _daan2->setPressColor(Color(25, 118, 210, 200));
        _daan2->setClickCallback(app::bind(&English::onClick, this));
        layer->addNode(_daan2);
        
        _daan3 = new Button();
        _daan3->setTag("d3");
        _daan3->setPosition(100, 150);
        _daan3->setSize(200, 40);
        _daan3->setText("Peter 出品3");
        _daan3->setFontName("sans-bold");
        _daan3->setTextColor(Color(187, 222, 251));
        _daan3->setNormalColor(Color(25, 118, 210));
        _daan3->setPressColor(Color(25, 118, 210, 200));
        _daan3->setClickCallback(app::bind(&English::onClick, this));
        layer->addNode(_daan3);
        
        _daan4 = new Button();
        _daan4->setTag("d4");
        _daan4->setPosition(400, 150);
        _daan4->setSize(200, 40);
        _daan4->setText("Peter 出品4");
        _daan4->setFontName("sans-bold");
        _daan4->setTextColor(Color(187, 222, 251));
        _daan4->setNormalColor(Color(25, 118, 210));
        _daan4->setPressColor(Color(25, 118, 210, 200));
        _daan4->setClickCallback(app::bind(&English::onClick, this));
        layer->addNode(_daan4);
        
        _rightImage = new Image();
        _rightImage->setPosition(320, 230);
        _rightImage->setSize(80, 80);
        _rightImage->setPath("english/right.png");
        _rightImage->setVisible(false);
        layer->addNode(_rightImage);
        
        _wrongImage = new Image();
        _wrongImage->setPosition(320, 230);
        _wrongImage->setSize(80, 80);
        _wrongImage->setPath("english/wrong.png");
        _wrongImage->setVisible(false);
        layer->addNode(_wrongImage);
        
        _tips = new Label();
        _tips->setPosition(100, 350);
        _tips->setSize(500, 40);
        _tips->setText("准备开始第 1 道题，加油啊~");
        _tips->setFontSize(48);
        _tips->setFontName("sans-bold");
        _tips->setTextColor(Color(150, 150, 150));
        layer->addNode(_tips);
        
        _continue = new Button();
        _continue->setPosition(580, 350);
        _continue->setSize(100, 40);
        _continue->setText("继续");
        _continue->setFontName("sans-bold");
        _continue->setTextColor(Color(187, 222, 251));
        _continue->setNormalColor(Color(183, 28, 28));
        _continue->setPressColor(Color(183, 28, 28, 200));
        _continue->setClickCallback(app::bind(&English::onClick, this));
        _continue->setVisible(false);
        layer->addNode(_continue);
        
        addLayer(layer);
    }
    
    void English::doTest() {
        _wordIndex = random(0, _words.size());
        _rightIndex = random(0, 4);
        
        _result.resize(4);
        _result[0] = -1;
        _result[1] = -1;
        _result[2] = -1;
        _result[3] = -1;
        
        _result[_rightIndex] = _wordIndex;
        
        for (int i=0; i<4; i++) {
            if (i != _rightIndex) {
                _result[i] = findWorng();
            }
        }
        
        _title->setText(_words[_wordIndex]);
        _daan1->setText(_chinese[_result[0]]);
        _daan2->setText(_chinese[_result[1]]);
        _daan3->setText(_chinese[_result[2]]);
        _daan4->setText(_chinese[_result[3]]);
        
        if (_count > 0) {
            updateTips();
        }
        playWord();
    }
    
    int English::random(int min, int max) {
        return (rand() % (max - min)) + min;
    }
    
    int English::findWorng() {
        while (1) {
            int idx = random(0, _words.size());
            
            if (idx != _result[0] && idx != _result[1] &&
                idx != _result[2] && idx != _result[3]) {
                return idx;
            }
        }
    }
    
    void English::playWord() {
        std::string this_wav = voice_path;
        this_wav += "/";
        this_wav += _words[_wordIndex][0] - 32;
        this_wav += "/";
        this_wav += _words[_wordIndex];
        this_wav += ".wav";
        if (file_exists(this_wav)) {
            delete _audio;
            _audio = new Audio(this_wav.c_str());
            _audio->play();
        }
    }
    
    void English::updateTips() {
        char buff[512];
        sprintf(buff, "共做了 %d 道题，答对了 %d 道！", _count, _right);
        _tips->setText(buff);
    }
    
}
