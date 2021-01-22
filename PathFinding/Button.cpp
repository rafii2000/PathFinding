#include "Button.h"


//constructor


Button::Button(int x, int y, int width, int height, sf::Font* font, int fontSize, 
	std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	btn_id buttonID, std::string texture_path)
{
	
	this->buttonState = BTN_IDLE;
	this->buttonID = buttonID;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(70, 70, 70));
	
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

	this->shape.setFillColor(this->idleColor);

	

	if (texture_path != ""){
		this->texturePath = texture_path;
		if (!texture.loadFromFile(texture_path)) { /*handle error*/}

		sprite.setTexture(texture);
		sprite.setPosition(x+width/2,y+height/2);
		sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);		
	}

}



const bool Button::isPressed()
{
	if (this->buttonState == BTN_PRESSED)
		return true; 
	
	return false;
}

void Button::update(int mouseX, int mouseY)
{
	/*Update the booleans for hover and pressed*/

	//bad solution - exclusion update some buttons
	if (RUN_ALGORITHM == true)
		if (buttonID != btn_id::START_BTN and buttonID != btn_id::BREAK_BTN)
			return;

	//Idle
	this->buttonState = BTN_IDLE;
	
	//Hover 	
	if (this->shape.getGlobalBounds().contains({(float)mouseX, (float)mouseY})) {

		this->buttonState = BTN_HOVER;
		
		//Pressed
		if (MOUSE_STATE == mf::LEFT_PRESSED) {

			this->buttonState = BTN_PRESSED;

		}
		//Click (on button released)
		else if (CLICK_EVENT == true) {
	
			std::cout << "CLICK_EVENT" << std::endl;
			CLICK_EVENT = false;

			CLICKED_BTN = buttonID; //tym sposobem pozbywam sie ogroma zbednych funkcji
			//callButtonFunction();
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

	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		break;


	default:
		this->shape.setFillColor(this->idleColor);
		break;
	}

}

void Button::render(sf::RenderWindow* window)
{
	window->draw(this->shape);
	window->draw(this->text);
	if (texturePath != "")
		window->draw(this->sprite);		
	
}



