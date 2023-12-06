import {ApplicationConfig} from '@angular/core';
import {provideRouter} from '@angular/router';

import {routes} from './app.routes';
import {provideClientHydration} from '@angular/platform-browser';
import {WEBGL_WINDOW_HEIGHT, WEBGL_WINDOW_WIDTH} from './services/webgl-window.service';
import {provideHttpClient} from '@angular/common/http';

export const appConfig: ApplicationConfig = {
    providers: [
        provideRouter(routes),
        provideClientHydration(),
        provideHttpClient(),
        {
            provide: WEBGL_WINDOW_WIDTH,
            useValue: 1920 * 0.8
        },
        {
            provide: WEBGL_WINDOW_HEIGHT,
            useValue: 1080
        },
    ]
};
