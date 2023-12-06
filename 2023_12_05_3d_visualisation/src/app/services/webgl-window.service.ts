import {ElementRef, Inject, Injectable, InjectionToken, OnDestroy} from '@angular/core';
import {WebGLModelFactory, WebGlWindow} from '../_common/webgl';
import {Box3, Color, MathUtils, Mesh, MeshStandardMaterial, Raycaster, Vector3} from 'three';
import {Observable, Subject, Subscription} from 'rxjs';
import {DragControls} from 'three/examples/jsm/controls/DragControls.js';
import {LoadMeshService} from './load-mesh.service';
import {LocalFileReaderApi} from '../_common/api/local-file-reader.api';

export const WEBGL_WINDOW_WIDTH = new InjectionToken<number>('webgl-window-width');
export const WEBGL_WINDOW_HEIGHT = new InjectionToken<number>('webgl-widow-height');

@Injectable({providedIn: 'root'})
export class WebGlWindowService implements OnDestroy {
    private _showAxes: boolean = false;
    private _showGrid: boolean = false;
    private _modelsMap: Map<string, Mesh> = new Map<string, Mesh>();
    private _selectedModel: Mesh | null = null;
    private _webglWindow: WebGlWindow;

    private _clickSubscription: Subscription;
    private _loadedModelsListener = new Subject<Map<string, Mesh>>()
    private _selectedModelListener = new Subject<Mesh | null>()

    constructor(
        @Inject(WEBGL_WINDOW_WIDTH) private _width: number,
        @Inject(WEBGL_WINDOW_HEIGHT) private _height: number,
        private loadMeshService: LoadMeshService,
        private fileReader: LocalFileReaderApi
    ) {
        this._webglWindow = new WebGlWindow(_width, _height);
        this._showAxes = false;
        this._showGrid = false;
        this._modelsMap = new Map<string, Mesh>()
        this._clickSubscription = this._webglWindow.mouseRayListener.subscribe((ray) => this.onModelClicked(ray));

        this.selectedModelListener.subscribe((selected: Mesh | null) => {
            if (selected === null) return;
            const dragControls = new DragControls([selected], this._webglWindow.camera, this._webglWindow!.renderer!.domElement);

            dragControls.addEventListener('hoveron', () => {
                this._webglWindow.enableOrbitalControls(false);
            });
            dragControls.addEventListener('hoveroff', () => {
                this._webglWindow.enableOrbitalControls(true);
            });
        });
    }

    ngOnDestroy() {
        this._clickSubscription.unsubscribe();
    }

    render(canvas: ElementRef<HTMLCanvasElement>) {
        this._webglWindow.render(canvas);
    }

    toggleAxes() {
        this._showAxes = !this._showAxes;
        this._webglWindow.showAxes(this._showAxes);
    }

    toggleGrid() {
        this._showGrid = !this._showGrid;
        this._webglWindow.showGrid(this._showGrid);
    }

    async loadModelFromFile(file: File) {
        const data = await this.loadMeshService.loadFromFile(file);
        const name = file.name.split('.').slice(0, -1).join('.');
        const meshList = WebGLModelFactory.createBasic(data, name);
        meshList.forEach((mesh: Mesh) => {
            this._webglWindow.addToScene(mesh);
            this._modelsMap.set(mesh.name, mesh);
        });
        this._loadedModelsListener.next(this._modelsMap);
    }

    async loadModelFromName(modelName: string) {
        return this.fileReader.readFile(`${modelName}.obj`).subscribe((data) => {
            const object = this.loadMeshService.loadFromData(data);
            const meshList = WebGLModelFactory.createBasic(object, modelName);
            meshList.forEach((mesh: Mesh) => {
                this._webglWindow.addToScene(mesh);
                this._modelsMap.set(mesh.name, mesh);
            });
            this._loadedModelsListener.next(this._modelsMap);
        })
    }

    get loadedModelsListener(): Observable<Map<string, Mesh>> {
        return this._loadedModelsListener.asObservable();
    }

    get selectedModelListener(): Observable<Mesh | null> {
        return this._selectedModelListener.asObservable();
    }

    async getModelByNameAndRotate(modelName: string, angle: number) {
        if (!this._modelsMap.has(modelName)) return;

        const model = this._modelsMap.get(modelName)!;

        // Convert the angle to radians
        const angleInRadians = MathUtils.degToRad(angle);

        // Assuming the model is a Three.js object3D
        // Set the rotation origin to the center of the model
        const boundingBox = new Box3().setFromObject(model);
        const center = boundingBox.getCenter(new Vector3(0, 0, 0));

        const originalPosition = model.position.clone();
        console.log(originalPosition);
        // Move the model to the origin
        model.rotation.set(0, 0, 0);
        model.rotateOnWorldAxis(new Vector3(0, 0, 1), angle);
        model.translateZ(3);
    }

    hasModel(name: string): boolean {
        return this._modelsMap.has(name);
    }

    selectModelByName(name: string) {
        if (this._selectedModel !== null) {
            (this._selectedModel?.material as MeshStandardMaterial).color = new Color(0xFFFFFF);
        }
        this._selectedModel = this._modelsMap.get(name) ?? null;
        (this._selectedModel?.material as MeshStandardMaterial).color = new Color(0x00FF00);
        this._selectedModelListener.next(this._selectedModel);
    }

    setModelName(model: Mesh, newName: string) {
        const existingModel = this._modelsMap.get(model.name);

        if (existingModel) {
            this._modelsMap.set(newName, existingModel);
            this._modelsMap.delete(model.name);
            existingModel.name = newName;  // Update the name property of the model
        }
    }

    private onModelClicked(mouseRay: Raycaster) {
        const intersects = mouseRay.intersectObjects([...this._modelsMap.values()], true); //array
        if (this._selectedModel !== null) {
            (this._selectedModel?.material as MeshStandardMaterial).color = new Color(0xFFFFFF);
        }
        if (intersects.length > 0) {
            this._selectedModel = intersects[0].object as Mesh;
            (this._selectedModel?.material as MeshStandardMaterial).color = new Color(0x00FF00);
        } else {
            this._selectedModel = null;
        }
        this._selectedModelListener.next(this._selectedModel);
    }


}
