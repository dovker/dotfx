#pragma once
#include "Clap.h"
#include "Components.h"

using namespace Clap;

namespace Game2D
{
    glm::vec2 ScreenspaceToWorld(const glm::vec2& position, const glm::mat4& matrix)
    {
        return glm::inverse(matrix) * glm::vec4((position.x/1280 - 0.5) * 2.0f, ((position.y/720 - 0.5f) * -2.0f), 0.0f, 1.0f);
    }
}