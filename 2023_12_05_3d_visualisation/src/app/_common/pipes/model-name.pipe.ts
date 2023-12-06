import {Pipe, PipeTransform} from '@angular/core';
import {Mesh} from 'three';

@Pipe({
    name: 'modelName',
    standalone: true
})
export class ModelNamePipe implements PipeTransform {

    transform(value: Mesh): string {
        const nameParts = value.name.split('-');
        return nameParts.length > 1 ? nameParts.slice(0, -1).join('-') : nameParts[0]; // Join all elements except the last one
    }
}
