///
/// Menu.hpp
/// warpdrive
///
/// Created by reworks on 26/07/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef WARPDRIVE_MENU_HPP_
#define WARPDRIVE_MENU_HPP_

#include <sl/core/StateMachine.hpp>

class Menu : public sl::State
{
public:
	Menu();
	~Menu() override;

	void event(ALLEGRO_EVENT* event) override;
	void update(double dt) override;
	void render() override;

private:
};

#endif