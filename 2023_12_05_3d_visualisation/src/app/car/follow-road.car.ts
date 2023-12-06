import {Injectable} from '@angular/core';
import {interval} from 'rxjs';
import {switchMap} from 'rxjs/operators';
import {RandomNumberApi} from '../_common/api/random-number.api';
import {WebGlWindowService} from '../services/webgl-window.service';

@Injectable({providedIn: 'root'})
export class FollowRoadCar {
    private rotationInterval$ = interval(150);

    constructor(
        private randomNumberApi: RandomNumberApi,
        private windowService: WebGlWindowService
    ) {
    }

    rotateWheel(wheelModelName: string) {
        if (!this.windowService.hasModel(wheelModelName)) {
            this.windowService.loadModelFromName(wheelModelName).then(() => {
                this.rotationInterval$.pipe(switchMap(() => this.randomNumberApi.getRandomNumber()))
                    .subscribe((numbers) => {
                        numbers.forEach((angle: number) => {
                            this.windowService.getModelByNameAndRotate(wheelModelName, angle).then();
                        });
                    });
            });
        } else {
            this.rotationInterval$.pipe(switchMap(() => this.randomNumberApi.getRandomNumber()))
                .subscribe((numbers) => {
                    numbers.forEach((angle: number) => {
                        this.windowService.getModelByNameAndRotate(wheelModelName, angle).then();
                    });
                });
        }

    }
}
