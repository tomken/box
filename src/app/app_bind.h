
#ifndef __APP_BIND_H__
#define __APP_BIND_H__

namespace app {
    
    template <typename Signature>
    struct FunctionTraits {
        typedef Signature ParamType;
    };

    template <typename RetType>
    struct FunctionTraits<RetType()> {
        typedef RetType (&ParamType)();
    };

    // arg 0
    template <typename R>
    class Invoke0 {
    public:
        virtual R invoke() = 0;
        virtual void apply(void* thiz) = 0;
        virtual Invoke0* clone() = 0;
        virtual ~Invoke0() {;}
    };
    
    template <typename R, typename T>
    class Function0 : public Invoke0<R> {
    public:
        Function0(const T& func) : _func(func) {;}
        void apply(void* thiz) {;}
        R invoke() { return _func(); }
        Invoke0<R>* clone() { return new Function0<R, T>(_func); }

    private:
        T _func;
    };
    
    template <typename R, typename T>
    class Member0 : public Invoke0<R> {
    public:
        Member0(T* thiz, R(T::*func)()) : _thiz(thiz), _func(func) {;}
        void apply(void* thiz) { _thiz = (T*)thiz; }
        R invoke() { return (_thiz->*_func)(); }
        Invoke0<R>* clone() { return new Member0<R, T>(_thiz, _func); }

    private:
        T* _thiz;
        R (T::*_func)();
    };
    
    // arg 1
    template <typename R, typename A1>
    class Invoke1 {
    public:
        virtual R invoke(A1) = 0;
        virtual void apply(void* thiz) = 0;
        virtual Invoke1* clone() = 0;
        virtual ~Invoke1() {;}
    };
    
    template <typename R, typename T, typename A1>
    class Function1 : public Invoke1<R, A1> {
    public:
        Function1(const T& func) : _func(func) {;}
        R invoke(A1 a1) { return (*_func)(a1); }
        void apply(void* thiz) {;}
        Invoke1<R, A1>* clone() { return new Function1<R, T, A1>(_func); }

    private:
        T _func;
    };

    template <typename R, typename T, typename A>
    class Member1 : public Invoke1<R, A> {
    public:
        Member1(T* thiz, R(T::*func)(A)) : _thiz(thiz), _func(func) {;}
        void apply(void* thiz) { _thiz = (T*)thiz; }
        R invoke(A a) { return (_thiz->*_func)(a); }
        Invoke1<R, A>* clone() { return new Member1<R, T, A>(_thiz, _func); }

    private:
        T* _thiz;
        R (T::*_func)(A);
    };
    
    // arg 2
    template <typename R, typename A1, typename A2>
    class Invoke2 {
    public:
        virtual R invoke(A1, A2) = 0;
        virtual void apply(void* thiz) = 0;
        virtual Invoke2* clone() = 0;
        virtual ~Invoke2() {;}
    };
    
    template <typename R, typename T, typename A1, typename A2>
    class Function2 : public Invoke2<R, A1, A2> {
    public:
        Function2(const T& func) : _func(func) {;}
        R invoke(A1 a1, A2 a2) { return _func(a1, a2); }
        void apply(void* thiz) {;}
        Invoke2<R, A1, A2>* clone() { return new Function2<R, T, A1, A2>(_func); }

    private:
        T _func;
    };

    template <typename R, typename T, typename A1, typename A2>
    class Member2 : public Invoke2<R, A1, A2> {
    public:
        Member2(T* thiz, R(T::*func)(A1, A2)) : _thiz(thiz), _func(func) {;}
        R invoke(A1 a1, A2 a2) { return (_thiz->*_func)(a1, a2); }
        void apply(void* thiz) { _thiz = (T*)thiz; }
        Invoke2<R, A1, A2>* clone() { return new Member2<R, T, A1, A2>(_thiz, _func); }

    private:
        T* _thiz;
        R (T::*_func)(A1, A2);
    };

    template <typename Signature>
    class Callable;

    template <typename R>
    class Callable<R()> {
    public:
        Callable() : _func(0) {}
        
        Callable(const Callable& other) {
            if (!other.isNull()) {
                _func = other._func->clone();
            }
        }
        
        Callable& operator=(const Callable& other) {
            if (!other.isNull()) {
                _func = other._func->clone();
            }
            return *this;
        }
        
        template <typename T>
        Callable(const T& func) : _func(new Function0<R, typename FunctionTraits<T>::ParamType>(func)) {}
        
        template <typename T>
        Callable(R(T::*func)(), T* obj) : _func(new Member0<R, T>(obj, func)) {;}

        R operator()() { return _func->invoke(); }
        Callable& apply(void* thiz) { _func->apply(thiz); return *this; }
        
        bool isNull() const { return !_func; }

    private:
        Invoke0<R>*  _func;
    };

    template <typename R, typename A1>
    class Callable<R(A1)> {
    public:
        Callable() : _func(0) {}
        
        Callable(const Callable& other) {
            if (!other.isNull()) {
                _func = other._func->clone();
            }
        }
        
        Callable& operator=(const Callable& other) {
            if (!other.isNull()) {
                _func = other._func->clone();
            }
            return *this;
        }

        template <typename T>
        Callable(const T& func) : _func(new Function1<R, typename FunctionTraits<T>::ParamType, A1>(func)) {}

        template <typename T>
        Callable(R(T::*func)(A1), T* obj) : _func(new Member1<R, T, A1>(obj, func)) {}

        ~Callable() { delete _func; }

        bool isNull() const { return !_func; }
        bool isGood() const { return _func; }

        R operator()(A1 a1) { return _func->invoke(a1); }
        Callable& apply(void* thiz) { _func->apply(thiz); return *this; }

    private:
        Invoke1<R, A1>*  _func;
    };
    
    template <typename R, typename A1, typename A2>
    class Callable<R(A1, A2)> {
    public:
        Callable() : _func(0) {}
        
        Callable(const Callable& other) {
            if (!other.isNull()) {
                _func = other._func->clone();
            }
        }
        
        Callable& operator=(const Callable& other) {
            if (!other.isNull()) {
                _func = other._func->clone();
            }
            return *this;
        }

        template <typename T>
        Callable(const T& func) : _func(new Function2<R,
                                        typename FunctionTraits<T>::ParamType,
                                        typename FunctionTraits<A1>::ParamType,
                                        typename FunctionTraits<A2>::ParamType>(func)) {}

        template <typename T>
        Callable(R(T::*func)(A1, A2), T* obj) : _func(new Member2<R, T, A1, A2>(obj, func)) {}
        
        ~Callable() { delete _func; }

        bool isNull() const { return !_func; }

        R operator()(A1 a1, A2 a2) { return _func->invoke(a1, a2); }
        Callable& apply(void* thiz) { _func->apply(thiz); return *this; }

    private:
        Invoke2<R, A1, A2>*  _func;
    };
    
    // for function args
    template <typename R>
    Callable<R()> bind(R(*f)()) {
        return Callable<R()>(f);
    }
    
    template <typename R, typename A1>
    Callable<R(A1)> bind(R(*f)(A1)) {
        return Callable<R(A1)>(f);
    }
    
    template <typename R, typename A1, typename A2>
    Callable<R(A1, A2)> bind(R(*f)(A1, A2)) {
        return Callable<R(A1, A2)>(f);
    }
    
    template <typename R, typename A1, typename A2, typename A3>
    Callable<R(A1, A2, A3)> bind(R(*f)(A1, A2, A3)) {
        return Callable<R(A1, A2, A3)>(f);
    }
    
    // for class member args
    template <typename R, typename T, typename S>
    Callable<R()> bind(R(T::*f)(), S s) {
        return Callable<R()>(f, s);
    }
    
    template <typename R, typename T, typename S, typename A1>
    Callable<R(A1)> bind(R(T::*f)(A1), S s) {
        return Callable<R(A1)>(f, s);
    }
    
    template <typename R, typename T, typename S, typename A1, typename A2>
    Callable<R(A1, A2)> bind(R(T::*f)(A1, A2), S s) {
        return Callable<R(A1, A2)>(f, s);
    }
    
}

#endif // __APP_BIND_H__
