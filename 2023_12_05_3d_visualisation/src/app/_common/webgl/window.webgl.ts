import {
  AmbientLight,
  AxesHelper,
  Camera,
  DirectionalLight,
  GridHelper,
  Object3D,
  PerspectiveCamera,
  Raycaster,
  Scene,
  Vector2,
  WebGLRenderer
} from 'three';
import {ElementRef} from '@angular/core';
import {Observable, Subject} from 'rxjs';
import {OrbitControls} from 'three/examples/jsm/controls/OrbitControls.js';

export class WebGlWindow {
    private _mouseRayListener = new Subject<Raycaster>();

    private _scene = new Scene();
    private _axes = new AxesHelper(100);
    private _grid = new GridHelper(100, 100);

    private _camera: Camera;
    private _renderer?: WebGLRenderer;
    private _orbitalControls?: OrbitControls;

    constructor(private width: number, private height: number) {
        this._camera = new PerspectiveCamera(45, width / height, 0.1, 100);
        this._camera.position.z = 10;
        this._scene.add(this._camera);
    }

    render(canvas: ElementRef<HTMLCanvasElement>) {
        this._renderer = new WebGLRenderer({canvas: canvas.nativeElement, antialias: true});
        this._renderer.domElement.addEventListener(
            'click',
            (e) => this._mouseRayListener.next(this.getMouseRay(e.clientX, e.clientY)),
            true
        );

        this._orbitalControls = new OrbitControls(this._camera, this._renderer.domElement);
        this._orbitalControls.listenToKeyEvents(window)

        this._renderer.setSize(this.width, this.height);
        this._renderer.render(this._scene, this._camera);

        const ambientLight = new AmbientLight(0xFFFFFF, 0.2);
        this._scene.add(ambientLight);

        const directionalLight = new DirectionalLight(0xFFFFFF, 1.0);
        directionalLight.position.y = 2;
        this._scene.add(directionalLight);

        this._renderer.setAnimationLoop(() => {
            this._orbitalControls?.update();
            this._renderer?.render(this._scene, this._camera);
        });
    }

    showAxes(show: boolean) {
        if (show) {
            this._scene.add(this._axes);
        } else {
            this._scene.remove(this._axes);
        }
    }

    showGrid(show: boolean) {
        if (show) {
            this._scene.add(this._grid);
        } else {
            this._scene.remove(this._grid);
        }
    }

    addToScene(object: Object3D) {
        this._scene.add(object)
    }

    enableOrbitalControls(enable: boolean) {
        if (this._orbitalControls) {
            this._orbitalControls.enabled = enable;
        }
    }

    get mouseRayListener(): Observable<Raycaster> {
        return this._mouseRayListener.asObservable();
    }

    get camera(): Camera {
        return this._camera;
    }

    get renderer(): WebGLRenderer | undefined {
        return this._renderer;
    }

    private getMouseRay(mouseX: number, mouseY: number): Raycaster {
        const raycaster = new Raycaster();
        const mouse = new Vector2();
        mouse.x = (mouseX / this._renderer!.domElement.width) * 2 - 1;
        mouse.y = -(mouseY / this._renderer!.domElement.height) * 2 + 1;
        raycaster.setFromCamera(mouse, this._camera);
        return raycaster;
    }
}
