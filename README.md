# [DEPRECATED] Fluid Simulation (SFML/C++17)

> **This project is deprecated and no longer maintained.**
> Superseded by [particle-sim](https://github.com/cpeddle/particle-sim) — a GPU-accelerated particle simulation framework using C++23, CUDA, and OpenGL.

## What This Was

An early configurable 2D particle simulator used for fluid simulation experiments. Built with SFML 2.6.x and C++17, it implemented:

- SPH-style density calculation with smoothing kernels
- Density heatmap background visualisation
- TOML-based configuration system
- Spatial grid partitioning for neighbour queries
- Factory pattern for particle spawning (grid and random layouts)
- Boundary collision with damping

## Why It Was Deprecated

A comparative analysis identified that the successor project (particle-sim) provides:

- **1000x particle scaling** — GPU-accelerated via CUDA vs CPU-bound single-threaded
- **Extensible architecture** — Strategy pattern with `ISimulationModel` and `ISpatialIndex` interfaces
- **Zero-copy rendering** — CUDA-GL interop eliminates CPU-GPU data transfer
- **Proper separation of concerns** — Rendering, compute, spatial indexing, and UI are decoupled
- **Modern C++23** — Non-owning views, namespaces, interface contracts

See [docs/COMPARISON_RESEARCH.md](docs/COMPARISON_RESEARCH.md) for the full comparative analysis, including transferable aspects that informed the successor design.

## Transferable Learnings

The following aspects from this project were identified as valuable for the successor:

| Aspect | Priority | Notes |
|--------|----------|-------|
| TOML config system | High | Working `ConfigReader` with toml11 |
| Smoothing kernel function | High | Cubic falloff influence function |
| Density & gradient calculation | High | SPH density estimation via finite differences |
| Density heatmap visualisation | Medium | Blue-to-red debug overlay |
| Boundary collision + damping | Medium | Reflection with energy loss |
| Factory spawn patterns | Low | Grid and random initial distributions |
| Vector/arrow debug drawing | Low | Gradient visualisation overlay |

## Original References

- Inspired by [Sebastian Lague's Fluid Sim](https://github.com/SebLague/Fluid-Sim/tree/main)
- Built from the [SFML CMake project template](https://github.com/SFML/cmake-sfml-project)

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
