#ifndef TYPED_GAME_RUNTIME_H
#define TYPED_GAME_RUNTIME_H

#include "game/game_runtime.h"
#include "game/game.h"
#include "ui/view.h"

template <class Derived, class Base>
concept DerivedFrom = std::is_base_of_v<Base, Derived>;

template<class GameType, class ViewType>
requires (DerivedFrom<GameType, Game> && DerivedFrom<ViewType, View>)
class TypedGameRuntime final : public GameRuntime {
    GameType m_game{};

public:
    void start() override { m_game.start(); }
    std::optional<GameStatus> update() override { return m_game.update(); }
    std::function<std::unique_ptr<View>()> create_view(lvgl::Object &parent) override { return [this, &parent] { return std::make_unique<ViewType>(parent, m_game); }; }
    std::string name() const override { return m_game.name(); }
    std::string description() const override { return m_game.description(); }
};

#endif