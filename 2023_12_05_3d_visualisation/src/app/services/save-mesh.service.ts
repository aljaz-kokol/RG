import {Injectable} from '@angular/core';
import {Mesh} from 'three';
import {OBJExporter} from 'three/examples/jsm/exporters/OBJExporter.js';
import {saveAs} from 'file-saver';
import {ModelNamePipe} from '../_common/pipes/model-name.pipe';

@Injectable({providedIn: 'root'})
export class SaveMeshService {
    saveToFile(meshList: Mesh[]) {
        const namePipe = new ModelNamePipe();
        const exporter = new OBJExporter();
        meshList.forEach(model => {
            const data = exporter.parse(model);
            saveAs(new Blob([data], {type: 'application/object'}), `assets/${namePipe.transform(model)}.obj`)
        });
    }
}
