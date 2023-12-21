#ifndef INC_2023_12_20_SHADEING_TEXTRENDERER_H
#define INC_2023_12_20_SHADEING_TEXTRENDERER_H

#include <unordered_map>
#include <queue>
#include "Font.h"

struct RenderCommand {
    std::string font;
    std::string text;
    float x;
    float y;
    float scale;
    Color color;
};

class TextRenderer {
public:
    std::shared_ptr<ShaderProgram> textShaderProgram;
    std::unordered_map<std::string, std::shared_ptr<Font>> fonts;
    std::vector<std::shared_ptr<RenderCommand>> prints;
public:
    TextRenderer(const std::shared_ptr<ShaderProgram>& textShaderProgram = nullptr);
    void addFont(const std::string& name, std::string_view filePath, FT_UInt fontHeight = 48.0);
    void render(const std::string& font, std::string_view text, float x = 0.0, float y = 0.0, float scale = 1.0, const Color& color = Color::WHITE) const;
    void pushRender(const std::string& font, const std::string& text, float x = 0.0, float y = 0.0, float scale = 1.0, const Color& color = Color::WHITE);
    void renderPushed() const;
    void setTextShaderProgram(const std::shared_ptr<ShaderProgram>& textShaderProgram);
    void clearPushed();
};

#endif