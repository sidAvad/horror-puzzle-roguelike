# Horror Puzzle Roguelike

## Stack
- Language: C with raylib
- Build target: WebAssembly via Emscripten
- Preview URL: https://sidavad.github.io/horror-puzzle-roguelike

## Workflow
I'm controlling this session from my iPhone and Mac. Keep responses concise.
After every code change, run `./deploy.sh` to build and deploy.
Confirm when it's live and briefly describe what changed in one sentence.

## After Every Code Change
1. Edit code in `src/main.c`
2. Run `./deploy.sh`
3. If the build fails, show me only the first compiler error — not the full log
4. If it succeeds, confirm it's deployed and summarize the change in one sentence

## Rules
- NEVER touch anything in `assets/` — sprites and sounds are managed locally
- NEVER edit files in `build/` directly
- Keep all game logic in `src/main.c` unless asked to split files
- When asked for multiple changes, batch them into a single build — don't deploy after each one

## Game Context
Horror puzzle roguelike. Top-down perspective. Dark atmosphere.
Player explores procedurally generated rooms solving puzzles to escape.

## Current State
Blank slate — title screen only. Next: define core game loop and room structure.
