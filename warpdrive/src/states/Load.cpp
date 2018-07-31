///
/// Load.cpp
/// warpdrive
///
/// Created by reworks on 26/07/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include <allegro5/events.h>
#include <allegro5/keycodes.h>

#include <sl/core/World.hpp>
#include <sl/graphics/Window.hpp>
#include <sl/core/ServiceLocator.hpp>
#include <sl/systems/RenderSystem.hpp>

#include "Load.hpp"

Load::Load()
{
	m_bounds.m_x = 0;
	m_bounds.m_y = 0;
	m_bounds.m_width = 1280;
	m_bounds.m_height = 720;
}

Load::~Load()
{
}

void Load::load()
{
	sl::Locator::world->createEntity("")
}

void Load::unload()
{
}

void Load::event(ALLEGRO_EVENT* event)
{
	switch (event->type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (event->keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			sl::Locator::window->close();
			break;
		}
		break;
	}
}

void Load::update(double dt)
{
}

void Load::render()
{
	sl::Locator::world->getSystem<sl::RenderSystem>()->render(sl::Locator::world->m_registry);
}