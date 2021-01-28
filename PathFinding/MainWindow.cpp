#include "MainWindow.h"


MainWindow::MainWindow(sf::RenderWindow& renderTarget, sf::Font font):
    renderTarget(renderTarget),
    nodesBoard(renderTarget, 30, 1, 1000, 1000),
    settingsWindow(&renderTarget, &nodesBoard, &font),

    appTitle("SFML PathFinding visualization", *Layout::font, Layout::APP_TITLE_LABLE_FONT_SIZE),
    appResultLabel("Path between points doesn't exist", font, Layout::APP_RESULT_LABLE_FONT_SIZE),
    appFPSLabel("150", font, 16),

    startButton(Layout::START_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Start", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::START_BTN),
    breakButton(Layout::BREAK_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Break", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::BREAK_BTN),
    pathResetButton(Layout::PATH_RESET_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Path Reset", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::PATH_RESET_BTN),
    boardResetButton(Layout::BOARD_RESET_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "Board Reset", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::BOARD_RESET_BTN),
    generateMaze(Layout::GENERATE_MAZE_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH_S, Layout::MW_TOP_BTNS_HEIGHT_S, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::GENERATE_MAZE_BTN, "maze2.png"),
    openSettingsButton(Layout::OPEN_SETTINGS_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH_S, Layout::MW_TOP_BTNS_HEIGHT_S, &font, Layout::MW_TOP_BTNS_FONT_SIZE, "", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::OPEN_SETTINGS_BTN, "settings2.png")
{

    //czy jest jakis sposob na zaladowanie czcionki tutaj?


    // Create lables   
    appTitle.setPosition(sf::Vector2f(Layout::APP_TITLE_LABLE_X, Layout::APP_TITLE_LABLE_Y));
   
    appResultLabel.setPosition(sf::Vector2f(Layout::APP_RESULT_LABLE_X, Layout::APP_RESULT_LABLE_Y));
    appResultLabel.setFillColor(sf::Color::Transparent);
  
    appFPSLabel.setPosition(10, 5);
    appFPSLabel.setFillColor(sf::Color::Blue);
   
}

void MainWindow::drawButtons()
{

    startButton.render(&renderTarget);
    breakButton.render(&renderTarget);
    pathResetButton.render(&renderTarget);
    boardResetButton.render(&renderTarget);
    openSettingsButton.render(&renderTarget);
    generateMaze.render(&renderTarget);

}

void MainWindow::drawLables()
{
}
