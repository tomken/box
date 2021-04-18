#include "scene_taskOne.h"

 #include <stdlib.h>

static void xxx() {
    
    std::string xx = "1.0";
    double vv = atof(xx.c_str());
}

struct Items {
    int x;
    int y;
    int w;
    int h;
    const char* name;
    Button** btn;
};

namespace app {
        
    Task1::Task1() {
        initButtons();
        _calcEnd = 0;
        _state   = CalcStateNumber;
        _numberA = "";
        _numberB = "";
        _hadNum = false;
        
        num();
    }
    
    Task1::~Task1() {
    }
    
    void Task1::onEnter() {
        initBackground();
    }
    
    void Task1::num() {
        _num = new Layer();
        _number = new Label();
        _number->setPosition(10, 10);
        _number->setSize(290, 60);
        _number->setFontSize(48);
        _number->setFontName("sans-bold");
        _number->setTextColor(Color::White);
        _number->setFillColor(Color::Red);
        _num->addNode(_number);
        
        char number[1024];
        sprintf(number,"%0.2f",_calcEnd);
        _number->setText(number);
        
        addLayer(_num);
    }
    
    void Task1::initBackground() {
        context().requestSetTitle("task1");
        context().requestSetBackgroundColor(Color(Color::White));
    }
    
    void Task1::initButtons() {
        _layer = new Layer();
        addLayer(_layer);

        _back = new ImageButton();
        _back->setTag("back");
        _back->setNormalImage("english/someback.png");
        _back->setPressImage("english/back_p.png");
        _back->setPosition(740,10);
        _back->setSize(50, 50);
        _back->setClickCallback(app::bind(&Task1::onBackClick, this));//回调
        _layer->addNode(_back);
        
        Items items[] = {
            { 190, 140, 50, 50, "0",   &_number0},
            { 10, 140, 50, 50,  "1",   &_number1},
            { 70, 140, 50, 50,  "2",   &_number2},
            { 130, 140, 50, 50, "3",   &_number3},
            { 10, 200, 50, 50,  "4",   &_number4},
            { 70, 200, 50, 50,  "5",   &_number5},
            { 130, 200, 50, 50, "6",   &_number6},
            { 10, 260, 50, 50,  "7",   &_number7},
            { 70, 260, 50, 50,  "8",   &_number8},
            { 130, 260, 50, 50, "9",   &_number9},
            
            { 190, 80, 110, 50,  "+",  &_opPlus},
            { 190, 260, 110, 50, "-",  &_opMinus},
            { 250, 140, 50, 50,  "×",  &_opMul},
            { 250, 200, 50, 50,  "÷",  &_opDivision},
            { 190, 200, 50, 50,  ".",  &_opDot},
            { 10, 80, 50, 50,    "AC", &_opClear},
            { 70, 80, 110, 50,   "=",  &_opEnd},
        };
        
        for (int i=0; i<sizeof(items)/sizeof(Items); i++) {
            Items& item = items[i];
            
            Button* btn = new Button();
            btn->setPosition(item.x, item.y);
            btn->setSize(item.w, item.h);
            btn->setRadius(20);
            btn->setText(item.name);
            btn->setFontName("sans-bold");
            btn->setTextColor(Color::DarkBlue);
            btn->setNormalColor(Color(144, 202, 249));
            btn->setPressColor(Color(66, 165, 245));
            btn->setClickCallback(app::bind(&Task1::onClick, this));
            btn->setUserData((void*)(long)i);
            _layer->addNode(btn);
            
            *item.btn = btn;
        }

    }
    
    void Task1::onBackClick(Button* btn) {
        context().requestChangeScene("menu");
    }
    
    void Task1::onClick(Button* btn) {
        if (_state == CalcStateNumber) {
            if (btn == _number0) {
                _numberA += "0";
            } else if (btn == _number1) {
                _numberA += "1";
            } else if (btn == _number2) {
                _numberA += "2";
            } else if (btn == _number3) {
                _numberA += "3";
            } else if (btn == _number4) {
                _numberA += "4";
            } else if (btn == _number5) {
                _numberA += "5";
            } else if (btn == _number6) {
                _numberA += "6";
            } else if (btn == _number7) {
                _numberA += "7";
            } else if (btn == _number8) {
                _numberA += "8";
            } else if (btn == _number9) {
                _numberA += "9";
            } else if (btn == _opDot) {
                _numberA += ".";
            } else if (btn == _opClear) {
                _numberA = "";
                _numberB = "";
                _state = CalcStateNumber;
            } else if (btn == _opPlus) {
                _state = CalcStateOp;
                _numberB = _numberA;
            } else {
                return;
            }
        
            _number->setText(_numberA);
        }
        
//        if (_state == CalcStateOp) {
//            if (btn == _opPlus) {
//                _calcEnd = _numberA + _numberB;
//            } else if (btn == _opMinus) {
//                _calcEnd = _numberA - _numberB;
//            } else if (btn == _opMul) {
//                _calcEnd = _numberA * _numberB;
//            } else if (btn == _opDivision) {
//                _calcEnd = _numberA / _numberB;
//            } else if (btn == _opDot) {
//
//            } else if (btn == _opEnd) {
//                num();
//            }
//
//        }
        
    }
    
}
