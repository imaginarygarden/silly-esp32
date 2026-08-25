#ifndef GAME_RUNTIME_H
#define GAME_RUNTIME_H

#include "interface/igame_runtime.h"
#include "interface/igame.h"
#include "ui/view.h"

template <class Derived, class Base>
concept DerivedFrom = std::is_base_of_v<Base, Derived>;

template<class GameType, class ViewType>
requires (DerivedFrom<GameType, IGame> && DerivedFrom<ViewType, View>)
class GameRuntime final : public IGameRuntime {
    GameType m_game{};

public:
    void start() override { m_game.start(); }
    std::optional<Status> update() override { return m_game.update(); }
    std::unique_ptr<View> create_view(lvgl::Object &parent) override { return std::make_unique<ViewType>(parent, m_game); }
    std::string name() const override { return m_game.name(); }
    std::string description() const override { return m_game.description(); }
};

#endif