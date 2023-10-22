

$(document).ready(() => {
    const canvas = document.getElementById('myCanvas');
    const webGlContext = new WebGLContext(canvas);

    webGlContext.addAndCompileShaders( [
        { type: webGlContext.glContext.VERTEX_SHADER, code: $("#simple-vs").text() },
        { type: webGlContext.glContext.FRAGMENT_SHADER, code: $("#simple-fs").text() }
    ]);

    const leftCube = new Cuboid(webGlContext,1, 1, 1);
    leftCube.addTransformations([
        { func: MeshTransform.translate, args: [ glMatrix.vec3.fromValues(-0.3, -0.6, -2.5) ] },
        { func: MeshTransform.scaleAll, args: [ 0.3 ] },
    ]);

    const rightCube = new Cuboid(webGlContext,1, 1, 1);
    rightCube.addTransformations([
        { func: MeshTransform.translate, args: [ glMatrix.vec3.fromValues(0.3, -0.6, -2.5) ] },
        { func: MeshTransform.scaleAll, args: [ 0.3 ] },
    ]);

    const topCube = new Cuboid(webGlContext,1, 1, 1);
    topCube.addTransformations([
        { func: MeshTransform.translate, args: [ glMatrix.vec3.fromValues(0.0, 0.0, -2.5) ] },
        { func: MeshTransform.scaleAll, args: [ 0.3 ] },
    ]);

    const floor = new Cuboid(webGlContext,3, 0.1, 2);
    floor.addTransformations([
        { func: MeshTransform.translate, args: [ glMatrix.vec3.fromValues(0, -0.9, -2.5) ] },
        { func: MeshTransform.scaleAll, args: [ 0.3 ] },
    ]);

    leftCube.setColor(glMatrix.vec4.fromValues(1, 1, 0, 1));
    rightCube.setColor(glMatrix.vec4.fromValues(1, 0, 0, 1));
    topCube.setColor(glMatrix.vec4.fromValues(1, 0, 1, 1));
    floor.setColor(glMatrix.vec4.fromValues(0, 1, 0, 1));

    setInterval(() => webGlContext.drawToScreen([leftCube, rightCube, topCube, floor]), 33);
});