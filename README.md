# HR Guinea Drive

HR Guinea Drive is a realistic offline-first driving game inspired by Guinea.

## Current phase

**Phase D — Unreal Engine migration / Mamou vertical slice**

The Base44/Web prototype is kept only as a historical prototype. The main game is now being rebuilt for Unreal Engine 5.8 with a native-first architecture focused on realistic visuals, real-world-inspired geography, offline play, mobile performance, and long-term scalability.

## First playable target

A realistic 1–3 km Mamou vertical slice containing:

- a realistic player character;
- a detailed starter vehicle inspired by the Toyota Verso;
- Chaos Vehicles driving physics;
- cockpit and chase cameras;
- Guinea-inspired roads, terrain, vegetation, buildings and traffic;
- local/offline saves;
- mobile-first performance targets;
- data-driven route architecture for future Mamou → Kindia → Coyah → Conakry expansion.

## Engine

- Unreal Engine 5.8
- C++ + Blueprints
- Chaos Vehicles
- Enhanced Input

## Important

Do not commit generated Unreal folders such as `Binaries`, `DerivedDataCache`, `Intermediate`, or `Saved`.
Large binary assets are configured for Git LFS through `.gitattributes`.
