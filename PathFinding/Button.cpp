#include "Button.h"


//constructor
Button::Button(int x, int y, int width, int height, sf::Font* font, int fontSize, 
	std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	btn_id buttonID, std::string texturePath)
{
	
	this->buttonState = BTN_IDLE;
	this->buttonID = buttonID;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(70, 70, 70));
	this->shape.setFillColor(idleColor);
	
	this->font = font;
	this->fontSize = fontSize;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color(50, 40, 50));
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2) - this->text.getGlobalBounds().width / 2,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2) - this->text.getGlobalBounds().height / 2 -fontSize/2
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	
	if (texturePath != ""){

		this->texturePath = texturePath;

		if (!texture.loadFromFile(texturePath)) {
			/*handle error*/
		}
		else {
			sprite.setTexture(texture);
			sprite.setPosition(x + width / 2, y + height / 2);
			sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
		}		
	}

}



const bool Button::isPressed()
{
	if (buttonState == BTN_PRESSED)
		return true; 
	
	return false;
}

void Button::update(int mouseX, int mouseY)
{
	//Idle
	buttonState = BTN_IDLE;
	
	//Hover 	
	if (shape.getGlobalBounds().contains({(float)mouseX, (float)mouseY})) {

		buttonState = BTN_HOVER;
		
		//Press
		if (MOUSE_STATE == mf::LEFT_PRESSED) {

			buttonState = BTN_PRESSED;
		}
		//Click (on mouse button released)
		else if (CLICK_EVENT == true) {

			std::cout << "CLICK_EVENT" << std::endl;

			//set global variable 'CLICKED_BTN' to current hovered button ID
			CLICKED_BTN = buttonID; 
		}
	}

	switch (buttonState)
	{
		case BTN_IDLE:		shape.setFillColor(idleColor);		break;
		case BTN_HOVER:		shape.setFillColor(hoverColor);		break;
		case BTN_PRESSED:	shape.setFillColor(activeColor);	break;
		default:			shape.setFillColor(idleColor);		break;
	}
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(shape);
	window->draw(text);
	if (texturePath != "")
		window->draw(sprite);

}



