#include "ClockSettingsUI.hpp"

ClockSettingsUI::ClockSettingsUI(lcd::UTFT *LCD, URTouch *Touch, DS1307 *rtc) 
    : Frame(LCD, Touch), rtc(rtc)
{
    Button *btnHoursUp, *btnHoursDown;
	Button *btnMinutesUp, *btnMinutesDown;
	Button *btnSecondesUp, *btnSecondesDown;
	Button *btnConfirm;

	Label *lblClock;

	GraphicalComponentContainer *gUpHour = new GraphicalComponentContainer();
	gUpHour->add(new Line(LCD, 5, 27, 16, 10));
	gUpHour->add(new Line(LCD, 16, 10, 27, 27));

	GraphicalComponentContainer *gDownHour = new GraphicalComponentContainer();
	gDownHour->add(new Line(LCD, 5, 5, 16, 22));
	gDownHour->add(new Line(LCD, 16, 22, 27, 5));

	GraphicalComponentContainer *gUpMinute = new GraphicalComponentContainer();
	gUpMinute->add(new Line(LCD, 5, 27, 16, 10));
	gUpMinute->add(new Line(LCD, 16, 10, 27, 27));

	GraphicalComponentContainer *gDownMinute = new GraphicalComponentContainer();
	gDownMinute->add(new Line(LCD, 5, 5, 16, 22));
	gDownMinute->add(new Line(LCD, 16, 22, 27, 5));

	GraphicalComponentContainer *gUpSecond = new GraphicalComponentContainer();
	gUpSecond->add(new Line(LCD, 5, 27, 16, 10));
	gUpSecond->add(new Line(LCD, 16, 10, 27, 27));

	GraphicalComponentContainer *gDownSecond = new GraphicalComponentContainer();
	gDownSecond->add(new Line(LCD, 5, 5, 16, 22));
	gDownSecond->add(new Line(LCD, 16, 22, 27, 5));

	lblClock = new Label(LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc->getTimeStr(), BigFont);
	this->add(lblClock);

	int center = lblClock->getY(false) + (lblClock->getHeight() / 2);
	int yUp = center - 32 - (lblClock->getHeight() / 2) - 8;
	int yDown = center + (lblClock->getHeight() / 2) + 8;
	int spacing = 48;
	// LCD.drawLine(50, center, 300, center);

	btnHoursUp = new Button(LCD, Touch, lblClock->getX(false), yUp, 32, 32, gUpHour);
	btnHoursDown = new Button(LCD, Touch, lblClock->getX(false), yDown, 32, 32, gDownHour);

	btnMinutesUp = new Button(LCD, Touch, btnHoursUp->getX() + spacing, yUp, 32, 32, gUpMinute);
	btnMinutesDown = new Button(LCD, Touch, btnHoursUp->getX() + spacing, yDown, 32, 32, gDownMinute);

	btnSecondesUp = new Button(LCD, Touch, btnMinutesUp->getX() + spacing, yUp, 32, 32, gUpSecond);
	btnSecondesDown = new Button(LCD, Touch, btnMinutesUp->getX() + spacing, yDown, 32, 32, gDownSecond);

	btnHoursUp->setBorderless(true);
	btnHoursDown->setBorderless(true);
	btnMinutesUp->setBorderless(true);
	btnMinutesDown->setBorderless(true);
	btnSecondesUp->setBorderless(true);
	btnSecondesDown->setBorderless(true);

	btnHoursUp->setContentHighlight(true);
	btnHoursDown->setContentHighlight(true);
	btnMinutesUp->setContentHighlight(true);
	btnMinutesDown->setContentHighlight(true);
	btnSecondesUp->setContentHighlight(true);
	btnSecondesDown->setContentHighlight(true);

	btnHoursUp->setBackground(lcd::TRANSPARENT);
	btnHoursDown->setBackground(lcd::TRANSPARENT);
	btnMinutesUp->setBackground(lcd::TRANSPARENT);
	btnMinutesDown->setBackground(lcd::TRANSPARENT);
	btnSecondesUp->setBackground(lcd::TRANSPARENT);
	btnSecondesDown->setBackground(lcd::TRANSPARENT);

	btnConfirm = new Button(LCD, Touch, HorizontalAlignment::Right, VerticalAlignment::Down, 60, 20, "Apply", SmallFont);

	this->add(btnHoursUp);
	this->add(btnHoursDown);
	this->add(btnMinutesUp);
	this->add(btnMinutesDown);
	this->add(btnSecondesUp);
	this->add(btnSecondesDown);
	this->add(btnConfirm);
	this->setBackground(lcd::RED);
}

ClockSettingsUI::~ClockSettingsUI() {

}