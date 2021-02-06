#include "AlarmScreenUI.hpp"

AlarmScreenUI::AlarmScreenUI(lcd::UTFT *LCD, URTouch *Touch, DS1307 *rtc)
    : Frame(LCD, Touch), rtc(rtc)
{
	btnMenu = new Button(LCD, Touch, HorizontalAlignment::Right, VerticalAlignment::Down, 16, 16);
	GraphicalComponentContainer *shapeBtnMenu = new GraphicalComponentContainer();
	shapeBtnMenu->add(new Rectangle(LCD, 2, 3, btnMenu->getWidth() - 2, 4, true));
	shapeBtnMenu->add(new Rectangle(LCD, 2, 7, btnMenu->getWidth() - 2, 8, true));
	shapeBtnMenu->add(new Rectangle(LCD, 2, 11, btnMenu->getWidth() - 2, 12, true));
	btnMenu->setGraphics(shapeBtnMenu);
	btnMenu->setBorderless(true);
	// btnMenu->setNormalPressAction(&switchFrame);
	btnMenu->setContentHighlight(true);
	this->add(btnMenu);

	Panel *pnlClock;
	Panel *pnlAlarms;

    Panel *pnlHeader = new Panel(this->LCD, 0, 0, LCD->getDisplayXSize() - 1, 20);
	pnlHeader->setBorder(false, true, false, false);
	pnlHeader->add(new Label(this->LCD, 2, VerticalAlignment::Center, "Alarm", SmallFont));
	this->add(pnlHeader);
	pnlHeader->setMargin(0, 5, 0, 5);

	Line *lineBtnSettingsTop = new Line(this->LCD, 2, 2, 14, 2);
	Rectangle *rectBtnSettingsTop = new Rectangle(this->LCD, lineBtnSettingsTop->getX() + lineBtnSettingsTop->getWidth() - 5, lineBtnSettingsTop->getY() - 2,
												  lineBtnSettingsTop->getX() + lineBtnSettingsTop->getWidth() - 2, lineBtnSettingsTop->getY() + 2, true);

	Line *lineBtnSettingsBottom1 = new Line(this->LCD, 2, 10, 5, 10);
	Line *lineBtnSettingsBottom2 = new Line(this->LCD, 8, 10, 14, 10);

	Rectangle *rectBtnSettingsBottom = new Rectangle(this->LCD, lineBtnSettingsBottom1->getX() + lineBtnSettingsBottom1->getWidth(), lineBtnSettingsBottom1->getY() - 2,
													 lineBtnSettingsBottom2->getX(), lineBtnSettingsBottom1->getY() + 2);

	GraphicalComponentContainer *shapeBtnSettings = new GraphicalComponentContainer();
	shapeBtnSettings->add(lineBtnSettingsTop);
	shapeBtnSettings->add(rectBtnSettingsTop);
	shapeBtnSettings->add(lineBtnSettingsBottom1);
	shapeBtnSettings->add(rectBtnSettingsBottom);
	shapeBtnSettings->add(lineBtnSettingsBottom2);

	btnSettings = new Button(this->LCD, this->Touch, HorizontalAlignment::Right, VerticalAlignment::Center, 16, 15, shapeBtnSettings);
	btnSettings->setBorderless(true);
	btnSettings->setContentHighlight(true);
	// btnSettings->setNormalPressAction(&goToSettingsAndBack);
	pnlHeader->add(btnSettings);
	
	
	
	this->add(pnlClock = new Panel(this->LCD, 0, pnlHeader->getHeight() + 1, 150, this->LCD->getDisplayYSize() - pnlHeader->getHeight() - 1));
	pnlClock->setBorder(false, false, false, true);
	pnlClock->add(lblClock = new Label(this->LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc->getTimeStr(), BigFont));
	this->add(pnlAlarms = new Panel(this->LCD, pnlClock->getWidth(), pnlHeader->getHeight() + 1,
										this->LCD->getDisplayXSize() - pnlClock->getWidth() - 1, this->LCD->getDisplayYSize() - pnlHeader->getHeight() - btnMenu->getHeight() - 5));
	pnlAlarms->setBorder(false, true, false, false);
	Panel *pnlBtnMenu = new Panel(this->LCD, pnlAlarms->getX(), pnlAlarms->getY() + pnlAlarms->getHeight(),
								  pnlAlarms->getWidth() - btnMenu->getWidth() - 5, this->LCD->getDisplayYSize() - pnlAlarms->getHeight() - pnlHeader->getHeight() - 1);
	pnlBtnMenu->add(btnAlarm = new Button(this->LCD, this->Touch, 0, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "A", SmallFont));
	pnlBtnMenu->add(btnStopwatch = new Button(this->LCD, this->Touch, HorizontalAlignment::Center, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "S", SmallFont));
	pnlBtnMenu->add(btnTimer = new Button(this->LCD, this->Touch, HorizontalAlignment::Right, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "T", SmallFont));
	pnlBtnMenu->setBorder(false);
	btnAlarm->setBorderHighlight(false);
	btnAlarm->setContentHighlight(true);
	btnStopwatch->setBorderHighlight(false);
	btnStopwatch->setContentHighlight(true);
	btnTimer->setBorderHighlight(false);
	btnTimer->setContentHighlight(true);

	Line *lnLeft = new Line(this->LCD, this->LCD->getDisplayXSize() - 1, pnlBtnMenu->getY(), this->LCD->getDisplayXSize() - 1, pnlBtnMenu->getY() + pnlBtnMenu->getHeight() - 1);
	Line *lnBottom = new Line(this->LCD, pnlBtnMenu->getX() + pnlBtnMenu->getWidth(), this->LCD->getDisplayYSize() - 1, this->LCD->getDisplayXSize() - 1, this->LCD->getDisplayYSize() - 1);

	this->add(lnLeft);
	this->add(lnBottom);

	this->add(pnlBtnMenu);

	static Panel *pnlAlarm1 = new Panel(this->LCD, 0, 0, pnlAlarms->getWidth(), 40);
	pnlAlarm1->setBorder(false, true, false, false);
	static Label *lblTime = new Label(this->LCD, 5, 5, "06:30", BigFont);
	pnlAlarm1->add(lblTime);
	static Label *lblLabel = new Label(this->LCD, 5, lblTime->getY() + lblTime->getHeight() + 5, "Alarm,", SmallFont);
	pnlAlarm1->add(lblLabel);
	static Label *lblRepeat = new Label(this->LCD, lblLabel->getX() + lblLabel->getWidth() + 10, lblLabel->getY(), "Repeat once", SmallFont);
	pnlAlarm1->add(lblRepeat);
	pnlAlarms->add(pnlAlarm1);
	static Label *lblNextRing = new Label(this->LCD, HorizontalAlignment::Center, pnlClock->getY() + pnlClock->getHeight() - 50, "No alarms on", SmallFont);
	pnlClock->add(lblNextRing);

	
}

AlarmScreenUI::~AlarmScreenUI() 
{

}

void AlarmScreenUI::draw() 
{
	lblClock->setText(rtc->getTimeStr());
	Frame::draw();
}