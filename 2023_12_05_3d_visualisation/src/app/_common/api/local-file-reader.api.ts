import {Injectable} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Observable} from 'rxjs';

@Injectable({providedIn: 'root'})
export class LocalFileReaderApi {
    constructor(private httpClient: HttpClient) {
    }

    readFile(fileName: string): Observable<string> {
        return this.httpClient.get(`assets/${fileName}`, {responseType: 'text'});
    }
}
