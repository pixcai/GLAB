#include "node.h"

#include <spdlog/spdlog.h>

namespace glab::scene {

Node::Node() : id(id_pool.Allocate()) { spdlog::debug("Node(index={}, generation={})", id.index, id.generation); }

Node::~Node() {
    spdlog::debug("~Node(index={}, generation={})", id.index, id.generation);
    id_pool.Deallocate(id);
}

}  // namespace glab::scene
