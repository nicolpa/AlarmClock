#include "SettingsScreenUI.hpp"

SettingsScreenUI::SettingsScreenUI(lcd::UTFT *LCD, URTouch *Touch) 
    : Frame(LCD, Touch)
{
	Panel *pnlHeader = new Panel(LCD, 0, 0, LCD->getDisplayXSize() - 1, 20);
	pnlHeader->setBorder(false, true, false, false);
	pnlHeader->add(new Label(LCD, 2, VerticalAlignment::Center, "Settings", SmallFont));
	Button *btnBack = new Button(LCD, Touch, HorizontalAlignment::Right, VerticalAlignment::Center, 16, 16);
	GraphicalComponentContainer *gBack = new GraphicalComponentContainer();
	gBack->add(new Line(LCD, 2, btnBack->getHeight() / 2, btnBack->getWidth() / 2, 2));
	gBack->add(new Line(LCD, 2, btnBack->getHeight() / 2, btnBack->getWidth() / 2, btnBack->getHeight() - 2));
	btnBack->setGraphics(gBack);
	// btnBack->setNormalPressAction(goToSettingsAndBack);
	btnBack->setBorderless(true);
	btnBack->setContentHighlight(true);
	pnlHeader->add(btnBack);

	Panel *pnlSettingsMenu = new Panel(LCD, 0, pnlHeader->getHeight() + 1, 135, LCD->getDisplayYSize() - pnlHeader->getHeight() - 1);
	pnlSettingsMenu->setBorder(false);
	Panel *pnlSettingsOption = new Panel(LCD, pnlSettingsMenu->getWidth(), pnlSettingsMenu->getY(), LCD->getDisplayXSize() - pnlSettingsMenu->getWidth() - 1, LCD->getDisplayYSize() - pnlHeader->getHeight() - 1);
	pnlSettingsOption->setBorder(false);

	byte nSettigns = 5;

	Button *btnTimeAndDate = new Button(LCD, Touch,
										HorizontalAlignment::Center, 0,
										pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns),
										"Time and Date", SmallFont);
	// btnTimeAndDate->setBorderless(true);
	btnTimeAndDate->setHorizontalAlignment(HorizontalAlignment::Left);
	btnTimeAndDate->setContentHighlight(true);
	pnlSettingsMenu->add(btnTimeAndDate);

	Button *btnSoundVolume = new Button(LCD, Touch,
										HorizontalAlignment::Center, btnTimeAndDate->getHeight(),
										pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns),
										"Sound", SmallFont);
	// btnSoundVolume->setBorderless(true);
	btnSoundVolume->setHorizontalAlignment(HorizontalAlignment::Left);
	btnSoundVolume->setContentHighlight(true);
	pnlSettingsMenu->add(btnSoundVolume);

	Button *btnSleepSchedule = new Button(LCD, Touch,
										  HorizontalAlignment::Center, btnSoundVolume->getY(false) + btnSoundVolume->getHeight(),
										  pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns),
										  "Sleep Schedule", SmallFont);
	// btnSleepSchedule->setBorderless(true);
	btnSleepSchedule->setHorizontalAlignment(HorizontalAlignment::Left);
	btnSleepSchedule->setContentHighlight(true);
	pnlSettingsMenu->add(btnSleepSchedule);

	Button *btnBrightness = new Button(LCD, Touch,
									   HorizontalAlignment::Center, btnSleepSchedule->getY(false) + btnSleepSchedule->getHeight(),
									   pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns),
									   "Brightness", SmallFont);
	// btnBrightness->setBorderless(true);
	btnBrightness->setHorizontalAlignment(HorizontalAlignment::Left);
	btnBrightness->setContentHighlight(true);
	pnlSettingsMenu->add(btnBrightness);

	Button *btnGentleWake = new Button(LCD, Touch,
									   HorizontalAlignment::Center, btnBrightness->getY(false) + btnBrightness->getHeight(),
									   pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns),
									   "Gentle Wake", SmallFont);
	// btnGentleWake->setBorderless(true);
	btnGentleWake->setHorizontalAlignment(HorizontalAlignment::Left);
	btnGentleWake->setContentHighlight(true);
	pnlSettingsMenu->add(btnGentleWake);

	// for(int i = 1; i < nSettigns; i++)
	//     pnlSettingsMenu->add(new Line(LCD, 7, (pnlSettingsOption->getHeight() / nSettigns) * i, pnlSettingsMenu->getWidth() - 15, (pnlSettingsOption->getHeight() / nSettigns) * i));

	this->add(pnlHeader);
	this->add(pnlSettingsMenu);

	// loadClockSettings(pnlSettingsOption);

	// auto lClock = [](Panel *pnl) {
	// 	frmSettings->add(pnl);
	// };
	// lClock(pnlSettingsOption);
	// void (*fcnPtr)(Panel *){lClock};
	// btnTimeAndDate->setNormalPressAction(fcnPtr(pnlSettingsOption));
}

SettingsScreenUI::~SettingsScreenUI() {

}