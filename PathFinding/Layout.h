#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

// All values here are proper for 1920x1080 resolution

class Layout
{

public:

	static void set_MW_TOP_BTNS_X();

	static void detectResolution(int screenWidth, int screenHeight);

private:
	static sf::Font loadDefaultFont();

	

public:


	inline static sf::Font defaultFont = loadDefaultFont();

	// ------------------ MAIN WINDOW ------------------ //	
	
					// top buttons group //
	//common properties
	inline static int MW_TOP_BTNS_Y = 35;
	inline static int MW_TOP_BTNS_X = 980;
	inline static int MW_TOP_BTNS_FONT_SIZE = 20;
	inline static int MW_TOP_BTNS_MARGIN = 50;
	inline static sf::Color MW_TOP_BTNS_IDLE = sf::Color(170, 170, 170);
	inline static sf::Color MW_TOP_BTNS_HOVER = sf::Color(150, 150, 150);
	inline static sf::Color MW_TOP_BTNS_CLICK = sf::Color(120, 120, 120);

	//half individual properties
	inline static int MW_TOP_BTNS_WIDTH = 130;
	inline static int MW_TOP_BTNS_HEIGHT = 50;
	inline static int MW_TOP_BTNS_WIDTH_S = 50;
	inline static int MW_TOP_BTNS_HEIGHT_S = 50;
	
	//individual properties
	inline static int START_BTN_X = MW_TOP_BTNS_X;
	inline static int BREAK_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 1;
	inline static int PATH_RESET_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 2;
	inline static int BOARD_RESET_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 3;
	inline static int GENERATE_MAZE_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 4;
	inline static int OPEN_SETTINGS_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 4 + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH_S) * 1;
	
					// --- window lables -- //	
	//app title lable
	inline static int APP_TITLE_LABLE_X = 75;
	inline static int APP_TITLE_LABLE_Y = 20;
	inline static int APP_TITLE_LABLE_FONT_SIZE = 50;
		
	//app result lable
	/*inline static int APP_RESULT_LABLE_X = 75;
	inline static int APP_RESULT_LABLE_Y = 80;*/
	inline static int APP_RESULT_LABLE_X = 780;
	inline static int APP_RESULT_LABLE_Y = 390;
	inline static int APP_RESULT_LABLE_FONT_SIZE = 25;
	inline static int APP_RESULT_LABLE_BACKGROUND_X = 710;
	inline static int APP_RESULT_LABLE_BACKGROUND_Y = 310;
	inline static int APP_RESULT_LABLE_BACKGROUND_WIDTH = 500;
	inline static int APP_RESULT_LABLE_BACKGROUND_HEIGHT = 200;

	

	// ---------------- SETTINGS WINDOW ---------------- //	
	
	//Text fields
	inline static int FILE_PATH_SAVE_GROUP_Y = 655;
	inline static int FILE_PATH_LOAD_GROUP_Y = 755;

};


