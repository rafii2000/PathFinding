#include "Settings.h"

void Settings::openWindowSettings()
{
	isOpen = true;
	Board::boardState = BLOCK;
	std::cout << "Stan planszy:" << Board::boardState << std::endl;
	
}

void Settings::closeWindowSettings()
{
	isOpen = false;
	Board::boardState = ACTIVE;
	std::cout << "Stan planszy:" << Board::boardState << std::endl;
	
}

void Settings::updateButtons()
{

	closeSettingsButton.update(mouseX, mouseY);

}

void Settings::draw()
{


	if (isOpen == true) {

		updateButtons();

		//std::cout << "Stan planszy:" << Board::boardState << std::endl;

		window->draw(settings_window);
		window->draw(windowTitle);
		closeSettingsButton.render(window);
	}
}
