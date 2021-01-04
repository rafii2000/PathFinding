#include "Button.h"


//constructor
Button::Button(int x, int y, int width, int height, 
	sf::Font *font, std::string text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	btn_id buttonID)
{
	
	this->buttonState = BTN_IDLE;
	this->buttonID = buttonID;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(70, 70, 70));
	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color(50, 40, 50));
	this->text.setCharacterSize(20);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2 -20/2
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);

}



const bool Button::isPressed()
{

	if (this->buttonState == BTN_ACTIVE)

		//block board
		return true;
	
	return false;
}

void Button::update(int mouseX, int mouseY)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;
	
	//Hover 	
	if (this->shape.getGlobalBounds().contains({(float)mouseX, (float)mouseY})) {

		this->buttonState = BTN_HOVER;
		
		//Pressed
		if (mouseState == mf::LEFT_PRESSED) {

			this->buttonState = BTN_ACTIVE;

		}
		//Click,
		else if (CLICK_EVENT == true) {
	
			std::cout << "CLICK_EVENT" << std::endl;
			CLICK_EVENT = false;
			callButtonFunction();
		}
			

	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;


	default:
		this->shape.setFillColor(sf::Color::Red);

		break;
	}

}

void Button::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
	window->draw(this->text);
}



void Button::callButtonFunction()
{
	//change the current clicked button flag

	if (buttonID == btn_id::START_BTN) {
		onStartButtonClick();
	}
	else if (buttonID == btn_id::BREAK_BTN) {
		onBreakButtonClick();
	}
	else if (buttonID == btn_id::BOARD_RESET_BTN) {
		onBoardResetButtonClick();
	}
	else if (buttonID == btn_id::PATH_RESET_BTN) {
		onPathResetButtonClick();
	}
}

//BUTTONS FUNCTION
void Button::onStartButtonClick()
{
	//change CLICKED_BTN flag
	clicked_btn = btn_id::START_BTN;
}

void Button::onBreakButtonClick()
{
	//change CLICKED_BTN flag
	clicked_btn = btn_id::BREAK_BTN;

}

void Button::onBoardResetButtonClick()
{
	//change CLICKED_BTN flag
	clicked_btn = btn_id::BOARD_RESET_BTN;
}

void Button::onPathResetButtonClick()
{
	//change CLICKED_BTN flag
	clicked_btn = btn_id::PATH_RESET_BTN;
}











