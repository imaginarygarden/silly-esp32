# Adding a game

Games in Silly consist of deterministic game rules, an LVGL view and one
catalog descriptor that connects the two. Keep game rules independent of LVGL,
ESP-IDF, Bluetooth and other hardware so they can run in tests and,
later, through different multiplayer transports.

## Module layout

Create a directory under `game/`:

```text
src/game/example/
├── example_command.h
├── example_descriptor.cpp
├── example_descriptor.h
├── example_game.cpp
├── example_game.h
├── example_phase.h          # Optional game-specific phases
├── example_state.h
├── example_view.cpp
└── example_view.h
```

Add rule tests under `tests/`, for example `tests/example_game_test.cpp`.

## 1. Add a route

Add a value to `GameRoute` in `game/game_route.h`. A route identifies a
game in navigation and catalog lookups; game logic should not depend on it.

## 2. Define state and commands

State is the read-only snapshot consumed by the view. It should contain game
data, not LVGL objects, callbacks, wall-clock timestamps or hardware handles.

```cpp
struct ExampleState final {
    std::uint32_t score{};
};
```

Commands describe player or presentation input:

```cpp
struct ExamplePress final {
    std::uint8_t index{};
};

using ExampleCommand = std::variant<ExamplePress>;
```

Prefer commands over exposing public mutation methods on the state.

## 3. Implement the rules

Derive the game from `Game`. The base class owns the common lifecycle:

- `IDLE`: constructed but not started
- `RUNNING`: receiving elapsed-time updates
- `PAUSED`: alive, but not receiving elapsed-time updates
- `FINISHED`: immutable terminal state with a result

Implement `_start()` and `_update(elapsed)`. Use the protected `_pause()`,
`_resume()` and `_finish(result)` transitions rather than duplicating lifecycle
flags in game state.

```cpp
class ExampleGame final : public Game {
   protected:
    void _start() override;
    void _update(std::chrono::milliseconds elapsed) override;

   public:
    using Game::input;
    void input(ExampleCommand command);

    [[nodiscard]] ExampleState state() const;
};
```

The rules must not read `steady_clock` directly. `GameSession` measures time and
passes elapsed durations to `update()`. Rules should also avoid global or
hardware randomness when deterministic behavior matters. 

Ignore game-specific commands while the base phase is `IDLE` or `FINISHED`.
Validate command values before indexing containers or changing state.

## 4. Implement the view

Derive the view from `View` and receive the concrete game by reference:

```cpp
class ExampleView final : public View {
    ExampleGame& m_game;

   public:
    ExampleView(lvgl::Object& parent, ExampleGame& game)
        : View{parent}, m_game{game} {}

    void build() override;
    void update() override;
};
```

The view may:

- Build and update LVGL widgets
- Read a state snapshot
- Translate UI events into typed game commands
- Report that a presentation animation has completed

The view should not decide wins or losses, alter state directly, measure gameplay
time or contain rules needed by another client. Put those decisions in the
game so local UI, tests and future multiplayer peers behave consistently.

Use components from `ui/component/` when one already represents the
required interaction or styling.

## 5. Register the game

Keep registration separate from the rule translation unit. This prevents the
host-testable game from acquiring LVGL dependencies.

Declare the descriptor in `example_descriptor.h`:

```cpp
extern const GameDescriptor EXAMPLE_GAME_DESCRIPTOR;
```

Define it in `example_descriptor.cpp`:

```cpp
const GameDescriptor EXAMPLE_GAME_DESCRIPTOR{
    GameRoute::EXAMPLE,
    "Example",
    "A short description shown before starting.",
    [] {
        return std::make_unique<
            TypedGameRuntime<ExampleGame, ExampleView>>();
    },
};
```

Finally, add the descriptor to `GameFactory::m_descriptors`. The menu and runtime
creation both consume this catalog entry, so no separate menu button or factory
switch is needed.

## 6. Add tests

Compile rule tests with the native compiler, not ESP-IDF. Add the rule `.cpp`
files to a test executable in `tests/CMakeLists.txt`; do not add descriptor or
view files to that executable.

At minimum, test:

- initial state and lifecycle phase;
- starting and repeated starts;
- valid commands and expected state transitions;
- invalid and out-of-range commands;
- pause and elapsed-time behavior;
- every terminal result;
- commands and updates after finishing;
- important boundary values;
- deterministic behavior for a known random source or seed.

Run all host tests locally with:

```sh
cmake -S tests -B build-tests -DCMAKE_BUILD_TYPE=Debug
cmake --build build-tests --parallel
ctest --test-dir build-tests --output-on-failure --no-tests=error
```

The same commands run in CI. Tests are expected for game rules because
they are fast and hardware-independent. ESP-IDF CI still verifies that rules,
views, catalog registration and hardware adapters compile together as firmware.

## Completion checklist

- [ ] Rule code has no LVGL, ESP-IDF, Bluetooth or hardware dependency.
- [ ] State contains no presentation objects or wall-clock timestamps.
- [ ] The base lifecycle is used consistently.
- [ ] Commands are ignored before start and after finish.
- [ ] All indices and external values are validated.
- [ ] Metadata and runtime construction are defined in one descriptor.
- [ ] The descriptor is added to `GameFactory`.
- [ ] The menu entry is generated from the catalog.
- [ ] Rule tests cover normal, invalid, timeout and terminal paths.
- [ ] Tests and the ESP-IDF build pass in CI.
