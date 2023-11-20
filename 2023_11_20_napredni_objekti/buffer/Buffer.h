#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_BUFFER_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_BUFFER_H

#include<GL/glew.h>
#include<vector>

template<typename T>
class Buffer {
protected:
    GLuint id;
    GLuint bufferType;
public:
    Buffer(GLuint bufferType, const std::vector<T>& data);
    ~Buffer();
    void bind() const;
    void unbind() const;
};

template<typename T>
void Buffer<T>::bind() const {
    glBindBuffer(bufferType, id);
}

template<typename T>
void Buffer<T>::unbind() const {
    glBindBuffer(bufferType, 0);
}

template<typename T>
Buffer<T>::~Buffer() {
    if (id != 0) {
        glDeleteBuffers(1, &id);
    }
}

template<typename T>
Buffer<T>::Buffer(GLuint bufferType, const std::vector<T>& data): id(0), bufferType(bufferType) {
    glGenBuffers(1, &id);
    glBindBuffer(bufferType, id);
    glBufferData(bufferType, sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
}

#endif