#pragma once

#include "../namespace.h"

GLAB_NAMESPACE_BEGIN()

class Scene;
class Renderer;

struct Component {
    Component() = default;
    virtual ~Component() = default;
};

struct Mesh;
struct Shader;

template <typename T>
class ResourceHandle;

GLAB_NAMESPACE_END()
