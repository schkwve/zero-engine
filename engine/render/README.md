# Renderer

The renderer subsystem is split into two different parts:

- Frontend
- Backend

### Renderer Frontend

This part of the rendering subsystem is responsible for communicating with other parts of the engine, abstracting the actual rendering (Vulkan/OpenGL/DirectX/etc.) away.

### Renderer Backend

This part of the rendering subsystem manages the actual rendering process. The backend consists of actually using Vulkan (or others!), so this part will only ever talk to the frontend, which abstracts the differences between these libraries away.