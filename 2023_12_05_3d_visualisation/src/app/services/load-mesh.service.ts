import {Injectable} from '@angular/core';
import {Object3D} from 'three';
import {OBJLoader} from 'three/examples/jsm/loaders/OBJLoader.js';

@Injectable({providedIn: 'root'})
export class LoadMeshService {
    async loadFromFile(file: File): Promise<Object3D> {
        const data = await file.text();
        const loader = new OBJLoader();
        return loader.parse(data);
    }

    loadFromData(data: string): Object3D {
        const loader = new OBJLoader();
        return loader.parse(data);
    }
}
