#include "MainWindow.h"


MainWindow::MainWindow(sf::RenderWindow* renderTarget):
    renderTarget(renderTarget),
    nodesBoard(renderTarget, 30, 1, 1000, 1000),
    settingsPanel(renderTarget, &nodesBoard, &Layout::defaultFont),

    appTitle("SFML PathFinding visualization", Layout::defaultFont, Layout::APP_TITLE_LABLE_FONT_SIZE),
    appResultLabel("Path between points doesn't exist", Layout::defaultFont, Layout::APP_RESULT_LABLE_FONT_SIZE),
    appFPSLabel("150", Layout::defaultFont, 16),

    startButton(Layout::START_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &Layout::defaultFont, Layout::MW_TOP_BTNS_FONT_SIZE, "Start", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::START_BTN),
    breakButton(Layout::BREAK_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &Layout::defaultFont, Layout::MW_TOP_BTNS_FONT_SIZE, "Break", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::BREAK_BTN),
    pathResetButton(Layout::PATH_RESET_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &Layout::defaultFont, Layout::MW_TOP_BTNS_FONT_SIZE, "Path Reset", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::PATH_RESET_BTN),
    boardResetButton(Layout::BOARD_RESET_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH, Layout::MW_TOP_BTNS_HEIGHT, &Layout::defaultFont, Layout::MW_TOP_BTNS_FONT_SIZE, "Board Reset", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::BOARD_RESET_BTN),
    generateMaze(Layout::GENERATE_MAZE_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH_S, Layout::MW_TOP_BTNS_HEIGHT_S, &Layout::defaultFont, Layout::MW_TOP_BTNS_FONT_SIZE, "", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::GENERATE_MAZE_BTN, "maze2.png"),
    openSettingsButton(Layout::OPEN_SETTINGS_BTN_X, Layout::MW_TOP_BTNS_Y, Layout::MW_TOP_BTNS_WIDTH_S, Layout::MW_TOP_BTNS_HEIGHT_S, &Layout::defaultFont, Layout::MW_TOP_BTNS_FONT_SIZE, "", Layout::MW_TOP_BTNS_IDLE, Layout::MW_TOP_BTNS_HOVER, Layout::MW_TOP_BTNS_CLICK, btn_id::OPEN_SETTINGS_BTN, "settings2.png")

{
    // Create lables   
    appTitle.setPosition(sf::Vector2f(Layout::APP_TITLE_LABLE_X, Layout::APP_TITLE_LABLE_Y));
   
    appResultLabel.setPosition(sf::Vector2f(Layout::APP_RESULT_LABLE_X, Layout::APP_RESULT_LABLE_Y));
    appResultLabel.setFillColor(sf::Color::Transparent);
  
    appFPSLabel.setPosition(10, 5);
    appFPSLabel.setFillColor(sf::Color::Blue);
   
    // Create lable background
    appResultLabelBackground.setPosition(sf::Vector2f(Layout::APP_RESULT_LABLE_BACKGROUND_X, Layout::APP_RESULT_LABLE_BACKGROUND_Y));
    appResultLabelBackground.setSize({ (float)Layout::APP_RESULT_LABLE_BACKGROUND_WIDTH, (float)Layout::APP_RESULT_LABLE_BACKGROUND_HEIGHT });
    appResultLabelBackground.setFillColor(sf::Color::Transparent);
}

void MainWindow::fpsCounter()
{
    currentTime = clock.getElapsedTime();
    fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
    appFPSLabel.setString(std::to_string(int(fps)));
    previousTime = currentTime;
}

void MainWindow::update()
{

    //idle, hover, click, set CLICKED_BTN id
    if (Settings::isOpen == false) {

        startButton.update(mouseX, mouseY);
        breakButton.update(mouseX, mouseY);

        if (RUN_ALGORITHM == false) {
            pathResetButton.update(mouseX, mouseY);
            boardResetButton.update(mouseX, mouseY);
            openSettingsButton.update(mouseX, mouseY);
            generateMaze.update(mouseX, mouseY);
        }

        //call proper function
        nodesBoard.callFunctionOnButtonClick();
    }

    if (Settings::isOpen == true) {

        settingsPanel.updateButtons();
        settingsPanel.callFunctionOnButtonClick();
    }


    nodesBoard.boardFunctionalities();

    nodesBoard.runVisualization(&appResultLabel, &appResultLabelBackground);

}

void MainWindow::draw()
{

    update();

    // Draw elements
    // object render sequence is important, objects cover each other
    renderTarget->draw(appTitle);
    renderTarget->draw(appFPSLabel);

    if(RUN_ALGORITHM == true and Settings::fastVisualization == true) {
        //std::cout << "nie powinno mnie tu byc" << std::endl;
    }
    else {
        nodesBoard.draw();        
    }

    startButton.render(renderTarget);
    breakButton.render(renderTarget);
    pathResetButton.render(renderTarget);
    boardResetButton.render(renderTarget);
    openSettingsButton.render(renderTarget);
    generateMaze.render(renderTarget);

    settingsPanel.draw();  //render last, must cover other elements

    renderTarget->draw(appResultLabelBackground);
    renderTarget->draw(appResultLabel);

}





