#ifndef __TASKONE_H__
#define __TASKONE_H__

#include "app/app.h"

using namespace app;

namespace app {
    
    class Task1 : public Scene {
    public:
        Task1();
        ~Task1();
        
    private:
        virtual void onEnter();
        
    private:
        void onBackClick(Button* btn);
        void onClick(Button* btn);
        
        void num();
        void initButtons();
        void initBackground();
    
    private:
        Button*     _number0;
        Button*     _number1;
        Button*     _number2;
        Button*     _number3;
        Button*     _number4;
        Button*     _number5;
        Button*     _number6;
        Button*     _number7;
        Button*     _number8;
        Button*     _number9;
        
        Button*     _opPlus;
        Button*     _opMinus;
        Button*     _opMul;
        Button*     _opDivision;
        Button*     _opDot;
        Button*     _opCalc;
        Button*     _opClear;
        Button*     _opEnd;
        
        Layer*      _layer;
        Layer*      _num;
        
        Label*      _number;
        
        ImageButton*     _back;
        
        bool             _hadNum;
        
        std::string      _numberA;
        std::string      _numberB;
        double      _calcEnd;
        
        enum CalcState {
            CalcStateNumber,
            CalcStateOp,
        };
        CalcState    _state;
        
    };
}

#endif // __TASK1_H__
