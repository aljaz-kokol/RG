#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::shared_ptr<ShaderProgram>& textShaderProgram): textShaderProgram(textShaderProgram) {}

void TextRenderer::addFont(const std::string &name, std::string_view filePath, FT_UInt fontHeight) {
    fonts.insert({ name, std::make_shared<Font>(filePath, fontHeight) });
}

void TextRenderer::render(const std::string& font, std::string_view text, float x, float y, float scale, const Color &color) const {
    if (!fonts.contains(font)) return;
    fonts.at(font)->renderText(*textShaderProgram, text, x, y, scale, color);
}

void TextRenderer::pushRender(const std::string &font, const std::string& text, float x, float y, float scale, const Color &color) {
    if (!fonts.contains(font)) return;
    prints.emplace_back(std::make_shared<RenderCommand>(RenderCommand{ font, text, x, y, scale, color }));
}

void TextRenderer::renderPushed() const {
    for (const auto &command : prints) {
        render(command->font, command->text, command->x, command->y, command->scale, command->color);
    }
}

void TextRenderer::setTextShaderProgram(const std::shared_ptr<ShaderProgram> &textShaderProgram) {
    this->textShaderProgram = textShaderProgram;
}