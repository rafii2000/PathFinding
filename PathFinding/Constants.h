#pragma once


const enum class mf { PRESSED = 0, LEFT_PRESSED, RIGHT_PRESSED, RELEASED };	//mouse_flags

const enum class btn_id { 
	NONE=0,
	START_BTN, BREAK_BTN, PATH_RESET_BTN, BOARD_RESET_BTN, GENERATE_MAZE_BTN, OPEN_SETTINGS_BTN, 	//mian window buttons
	SAVE_BOARD_BTN, LOAD_BOARD_BTN, APPLY_BOARD_RESIZE_BTN, CLOSE_SETTINGS_BTN						//settings card buttons
};


//temporary value, because layout is not responsive
const int board2DMargin = 30;


//Board layout properties
const int MAIN_LEFT_PADDING = 50;
const int MAIN_RIGHT_PADDING = 50;
const int MAIN_TOP_PADDING = 150;
const int MAIN_BOTTOM_PADDING = 50;
const int HORIZONTAL_PADDING = 50;
