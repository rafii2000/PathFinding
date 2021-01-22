#pragma once


//GLOBALS
const enum class mf { PRESSED = 0, LEFT_PRESSED, RIGHT_PRESSED, RELEASED };	//mouse_flags

const enum class btn_id { NONE=0, START_BTN, BREAK_BTN, PATH_RESET_BTN, BOARD_RESET_BTN, 
							OPEN_SETTINGS_BTN, CLOSE_SETTINGS_BTN, 
							SAVE_BOARD_BTN, LOAD_BOARD_BTN, APPLY_BOARD_RESIZE_BTN,
							GENERATE_MAZE_BTN};





//board, old, dont use it
//const int board_max_width = 1799; 	//58
//const int board_max_height = 838;	//27
const int board2DMargin = 30;





//BOARD LAYOUT PROPERTIES
const int MAIN_LEFT_PADDING = 50;
const int MAIN_RIGHT_PADDING = 50;
const int MAIN_TOP_PADDING = 150;
const int MAIN_BOTTOM_PADDING = 50;
const int HORIZONTAL_PADDING = 50;






