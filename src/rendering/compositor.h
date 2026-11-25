#pragma once

namespace glab {

namespace scene {

class Scene;

}

namespace rendering {

class Compositor {
public:
    void BeginFrame();
    void Render(scene::Scene& scene);
    void EndFrame();
};

}  // namespace rendering

}  // namespace glab
