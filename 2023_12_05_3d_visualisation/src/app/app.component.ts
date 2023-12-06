import {Component, ElementRef, OnDestroy, OnInit, ViewChild} from '@angular/core';
import {CommonModule} from '@angular/common';
import {RouterOutlet} from '@angular/router';
import {SpeedDialModule} from 'primeng/speeddial';
import {MenuItem} from 'primeng/api';
import {WebGlWindowService} from './services/webgl-window.service';
import {SidebarModule} from 'primeng/sidebar';
import {PanelModule} from 'primeng/panel';
import {CardModule} from 'primeng/card';
import {ModelNamePipe} from './_common/pipes/model-name.pipe';
import {Mesh} from 'three';
import {Subscription} from 'rxjs';
import {SaveMeshService} from './services/save-mesh.service';
import {HttpClientModule} from '@angular/common/http';
import {FollowRoadCar} from './car/follow-road.car';

@Component({
    selector: 'app-root',
    standalone: true,
    imports: [CommonModule, HttpClientModule, RouterOutlet, SpeedDialModule, SidebarModule, PanelModule, CardModule, ModelNamePipe],
    templateUrl: './app.component.html',
    styleUrl: './app.component.scss',
})
export class AppComponent implements OnInit, OnDestroy {
    @ViewChild('webgl', {static: true}) private webgl!: ElementRef<HTMLCanvasElement>;
    @ViewChild('modelFilePicker', {static: true}) private modelFilePicker!: ElementRef<HTMLInputElement>;

    acceptModels = ['.obj']
    items: MenuItem[] = []
    selectedModel: Mesh | null = null;
    loadedModels = new Map<string, Mesh>([]);

    private _selectedModelSubscription?: Subscription;
    private _loadedModelsSubscription?: Subscription;

    constructor(private webglWindowService: WebGlWindowService, private saveMeshService: SaveMeshService, private followRoad: FollowRoadCar) {
    }

    onModelSelectedFromFile() {
        const files = this.modelFilePicker.nativeElement.files ?? new FileList();
        if (files.length === 0) return;
        const file: File = files[0];
        this.webglWindowService.loadModelFromFile(file);
    }

    ngOnInit() {
        this.webglWindowService.render(this.webgl);
        this.items = [
            {
                icon: 'pi pi-table',
                tooltip: 'Show grid',
                command: () => this.webglWindowService.toggleGrid()
            },
            {
                icon: 'pi pi-arrows-alt',
                tooltip: 'Show axes',
                command: () => this.webglWindowService.toggleAxes()
            },
            {
                icon: 'pi pi-plus',
                tooltip: 'Add model',
                command: () => this.modelFilePicker.nativeElement.click()
            }
        ];
        this.loadedModels = new Map<string, Mesh>();
        this._selectedModelSubscription = this.webglWindowService.selectedModelListener.subscribe((model) => this.selectedModel = model);
        this._loadedModelsSubscription = this.webglWindowService.loadedModelsListener.subscribe(models => {
            this.loadedModels = models;
        });
        this.webglWindowService.loadModelFromName('board');
        this.webglWindowService.loadModelFromName('stick');
        this.webglWindowService.loadModelFromName('wheel');
    }

    ngOnDestroy() {
        this._selectedModelSubscription?.unsubscribe();
        this._loadedModelsSubscription?.unsubscribe();
    }

    onSelectModel(name: string) {
        this.webglWindowService.selectModelByName(name);
    }

    onNameChange(event: Event, model: Mesh) {
        this.webglWindowService.setModelName(model, (event.target as HTMLInputElement).value)
    }

    onSaveClicked() {
        this.saveMeshService.saveToFile([...this.loadedModels.values()]);
    }
}
