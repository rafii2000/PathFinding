#pragma once

// All values here are proper for 1920x1080 resolution

class Layout
{

public:

	static void set_MW_TOP_BTNS_X() {

		START_BTN_X = MW_TOP_BTNS_X;
		BREAK_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 1;
		PATH_RESET_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 2;
		BOARD_RESET_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 3;
		GENERATE_MAZE_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 4;
		OPEN_SETTINGS_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 4 + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH_S) * 1;
	}

public:

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
	inline static int APP_RESULT_LABLE_X = 75;
	inline static int APP_RESULT_LABLE_Y = 80;
	inline static int APP_RESULT_LABLE_FONT_SIZE = 25;
	

	// ---------------- SETTINGS WINDOW ---------------- //	
	
	//Text fields
	inline static int FILE_PATH_SAVE_GROUP_Y = 605;
	inline static int FILE_PATH_LOAD_GROUP_Y = 705;

};


