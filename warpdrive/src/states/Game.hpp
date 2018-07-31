///
/// Game.hpp
/// warpdrive
///
/// Created by reworks on 26/07/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef WARPDRIVE_GAME_HPP_
#define WARPDRIVE_GAME_HPP_

#include <sl/core/StateMachine.hpp>

class Game : public sl::State
{
public:
	Game();
	~Game() override;

	void load() override;
	void unload() override;

	void event(ALLEGRO_EVENT* event) override;
	void update(double dt) override;
	void render() override;

private:
};

#endif