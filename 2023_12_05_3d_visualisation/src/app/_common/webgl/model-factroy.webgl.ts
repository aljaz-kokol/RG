import {Mesh, MeshStandardMaterial, Object3D} from 'three';

export abstract class WebGLModelFactory {
    static createBasic(data: Object3D, name: string = ''): Mesh[] {
        const meshList: Mesh[] = [];
        data.children.forEach((object: Object3D, index: number) => {
            const geometry = (object as Mesh).geometry;
            const material = new MeshStandardMaterial({color: 0xFFFFFF});
            const mesh = new Mesh(geometry, material);
            mesh.name = meshList.length > 1 ? `${index}-${name}` : name;
            meshList.push(mesh);
        });
        return meshList;
    }
}
