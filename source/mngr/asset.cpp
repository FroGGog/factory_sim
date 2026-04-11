#include "mngr/asset.hpp"
#include <filesystem>
#include <unordered_map>

// Globals

static std::unordered_map<std::string, Texture> textures;
static std::unordered_map<std::string, Font> fonts;
static std::unordered_map<std::string, Shader> shaders;

// Fallback functions

Texture &getFallbackTexture() {
   static Texture fallbackTexture;
   static bool loaded = false;

   if (!loaded) {
      // Create the iconic missing texture
      Image image = GenImageChecked(8, 8, 2, 2, MAGENTA, BLACK);
      fallbackTexture = LoadTextureFromImage(image);
      UnloadImage(image);
      loaded = true;
   }
   return fallbackTexture;
}

Font &getFallbackFont() {
   static Font fallbackFont = GetFontDefault();
   return fallbackFont;
}

// Load functions

Texture &loadTexture(const std::string &name, const std::string &path) {
   if (textures.count(name)) {
      return textures[name];
   }

   Texture texture = LoadTexture(path.c_str());
   if (texture.id == 0) {
      printf("Failed to load texture from file '%s'.\n", path.c_str());
      return getFallbackTexture();
   }

   textures.insert({name, texture});
   return textures[name];
}

Font &loadFont(const std::string &name, const std::string &path) {
   if (fonts.count(name)) {
      return fonts[name];
   }

   // Apply some dark magic that makes fonts look better
   Font font = LoadFontEx(path.c_str(), 120, nullptr, 0);
   SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

   if (font.texture.id == 0) {
      printf("Failed to load font from file '%s'.\n", path.c_str());
      return getFallbackFont();
   }

   fonts.insert({name, font});
   return fonts[name];
}

Shader &loadShader(const std::string &name,
                   const std::string &vertexPath,
                   const std::string &fragmentPath) {
   if (shaders.count(name)) {
      return shaders[name];
   }

   Shader shader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());
   if (shader.id == 0) {
      printf("Failed to load shader from files: vertex: '%s', fragment: '%s'.\n",
         vertexPath.c_str(), fragmentPath.c_str());
      exit(EXIT_FAILURE);
   }

   shaders.insert({name, shader});
   return shaders[name];
}

void loadTextures() {
   std::filesystem::create_directories("assets/sprites/");
   for (const auto &file: std::filesystem::recursive_directory_iterator("assets/sprites/")) {
      if (file.is_regular_file()) {
         std::string name = file.path().stem().string();
         std::string path = file.path().string();
         loadTexture(name, path);
      }
   }
}

void loadFonts() {
   std::filesystem::create_directories("assets/fonts/");
   for (const auto &file: std::filesystem::recursive_directory_iterator("assets/fonts/")) {
      if (file.is_regular_file()) {
         std::string name = file.path().stem().string();
         std::string path = file.path().string();
         loadFont(name, path);
      }
   }
}

void loadShaders() {
   std::filesystem::create_directories("assets/shaders/");
   for (const auto &file: std::filesystem::recursive_directory_iterator("assets/shaders/")) {
      std::string name = file.path().stem().string();

      if (shaders.count(name)) {
         continue;
      }

      std::string extension = file.path().extension().string();
      std::string path = file.path().string();
      
      if (extension == ".fs") {
         std::filesystem::path vertexPath = "assets/shaders/" + name + ".vs";
         std::string vertex;
         if (std::filesystem::exists(vertexPath)) {
            vertex = vertexPath.string();
         }
         
         loadShader(name, vertex, path);
      } else if (extension == ".vs") {
         std::filesystem::path fragmentPath = "assets/shaders/" + name + ".fs";
         std::string fragment;
         if (std::filesystem::exists(fragmentPath)) {
            fragment = fragmentPath.string();
         }
         
         loadShader(name, path, fragment);
      }
   }
}

// Get functions

Texture &getTexture(const std::string &name) {
   if (!textures.count(name)) {
      printf("Texture '%s' does not exist, using fallback texture.\n", name.c_str());
      return getFallbackTexture();
   }
   return textures[name];
}

Font& getFont(const std::string &name) {
   if (!fonts.count(name)) {
      printf("Font '%s' does not exist, using fallback font.\n", name.c_str());
      return getFallbackFont();
   }
   return fonts[name];
}

Shader& getShader(const std::string &name) {
   if (!shaders.count(name)) {
      printf("Shader '%s' does not exist.\n", name.c_str());
      exit(EXIT_FAILURE); // No way to recover, will just throw an error down the line
   }
   return shaders[name];
}
