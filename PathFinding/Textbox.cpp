#include "Textbox.h"



bool Textbox::isMouseOn()
{
	if (this->shape.getGlobalBounds().contains({ (float)mouseX, (float)mouseY }))
		return true;
	
	return false;
}

void Textbox::update()
{
	
	if (CLICK_EVENT == true) {

		if (isMouseOn()) {

			hasFocus = true;
			activeTextboxPtr = this;
			shape.setOutlineColor(sf::Color::Yellow);
			text = "";
		}
		else {
			hasFocus = false;			
			shape.setOutlineColor(sf::Color::White);
		}

	}

}

void Textbox::draw()
{
	update();

	window->draw(typedText);
	window->draw(shape);
}

void Textbox::writeText(int char_unicode)
{

	if (hasFocus) {

		
		if (char_unicode == BACKSPACE_KEY) {
			if (text.length() > 0)
				text.pop_back();
		}
		else {

			if(text.length() < charLimit)
				text += static_cast<char>(char_unicode);			
		}

		typedText.setString(text);
	}
}

void Textbox::setPlaceholderInTextbox()
{
	typedText.setString(placeholder);
	text = "";
}

void Textbox::setTextboxString(std::string str)
{
	typedText.setString(str);
	text = str;
	
}

void Textbox::justifyText(const char option)
{
	int textWidth = typedText.getLocalBounds().width;
	int textHeight = typedText.getLocalBounds().height;
	int textX=0, textY=0;

	if (option == 'L') {
		textX = screenX + 10;
	}
	else if (option == 'R') {
		
	}
	else if (option == 'C') {
		textX = screenX + (width - textWidth) / 2;
	}

	typedText.setPosition(textX, screenY);

}


