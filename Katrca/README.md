# Katrca 3D Visualisation

## Supported functionalities:

- New .obj import
- .obj repositioning
- state saving (assets folder)

## Adding new functionalities

### Interactive object

- Any loaded object can be accessed by it's name by calling the getModelByName method from webgl-window.service.ts
- To add interactions write a method in webgl-window service e.g. getModelByNameAndRotate and call it from wherever you need to

### Custom API connections

- Add new .api file to the app/_common/api folder which will contain api logic

