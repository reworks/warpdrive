///
/// main.cpp
/// warpdrive
///
/// Created by reworks on 25/07/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include <sl/events/Keys.hpp>
#include <sl/tags/CameraTag.hpp>
#include <sl/core/Application.hpp>
#include <sl/systems/RenderSystem.hpp>
#include <sl/systems/CameraSystem.hpp>
#include <sl/systems/ScrollingBackgroundSystem.hpp>
#include <sl/systems/AnimationSystem.hpp>
#include <sl/systems/PhysicsSystem.hpp>
#include <allegro5/allegro_native_dialog.h>

#include "states/Menu.hpp"
#include "states/Load.hpp"
#include "states/Game.hpp"

///
/// The main class for creating a starlight application.
///
class warpdrive : public sl::Application
{
public:
	///
	/// Constructor for main class, initializing application and game.
	///
	inline warpdrive(const std::string& config, std::function<void(std::ofstream&)> newConfig) : sl::Application(config, newConfig)
	{
		// Register game systems.
		m_world->registerSystem<sl::RenderSystem>(m_configReader->lookup<int>(config, "graphics", "quadTreeLevels"), m_configReader->lookup<int>(config, "graphics", "quadTreeMaxEntities"));
		m_world->registerSystem<sl::CameraSystem>();
		m_world->registerSystem<sl::PhysicsSystem>("", m_configReader->lookup<float>(config, "box2d", "ups"), m_configReader->lookup<int>(config, "box2d", "velocityIterations"), m_configReader->lookup<int>(config, "box2d", "positionIterations"));
		m_world->registerSystem<sl::AnimationSystem>();
		m_world->registerSystem<sl::ScrollingBackgroundSystem>();

		// Set up game states.
		m_stateMachine->createState<Load>("load");
		m_stateMachine->createState<Menu>("menu");
		m_stateMachine->createState<Game>("game");
		m_stateMachine->push("load");
		//m_stateMachine->push("menu");
		//m_stateMachine->push("game");

		// And the camera.
		entt::DefaultRegistry::entity_type cameraEntity = m_world->m_registry.create();
		m_world->m_registry.assign<sl::CameraTag>(entt::tag_t{}, cameraEntity, sl::Rect<float, int>{ 0, 0, 1280, 720 });
	}

	///
	/// Default destructor.
	///
	~warpdrive() = default;
};

///
/// Entry point, command-line arguments are not used.
///
int main(int argc, char **argv)
{
	bool restart = false;

	do
	{
		restart = false;

		{
			try
			{
				warpdrive game("assets/config.cfg", [](std::ofstream& newConfig)
				{
					newConfig << "[graphics]\n";
					newConfig << "width = 1280\n";
					newConfig << "height = 720\n";
					newConfig << "fullscreen = false\n";
					newConfig << "msaa = true\n";
					newConfig << "msaaValue = 2\n";
					newConfig << "title = warpdrive\n";
					newConfig << "icon = textures/icon.png\n";
					newConfig << "atlasPowerOf = 11\n";
					newConfig << "quadTreeLevels = 20\n";
					newConfig << "quadTreeMaxEntities = 100\n";
					newConfig << "shaderScript = scripts/shaders.lua\n";
					newConfig << "nullTexture = null\n";
					newConfig << std::endl;

					newConfig << "[box2d]\n";
					newConfig << "gravity = 9.81\n";
					newConfig << "ups = 60.0\n";
					newConfig << "velocityIterations = 8\n";
					newConfig << "positionIterations = 3\n";
					newConfig << std::endl;

					newConfig << "[font]\n";
					newConfig << "fontScript = scripts/fonts.lua\n";
					newConfig << std::endl;

					newConfig << "[audio]\n";
					newConfig << "musicScript = scripts/music.lua\n";
					newConfig << "soundScript = scripts/sound.lua\n";
					newConfig << "reserveSamples = 32\n";
					newConfig << "nullMusic = null\n";
					newConfig << "nullSound = null\n";
					newConfig << std::endl;

					newConfig << "# see allegro key codes\n";
					newConfig << "[keys]\n";
					newConfig << "forward = 23\n";
					newConfig << "backward = 19\n";
					newConfig << "left = 1\n";
					newConfig << "right = 4\n";
					newConfig << "quit = 59\n";
					newConfig << std::endl;

					newConfig << "[debug]\n";
					newConfig << "isDisabled = false\n";
					newConfig << std::endl;

					newConfig << "[fs]\n";
					newConfig << "writeDir = assets/\n";
					newConfig << "scriptFolderPath = scripts/\n";
					newConfig << "textureFolderPath = textures/\n";
					newConfig << "musicFolderPath = music/\n";
					newConfig << "soundFolderPath = sound/\n";
					newConfig << std::endl;

					newConfig << "[archives]\n";
					newConfig << "assets/\n";
					newConfig << std::endl;
				});

				restart = game.run();
			}
			catch (const std::exception& e)
			{
				LOG_S(INFO) << "EXCEPTION OUTPUT: " << e.what();
				al_show_native_message_box(nullptr, "Runtime Exception", "Error Message:", e.what(), nullptr, ALLEGRO_MESSAGEBOX_ERROR);
			}
			catch (...)
			{
				LOG_S(WARNING) << "Threw an unknown exception. Why are you not inheriting from std::exception?";
			}
		}

	} while (restart);
}