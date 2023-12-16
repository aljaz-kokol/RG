import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';

@Injectable({providedIn: 'root'})
export class RandomNumberApi {
    constructor(private http: HttpClient) {
    }

    getRandomNumber(): Observable<number[]> {
        return this.http.get<number[]>('http://localhost:3000/api/random');
    }
}
