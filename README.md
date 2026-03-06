# ⚔️ Valinor Engine

> *A custom C++20 graphics engine built for learning, portfolio, and industry relevance — bridging Software Engineering fundamentals with modern Game Programming and Technical Art.*

---

## Overview

**Valinor Engine** is a custom-built graphics engine developed in **C++20**, designed as an educational and professional project that demonstrates deep knowledge in **real-time rendering**, **system architecture**, and **data-oriented design** — the exact skill set expected from a Graphics Programmer, Game Developer, or Technical Artist in the modern games industry.

The engine is being developed incrementally, with each module serving both a learning purpose and a portfolio-ready deliverable. The architecture draws inspiration from production engines like **RE Engine (Capcom)**, **BlackSpace Engine (Pearl Abyss)**, and **Unreal Engine**, while maintaining a lean, readable codebase optimized for study and extension.

> **Status:** 🚧 In active development — architecture and core systems being established.

---

## Goals

- Demonstrate applied knowledge of **real-time graphics**, **engine architecture**, and **modern C++**
- Build a foundation for freelance tools, technical demos, and game prototypes
- Serve as a portfolio piece for applications to programs at **Vertex School** and **FutureGames**
- Progressively evolve toward production-quality rendering with Vulkan support

---

## Architecture

Valinor Engine is designed around three core principles: **Ortogonality**, **Domain-Driven Design (DDD)**, and **Data-Oriented Design (DOD)**. These are not in conflict — they operate at different layers of the system.

```
┌─────────────────────────────────────────────────────────────┐
│                        Editor Layer                         │
│               (MVC — ImGui + SDL2 + OpenGL)                 │
├──────────────────────────┬──────────────────────────────────┤
│      Game Domain         │        Engine Core               │
│  (DDD — Bounded          │  (ECS via EnTT — DOD,            │
│   Contexts, Events)      │   Cache-Friendly Systems)        │
├──────────────────────────┴──────────────────────────────────┤
│                    RHI — Render Hardware Interface          │
│          (Abstract layer — no OpenGL/Vulkan leakage)        │
├───────────────────────────┬─────────────────────────────────┤
│   Engine_OpenGL (now)     │   Engine_Vulkan (planned)       │
│   SPIR-V Shaders (GLSL)   │   Full Vulkan backend           │
└───────────────────────────┴─────────────────────────────────┘
```

### Layer Breakdown

| Layer | Pattern | Responsibility |
|---|---|---|
| **Editor** | MVC | Visual tools, level editing, asset inspection (ImGui) |
| **Game Domain** | DDD | Game rules, entities, events, bounded contexts |
| **Engine Core** | ECS (EnTT) | Transform, Physics, Render components — DOD / cache-friendly |
| **RHI** | Strategy + Interface | Abstracts all GPU API calls behind pure C++ interfaces |
| **Backend** | OpenGL 4.5 → Vulkan | Concrete implementations hidden from all other layers |

---

## Technology Stack

| Component | Technology | Rationale |
|---|---|---|
| **Language** | C++20 | Concepts, coroutines, ranges — modern and safe |
| **Graphics (current)** | OpenGL 4.5+ (DSA) | Rapid iteration; RHI-ready for Vulkan migration |
| **Graphics (planned)** | Vulkan | Industry standard for high-performance rendering |
| **Shader Pipeline** | GLSL → SPIR-V | Pre-compiled at build time via `glslc` (CMake step) |
| **ECS** | EnTT | Production-proven, header-only, cache-friendly |
| **Windowing / Input** | SDL2 | Cross-platform, audio, controller support |
| **Mathematics** | GLM | Industry standard, mirrors GLSL conventions |
| **Build System** | CMake | Modular, portable, industry expected |
| **Containerization** | Docker | Reproducible builds and future deploy targets |
| **Memory** | Custom Allocators (Pool/Arena) | Performance-critical paths, no heap fragmentation |

---

## CMake Module Structure

```
Valinor/
├── Engine_Core/        # Math, Memory, Allocators (no dependencies)
├── Engine_RHI/         # Abstract render interfaces (no GL/Vulkan headers)
├── Engine_OpenGL/      # Concrete OpenGL 4.5 backend (depends on RHI)
├── Engine_Vulkan/      # (Planned) Vulkan backend (depends on RHI)
├── Engine_Platform/    # SDL2, Input, Window management
├── Engine_ECS/         # EnTT integration, system registration
├── Engine_Assets/      # Async asset loading, shader compilation
├── Engine_Editor/      # ImGui tools, MVC-based level editor
└── Sandbox/            # Demo projects and rendering experiments
```

Each module compiles as a **static library** with strict dependency rules enforced via CMake — no circular dependencies, no API leakage between domains.

---

## Render Hardware Interface (RHI)

A core architectural decision: **zero OpenGL or Vulkan types are ever exposed outside the rendering module.**

The RHI defines pure abstract interfaces for all GPU resources:

```cpp
// Engine_RHI — no GL headers here
class Texture2D {
public:
    virtual ~Texture2D() = default;
    virtual void Bind(uint32_t slot = 0) const = 0;
    static std::shared_ptr<Texture2D> Create(uint32_t w, uint32_t h);
};

class Shader {
public:
    virtual void Bind() const = 0;
    virtual void SetUniform(const std::string& name, const glm::mat4&) = 0;
    static std::shared_ptr<Shader> Create(const std::filesystem::path& spirv);
};
```

Shaders are written in **GLSL (450+)** and compiled to **SPIR-V binaries** as a CMake pre-build step — eliminating runtime shader compilation stutters and making them Vulkan-ready without rewriting.

---

## ECS and Data-Oriented Design

Game objects are not class hierarchies. They are **entities** (IDs) with **components** (plain data) processed by **systems** (logic).

```cpp
// Components — plain data, no behavior
struct Transform { glm::vec3 position; glm::quat rotation; glm::vec3 scale; };
struct MeshRenderer { AssetHandle mesh; MaterialHandle material; };

// System — iterates contiguous memory, cache-friendly
void RenderSystem::Update(entt::registry& registry) {
    auto view = registry.view<Transform, MeshRenderer>();
    for (auto [entity, transform, renderer] : view.each()) {
        // All data is contiguous — no cache misses
        SubmitDrawCall(transform, renderer);
    }
}
```

This mirrors patterns used in **Unity DOTS**, **Unreal's Mass Entity**, and production engines at Naughty Dog and EA.

---

## Key Architectural Principles

**Ortogonality** — No module knows about another's implementation. Communication happens through interfaces, events, or the ECS registry.

**DDD Bounded Contexts** — `AssetManagement`, `WorldSimulation`, `HardwareRendering`, and `EditorTools` are treated as separate domains with explicit boundaries.

**RAII by Default** — No raw `new`/`delete`. All resources are managed via `std::unique_ptr`, `std::shared_ptr`, or custom RAII wrappers. Memory safety is not optional.

**Vulkan-Forward** — Every OpenGL decision is made with future Vulkan migration in mind: SPIR-V shaders, command buffer abstraction, Pipeline State Objects, and explicit render passes.

---

## Roadmap

- [x] Project structure and CMake module skeleton
- [ ] RHI interface layer definition
- [ ] OpenGL 4.5 backend (DSA)
- [ ] SDL2 window and input system
- [ ] SPIR-V shader pipeline (CMake + glslc)
- [ ] EnTT ECS integration
- [ ] Basic 3D rendering (mesh, camera, transforms)
- [ ] PBR material system (GLSL)
- [ ] ImGui editor foundation (MVC)
- [ ] Custom memory allocators (Pool/Arena)
- [ ] Async asset loading
- [ ] Vulkan backend (Engine_Vulkan module)
- [ ] Compute shader experiments (fluid, particles)

---

## About the Author

Developed by Tiago Peniche - a Software Engineering graduate combining formal training in **system architecture, design patterns, and software engineering** with a deep interest in **real-time graphics, game engine development, and technical art**.

This project targets a career path in **Game Programming** and **Technical Art** — with specific interest in roles at studios that value both engineering rigor and creative output.

---

*Valinor Engine is an independent study project. Inspired by RE Engine, BlackSpace Engine, and the open-source game engine community.*