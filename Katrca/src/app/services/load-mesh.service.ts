import {Injectable} from '@angular/core';
import {Object3D} from 'three';
import {OBJLoader} from 'three/examples/jsm/loaders/OBJLoader.js';
import {WebGLModelFactory} from '../_common/webgl';
import {LocalFileReaderApi} from '../_common/api/local-file-reader.api';
import {from, map} from 'rxjs';

@Injectable({providedIn: 'root'})
export class LoadMeshService {

    constructor(private fileReader: LocalFileReaderApi) {
    }

    async loadFromFile(file: File): Promise<Object3D> {
        const data = await file.text();
        const loader = new OBJLoader();
        return loader.parse(data);
    }

    loadFromData(data: string): Object3D {
        const loader = new OBJLoader();
        return loader.parse(data);
    }


    async loadModelFromFile(file: File) {
        const data = await this.loadFromFile(file);
        const name = file.name.split('.').slice(0, -1).join('.');
        return WebGLModelFactory.createBasic(data, name);
    }

    async loadModelFromName(modelName: string) {
        return from(this.fileReader.readFile(`${modelName}.obj`)).pipe(
            map((data) => {
                const object = this.loadFromData(data);
                const meshList = WebGLModelFactory.createBasic(object, modelName);
                return meshList;
            })
        );
    }
}
