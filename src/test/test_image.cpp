
#include <assert.h>
//#include "stb.h"
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

//const char* test_path = "/usr/local/Cellar/go/1.13.5/libexec/doc/gopher/appenginelogo.gif";
//const char* test_path = "/Users/zy/Downloads/girl.gif";
//const char* test_path = "/Users/zy/peter/box/images/link/iconList.png";
const char* test_path = "/Users/zy/peter/box/images/box.png";

static uint8_t* readAll(const char* path, int& size) {
    FILE* file = fopen(path, "rb");
    if (!file)
        return 0;
    
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    uint8_t* p = (uint8_t *)malloc(size+1);
    fseek(file, 0L, SEEK_SET);
    fread(p, size, 1, file);
    p[size]=0;
    fclose(file);
    return p;
}

static void test_gif() {
    int size = 0;
    uint8_t* data = readAll(test_path, size);
    
    int x, y, z, n;
    int* delay;
    stbi_uc* img = stbi_load_gif_from_memory((const stbi_uc*)data, size, &delay, &x, &y, &z, &n, 4);
    
    int img_size = x * y * n;
    for (int i=0; i<z; i++) {
        printf("delay=%d\n", *delay++);
        char pp[256];
        sprintf(pp, "/Users/zy/peter/box/%d.png", i);
        stbi_write_bmp(pp, x, y, n, img + i * img_size);
    }
    printf("x=%d y=%d z=%d n=%d\n", x, y, z, n);
    stbi_image_free(img);
}

class IconSet {
public:
    IconSet(int w, int h, int n) {
        _w = w;
        _h = h;
        _n = n;
    }
    
    void use(int row, int col) {
        _row = row;
        _col = col;
        
        _lineStart = row * _iconHeight;
        _lineEnd   = _lineStart + _iconHeight;
    }
    
    int lineStart() const {
        return _lineStart;
    }
    
    int lineEnd() const {
        return _lineEnd;
    }
    
    int offset(int line) const {
        return line * _w * _n + (_col * _iconWidth * _n);
    }
    
    int iconWidth() const {
        return _iconWidth;
    }
    
    int iconHeight() const {
        return _iconHeight;
    }
    
    int iconSize() const {
        return _iconWidth * _iconHeight * _n;
    }
    
    int lineSize() const {
        return _iconWidth * _n;
    }
    
    void split(int row, int col) {
        _iconWidth  = _w / col;
        _iconHeight = _h / row;
    }
    
private:
    int _w;
    int _h;
    int _n;
    
    int _row;
    int _col;
    
    int _lineStart;
    int _lineEnd;
    
    int _iconWidth;
    int _iconHeight;
};

static void split() {
    int w, h, n;
    unsigned char* img = stbi_load(test_path, &w, &h, &n, 0);
    printf("w=%d h=%d n=%d\n", w, h, n);
    
    IconSet icon(w, h, n);
    icon.split(4, 4);
    
    unsigned char* image = (unsigned char*)malloc(icon.iconSize());
    for (int row=0; row<4; row++) {
        for (int col=0; col<4; col++) {
            unsigned char* p = image;
            
            icon.use(row, col);
            for (int j=icon.lineStart(); j<icon.lineEnd(); j++) {
                int offset = icon.offset(j);
                memcpy((void*)p, (void*)(img+offset), icon.lineSize());
                p += icon.lineSize();
            }

            char pp[256];
            sprintf(pp, "/Users/zy/peter/box/%d-%d.png", row, col);
            stbi_write_png(pp, icon.iconWidth(), icon.iconHeight(), n, image, icon.lineSize());
        }
    }
    
    exit(0);
}

void test_image() {
    split();

    int w, h, n;
    unsigned char* img = stbi_load(test_path, &w, &h, &n, 0);
    printf("w=%d h=%d n=%d\n", w, h, n);
    stbi_image_free(img);
    
    // test_gif();
    
    exit(0);
}
