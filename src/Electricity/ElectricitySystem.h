#pragma once
#include "Clap.h"
#include "Components.h"
#include "Utils.h"

using namespace Clap;

namespace Game2D
{
    class ElectricitySystem : public System
    {
    public:
        ElectricitySystem(Ref<World> world) : System(world) {}

        void OnInit() override
        {
            m_Elements = TileMap<Entity>::Create(100, 100, NULL_ENTITY);
            m_Texture = Texture2D::Create("../../../Game2D/res/textures/ElectricTilemap.png");
            m_World->RegisterComponent<ElectricalComponent>();
        }

        void OnUpdate(double deltaTime) override
        {
            for(int i = 0; i < 100; i++)
            {
                for(int j = 0; j < 100; j++)
                {
                    Entity e = m_Elements->At(i, j);
                    if(e != NULL_ENTITY && m_World->HasComponent<ElectricalComponent>(e))
                    {
                        auto eComp = m_World->GetComponent<ElectricalComponent>(e);
                        if(eComp.Type == ElectricalType::BATTERY)
                        {
                            std::deque<Entity> visited;
                            //Traverse()
                        }
                    }
                }
            }
        }
        void OnEvent(Event& e)
        {
            switch(e.Type)
            {
                case EventType::MouseButtonPressed:
                    if(e.Data.MouseButtonEvent.MouseCode == MOUSE_BUTTON_LEFT)
                    {
                        m_LeftMouseDown = true;
                    }
                break;
                case EventType::MouseButtonReleased:
                    if(e.Data.MouseButtonEvent.MouseCode == MOUSE_BUTTON_LEFT && m_LeftMouseDown)
                    {
                        m_LeftMouseDown = false;

                        glm::vec2 ClickPosition = {0.0f, 0.0f};
                        for(Entity e : m_World->GetGroup<TransformComponent, CameraComponent>())
                        {
                            CameraComponent camera = m_World->GetComponent<CameraComponent>(e);
                            if(camera.Primary)
                            {
                                auto cameraTransform = m_World->GetComponent<TransformComponent>(e).GetTransform();
                                auto cameraProjection = camera.Projection;
                                ClickPosition = ScreenspaceToWorld({Input::GetMouseX(), Input::GetMouseY()}, cameraProjection * glm::inverse(cameraTransform));
                            }
                        }
                        ProcessLeftClick(ClickPosition);
                    }
                break;
                default: break;
            }
        }

    private:
        Ref<TileMap<Entity>> m_Elements;
        Ref<Texture2D> m_Texture;
        bool m_LeftMouseDown = false;
        ElectricalType m_Selection = ElectricalType::BATTERY;
        uint32_t m_TileWidth = 8;

        void ProcessLeftClick(const glm::vec2& position)
        {
            uint32_t x = glm::floor(position.x / m_TileWidth);
            uint32_t y = glm::floor(position.y / m_TileWidth);

            if(m_Elements->InBounds(x, y) && m_Elements->At(x, y) == NULL_ENTITY) //TODO: ADD CHECKING FOR ALL LOCTIONS AROUND
            {
                //Add Automatic addition with custom functions and JSON prefabs for textures and all
                switch(m_Selection)
                {
                    case ElectricalType::WIRE:
                    {
                        Entity entity = m_World->CreateEntity();
                        m_World->AddComponent<ElectricalComponent>(entity, {m_Selection, 1, 1, false});
                        m_World->AddComponent<SpriteComponent>(entity, SpriteComponent(m_Texture, {8.0f, 0.0f}, {8.0f, 8.0f}));
                        m_World->AddComponent<TransformComponent>(entity, Transform(glm::vec3(x * m_TileWidth, y * m_TileWidth, 0.0f)));

                        m_Elements->At(x, y) = entity;
                    }
                    break;
                    case ElectricalType::BATTERY:
                    {
                        Entity entity = m_World->CreateEntity();
                        m_World->AddComponent<ElectricalComponent>(entity, {m_Selection, 2, 1, false});
                        m_World->AddComponent<SpriteComponent>(entity, SpriteComponent(m_Texture, {16.0f, 0.0f}, {16.0f, 8.0f}));
                        m_World->AddComponent<TransformComponent>(entity, Transform(glm::vec3(x * m_TileWidth, y * m_TileWidth, 0.0f)));

                        m_Elements->At(x, y) = entity;
                        m_Elements->At(x+1, y) = entity;
                    }
                    break;
                    case ElectricalType::LED:
                    {
                        Entity entity = m_World->CreateEntity();
                        m_World->AddComponent<ElectricalComponent>(entity, {m_Selection, 1, 1, false});
                        m_World->AddComponent<SpriteComponent>(entity, SpriteComponent(m_Texture, {32.0f, 0.0f}, {8.0f, 8.0f}));
                        m_World->AddComponent<TransformComponent>(entity, Transform(glm::vec3(x * m_TileWidth, y * m_TileWidth, 0.0f)));

                        m_Elements->At(x, y) = entity;
                    }
                    break;
                    
                    default:
                    break;
                }
            }
        }
    };
}


