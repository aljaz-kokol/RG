class MeshTransform {
    static rotate(model, angle, axis) {
        return glMatrix.mat4.rotate(glMatrix.mat4.create(), model, glMatrix.glMatrix.toRadian(angle), axis);
    }

    static scale(model, scaleFactors) {
        return glMatrix.mat4.scale(glMatrix.mat4.create(), model, scaleFactors);
    }

    static scaleAll(model, factor) {
        return glMatrix.mat4.scale(glMatrix.mat4.create(), model, glMatrix.vec3.fromValues(factor, factor, factor));
    }

    static translate(model, transValues) {
        return glMatrix.mat4.translate(glMatrix.mat4.create(), model, transValues);
    }
}

class Mesh {
    constructor(webGlContext, vertices, indices) {
        this.webGL = webGlContext;
        this.vao = this.webGL.glContext.createVertexArray();
        this.vbo = this.webGL.glContext.createBuffer();
        this.ibo = this.webGL.glContext.createBuffer();
        this.vertices = vertices;
        this.indices = indices;
        this.transformations = [];
        this.color = glMatrix.vec4.fromValues(1, 1, 1, 1);

        this.webGL.glContext.bindVertexArray(this.vao)
            this.webGL.glContext.bindBuffer(this.webGL.glContext.ELEMENT_ARRAY_BUFFER, this.ibo)
                this.webGL.glContext.bufferData(this.webGL.glContext.ELEMENT_ARRAY_BUFFER, indices, this.webGL.glContext.STATIC_DRAW)
            this.webGL.glContext.bindBuffer(this.webGL.glContext.ELEMENT_ARRAY_BUFFER, null)

            this.webGL.glContext.bindBuffer(this.webGL.glContext.ARRAY_BUFFER, this.vbo)
                this.webGL.glContext.bufferData(this.webGL.glContext.ARRAY_BUFFER, vertices, this.webGL.glContext.STATIC_DRAW)
                this.webGL.glContext.vertexAttribPointer(0, 3, this.webGL.glContext.FLOAT, false, 0, null)
                this.webGL.glContext.enableVertexAttribArray(0)
            this.webGL.glContext.bindBuffer(this.webGL.glContext.ARRAY_BUFFER, null)
        this.webGL.glContext.bindVertexArray(null)
    }

    addTransformations(transformations ) {
        transformations.forEach(transform => this.transformations.push(transform));
    }

    setColor(color) {
        this.color = color;
    }

    render() {
        let modelMatrix = glMatrix.mat4.identity(glMatrix.mat4.create());
        this.transformations.forEach(transformation => {
           modelMatrix = transformation.func.apply(null, [modelMatrix, ...transformation.args])
        });
        this.webGL.bindUniformMat4("model", modelMatrix);
        this.webGL.bindUniformVec4("color", this.color);
        this.webGL.glContext.bindVertexArray(this.vao)
            this.webGL.glContext.bindBuffer(this.webGL.glContext.ELEMENT_ARRAY_BUFFER, this.ibo);
                this.webGL.glContext.drawElements(this.webGL.glContext.TRIANGLES, this.indices.length, this.webGL.glContext.UNSIGNED_BYTE, null)
            this.webGL.glContext.bindBuffer(this.webGL.glContext.ELEMENT_ARRAY_BUFFER, null);
        this.webGL.glContext.bindVertexArray(null)
    }
}

class Cuboid extends Mesh {
    constructor(webGlContext, width, height, depth) {
        super(
            webGlContext,
            new Float32Array([
                -width, -height,  depth,
                width, -height,  depth,
                width,  height,  depth,
                -width,  height,  depth,
                // back
                -width, -height, -depth,
                width, -height, -depth,
                width,  height, -depth,
                -width,  height, -depth
            ]),
            new Uint8Array([
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
            ])
        );
    }
}

