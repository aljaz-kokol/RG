#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_INDEXBUFFER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_INDEXBUFFER_H

#include "../Buffer.h"

class IndexBuffer : public Buffer<GLuint> {
private:
    GLuint count;
public:
    explicit IndexBuffer(const std::vector<GLuint>& indices);
    [[nodiscard]] GLuint getCount() const;
};


#endif
