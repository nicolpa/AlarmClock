#include "MainScreenUI.hpp"

MainScreenUI::MainScreenUI(lcd::UTFT *LCD, URTouch *Touch, DS1307 *rtc, int LM35) 
    : Frame(LCD, Touch), rtc(rtc), LM35(LM35)
{
	btnMenu = new Button(LCD, Touch, HorizontalAlignment::Right, VerticalAlignment::Down, 16, 16);
	GraphicalComponentContainer *shapeBtnMenu = new GraphicalComponentContainer();
	shapeBtnMenu->add(new Rectangle(LCD, 2, 3, btnMenu->getWidth() - 2, 4, true));
	shapeBtnMenu->add(new Rectangle(LCD, 2, 7, btnMenu->getWidth() - 2, 8, true));
	shapeBtnMenu->add(new Rectangle(LCD, 2, 11, btnMenu->getWidth() - 2, 12, true));
	btnMenu->setGraphics(shapeBtnMenu);
	btnMenu->setBorderless(true);
	btnMenu->setContentHighlight(true);
	this->add(btnMenu);

    this->add(lblDOW = new Label(this->LCD, 2, 2, rtc->getDOWStr(), SmallFont));
	this->add(lblDate = new Label(this->LCD, 2, 15, rtc->getDateStr(), SmallFont));
	this->add(lblClock = new Label(this->LCD, HorizontalAlignment::Center, VerticalAlignment::Center, this->rtc->getTimeStr(), SevenSegNumFontPlus));

	Panel *pnlTemp = new Panel(this->LCD, HorizontalAlignment::Right, VerticalAlignment::Up, 57, 12);
	pnlTemp->setBorder(false);
	pnlTemp->add(lblTemp = new Label(this->LCD, HorizontalAlignment::Left, 2, String(getTemp()), SmallFont));
	pnlTemp->add(new Circle(this->LCD, 42, 4, 2));
	pnlTemp->add(new Label(this->LCD, HorizontalAlignment::Right, 2, "C", SmallFont));
	this->add(pnlTemp);

	this->setClickable(true);
	// screen->setNormalPressAction(&sleep);
	// screen->setLongPressAction(&cycleBrightness);

	this->setMargin(5, 5, 5, 5);    
}

MainScreenUI::~MainScreenUI() 
{

}

void MainScreenUI::draw() 
{
	lblDOW->setText(rtc->getDOWStr());
	lblDate->setText(rtc->getDateStr());
	lblClock->setText(rtc->getTimeStr());

	lblTemp->setText(String(getTemp()));

	Frame::draw();
}

float MainScreenUI::getTemp()
{
	return analogRead(LM35) / (10 / 1.0742);
}