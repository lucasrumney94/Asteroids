#include "Core/System.cpp"
#include "Graphics/GlLoader.hpp"
#include "Graphics/Shader.hpp"
#include <memory>


class RenderSystem : public System
{
public:
	void Init();

	void Update(float dt);
};