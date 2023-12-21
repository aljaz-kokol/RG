#ifndef INC_2023_12_20_SHADEING_FONT_H
#define INC_2023_12_20_SHADEING_FONT_H

#include <string_view>
#include <ft2build.h>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../../buffer/layout/BufferLayout.h"
#include "../../vertex_array/VertexArray.h"
#include "../../shader/program/ShaderProgram.h"
#include "../../color/Color.h"
#include FT_FREETYPE_H

struct Character {
    uint32_t textureId;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    FT_Pos advance;    // Offset to advance to next glyph
};

class Font {
private:
    static Character loadChar(uint8_t chr, const FT_Face& face);
    std::unordered_map<char, Character> characters;
    VertexArray vao;
    VertexBuffer vbo;
    BufferLayout bufferLayout;
public:
    Font(std::string_view filePath, FT_UInt fontHeight = 48.0);
    void renderText(const ShaderProgram &program, std::string_view text, float x = 0.0, float y = 0.0, float scale = 1.0, const Color& color = Color::WHITE) const;
};

#endif