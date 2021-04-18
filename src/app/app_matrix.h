
#ifndef __APP_MATRIX_H__
#define __APP_MATRIX_H__

#include <stdint.h>

namespace app {
    
    template <typename N>
    class Vector2 {
    public:
        union { float x; float w; };
        union { float y; float h; };
        
    public:
        Vector2() : x(0), y(0) {}
        Vector2(float nx, float ny) : x(nx), y(ny) {}

        void set(float nx, float ny) {
            x = nx; y = ny;
        }

        float dot(const Vector2& v) {
            return x * v.x + y * v.y;
        }

        float length() const {
            return sqrtf(x * x + y * y);
        }

        const Vector2& normalize() {
            if ( this->length() == 0 ) return *this;

            float n = 1 / this->length();
            x *= n; y *= n;
            return *this;
        }
    };
    
    /* + */
    template <typename N>
    inline Vector2<N> operator + (const Vector2<N> &v1, const Vector2<N> &v2) { return Vector2<N>(v1.x + v2.x, v1.y + v2.y); }
    
    template <typename N>
    inline Vector2<N> operator + (float s, const Vector2<N> &v) { return Vector2<N>(v.x + s, v.y + s); }
    
    template <typename N>
    inline Vector2<N> operator + (const Vector2<N> &v, float s) { return Vector2<N>(v.x + s, v.y + s); }

    /* - */
    template <typename N>
    inline Vector2<N> operator - (const Vector2<N> &v1, const Vector2<N> &v2) { return Vector2<N>(v1.x - v2.x, v1.y - v2.y); }
    
    template <typename N>
    inline Vector2<N> operator - (float s, const Vector2<N> &v) { return Vector2<N>(s - v.x, s - v.y); }
    
    template <typename N>
    inline Vector2<N> operator - (const Vector2<N> &v, float s) { return Vector2<N>(v.x - s, v.y - s); }

    /* * */
    template <typename N>
    inline Vector2<N> operator * (const Vector2<N> &v1, const Vector2<N> &v2) { return Vector2<N>(v1.x * v2.x, v1.y * v2.y); }
    
    template <typename N>
    inline Vector2<N> operator * (float s, const Vector2<N> &v) { return Vector2<N>(v.x * s, v.y * s); }
    
    template <typename N>
    inline Vector2<N> operator * (const Vector2<N> &v, float s) { return Vector2<N>(v.x * s, v.y * s); }

    /* / */
    template <typename N>
    inline Vector2<N> operator / (const Vector2<N> &v1, const Vector2<N> &v2) { return Vector2<N>(v1.x / v2.x, v1.y / v2.y); }
    
    template <typename N>
    inline Vector2<N> operator / (float s, const Vector2<N> &v) { return Vector2<N>(s / v.x, s / v.y); }
    
    template <typename N>
    inline Vector2<N> operator / (const Vector2<N> &v, float s) { return Vector2<N>(v.x / s, v.y / s); }

    
    /**
     * @brief   3D Vector
     */
    template<typename N>
    class Vector3
    {
    public:
        typedef N Type;
        
    public:
        Vector3() :x(N(0)), y(N(0)), z(N(0)){}
        
        Vector3(N a, N b, N c) : x(a), y(b), z(c){}
        Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z){}
        
        template<typename V>
        Vector3(const V& v):x(N(v.x)),y(N(v.y)),z(N(v.z)){}
        
    public:
        template<typename V>
        Vector3& operator = (const V& v)
        {
            x = N(v.x);
            y = N(v.y);
            z = N(v.z);
            return *this;
        }
        
        Vector3& operator += (const Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        
        Vector3& operator -= (const Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        
        Vector3& operator *= (N s)
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        
        Vector3& operator /= (N s)
        {
            s = N(1) / s;
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }
        
        Vector3 operator + () const
        {
            return *this;
        }
        
        Vector3 operator - () const
        {
            return Vector3(-x, -y, -z);
        }
        
        Vector3 operator + (const Vector3& v) const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }
        
        Vector3 operator - (const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }
        
        Vector3 operator * (N s) const
        {
            return Vector3<N>(x * s, y * s, z * s);
        }
        
        Vector3 operator / (N s) const
        {
            s = N(1) / s;
            return Vector3<N>(x * s, y * s, z * s);
        }
        
        bool operator == (const Vector3& v) const
        {
//            return (asl::Math<N>::equal(x, v.x)) && (asl::Math<N>::equal(y, v.y)) && (asl::Math<N>::equal(z, v.z));
        }
        
        bool operator != (const Vector3& v) const
        {
//            return (!asl::Math<N>::equal(x, v.x)) || (!asl::Math<N>::equal(y, v.y)) || (!asl::Math<N>::equal(z, v.z));
        }
        
        bool operator > (const Vector3& v) const
        {
            return (x > v.x && y > v.y && z > v.z);
        }
        
        bool operator < (const Vector3& v) const
        {
            return (x < v.x && y < v.y && z < v.z);
        }
        
        operator N* () {
            return &x;
        }
        
        operator const N* () const
        {
            return &x;
        }
        
        friend Vector3 operator * ( N scalar, const Vector3& vec )
        {
            return Vector3(scalar * vec.x, scalar * vec.y, scalar * vec.z);
        }
        
    public:
        void Set(N xx = 0, N yy = 0, N zz = 0)
        {
            x = xx;
            y = yy;
            z = zz;
        }
        void Negate()
        {
            x = -x;
            y = -y;
            z = -z;
        }
        
        /**
         * @brief   标准化此向量
         */
        N Normalize(void)
        {
            N len = LengthSquare();
            // TODO
//            if (len > asl::g_tolerance)
//            {
//                len = asl::Math<N>::sqrt_(len);
//                N recip_len = 1.0 / len;
//                x *= recip_len;
//                y *= recip_len;
//                z *= recip_len;
//            }
            return len;
        }
        
        /**
         * @brief   取长度
         * @return  返回 向量长度
         */
        N Length(void) const
        {
            // return asl::Math<N>::sqrt_(x * x + y * y + z * z);
        }
        
        /**
         * @brief   取向量长度的平方
         * @return  返回 向量长度的平方
         */
        N LengthSquare(void) const
        {
            return x * x + y * y + z * z;
        }
        
        /**
         * @brief   向量点乘
         * @param   vec       向量
         * @return  返回 向量点乘值
         */
        N Dot( const Vector3& vec ) const
        {
            return vec.x * x + vec.y * y + vec.z * z;
        }
        
        /**
         * @brief   向量叉乘
         * @param   vec       向量
         * @return  返回 叉乘后向量
         */
        Vector3 Cross( const Vector3& vec ) const
        {
            return Vector3(    y * vec.z - z * vec.y,
                           z * vec.x - x * vec.z,
                           x * vec.y - y * vec.x);
        }
        
    public:
        static const Vector3& Zero()
        {
            static Vector3 s_zero(0, 0, 0);
            return s_zero;
        }
        
        static const Vector3& Unit_X()
        {
            static Vector3 s_unit_x(1, 0, 0);
            return s_unit_x;
        }
        
        static const Vector3& Unit_Y()
        {
            static Vector3 s_unit_y(0, 1, 0);
            return s_unit_y;
        }
        
        static const Vector3& Unit_Z()
        {
            static Vector3 s_unit_z(0, 0, 1);
            return s_unit_z;
        }
        
        /**
         * @brief   标准化
         * @param   vec       向量
         * @return  返回 标准化后的向量
         */
        static Vector3 Normalize( const Vector3& vec )
        {
            N len = vec.LengthSquare();
//            if (len > asl::g_tolerance)
//            {
//                len = asl::Math<N>::recip_sqrt_(len);
//                return Vector3(vec.x * len, vec.y * len, vec.z * len);
//            }
            return vec;
        }
        
        /**
         * @brief   Length
         * @param   vec       向量
         * @return  返回 向量的长度
         */
        static N Length( const Vector3& vec )
        {
//            return asl::Math<N>::sqrt_(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
        }
        
        /**
         * @brief   LengthSquare
         * @param   vec       向量
         * @return  返回 向量的平方
         */
        static N LengthSquare(const Vector3& v)
        {
            return v.x * v.x + v.y * v.y + v.z * v.z;
        }
        
        /**
         * @brief   Dot
         * @param   vec1       向量
         * @param   vec2       向量
         * @return  返回 向量的点积
         */
        template<typename N1,typename N2>
        static N Dot( const Vector3<N1>& vec1, const Vector3<N2>& vec2 )
        {
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        }
        
        /**
         * @brief   Cross
         * @param   vec1       向量
         * @param   vec2       向量
         * @return  返回 叉乘后的向量
         */
        template<typename N1, typename N2>
        static Vector3 Cross( const Vector3<N1>& vec1, const Vector3<N2>& vec2 )
        {
            return Vector3(    vec1.y * vec2.z - vec1.z * vec2.y,
                           vec1.z * vec2.x - vec1.x * vec2.z,
                           vec1.x * vec2.y - vec1.y * vec2.x);
        }
        
    public:
        N x, y, z;
    };
    
    template<typename Real>
    class Vector4
    {
    public:
        typedef Real Type;
    public:
        Vector4() : x(0), y(0), z(0), w(0) {}

        Vector4(Real a, Real b, Real c, Real d) : x(a), y(b), z(c), w(d) {}

        Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
        
    public:
        Vector4& operator = (Real v[4])
        {
            this->x = v[0];
            this->y = v[1];
            this->z = v[2];
            this->w = v[3];
            return *this;
        }
        
        template<typename V>
        Vector4& operator = (const V& v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = v.w;
            return *this;
        }
        
        Vector4 operator + (const Vector4& v) const
        {
            return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
        }
        
        Vector4 operator - (const Vector4& v) const
        {
            return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
        }
        
        bool operator == (const Vector4& v) const
        {
//            return 0 == memcmp(this, &matx, sizeof(AppMatrix<N>));
            return !(this != v);
        }
        
        bool operator != (const Vector4& v) const
        {
//            (!Math<Real>::equal(this->x, v.x)) ||
//                   (!Math<Real>::equal(this->y, v.y)) ||
//                   (!Math<Real>::equal(this->z, v.z)) ||
//                   (!Math<Real>::equal(this->w, v.w));
        }
        
        Vector4 operator * (Real s) const
        {
            return Vector4(this->x * s, this->y * s, this->z * s, this->w * s);
        }
        
        bool operator<=(Vector4 const& vec) const
        {
            return this->x <= vec.x;
        }
        
        bool operator>=(Vector4 const& vec) const
        {
            return this->x >= vec.x;
        }

    public:
        operator Real* () {
            return &this->x;
        }

        operator const Real* () const {
            return &this->x;
        }

    public:
        void Set(Real xx, Real yy, Real zz, Real ww) {
            this->x = xx;
            this->y = yy;
            this->z = zz;
            this->w = ww;
        }
        
    public:
        static Vector4 Zero()
        {
            Vector4 v;
            v.MakeZero();
            return v;
        }
        
        static Vector4 Ones()
        {
            Vector4 v;
            v.MakeOnes();
            return v;
        }
        
        static Vector4 Unit(int d)
        {
            Vector4 v;
            v.MakeUnit(d);
            return v;
        }
        
    public:
        Real x, y, z, w;
    };
    
    /**
     * @brief 定义矩阵模板类的接口
     */
    template<typename N>
    class AppMatrix
    {
    public:
        typedef N Type;
        
        enum Axis{
            axisX = 0,
            axisY,
            axisZ
        };
        
    public:
        /**
         * @brief   默认构造函数
         */
        AppMatrix()
        : m11(1), m12(0), m13(0), m14(0)
        , m21(0), m22(1), m23(0), m24(0)
        , m31(0), m32(0), m33(1), m34(0)
        , m41(0), m42(0), m43(0), m44(1) {
        }
        
        /**
         * @brief   拷贝构造函数
         */
        template<typename M>
        AppMatrix(const AppMatrix<M> mat)
        : m11((N)mat.m11), m12((N)mat.m12), m13((N)mat.m13), m14((N)mat.m14)
        , m21((N)mat.m21), m22((N)mat.m22), m23((N)mat.m23), m24((N)mat.m24)
        , m31((N)mat.m31), m32((N)mat.m32), m33((N)mat.m33), m34((N)mat.m34)
        , m41((N)mat.m41), m42((N)mat.m42), m43((N)mat.m43), m44((N)mat.m44) {
        }
        
        /**
         * @brief   构造函数
         */
        AppMatrix(const N* s) {
            memcpy(&m11, s, sizeof(AppMatrix<N>));
        }
        
        /**
         * @brief   构造函数
         */
        AppMatrix(N f11, N f12, N f13, N f14,
                  N f21, N f22, N f23, N f24,
                  N f31, N f32, N f33, N f34,
                  N f41, N f42, N f43, N f44)
        : m11(f11), m12(f12), m13(f13), m14(f14)
        , m21(f21), m22(f22), m23(f23), m24(f24)
        , m31(f31), m32(f32), m33(f33), m34(f34)
        , m41(f41), m42(f42), m43(f43), m44(f44) {
        }
    public:
        /**
         * @brief 赋值操作符
         * @param matrix 需要拷贝的矩阵
         * @return  拷贝后的矩阵
         */
        template<typename T>
        AppMatrix& operator = (const AppMatrix<T>& matrix) {
            m11 = (N)matrix.m11; m12 = (N)matrix.m12; m13 = (N)matrix.m13; m14 = (N)matrix.m14;
            m21 = (N)matrix.m21; m22 = (N)matrix.m22; m23 = (N)matrix.m23; m24 = (N)matrix.m24;
            m31 = (N)matrix.m31; m32 = (N)matrix.m32; m33 = (N)matrix.m33; m34 = (N)matrix.m34;
            m41 = (N)matrix.m41; m42 = (N)matrix.m42; m43 = (N)matrix.m43; m44 = (N)matrix.m44;
            return *this;
        }
        
        /**
         * @brief 判断矩阵是否相等
         * @param matx 需要比较的矩阵
         * @return  true为相等，false为不相等
         */
        bool operator == (const AppMatrix& matx) const {
            return 0 == memcmp(this, &matx, sizeof(AppMatrix<N>));
        }
        
        /**
         * @brief 判断矩阵是否不相等
         * @param matx 需要比较的矩阵
         * @return  true为不相等，false为相等
         */
        bool operator != (const AppMatrix& matx) const {
            return !(operator == (matx));
        }
        
        /**
         * @brief 矩阵元素乘
         * @param s 系数
         * @return  乘后的矩阵
         */
        AppMatrix<N> operator * (N s) const {
            return AppMatrix<N>(
                                m11 * s, m12 * s, m13 * s, m14 * s,
                                m21 * s, m22 * s, m23 * s, m24 * s,
                                m31 * s, m32 * s, m33 * s, m34 * s,
                                m41 * s, m42 * s, m43 * s, m44 * s);
        }
        
        /**
         * @brief 计算与另一个矩阵相乘
         * @param mat 参与计算的矩阵
         * @return  相乘后的矩阵
         */
        AppMatrix operator * (const AppMatrix& matx) const {
            AppMatrix mat_ret;
            for (int32_t row = 0; row < 4; ++row)
            {
                for (int32_t col = 0; col < 4; ++col)
                {
                    mat_ret.m[row][col] = N(0);
                    for (int32_t mid = 0; mid < 4; mid++)
                    {
                        mat_ret.m[row][col] += m[row][mid] * matx.m[mid][col];
                    }
                }
            }
            return mat_ret;
        }
        
        /**
         * @brief 计算与另一个矩阵相加，并赋值
         * @param mat 参与计算的矩阵
         * @return  计算后的矩阵
         */
        AppMatrix& operator += (const AppMatrix& mat) {
            m11 += mat.m11; m12 += mat.m12; m13 += mat.m13; m14 += mat.m14;
            m21 += mat.m21; m22 += mat.m22; m23 += mat.m23; m24 += mat.m24;
            m31 += mat.m31; m32 += mat.m32; m33 += mat.m33; m34 += mat.m34;
            m41 += mat.m41; m42 += mat.m42; m43 += mat.m43; m44 += mat.m44;
            return *this;
        }
        
        /**
         * @brief 计算与另一个矩阵相减，并赋值
         * @param mat 参与计算的矩阵
         * @return  计算后的矩阵
         */
        AppMatrix& operator -= (const AppMatrix& mat) {
            m11 -= mat.m11; m12 -= mat.m12; m13 -= mat.m13; m14 -= mat.m14;
            m21 -= mat.m21; m22 -= mat.m22; m23 -= mat.m23; m24 -= mat.m24;
            m31 -= mat.m31; m32 -= mat.m32; m33 -= mat.m33; m34 -= mat.m34;
            m41 -= mat.m41; m42 -= mat.m42; m43 -= mat.m43; m44 -= mat.m44;
            return *this;
        }
        
        /**
         * @brief 计算矩阵元素乘，并赋值
         * @param s 系数
         * @return  乘后的矩阵
         */
        AppMatrix& operator *= (N s) {
            m11 *= s; m12 *= s; m13 *= s; m14 *= s;
            m21 *= s; m22 *= s; m23 *= s; m24 *= s;
            m31 *= s; m32 *= s; m33 *= s; m34 *= s;
            m41 *= s; m42 *= s; m43 *= s; m44 *= s;
            return *this;
        }
        
        /**
         * @brief 矩阵元素除
         * @param s 系数
         * @return  除后的矩阵
         */
        AppMatrix& operator /= (N s) {
            s = N(1) / s;
            return operator*=(s);
        }
        
        /**
         * @brief   计算与另外一个矩阵的和
         * @param   mat1 mat1
         * @return  返回计算后的矩阵
         */
        AppMatrix<N> operator + (const AppMatrix<N>& mat1) {
            return AppMatrix<N>(
                                mat1.m11 + m11, mat1.m12 + m12, mat1.m13 + m13, mat1.m14 + m14,
                                mat1.m21 + m21, mat1.m22 + m22, mat1.m23 + m23, mat1.m24 + m24,
                                mat1.m31 + m31, mat1.m32 + m32, mat1.m33 + m33, mat1.m34 + m34,
                                mat1.m41 + m41, mat1.m42 + m42, mat1.m43 + m43, mat1.m44 + m44);
        }
        
        /**
         * @brief   计算与另外一个矩阵的差值
         * @param   mat2 mat2
         * @return  返回计算后的矩阵
         */
        AppMatrix<N> operator - (const AppMatrix<N>& mat2) {
            return AppMatrix<N>(
                                m11 - mat2.m11, m12 - mat2.m12, m13 - mat2.m13, m14 - mat2.m14,
                                m21 - mat2.m21, m22 - mat2.m22, m23 - mat2.m23, m24 - mat2.m24,
                                m31 - mat2.m31, m32 - mat2.m32, m33 - mat2.m33, m34 - mat2.m34,
                                m41 - mat2.m41, m42 - mat2.m42, m43 - mat2.m43, m44 - mat2.m44);
        }
        
        /**
         * @brief   获取第row行,col列的值
         * @param   row       行号
         * @param   col       列号
         * @return  返回第row行,col列的值
         */
        N& operator () (uint32_t row, uint32_t col) {
            // Gassert(row < 4 && col < 4);
            return m[row][col];
        }
        
        /**
         * @brief   获取第row行,col列的值
         * @param   row       行号
         * @param   col       列号
         * @return  返回第row行,col列的值
         */
        N operator () (uint32_t row, uint32_t col) const {
            // Gassert(row < 4 && col < 4);
            return m[row][col];
        }
        
        /**
         * @brief 返回矩阵的内存指针
         * @return  返回矩阵的内存指针
         */
        operator N* () {
            return &m11;
        }
        
        /**
         * @brief 返回矩阵的内存指针
         * @return  返回矩阵的内存指针
         */
        operator const N* () const {
            return &m11;
        }
        
        /**
         * @brief   获取第row行,col列的矩阵序号
         * @param   row       行号
         * @param   col       列号
         * @return  返回 序号
         */
        int32_t I(int32_t row, int32_t col) {
            // Gassert(0 <= row && row < 4 && 0 <= col && col < 4);
            return col + row * 4;
        }
        
        /**
         * @brief   把当前矩阵设置为单位矩阵
         */
        void Normalize() {
            m12 = m13 = m14 = N(0);
            m21 = m23 = m24 = N(0);
            m31 = m32 = m34 = N(0);
            m41 = m42 = m43 = N(0);
            m11 = m22 = m33 = m44 = N(1);
        }
        
    public:
        
        /**
         * @brief   构建旋转矩阵,绕x轴旋转
         * @param   radian_value       弧度
         * @return  返回 AppMatrix:矩阵
         */
        static AppMatrix RotateAxisX(N radian_value) {
//            if (asl::Math<N>::abs_(radian_value) < asl::g_tolerance)
//            {
//                return AppMatrix<N>::Identity();
//            }
            N s, c;
//            asl::Math<N>::sincos_(s, c, radian_value);
            return AppMatrix<N>(
                                (N)1, (N)0, (N)0, (N)0,
                                (N)0, (N)c, (N)s, (N)0,
                                (N)0, (N)-s, (N)c, (N)0,
                                (N)0, (N)0, (N)0, (N)1);
        }
        
        /**
         * @brief   构建旋转矩阵,绕y轴旋转
         * @param   radian_value       弧度
         * @return  返回 AppMatrix:矩阵
         */
        static AppMatrix RotateAxisY(N radian_value) {
//            if (asl::Math<N>::abs_(radian_value) < asl::g_tolerance)
//            {
//                return AppMatrix<N>::Identity();
//            }
            N s, c;
//            asl::Math<N>::sincos_(s, c, radian_value);
            return AppMatrix<N>(
                                (N)c, (N)0, (N)s, (N)0,
                                (N)0, (N)1, (N)0, (N)0,
                                (N)-s, (N)0, (N)c, (N)0,
                                (N)0, (N)0, (N)0, (N)1);
        }
        
        /**
         * @brief   构建旋转矩阵,绕z轴旋转
         * @param   radian_value       弧度
         * @return  返回 AppMatrix:矩阵
         */
        static AppMatrix RotateAxisZ(N radian_value) {
//            if (asl::Math<N>::abs_(radian_value) < asl::g_tolerance)
//            {
//                return AppMatrix<N>::Identity();
//            }
            N s, c;
//            asl::Math<N>::sincos_(s, c, radian_value);
            return AppMatrix<N>(
                                (N)c, (N)s, (N)0, (N)0,
                                (N)-s, (N)c, (N)0, (N)0,
                                (N)0, (N)0, (N)1, (N)0,
                                (N)0, (N)0, (N)0, (N)1);
        }
        
        /**
         * @brief   构建平移矩阵
         * @param   x       x方向平移分量
         * @param   y       y方向平移分量
         * @param   z       z方向平移分量
         * @return  返回 AppMatrix:矩阵
         */
        static AppMatrix Translation(N x, N y, N z) {
            return AppMatrix<N>(
                                (N)1, (N)0, (N)0, (N)0,
                                (N)0, (N)1, (N)0, (N)0,
                                (N)0, (N)0, (N)1, (N)0,
                                (N)x, (N)y, (N)z, (N)1);
        }
        
        /**
         * @brief   构建缩放矩阵
         * @param   x       x方向缩放分量
         * @param   y       y方向缩放分量
         * @param   z       z方向缩放分量
         * @return  返回 AppMatrix:矩阵
         */
        static AppMatrix Scaling(N x, N y, N z) {
            return AppMatrix<N>(
                                (N)x, (N)0, (N)0, (N)0,
                                (N)0, (N)y, (N)0, (N)0,
                                (N)0, (N)0, (N)z, (N)0,
                                (N)0, (N)0, (N)0, (N)1);
        }
        
        /**
         * @brief   构建倾斜矩阵
         * @param   x       x方向倾斜弧度
         * @param   y       y方向倾斜弧度
         * @return  返回 AppMatrix:矩阵
         */
        static AppMatrix Skewing(N x, N y) {
//            return AppMatrix<N>(
//                                  (N)1, (N)asl::Math<N>::tan_(y), (N)0, (N)0,
//                                  (N)asl::Math<N>::tan_(x), (N)1, (N)0, (N)0,
//                                  (N)0, (N)0, (N)1, (N)0,
//                                  (N)0, (N)0, (N)0, (N)1);
        }
        
        /**
         * @brief   矩阵的逆
         * @param   mat       源矩阵
         * @return  返回 AppMatrix:逆矩阵
         */
        static AppMatrix Inverse(const AppMatrix<N>& mat) {
            N a0 = mat.mat[0] * mat.mat[5] - mat.mat[1] * mat.mat[4];
            N a1 = mat.mat[0] * mat.mat[6] - mat.mat[2] * mat.mat[4];
            N a2 = mat.mat[0] * mat.mat[7] - mat.mat[3] * mat.mat[4];
            N a3 = mat.mat[1] * mat.mat[6] - mat.mat[2] * mat.mat[5];
            N a4 = mat.mat[1] * mat.mat[7] - mat.mat[3] * mat.mat[5];
            N a5 = mat.mat[2] * mat.mat[7] - mat.mat[3] * mat.mat[6];
            
            N b0 = mat.mat[8] * mat.mat[13] - mat.mat[9] * mat.mat[12];
            N b1 = mat.mat[8] * mat.mat[14] - mat.mat[10] * mat.mat[12];
            N b2 = mat.mat[8] * mat.mat[15] - mat.mat[11] * mat.mat[12];
            N b3 = mat.mat[9] * mat.mat[14] - mat.mat[10] * mat.mat[13];
            N b4 = mat.mat[9] * mat.mat[15] - mat.mat[11] * mat.mat[13];
            N b5 = mat.mat[10] * mat.mat[15] - mat.mat[11] * mat.mat[14];
            
            N det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
//            if (asl::Math<N>::abs_(det) <= asl::g_tolerance)
//            {
//                return AppMatrix<N>::Zero();
//            }
            
            AppMatrix mat_ret;
            mat_ret.mat[0] = +mat.mat[5] * b5 - mat.mat[6] * b4 + mat.mat[7] * b3;
            mat_ret.mat[4] = -mat.mat[4] * b5 + mat.mat[6] * b2 - mat.mat[7] * b1;
            mat_ret.mat[8] = +mat.mat[4] * b4 - mat.mat[5] * b2 + mat.mat[7] * b0;
            mat_ret.mat[12] = -mat.mat[4] * b3 + mat.mat[5] * b1 - mat.mat[6] * b0;
            mat_ret.mat[1] = -mat.mat[1] * b5 + mat.mat[2] * b4 - mat.mat[3] * b3;
            mat_ret.mat[5] = +mat.mat[0] * b5 - mat.mat[2] * b2 + mat.mat[3] * b1;
            mat_ret.mat[9] = -mat.mat[0] * b4 + mat.mat[1] * b2 - mat.mat[3] * b0;
            mat_ret.mat[13] = +mat.mat[0] * b3 - mat.mat[1] * b1 + mat.mat[2] * b0;
            mat_ret.mat[2] = +mat.mat[13] * a5 - mat.mat[14] * a4 + mat.mat[15] * a3;
            mat_ret.mat[6] = -mat.mat[12] * a5 + mat.mat[14] * a2 - mat.mat[15] * a1;
            mat_ret.mat[10] = +mat.mat[12] * a4 - mat.mat[13] * a2 + mat.mat[15] * a0;
            mat_ret.mat[14] = -mat.mat[12] * a3 + mat.mat[13] * a1 - mat.mat[14] * a0;
            mat_ret.mat[3] = -mat.mat[9] * a5 + mat.mat[10] * a4 - mat.mat[11] * a3;
            mat_ret.mat[7] = +mat.mat[8] * a5 - mat.mat[10] * a2 + mat.mat[11] * a1;
            mat_ret.mat[11] = -mat.mat[8] * a4 + mat.mat[9] * a2 - mat.mat[11] * a0;
            mat_ret.mat[15] = +mat.mat[8] * a3 - mat.mat[9] * a1 + mat.mat[10] * a0;
            
            N inv_det = ((N)1.0) / det;
            for (int32_t row = 0; row < 4; row++) {
                for (int32_t col = 0; col < 4; col++) {
                    mat_ret.mat[(row << 2) + col] *= inv_det;
                }
            }
            
            return mat_ret;
        }
        
        
        static const AppMatrix& Identity()
        {
            static AppMatrix indentity(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);
            return indentity;
        }
        
        static const AppMatrix& Zero()
        {
            static AppMatrix zero(0, 0, 0, 0,
                                  0, 0, 0, 0,
                                  0, 0, 0, 0,
                                  0, 0, 0, 0);
            return zero;
        }
     
    public:
        
        /**
         * @brief   判断是否为单位矩阵
         */
        bool isIdentity() const {
            return *this == Identity();
        }
        
        /**
         * @brief   平移矩阵
         * @param   x, y, z 平移坐标
         */
        void translate(N x, N y, N z =0 ) {
            const AppMatrix& tempM = Translation(x, y, z);
            concat(tempM);
        }
        
        /**
         * @brief   缩放矩阵
         * @param   x, y, z 平移坐标， centerX，centerY，centerZ平移的锚点
         */
        void scale(N x, N y, N z = 1, N centerX = 0, N centerY =0, N centerZ = 0) {
            
            AppMatrixMultiply(*this, *this, Translation(-centerX, -centerY, -centerZ));
            
            const AppMatrix& tempM = Scaling(x, y, z);
            AppMatrixMultiply(*this, *this, tempM);
            
            AppMatrixMultiply(*this, *this, Translation(centerX, centerY, centerZ));
        }
        
        /**
         * @brief   旋转矩阵
         * @param   angle， 旋转角度， axis 旋转绕轴
         */
        void rotate(N angle, Axis axis = axisZ) {
            const AppMatrix& tempM = getRotateMatrix(angle, axis);
            concat(tempM);
        }
        
        /**
         * @brief   旋转矩阵
         * @param   angle旋转角度， axis 旋转绕轴， x，y，z旋转的锚点
         */
        void rotate(N angle, N x, N y, N z = 0, Axis axis = axisZ) {
            *this = AppMatrixMultiply(*this, Translation(-x, -y, -z));
            if (axis == axisZ){
                const AppMatrix& tempM = getRotateMatrix(angle, axis);
                AppMatrixMultiply(*this, *this, tempM);
            } else {
                N V13 = 0;
                N V23 = 0;
                if (axis == axisY) {
                    V13 = tan(-angle);
                } else {
                    V23 = tan(-angle);
                }
                N tmpVal = 50;
                AppMatrix<N> tmp1(1, 0, V13, 0,
                                    0, 1, V23, 0,
                                    0, 0, 0, 0,
                                    0, 0, 0, 1);
                AppMatrix<N> tmp2(tmpVal, 0, 0, 0,
                                    0, tmpVal, 0, 0,
                                    0, 0, 1, 1,
                                    0, 0, 0, tmpVal);
                AppMatrixMultiply(*this, *this, tmp1);
                AppMatrixMultiply(*this, *this, tmp2);
            }
            AppMatrixMultiply(*this, *this, Translation(x, y, z));
        }
        
        /**
         * @brief   倾斜矩阵
         * @param   angleX x轴倾斜弧度，angleY y轴倾斜弧度 centerX，centerY 倾斜的锚点
         */
        void skew(N angleX, N angleY, N centerX = 0, N centerY = 0) {
            *this = AppMatrixMultiply(*this, Translation(-centerX, -centerY, 0));
            
            const AppMatrix& tempM = Skewing(angleX, angleY);
            concat(tempM);
            
            AppMatrixMultiply(*this, *this, Translation(centerX, centerY, 0));
        }

        /**
         * @brief   前乘矩阵
         * @param   t 前乘的矩阵
         */
        void concat(const AppMatrix& t) {
            AppMatrixMultiply(*this, t, *this);
        }
     
    private:
        AppMatrix getRotateMatrix(N angle, Axis axis) {
            switch (axis) {
                case axisX:
                    return RotateAxisX(angle);
                case axisY:
                    return RotateAxisY(angle);
                case axisZ:
                    return RotateAxisZ(angle);
                default:
                    return Identity();
            }
        }
        
    public:
        union{
            struct{
                N m11, m12, m13, m14;
                N m21, m22, m23, m24;
                N m31, m32, m33, m34;
                N m41, m42, m43, m44;
                
            };
            N m[4][4];
            N mat[16];
        };
    };
    
    //------------------------------------------------------------------------------
    typedef AppMatrix<float> AppMatrixf;
    typedef AppMatrix<double> AppMatrixd;
    
    //------------------------------------------------------------------------------
    
    /**
     * @brief   设置矩阵为单位矩阵
     * @param   mat       矩阵
     */
    template<typename M>
    inline void AppMatrixIdentity(M& mat) {
        mat = M::Identity();
    }
    
    /**
     * @brief   判断是否是单位矩阵
     * @param   mat       矩阵
     * @return  返回 true:是单位矩阵,false:不是单位矩阵
     */
    template<typename M>
    inline bool AppMatrixIsIdentity(const M& mat) {
        return mat == M::Identity();
    }
    
    /**
     * @brief   矩阵赋值
     * @param   m       矩阵
     * @param   mOut       赋值后的矩阵
     */
    template<typename M, typename M1>
    inline void AppMatrixAssign(M& mOut, const M1& m) {
        mOut.m11 = m.m11; mOut.m12 = m.m12; mOut.m13 = m.m13; mOut.m14 = m.m14;
        mOut.m21 = m.m21; mOut.m22 = m.m22; mOut.m23 = m.m23; mOut.m24 = m.m24;
        mOut.m31 = m.m31; mOut.m32 = m.m32; mOut.m33 = m.m33; mOut.m34 = m.m34;
        mOut.m41 = m.m41; mOut.m42 = m.m42; mOut.m43 = m.m43; mOut.m44 = m.m44;
    }
    
    /**
     * @brief   根据Vector4设置矩阵行
     * @param   v       Vector4
     * @param   n       矩阵第几行
     * @param   mOut       赋值后的矩阵
     */
    template<typename M, typename V>
    inline void AppMatrixSetRow(M& mOut, int32_t n, const V& v) {
        mOut.m[n][0] = v.x;
        mOut.m[n][1] = v.y;
        mOut.m[n][2] = v.z;
        mOut.m[n][3] = v.w;
    }
    
    /**
     * @brief   根据GVector4设置矩阵列
     * @param   v       Vector4
     * @param   n       矩阵第几列
     * @param   mOut       赋值后的矩阵
     */
    template<typename M, typename V>
    void AppMatrixSetCol(M& mOut, int32_t n, const V& v) {
        mOut.m[0][n] = v.x;
        mOut.m[1][n] = v.y;
        mOut.m[2][n] = v.z;
        mOut.m[3][n] = v.w;
    }
    
    /**
     * @brief   把传入的矩阵进行转置
     * @param   mOut       转置后的矩阵
     */
    template<typename M>
    inline void AppMatrixTranspose(M& mOut) {
        typename M::Type tmp;
        tmp = mOut.m12; mOut.m12 = mOut.m21; mOut.m21 = tmp;
        tmp = mOut.m13; mOut.m13 = mOut.m31; mOut.m31 = tmp;
        tmp = mOut.m14; mOut.m14 = mOut.m41; mOut.m41 = tmp;
        tmp = mOut.m23; mOut.m23 = mOut.m32; mOut.m32 = tmp;
        tmp = mOut.m24; mOut.m24 = mOut.m42; mOut.m42 = tmp;
        tmp = mOut.m34; mOut.m34 = mOut.m43; mOut.m43 = tmp;
    }
    
    /**
     * @brief   把传入的矩阵进行转置
     * @param   mat       源矩阵
     * @return  返回 转置后的矩阵
     */
    template<typename M>
    inline M AppMatrixTranspose(const M& mat) {
        return M(
                 mat.m11, mat.m21, mat.m31, mat.m41,
                 mat.m12, mat.m22, mat.m32, mat.m42,
                 mat.m13, mat.m23, mat.m33, mat.m34,
                 mat.m14, mat.m24, mat.m34, mat.m44);
    }
    
    /**
     * @brief   把传入的矩阵进行转置
     * @param   mat       源矩阵
     * @param   mOut       转置后的矩阵
     */
    template<typename M, typename M1>
    inline void AppMatrixTranspose(M& mOut, const M1& mat) {
        if (&mat == &mOut)
        {
            typename M::Type tmp;
            tmp = mOut.m12; mOut.m12 = mOut.m21; mOut.m21 = tmp;
            tmp = mOut.m13; mOut.m13 = mOut.m31; mOut.m31 = tmp;
            tmp = mOut.m14; mOut.m14 = mOut.m41; mOut.m41 = tmp;
            tmp = mOut.m23; mOut.m23 = mOut.m32; mOut.m32 = tmp;
            tmp = mOut.m24; mOut.m24 = mOut.m42; mOut.m42 = tmp;
            tmp = mOut.m34; mOut.m34 = mOut.m43; mOut.m43 = tmp;
        }
        else
        {
            mOut.m11 = mat.m11; mOut.m12 = mat.m21; mOut.m13 = mat.m31; mOut.m14 = mat.m41;
            mOut.m21 = mat.m12; mOut.m22 = mat.m22; mOut.m23 = mat.m32; mOut.m24 = mat.m42;
            mOut.m31 = mat.m13; mOut.m32 = mat.m23; mOut.m33 = mat.m33; mOut.m34 = mat.m43;
            mOut.m41 = mat.m14; mOut.m42 = mat.m24; mOut.m43 = mat.m34; mOut.m44 = mat.m44;
        }
    }
    
    /**
     * @brief   矩阵缩放
     * @param   x       x方向缩放系数
     * @param   y       y方向缩放系数
     * @param   z       z方向缩放系数
     * @param   mOut       缩放后的矩阵
     */
    template<typename M, typename N>
    inline void AppMatrixScaling(M& mOut, N x, N y, N z) {
        mOut.m12 = mOut.m13 = mOut.m14 = N(0);
        mOut.m21 = mOut.m23 = mOut.m24 = N(0);
        mOut.m31 = mOut.m32 = mOut.m34 = N(0);
        mOut.m41 = mOut.m42 = mOut.m43 = N(0);
        
        mOut.m11 = x;
        mOut.m22 = y;
        mOut.m33 = z;
        mOut.m44 = N(1);
    }
    
    /**
     * @brief   矩阵缩放
     * @param   x       x方向缩放系数
     * @param   y       y方向缩放系数
     * @param   z       z方向缩放系数
     * @return  返回 缩放系数的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixScaling(N x, N y, N z) {
        return AppMatrix<N>(
                            x, 0, 0, 0,
                            0, y, 0, 0,
                            0, 0, z, 0,
                            0, 0, 0, 1);
    }
    
    /**
     * @brief   矩阵平移
     * @param   x       x方向平移分量
     * @param   y       y方向平移分量
     * @param   z       z方向平移分量
     * @param   mOut       平移后的矩阵
     */
    template<typename M, typename N>
    inline void AppMatrixTranslation(M& mOut, N x, N y, N z) {
        mOut.m12 = mOut.m13 = mOut.m14 = N(0);
        mOut.m21 = mOut.m23 = mOut.m24 = N(0);
        mOut.m31 = mOut.m32 = mOut.m34 = N(0);
        mOut.m41 = x;
        mOut.m42 = y;
        mOut.m43 = z;
        mOut.m11 = mOut.m22 = mOut.m33 = mOut.m44 = N(1);
    }
    
    /**
     * @brief   矩阵平移
     * @param   x       x方向平移分量
     * @param   y       y方向平移分量
     * @param   z       z方向平移分量
     * @param   mOut       平移后的矩阵
     * @return  返回 平移后的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixTranslation(N x, N y, N z) {
        return AppMatrix<N>(
                            1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            x, y, z, 1);
    }
    
    /**
     * @brief   绕X轴旋转angle幅度
     * @param   mOut       旋转后的矩阵
     * @param   angle   旋转幅度
     */
    template<typename T, typename N>
    inline void AppMatrixRotationX(AppMatrix<T>& mOut, N angle) {
        T s = T(0);
        T c = T(1);
//        if (asl::Math<N>::abs_(angle) > asl::g_tolerance)
//        {
//            asl::Math<T>::sincos_(s, c, angle);
//        }
        
        mOut.m22 = c;
        mOut.m23 = s;
        mOut.m32 = -s;
        mOut.m33 = c;
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m24 = T(0);
        mOut.m31 = mOut.m34 = T(0);
        mOut.m41 = mOut.m42 = mOut.m43 = T(0);
        mOut.m11 = mOut.m44 = T(1);
    }
    
    /**
     * @brief   绕X轴旋转angle幅度
     * @param   angle   旋转幅度
     * @return  返回 旋转后的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixRotationX(N angle) {
        N s = N(0);
        N c = N(1);
//        if (asl::Math<N>::abs_(angle) > asl::g_tolerance)
//        {
//            asl::Math<N>::sincos_(s, c, angle);
//        }
        return AppMatrix<N>(
                            1, 0, 0, 0,
                            0, c, s, 0,
                            0, -s, c, 0,
                            0, 0, 0, 1);
    }
    
    /**
     * @brief   绕Y轴旋转angle幅度
     * @param   mOut     旋转后的矩阵
     * @param   angle   旋转幅度
     */
    template<typename T, typename N>
    inline void AppMatrixRotationY(AppMatrix<T>& mOut, N angle) {
        T s = T(0);
        T c = T(1);
//        if (asl::Math<N>::abs_(angle) > asl::g_tolerance)
//        {
//            asl::Math<T>::sincos_(s, c, angle);
//        }
        
        mOut.m11 = c;
        mOut.m13 = -s;
        mOut.m31 = s;
        mOut.m33 = c;
        mOut.m12 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m32 = mOut.m34 = T(0);
        mOut.m41 = mOut.m42 = mOut.m43 = T(0);
        mOut.m22 = mOut.m44 = T(1);
    }
    
    /**
     * @brief   绕Y轴旋转angle幅度
     * @param   angle   旋转幅度
     * @return  返回 旋转后的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixRotationY(N angle) {
        N s = N(0);
        N c = N(1);
//        if (asl::Math<N>::abs_(angle) > asl::g_tolerance)
//        {
//            asl::Math<N>::sincos_(s, c, angle);
//        }
        return AppMatrix<N>(
                            c, 0, -s, 0,
                            0, 1, 0, 0,
                            s, 0, c, 0,
                            0, 0, 0, 1);
    }
    
    /**
     * @brief   绕Z轴旋转angle幅度
     * @param   mOut       旋转后的矩阵
     * @param   angle   旋转幅度
     */
    template<typename T, typename N>
    inline void AppMatrixRotationZ(AppMatrix<T>& mOut, N angle) {
        T s = T(0);
        T c = T(1);
//        if (asl::Math<N>::abs_(angle) > asl::g_tolerance)
//        {
//            asl::Math<T>::sincos_(s, c, angle);
//        }
        
        mOut.m11 = c;
        mOut.m12 = s;
        mOut.m21 = -s;
        mOut.m22 = c;
        mOut.m13 = mOut.m14 = T(0);
        mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = mOut.m34 = T(0);
        mOut.m41 = mOut.m42 = mOut.m43 = T(0);
        mOut.m33 = mOut.m44 = T(1);
    }
    
    /**
     * @brief   绕Z轴旋转angle幅度
     * @param   angle   旋转幅度
     * @return  返回 旋转后的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixRotationZ(N angle) {
        N s = N(0);
        N c = N(1);
//        if (asl::Math<N>::abs_(angle) > asl::g_tolerance)
//        {
//            asl::Math<N>::sincos_(s, c, angle);
//        }
        
        return AppMatrix<N>(
                            c, s, 0, 0,
                            -s, c, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);
    }
    
//    /**
//     * @brief   绕axis轴旋转angle幅度
//     * @param   mOut       旋转后的矩阵
//     * @param   axis       旋转轴
//     * @param   angle   旋转幅度
//     */
//    template<typename N>
//    inline void AppMatrixRotationAxis(AppMatrix<N>& mOut, const Vector3<N>& axis, N angle) {
//        if (Math<N>::abs_(angle) < g_tolerance)
//        {
//            mOut = AppMatrix<N>::Identity();
//            return;
//        }
//        // Normalize axis
//        Vector3<N> normal_axis = Vector3Normalize(axis);
//
//        N x = normal_axis.x;
//        N y = normal_axis.y;
//        N z = normal_axis.z;
//
//        // angle
//        N c = Math<N>::cos_(angle);
//        N s = Math<N>::sin_(angle);
//        N p = 1 - c;
//
//        mOut.m11 = x * x * p + c;
//        mOut.m12 = x * y * p + z * s;
//        mOut.m13 = x * z * p - y * s;
//
//        mOut.m21 = x * y * p - z * s;
//        mOut.m22 = y * y * p + c;
//        mOut.m23 = y * z * p + x * s;
//
//        mOut.m31 = x * z * p + y * s;
//        mOut.m32 = y * z * p - x * s;
//        mOut.m33 = z * z * p + c;
//
//        mOut.m14 = mOut.m24 = mOut.m34 = mOut.m41 = mOut.m42 = mOut.m43 = 0.0;
//        mOut.m44 = 1.0;
//    }
//
//    /**
//     * @brief   绕axis轴旋转angle幅度
//     * @param   axis       旋转轴
//     * @param   angle   旋转幅度
//     * @return  返回 旋转后的矩阵
//     */
//    template<typename N>
//    inline AppMatrix<N> AppMatrixRotationAxis(const Vector3<N>& axis, N angle) {
//        if (Math<N>::abs_(angle) < g_tolerance)
//        {
//            return AppMatrix<N>::Identity();
//        }
//        // Normalize axis
//        Vector3<N> normal_axis = Vector3Normalize(axis);
//
//        N x = normal_axis.x;
//        N y = normal_axis.y;
//        N z = normal_axis.z;
//
//        // angle
//        N c = Math<N>::cos_(angle);
//        N s = Math<N>::sin_(angle);
//        N p = 1 - c;
//
//        N m11 = x * x * p + c;
//        N m12 = x * y * p + z * s;
//        N m13 = x * z * p - y * s;
//
//        N m21 = x * y * p - z * s;
//        N m22 = y * y * p + c;
//        N m23 = y * z * p + x * s;
//
//        N m31 = x * z * p + y * s;
//        N m32 = y * z * p - x * s;
//        N m33 = z * z * p + c;
//
//        return AppMatrix<N>(
//                            m11, m12, m13, 0,
//                            m21, m22, m23, 0,
//                            m31, m32, m33, 0,
//                            0, 0, 0, 1);
//    }
    
    /**
     * @brief   矩阵的逆运算
     * @param   mOut       逆运算后的矩阵
     * @param   mat       需要逆运算的矩阵
     */
    template<typename N>
    inline void AppMatrixInverse(AppMatrix<N>& mOut, const AppMatrix<N>& mat) {
        N m00 = mat.m11, m01 = mat.m12, m02 = mat.m13, m03 = mat.m14;
        N m10 = mat.m21, m11 = mat.m22, m12 = mat.m23, m13 = mat.m24;
        N m20 = mat.m31, m21 = mat.m32, m22 = mat.m33, m23 = mat.m34;
        N m30 = mat.m41, m31 = mat.m42, m32 = mat.m43, m33 = mat.m44;
        
        N v0 = m20 * m31 - m21 * m30;
        N v1 = m20 * m32 - m22 * m30;
        N v2 = m20 * m33 - m23 * m30;
        N v3 = m21 * m32 - m22 * m31;
        N v4 = m21 * m33 - m23 * m31;
        N v5 = m22 * m33 - m23 * m32;
        
        N t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
        N t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
        N t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
        N t30 = -(v3 * m10 - v1 * m11 + v0 * m12);
        
        N invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);
        
        mOut.m11 = t00 * invDet;
        mOut.m21 = t10 * invDet;
        mOut.m31 = t20 * invDet;
        mOut.m41 = t30 * invDet;
        
        mOut.m12 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        mOut.m22 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        mOut.m32 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        mOut.m42 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
        
        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;
        
        mOut.m13 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        mOut.m23 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        mOut.m33 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        mOut.m43 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
        
        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;
        
        mOut.m14 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        mOut.m24 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        mOut.m34 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        mOut.m44 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
    }
    
    /**
     * @brief   矩阵的逆运算
     * @param   mat       需要逆运算的矩阵
     * @return  返回 逆运算后的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixInverse(const AppMatrix<N>& mat) {
        N m00 = mat.m11, m01 = mat.m12, m02 = mat.m13, m03 = mat.m14;
        N m10 = mat.m21, m11 = mat.m22, m12 = mat.m23, m13 = mat.m24;
        N m20 = mat.m31, m21 = mat.m32, m22 = mat.m33, m23 = mat.m34;
        N m30 = mat.m41, m31 = mat.m42, m32 = mat.m43, m33 = mat.m44;
        
        N v0 = m20 * m31 - m21 * m30;
        N v1 = m20 * m32 - m22 * m30;
        N v2 = m20 * m33 - m23 * m30;
        N v3 = m21 * m32 - m22 * m31;
        N v4 = m21 * m33 - m23 * m31;
        N v5 = m22 * m33 - m23 * m32;
        
        N t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
        N t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
        N t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
        N t30 = -(v3 * m10 - v1 * m11 + v0 * m12);
        
        N invDet = 1.0 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);
        
        N d00 = t00 * invDet;
        N d10 = t10 * invDet;
        N d20 = t20 * invDet;
        N d30 = t30 * invDet;
        
        N d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        N d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        N d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        N d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
        
        v0 = m10 * m31 - m11 * m30;
        v1 = m10 * m32 - m12 * m30;
        v2 = m10 * m33 - m13 * m30;
        v3 = m11 * m32 - m12 * m31;
        v4 = m11 * m33 - m13 * m31;
        v5 = m12 * m33 - m13 * m32;
        
        N d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        N d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        N d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        N d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
        
        v0 = m21 * m10 - m20 * m11;
        v1 = m22 * m10 - m20 * m12;
        v2 = m23 * m10 - m20 * m13;
        v3 = m22 * m11 - m21 * m12;
        v4 = m23 * m11 - m21 * m13;
        v5 = m23 * m12 - m22 * m13;
        
        N d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
        N d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
        N d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
        N d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;
        
        return AppMatrix<N>(
                            d00, d01, d02, d03,
                            d10, d11, d12, d13,
                            d20, d21, d22, d23,
                            d30, d31, d32, d33);
    }
    
    /**
     * @brief   矩阵的相乘并转置
     * @param   mOut       相乘并转置后的矩阵
     * @param   mat1       矩阵1
     * @param   mat2       矩阵2
     */
    template<typename N, typename N1, typename N2>
    inline void AppMatrixMultiplyTranspose(AppMatrix<N>& mOut, const AppMatrix<N1>& mat1, const AppMatrix<N2>& mat2) {
        N m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31 + mat1.m14 * mat2.m41;
        N m21 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32 + mat1.m14 * mat2.m42;
        N m31 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33 + mat1.m14 * mat2.m43;
        N m41 = mat1.m11 * mat2.m14 + mat1.m12 * mat2.m24 + mat1.m13 * mat2.m34 + mat1.m14 * mat2.m44;
        
        N m12 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31 + mat1.m24 * mat2.m41;
        N m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32 + mat1.m24 * mat2.m42;
        N m32 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33 + mat1.m24 * mat2.m43;
        N m42 = mat1.m21 * mat2.m14 + mat1.m22 * mat2.m24 + mat1.m23 * mat2.m34 + mat1.m24 * mat2.m44;
        
        N m13 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31 + mat1.m34 * mat2.m41;
        N m23 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32 + mat1.m34 * mat2.m42;
        N m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33 + mat1.m34 * mat2.m43;
        N m43 = mat1.m31 * mat2.m14 + mat1.m32 * mat2.m24 + mat1.m33 * mat2.m34 + mat1.m34 * mat2.m44;
        
        N m14 = mat1.m41 * mat2.m11 + mat1.m42 * mat2.m21 + mat1.m43 * mat2.m31 + mat1.m44 * mat2.m41;
        N m24 = mat1.m41 * mat2.m12 + mat1.m42 * mat2.m22 + mat1.m43 * mat2.m32 + mat1.m44 * mat2.m42;
        N m34 = mat1.m41 * mat2.m13 + mat1.m42 * mat2.m23 + mat1.m43 * mat2.m33 + mat1.m44 * mat2.m43;
        N m44 = mat1.m41 * mat2.m14 + mat1.m42 * mat2.m24 + mat1.m43 * mat2.m34 + mat1.m44 * mat2.m44;
        
        mOut.m11 = m11; mOut.m12 = m12; mOut.m13 = m13; mOut.m14 = m14;
        mOut.m21 = m21; mOut.m22 = m22; mOut.m23 = m23; mOut.m24 = m24;
        mOut.m31 = m31; mOut.m32 = m32; mOut.m33 = m33; mOut.m34 = m34;
        mOut.m41 = m41; mOut.m42 = m42; mOut.m43 = m43; mOut.m44 = m44;
    }
    
    /**
     * @brief   矩阵的相乘
     * @param   mOut       相乘后的矩阵
     * @param   mat1       矩阵1
     * @param   mat2       矩阵2
     */
    template<typename N, typename N1, typename N2>
    inline void AppMatrixMultiply(AppMatrix<N>& mOut, const AppMatrix<N1>& mat1, const AppMatrix<N2>& mat2) {
        N m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31 + mat1.m14 * mat2.m41;
        N m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32 + mat1.m14 * mat2.m42;
        N m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33 + mat1.m14 * mat2.m43;
        N m14 = mat1.m11 * mat2.m14 + mat1.m12 * mat2.m24 + mat1.m13 * mat2.m34 + mat1.m14 * mat2.m44;
        
        N m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31 + mat1.m24 * mat2.m41;
        N m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32 + mat1.m24 * mat2.m42;
        N m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33 + mat1.m24 * mat2.m43;
        N m24 = mat1.m21 * mat2.m14 + mat1.m22 * mat2.m24 + mat1.m23 * mat2.m34 + mat1.m24 * mat2.m44;
        
        N m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31 + mat1.m34 * mat2.m41;
        N m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32 + mat1.m34 * mat2.m42;
        N m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33 + mat1.m34 * mat2.m43;
        N m34 = mat1.m31 * mat2.m14 + mat1.m32 * mat2.m24 + mat1.m33 * mat2.m34 + mat1.m34 * mat2.m44;
        
        N m41 = mat1.m41 * mat2.m11 + mat1.m42 * mat2.m21 + mat1.m43 * mat2.m31 + mat1.m44 * mat2.m41;
        N m42 = mat1.m41 * mat2.m12 + mat1.m42 * mat2.m22 + mat1.m43 * mat2.m32 + mat1.m44 * mat2.m42;
        N m43 = mat1.m41 * mat2.m13 + mat1.m42 * mat2.m23 + mat1.m43 * mat2.m33 + mat1.m44 * mat2.m43;
        N m44 = mat1.m41 * mat2.m14 + mat1.m42 * mat2.m24 + mat1.m43 * mat2.m34 + mat1.m44 * mat2.m44;
        
        mOut.m11 = m11; mOut.m12 = m12; mOut.m13 = m13; mOut.m14 = m14;
        mOut.m21 = m21; mOut.m22 = m22; mOut.m23 = m23; mOut.m24 = m24;
        mOut.m31 = m31; mOut.m32 = m32; mOut.m33 = m33; mOut.m34 = m34;
        mOut.m41 = m41; mOut.m42 = m42; mOut.m43 = m43; mOut.m44 = m44;
    }
    
    /**
     * @brief   矩阵的相乘
     * @param   mat1       矩阵1
     * @param   mat2       矩阵2
     * @return  返回 相乘后的矩阵
     */
    template<typename N>
    inline AppMatrix<N> AppMatrixMultiply(const AppMatrix<N>& mat1, const AppMatrix<N>& mat2) {
        N m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31 + mat1.m14 * mat2.m41;
        N m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32 + mat1.m14 * mat2.m42;
        N m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33 + mat1.m14 * mat2.m43;
        N m14 = mat1.m11 * mat2.m14 + mat1.m12 * mat2.m24 + mat1.m13 * mat2.m34 + mat1.m14 * mat2.m44;
        
        N m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31 + mat1.m24 * mat2.m41;
        N m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32 + mat1.m24 * mat2.m42;
        N m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33 + mat1.m24 * mat2.m43;
        N m24 = mat1.m21 * mat2.m14 + mat1.m22 * mat2.m24 + mat1.m23 * mat2.m34 + mat1.m24 * mat2.m44;
        
        N m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31 + mat1.m34 * mat2.m41;
        N m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32 + mat1.m34 * mat2.m42;
        N m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33 + mat1.m34 * mat2.m43;
        N m34 = mat1.m31 * mat2.m14 + mat1.m32 * mat2.m24 + mat1.m33 * mat2.m34 + mat1.m34 * mat2.m44;
        
        N m41 = mat1.m41 * mat2.m11 + mat1.m42 * mat2.m21 + mat1.m43 * mat2.m31 + mat1.m44 * mat2.m41;
        N m42 = mat1.m41 * mat2.m12 + mat1.m42 * mat2.m22 + mat1.m43 * mat2.m32 + mat1.m44 * mat2.m42;
        N m43 = mat1.m41 * mat2.m13 + mat1.m42 * mat2.m23 + mat1.m43 * mat2.m33 + mat1.m44 * mat2.m43;
        N m44 = mat1.m41 * mat2.m14 + mat1.m42 * mat2.m24 + mat1.m43 * mat2.m34 + mat1.m44 * mat2.m44;
        
        return AppMatrix<N>(
                            m11, m12, m13, m14,
                            m21, m22, m23, m24,
                            m31, m32, m33, m34,
                            m41, m42, m43, m44);
    }
    
    /**
     * @brief   利用右手坐标系计算透视投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   w       近裁减面的宽度
     * @param   h       近裁减面的高度
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixPerspectiveRH(AppMatrix<T>& mOut, N w, N h, N zn, N zf) {
        T q = zf / (zf - zn);
        T near2 = zn + zn;
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = T(0);
        mOut.m41 = mOut.m42 = mOut.m44 = T(0);
        mOut.m11 = near2 / w;
        mOut.m22 = near2 / h;
        mOut.m33 = -q;
        mOut.m34 = T(-1);
        mOut.m43 = -zn * q;
    }
    
    /**
     * @brief   利用右手坐标系计算透视投影矩阵
     * @param   w       近裁减面的宽度
     * @param   h       近裁减面的高度
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     * @param   返回计算后的矩阵
     */
    template<typename T>
    inline AppMatrix<T> AppMatrixPerspectiveRH(T w, T h, T zn, T zf) {
        T q = zf / (zf - zn);
        T near2 = zn + zn;
        
        return AppMatrix<T>(
                            near2 / w, 0, 0, 0,
                            0, near2 / w, 0, 0,
                            0, 0, -q, -1,
                            0, 0, -zn * q, 0);
    }
    
    /**
     * @brief   利用左手坐标系计算透视投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   w       近裁减面的宽度
     * @param   h       近裁减面的高度
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixPerspectiveLH(AppMatrix<T>& mOut, N w, N h, N zn, N zf) {
        T q = zf / (zf - zn);
        T near2 = zn + zn;
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = T(0);
        mOut.m41 = mOut.m42 = mOut.m44 = T(0);
        mOut.m11 = near2 / w;
        mOut.m22 = near2 / h;
        mOut.m33 = q;
        mOut.m34 = T(1);
        mOut.m43 = -zn * q;
    }
    
    /**
     * @brief   利用左手坐标系计算透视投影矩阵
     * @param   w       近裁减面的宽度
     * @param   h       近裁减面的高度
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     * @param   返回计算后的矩阵
     */
    template<typename T>
    inline AppMatrix<T> AppMatrixPerspectiveLH(T w, T h, T zn, T zf) {
        T q = zf / (zf - zn);
        T near2 = zn + zn;
        
        return AppMatrix<T>(
                            near2 / w, 0, 0, 0,
                            0, near2 / h, 0, 0,
                            0, 0, q, 1,
                            0, 0, -zn * q, 0);
    }
    
    /**
     * @brief   利用右手坐标系计算透视投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   fovy       fov
     * @param   aspect  近裁减面的宽高比
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixPerspectiveFovRH(AppMatrix<T>& mOut, N fovy, N aspect, N zn, N zf) {
        T h; // = T(1) / asl::Math<T>::tan_(fovy * 0.5);
        T w = h / aspect;
        T q = zf / (zf - zn);
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = T(0);
        mOut.m41 = mOut.m42 = mOut.m44 = T(0);
        mOut.m11 = w;
        mOut.m22 = h;
        mOut.m33 = -q;
        mOut.m34 = T(-1);
        mOut.m43 = -zn * q;
    }
    
    /**
     * @brief   利用左手坐标系计算透视投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   fovy       fov
     * @param   aspect  近裁减面的宽高比
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixPerspectiveFovLH(AppMatrix<T>& mOut, N fovy, N aspect, N zn, N zf) {
        T h; //  = T(1) / asl::Math<T>::tan_(fovy * 0.5);
        T w = h / aspect;
        T q = zf / (zf - zn);
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = T(0);
        mOut.m41 = mOut.m42 = mOut.m44 = T(0);
        mOut.m11 = w;
        mOut.m22 = h;
        mOut.m33 = q;
        mOut.m34 = T(1);
        mOut.m43 = -zn * q;
    }
    
    /**
     * @brief   利用右手坐标系计算透视投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   l       left
     * @param   r       right
     * @param   b       bottom
     * @param   t       top
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixPerspectiveOffCenterRH(AppMatrix<T>& mOut, N l, N r, N b, N t, N zn, N zf) {
        T q = T(zf) / T(zf - zn);
        T near2 = T(zn + zn);
        T invWidth = T(1) / T(r - l);
        T invHeight = T(1) / T(t - b);
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m41 = mOut.m42 = mOut.m44 = T(0);
        mOut.m11 = near2 * invWidth;
        mOut.m22 = near2 * invHeight;
        mOut.m31 = (l + r) * invWidth;
        mOut.m32 = (t + b) * invHeight;
        mOut.m33 = -q;
        mOut.m34 = T(-1);
        mOut.m43 = -zn * q;
    }
    
    /**
     * @brief   利用左手坐标系计算透视投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   l       left
     * @param   r       right
     * @param   b       bottom
     * @param   t       top
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixPerspectiveOffCenterLH(AppMatrix<T>& mOut, N l, N r, N b, N t, N zn, N zf) {
        T q = T(zf) / T(zf - zn);
        T near2 = T(zn + zn);
        T invWidth = T(1) / T(r - l);
        T invHeight = T(1) / T(t - b);
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m41 = mOut.m42 = mOut.m44 = T(0);
        mOut.m11 = near2 * invWidth;
        mOut.m22 = near2 * invHeight;
        mOut.m31 = -(l + r) * invWidth;
        mOut.m32 = -(t + b) * invHeight;
        mOut.m33 = q;
        mOut.m34 = T(1);
        mOut.m43 = -zn * q;
    }
    
    /**
     * @brief   利用右手坐标系计算正交投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   w       近裁减面的宽度
     * @param   h       近裁减面的高度
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixOrthoRH(AppMatrix<T>& mOut, N w, N h, N zn, N zf) {
        T q = T(1) / (zf - zn);
        T invWidth = T(1) / w;
        T invHeight = T(1) / h;
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = mOut.m34 = T(0);
        mOut.m41 = mOut.m42 = T(0);
        mOut.m11 = invWidth + invWidth;
        mOut.m22 = invHeight + invHeight;
        mOut.m33 = -q;
        mOut.m43 = -zn * q;
        mOut.m44 = T(1);
    }
    
    /**
     * @brief   利用左手坐标系计算正交投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   w       近裁减面的宽度
     * @param   h       近裁减面的高度
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixOrthoLH(AppMatrix<T>& mOut, N w, N h, N zn, N zf) {
        T q = T(1) / (zf - zn);
        T invWidth = T(1) / w;
        T invHeight = T(1) / h;
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = mOut.m34 = T(0);
        mOut.m41 = mOut.m42 = T(0);
        mOut.m11 = invWidth + invWidth;
        mOut.m22 = invHeight + invHeight;
        mOut.m33 = q;
        mOut.m43 = -zn * q;
        mOut.m44 = T(1);
    }
    
    /**
     * @brief   利用右手坐标系计算正交投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   l       left
     * @param   r       right
     * @param   b       bottom
     * @param   t       top
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixOrthoOffCenterRH(AppMatrix<T>& mOut, N l, N r, N b, N t, N zn, N zf) {
        T q = T(1) / (zf - zn);
        T invWidth = T(1) / (r - l);
        T invHeight = T(1) / (t - b);
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = mOut.m34 = T(0);
        mOut.m11 = invWidth + invWidth;
        mOut.m22 = invHeight + invHeight;
        mOut.m33 = -q;
        mOut.m41 = -(l + r) * invWidth;
        mOut.m42 = -(t + b) * invHeight;
        mOut.m43 = -zn * q;
        mOut.m44 = T(1);
    }
    
    /**
     * @brief   利用左手坐标系计算正交投影矩阵
     * @param   mOut       计算后的矩阵
     * @param   l       left
     * @param   r       right
     * @param   b       bottom
     * @param   t       top
     * @param   zn       近裁减面的距离
     * @param   zf       远裁减面的距离
     */
    template<typename T, typename N>
    inline void AppMatrixOrthoOffCenterLH(AppMatrix<T>& mOut, N l, N r, N b, N t, N zn, N zf) {
        T q = T(1) / (zf - zn);
        T invWidth = T(1) / (r - l);
        T invHeight = T(1) / (t - b);
        
        mOut.m12 = mOut.m13 = mOut.m14 = T(0);
        mOut.m21 = mOut.m23 = mOut.m24 = T(0);
        mOut.m31 = mOut.m32 = mOut.m34 = T(0);
        mOut.m11 = invWidth + invWidth;
        mOut.m22 = invHeight + invHeight;
        mOut.m33 = q;
        mOut.m41 = -(l + r) * invWidth;
        mOut.m42 = -(t + b) * invHeight;
        mOut.m43 = -zn * q;
        mOut.m44 = T(1);
    }
    
    /**
     * @brief   通过透视投影矩阵提取近裁减面距离
     * @param   mat  透视投影矩阵
     * @return  返回近裁减面的距离
     */
    template<typename N>
    inline N GetZnFromProjectionMatrix(const AppMatrix<N>& mat) {
        return -mat.m43 * mat.m34 / mat.m33;
    }
    
    /**
     * @brief   通过透视投影矩阵提取远裁减面距离
     * @param   mat  透视投影矩阵
     * @return  返回远裁减面的距离
     */
    template<typename N>
    inline N GetZfFromProjectionMatrix(const AppMatrix<N>& mat) {
        // return asl::Math<N>::abs_((mat.m44 - mat.m43) / (mat.m33 - mat.m34));
    }
    
    /**
     * @brief   设备坐标(NDC)到视口坐标的转换矩阵
     * @param   x   视口的左下角x坐标
     * @param   y   视口的左下角y坐标
     * @param   width   视口的宽度
     * @param   height  视口的高度
     * @return  返回计算好的矩阵
     */
    template<typename N>
    inline AppMatrixf AppMatrixViewport(N x, N y, N width, N height)
    {
        float m11 = width * 0.5f;
        float m22 = -height * 0.5f;
        float m41 = x + m11;
        float m42 = y - m22;
        return AppMatrixf(m11, 0, 0, 0,
                          0, m22, 0, 0,
                          0, 0, 1.0f, 0,
                          m41, m42, 0, 1.0f);
    }
    
    /**
     * @brief   设备坐标(NDC)到视口坐标的转换矩阵
     * @param   mat 计算后的矩阵
     * @param   x   视口的左下角x坐标
     * @param   y   视口的左下角y坐标
     * @param   width   视口的宽度
     * @param   height  视口的高度
     */
    template<typename N>
    inline void AppMatrixViewport(AppMatrixf& mat, N x, N y, N width, N height)
    {
        AppMatrixIdentity(mat);
        mat.m11 = width * 0.5f;
        mat.m22 = -height * 0.5f;
        mat.m41 = x + mat.m11;
        mat.m42 = y - mat.m22;
    }
    
    /**
     * @brief   视口坐标到设备坐标(NDC)的转换矩阵
     * @param   x   视口的左下角x坐标
     * @param   y   视口的左下角y坐标
     * @param   width   视口的宽度
     * @param   height  视口的高度
     * @return  返回计算好的矩阵
     */
    template<typename N>
    inline AppMatrixf AppMatrixNDC(N x, N y, N width, N height)
    {
        float m11 = 2.0f / width;
        float m22 = -2.0f / height;
        float m41 = -1.0f - 2.0f * x / width;
        float m42 = 1.0f + 2.0f * y / height;
        return AppMatrixf(m11, 0, 0, 0,
                          0, m22, 0, 0,
                          0, 0, 1.0f, 0,
                          m41, m42, 0, 1.0f);
    }
    
    /**
     * @brief   视口坐标到设备坐标(NDC)的转换矩阵
     * @param   mat 计算后的矩阵
     * @param   x   视口的左下角x坐标
     * @param   y   视口的左下角y坐标
     * @param   width   视口的宽度
     * @param   height  视口的高度
     */
    template<typename N>
    inline void AppMatrixNDC(AppMatrixf& mat, N x, N y, N width, N height)
    {
        AppMatrixIdentity(mat);
        mat.m11 = 2.0f / width;
        mat.m22 = -2.0f / height;
        mat.m41 = -1.0f - 2.0f * x / width;
        mat.m42 = 1.0f + 2.0f * y / height;
    }
    
    /**
     * @brief   向量转换
     * @param   v   需要转换的向量,
     * @param   mat 矩阵
     * @return  返回转换后的坐标
     */
    template<typename N, typename N1, typename N2>
    inline Vector3<N> LmkTransformVector3(const Vector3<N1>& v, const AppMatrix<N2>& mat) {
        return Vector3<N>(
                        N(v.x * mat.m11 + v.y * mat.m21 + v.z * mat.m31),
                        N(v.x * mat.m12 + v.y * mat.m22 + v.z * mat.m32),
                        N(v.x * mat.m13 + v.y * mat.m23 + v.z * mat.m33));
    }

    /**
     * @brief  坐标转换，不进行归一化
     * @param  vOut 转换后的坐标
     * @param  v    需要转换的坐标,
     * @param  mat  矩阵
     */
    template<typename N, typename N1, typename N2>
    inline void LmkTransformCoord3(Vector3<N>& vOut, const Vector3<N1>& v, const AppMatrix<N2>& mat) {
        N1 x = v.x;
        N1 y = v.y;
        N1 z = v.z;
        vOut.x = x * mat.m11 + y * mat.m21 + z * mat.m31 + mat.m41;
        vOut.y = x * mat.m12 + y * mat.m22 + z * mat.m32 + mat.m42;
        vOut.z = x * mat.m13 + y * mat.m23 + z * mat.m33 + mat.m43;
    }
    
    template<typename N>
    static AppMatrix<N> LookAtRH(const Vector3<N>& position, const Vector3<N>& target, const Vector3<N>& up) {
        Vector3<N> zaxis = position - target;
        zaxis.Normalize();

        Vector3<N> xaxis = Vector3<N>::Cross(up, zaxis);
        xaxis.Normalize();

        Vector3<N> yaxis = Vector3<N>::Cross(zaxis, xaxis);
        yaxis.Normalize();

        return AppMatrix<N>(
            xaxis.x, yaxis.x, zaxis.x, 0.0,
            xaxis.y, yaxis.y, zaxis.y, 0.0,
            xaxis.z, yaxis.z, zaxis.z, 0.0,
            -xaxis.Dot(position), -yaxis.Dot(position), -zaxis.Dot(position), 1.0);
    }
    
    typedef AppMatrix<float>    AppMatrixf;
    typedef AppMatrix<double>    AppMatrixd;
    
    typedef Vector3<float>    Vector3f;
    typedef Vector3<double>   Vector3d;
    
}

#endif // __LMK_MATRIX_H__



