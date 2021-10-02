#pragma once

#include "pch.hpp"

#include "Util/Display/Display.hpp"

#include "imgui/include/imgui_impl_dx11.h"

namespace Textures {
    //Texture variables go here
    const char* imagename01 = "MyImage01.jpg";
    ID3D11ShaderResourceView* test;
    int image01JpgW = 500;
    int image01JpgH = 500;
    class functions {
    public:
        //Initializes texture, run once on startup. Allocates memory region for it.
        void initializeTexture(const char* filename, ID3D11ShaderResourceView* textureName, int imageWidth, int imageHeight) {
            textureName = NULL;
            bool ret = util::display::load::loadTextureFromFile(filename, &textureName, &imageWidth, &imageHeight);
            IM_ASSERT(ret);
        }        
        void loadTextures();
    };
}