class WebGLContext {
    constructor(canvas) {
        try {
            this.glContext = canvas.getContext("webgl2")
            this.glContext.enable(this.glContext.DEPTH_TEST)
        } catch (err) {
            alert(err);
        }
    }

    addAndCompileShaders(shaderList) {
        this._program = this.glContext.createProgram();

        shaderList.forEach(shader => {
            const shaderId = this.glContext.createShader(shader.type);
            this.glContext.shaderSource(shaderId, shader.code);
            this.glContext.compileShader(shaderId);

            const shaderInfoLog = this.glContext.getShaderInfoLog(shaderId);
            if (shaderInfoLog.length > 0) {
                alert(`${shader.type} : ${shaderInfoLog}`);
            }
            this.glContext.attachShader(this._program, shaderId)
        });

        this.glContext.linkProgram(this._program);
        const programInfoLog = this.glContext.getProgramInfoLog(this._program);
        if (programInfoLog.length > 0) {
            alert(`Shader program : ${programInfoLog}`)
        }

    }

    drawToScreen(meshList) {
        this.glContext.clearColor(0, 0, 0, 1);
        this.glContext.clear(this.glContext.COLOR_BUFFER_BIT | this.glContext.DEPTH_BUFFER_BIT);

        this.glContext.useProgram(this._program);
        const projection = glMatrix.mat4.perspective(glMatrix.mat4.create(), glMatrix.glMatrix.toRadian(89.0), 1.0, 0.1, 100);
        this.bindUniformMat4("projection", projection);

        meshList.forEach(mesh => mesh.render());
        this.glContext.useProgram(null);
        let e = this.glContext.getError();
        if (e) {
            alert("Draw error: " + e);
        }
    }

    getUniformLocation(name) {
        return this.glContext.getUniformLocation(this._program, name);
    }

    bindUniformMat4(name, matrix) {
        const location = this.getUniformLocation(name)
        this.glContext.uniformMatrix4fv(location, false, matrix)
    }

    bindUniformVec4(name, vector) {
        const location = this.getUniformLocation(name)
        this.glContext.uniform4fv(location, vector)
    }
}