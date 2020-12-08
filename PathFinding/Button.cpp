#include "Button.h"



Button::Button(int x, int y, int width, int height, 
	sf::Font *font, std::string text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	std::string buttonID)
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

Button::~Button()
{
}




const bool Button::isPressed()
{

	if (this->buttonState == BTN_ACTIVE)

		//block board
		return true;
	
	return false;
}

void Button::callButtonFunction()
{
	if (buttonID == START_BTN) {
		onStartButtonClick();
	}
	else if (buttonID == STOP_BTN) {
		onStopButtonClick();
	}
	else if (buttonID == RESET_BTN) {
		onResetButtonClick();
	}
}

void Button::update(const sf::Vector2f mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;
	
	//Hover 	
	if (this->shape.getGlobalBounds().contains(mousePos)) {

		this->buttonState = BTN_HOVER;
		
		//Pressed
		if (mouseState == "left") {

			std::cout << "pressing" << std::endl;

			this->buttonState = BTN_ACTIVE;

		}
		//Click,
		else if (CLICK_EVENT == true) {
	
			std::cout << "CLICK" << std::endl;
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

void Button::onStartButtonClick()
{
	CLICKED_BTN = START_BTN;
}

void Button::onStopButtonClick()
{
	CLICKED_BTN = STOP_BTN;
}

void Button::onResetButtonClick()
{
	CLICKED_BTN = RESET_BTN;
}






//BUTTONS FUNCTION




