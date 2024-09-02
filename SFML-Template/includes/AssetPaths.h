#pragma once

#include <string>

class AssetPaths {
public:
    // Image paths
    static const std::string bgImage;

    // Sound paths
    static const std::string bounceSound;

    // Font paths
    static const std::string mainFont;

    // shaders
    static const std::string glowShaderPath;

private:
    // Prevent instantiation of this static class (private constructor)
    // note that a method of this class can still instantiate this class so dont make that mistake 
    AssetPaths() {}
};