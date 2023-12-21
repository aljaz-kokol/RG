#include <glm/ext/matrix_clip_space.hpp>
#include "Font.h"

Character Font::loadChar(uint8_t chr, const FT_Face &face) {
    // load char glyph
    if (FT_Load_Char(face, chr, FT_LOAD_RENDER)) {
        throw std::runtime_error("ERROR::FREETYPE: Failed to load glyph" );
    }
    uint32_t textureId = 0;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                 face->glyph->bitmap.width,
                 face->glyph->bitmap.rows,
                 0,
                 GL_RED,
                 GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer
    );
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character character = {
            textureId,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
    };
    return character;
}

Font::Font(std::string_view filePath, FT_UInt fontHeight): vbo({}) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("ERROR::FREETYPE: Could not init FreeType Library");
    }
    FT_Face face;
    if (FT_New_Face(ft, filePath.data(), 0, &face)) {
        throw std::runtime_error("ERROR::FREETYPE: Failed to load font" );
    }
    FT_Set_Pixel_Sizes(face, 0, fontHeight);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable bite allignment
    for (uint8_t chr = 0; chr < 128; chr++) { // Load basic ASCII chars
        characters.insert({chr, loadChar(chr, face)});
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    vao.bind();
    vbo.bind();
    bufferLayout.push<GL_FLOAT>(4);
    vao.addBuffer(vbo, bufferLayout);
}

void Font::renderText(const ShaderProgram &program, std::string_view text, float x, float y, float scale, const Color &color) const {
    program.bind();
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    program.setUniform("textColor", color.getRGB());
    program.setUniform("projection", projection);
    glActiveTexture(GL_TEXTURE1);
    program.setUniform("text", 1);
    vao.bind();
    for (char chr : text) {
        Character ch = characters.at(chr);

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        std::vector<GLfloat> vertices = {
            xpos,     ypos + h,   0.0f, 0.0f,
            xpos,     ypos,       0.0f, 1.0f,
            xpos + w, ypos,       1.0f, 1.0f,
            xpos,     ypos + h,   0.0f, 0.0f,
            xpos + w, ypos,       1.0f, 1.0f,
            xpos + w, ypos + h,   1.0f, 0.0f
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        vbo.bind();
        vbo.updateData(vertices);
        vbo.unbind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    vao.unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
    program.unbind();
}