# Cloth simulation

Simple cloth simulation in C using raylib

[![Watch the video](https://img.youtube.com/vi/N-ff9OTw24g/0.jpg
)](https://youtu.be/N-ff9OTw24g)
# Run it yourself :)

Simply download it and run
```sh
make
```
then

```sh
make run
```

If you have raylib installed, it should work

## Verlet

The solution is found using verlet integration with 8 substeps, part of the code for the integration comes from [here](https://www.youtube.com/watch?v=lS_qeBy3aQI) (I recommand watching it if you are unfamiliar with that)

To apply constrains, some node are set to constrained, meaning their position will never change and they are skipped when performing integration

## Rendering

Most of the hardwork is done by raylib, the cloth is stored as a struct containing an array of links and nodes where a link points to two node and has a boolean to know if it was already cut or not

When trying to see wheter we hit or not a node, raylib gives us the nodes position on the screen canvas

## Cloth

The cloth data structure is defined here and serves as the mesh for computation and rendering
```c
typedef struct Point {
    Vector3 position;
    Vector3 acceleration;
    Vector3 old_position;
    bool constrained;
} ClothPoint;

typedef struct Link {
    int x1;
    int x2;
    bool skip;
} ClothLink;

typedef struct Cloth {
    int n_point;
    ClothPoint* points;
    int n_link;
    ClothLink* links;
} Cloth;
```
As you can see it is quite simple, the quad mesh comes from the generation algorithm, here we simply make squares

Most of the code is in `cloth.c` and is there simply to create the data structure, this takes some time at startup but once done the rendering is done it runs smoothly

Reagarding the "wind" this is added to avoid a stalling cloth, a simple acceleration is added to each node

## Performance

Overall you can expect 300 FPS on average with some lower time at startup

