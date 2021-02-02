#include "Layout.h"



void Layout::set_MW_TOP_BTNS_X(){

    START_BTN_X = MW_TOP_BTNS_X;
    BREAK_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 1;
    PATH_RESET_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 2;
    BOARD_RESET_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 3;
    GENERATE_MAZE_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 4;
    OPEN_SETTINGS_BTN_X = MW_TOP_BTNS_X + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH) * 4 + (MW_TOP_BTNS_MARGIN + MW_TOP_BTNS_WIDTH_S) * 1;
}

void Layout::detectResolution(int screenWidth, int screenHeight)
{
    //1364 x 768
    if (screenWidth < 1920 and screenHeight < 1080) {

        //MAIN WINDOW
        APP_TITLE_LABLE_FONT_SIZE = 40;
        APP_TITLE_LABLE_X = 60;
        APP_RESULT_LABLE_FONT_SIZE = 22;
        APP_RESULT_LABLE_X = 60;

        //common properties
        MW_TOP_BTNS_X = 725;
        MW_TOP_BTNS_Y = 35;
        MW_TOP_BTNS_MARGIN = 25;
        MW_TOP_BTNS_FONT_SIZE = 17;

        //half common properties
        MW_TOP_BTNS_WIDTH = 95;
        MW_TOP_BTNS_HEIGHT = 35;
        MW_TOP_BTNS_WIDTH_S = 35;
        MW_TOP_BTNS_HEIGHT_S = 35;

        //individual properties
        set_MW_TOP_BTNS_X();
        
        //SETTINGS WINDOW
        FILE_PATH_SAVE_GROUP_Y = 525;
        FILE_PATH_LOAD_GROUP_Y = 625;
    }
}

sf::Font Layout::loadDefaultFont()
{

    sf::Font font;
   
    font.loadFromFile("arial_narrow_7.ttf");

    return (sf::Font&&)font;
}
