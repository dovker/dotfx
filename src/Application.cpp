#include <glm/glm.hpp>
#include <memory>

#include "Clap.h"
#include "Tiles.h"
#include "Benchmark.h"


using namespace Clap;
namespace Game2D
{
    void Start()
    {
        bool running = true;

        Window* window = Window::Create();

        Graphics::Init();
        Batch::Init();

        Transform cameraTransform(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 cameraProjection = glm::ortho(-320.0f, 320.0f, 180.0f, -180.0f, 100.0f, -100.0f);

        uint32_t* texture = new uint32_t[100 * 100];

        for(int i = 0; i < 100; i++)
        {
            for(int j = 0; j < 100; j++)
            {
                //glm::vec4 color = {1.0f, (float)i/100, (float)j/100, 1.0f};
                glm::vec4 color = {1.0f, 0.5f, 0.2f, 1.0f};

                color *= 255;
                uint32_t data = ((uint32_t)color.r << 24) | ((uint32_t)color.g << 16) | ((uint32_t)color.b << 8) | ((uint32_t)color.a);
                texture[i * 100 + j] = data;
            }
        }

        TextureSpecification spec(TextureFormat::RGBA8);

        Ref<Texture2D> tex = Texture2D::Create(100, 100, spec);
        
        tex->SetData((void*)texture, 100 * 100 * sizeof(uint32_t));

        double CurrentTime = 0.0;
        double PreviousTime = window->GetTime();
        double DeltaTime;

        while(running)
        {
            PreviousTime = CurrentTime;
            CurrentTime = window->GetTime();

            DeltaTime = (double)((CurrentTime - PreviousTime) / window->GetFrequency() ); //SDL WAY
            //CLAP_INFO("FPS: ", 1.0/DeltaTime);

            while(!EventSystem::IsEmpty())
            {
                Event e = EventSystem::GetEvent();
                switch(e.Type)
                {
                    case EventType::WindowClose:
                        running = false;
                    break;
                    default: break;
                }
            }
            
            Graphics::ToggleDepthTest(true);
            Graphics::ToggleBlending(true);
            Graphics::SetClearColor({0.0f, 0.0f, 0.0f, 0.0f});

            Graphics::Clear();

            Batch::Begin(cameraProjection, cameraTransform.GetTransform());

            Batch::Submit({0.0f, 0.0f, 0.0f}, {100, 100}, tex, {0.0f, 0.0f, 1.0f, 1.0f}, glm::vec4(1.0f));

            Batch::End();
            
            window->OnUpdate();
        }
        Batch::Shutdown();
        delete texture;
    }
}

int main()
{
    Game2D::Start();
    return 0;
}
