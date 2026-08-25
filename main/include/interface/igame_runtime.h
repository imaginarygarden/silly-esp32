#ifndef IGAME_RUNTIME_H
#define IGAME_RUNTIME_H

#include "ui/view.h"
#include "enum/status.h"

#include "lvgl_cpp.h"

#include <optional>
#include <memory>

class IGameRuntime {
public:
    virtual ~IGameRuntime() = default;
    virtual void start() = 0;
    virtual std::optional<Status> update() = 0;
    virtual std::unique_ptr<View> create_view(lvgl::Object &parent) = 0;
    virtual std::string name() const = 0;
    virtual std::string description() const = 0;
};

#endif