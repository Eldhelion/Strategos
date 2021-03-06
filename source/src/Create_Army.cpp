/*
 *  Menu.cpp
 *  Strategos
 *
 *
 */

#include "Create_Army.h"
#include "Global.h"
#include "Image.h"

Create_Army::Create_Army(STATE previous) :
		StateMachine(previous, CREATE_ARMY, CREATE_ARMY)
{
	int scrWidth = Game::getGlobalGame()->getWidth();
	int scrHeight = Game::getGlobalGame()->getHeight();
	Font *fntEthnocentric;

	Resource *resource = Game::getGlobalGame()->getResourceMNGR();
	resource->AddImage("assets/ui.gfx", "bg_create_army");

	resource->AddImage("assets/base.gfx", "blueprint1-bg");

	resource->AddImage("assets/ui.gfx", "menu-bt");
	resource->AddImage("assets/ui.gfx", "exit-bt");
	resource->AddImage("assets/ui.gfx", "play-bt");
	resource->AddImage("assets/army.gfx", "human-ships");
	fntEthnocentric = resource->GetFont("jostix-14");

	resource->AddFont("assets/fonts.gfx", "jostix-14");
	//imagens de fundo
	imgBackground = resource->GetImage("bg_create_army");

	btn_Next = new Button(scrWidth * 0.85, scrHeight * 0.05, 150, 24, resource->GetImage("menu-bt"), "BT02");
	btn_Next->setText(resource->GetFont("jostix-14"), "Unit Setup", ColorRGB8::White, ColorRGB8::White);
	addGuiElement(btn_Next);

	btn_Back = new Button(scrWidth * 0.05, scrHeight * 0.05, 150, 24, resource->GetImage("menu-bt"), "BT03");
	btn_Back->setText(resource->GetFont("jostix-14"), "BACK", ColorRGB8::White, ColorRGB8::White);
	addGuiElement(btn_Back);

	btn_Load = new Button(scrWidth * 0.2, scrHeight * 0.4+100, 150, 24, resource->GetImage("menu-bt"), "BT03");
	btn_Load->setText(resource->GetFont("jostix-14"), "Load", ColorRGB8::White, ColorRGB8::White);
	addGuiElement(btn_Load);

	lbl_Title = new Label("Create Army", resource->GetFont("jostix-14"), ColorRGB8::Green, ColorRGB8::White, "LB02");
	lbl_Title->setPosition(scrWidth * 0.45, scrHeight * 0.05);
	addGuiElement(lbl_Title);

	lbl_GenName = new Label("General Name", resource->GetFont("jostix-14"), ColorRGB8::Green, ColorRGB8::White, "LB02");
	lbl_GenName->setPosition(scrWidth * 0.2, scrHeight * 0.2);
	addGuiElement(lbl_GenName);

	txt_GenName = new TextField(scrWidth * 0.4, scrHeight * 0.2, 190, 17, Game::getGlobalGame()->getResourceMNGR()->GetImage("textfield-text"),
	        ColorRGB8::White, "TF02");
	txt_GenName->setFont(Game::getGlobalGame()->getResourceMNGR()->GetFont("jostix-14"));
	txt_GenName->setText("");
	addGuiElement(txt_GenName);

	lbl_ArmyName = new Label("Army Name", resource->GetFont("jostix-14"), ColorRGB8::Green, ColorRGB8::White, "LB02");
	lbl_ArmyName->setPosition(scrWidth * 0.2, scrHeight * 0.3);
	addGuiElement(lbl_ArmyName);

	txt_ArmyName = new TextField(scrWidth * 0.4, scrHeight * 0.3, 190, 17, Game::getGlobalGame()->getResourceMNGR()->GetImage("textfield-text"),
	        ColorRGB8::White, "TF02");
	txt_ArmyName->setFont(Game::getGlobalGame()->getResourceMNGR()->GetFont("jostix-14"));
	txt_ArmyName->setText("");
	addGuiElement(txt_ArmyName);
	dct = Game::getGlobalGame()->getDictionary(0);
	cmb_species = new ComboBox(scrWidth * 0.4, scrHeight * 0.4, 150, 17, Game::getGlobalGame()->getResourceMNGR()->GetImage("combo-cmb"),
	        ColorRGB8::Green, ColorRGB8::White, "CB01");
	cmb_species->setFont(fntEthnocentric);
	cmb_species->addText(dct->title);
	dct = Game::getGlobalGame()->getDictionary(1);
	cmb_species->addText(dct->title);
	dct = Game::getGlobalGame()->getDictionary(2);
	cmb_species->addText(dct->title);

	addGuiElement(cmb_species);

	dct = Game::getGlobalGame()->getDictionary(0);

	lbl_Descr = new Label("Description", resource->GetFont("jostix-14"), ColorRGB8::Green, ColorRGB8::White, "LB02");
	lbl_Descr->setPosition(scrWidth * 0.15, scrHeight * 0.6);
	lbl_Descr->setText(dct->description);
	addGuiElement(lbl_Descr);

	st_box = new StatusBox(0, 0, NULL, NULL, "Statusbox");
	st_box->update(0, 0, dct->getInfoFor(0));
	st_box->setVisible(false);
	addGuiElement(st_box);

	// adicionando box com as imagens das naves
	bx1 = new ImageBox(scrWidth * 0.3, scrHeight * 0.8, 50, 50, resource->GetImage("human-ships"), 0, NULL, "BX1");
	addGuiElement(bx1);
	bx2 = new ImageBox(scrWidth * 0.4, scrHeight * 0.8, 50, 50, resource->GetImage("human-ships"), 1, NULL, "BX1");
	addGuiElement(bx2);
	bx3 = new ImageBox(scrWidth * 0.5, scrHeight * 0.8, 50, 50, resource->GetImage("human-ships"), 2, NULL, "BX1");
	addGuiElement(bx3);
	bx4 = new ImageBox(scrWidth * 0.6, scrHeight * 0.8, 50, 50, resource->GetImage("human-ships"), 3, NULL, "BX1");
	addGuiElement(bx4);

	cmb_armys = new ComboBox(scrWidth * 0.4, scrHeight * 0.4+100, 150, 17, Game::getGlobalGame()->getResourceMNGR()->GetImage("combo-cmb"),
	        ColorRGB8::Green, ColorRGB8::White, "CB01");
	cmb_armys->setFont(fntEthnocentric);
	addGuiElement(cmb_armys);
	vector<string*> datFiles;
	Resource::getListOfFiles(datFiles, "assets/saves/", ".dat");

	for (unsigned int i = 0; i < datFiles.size(); ++i)
	{
		string aux =datFiles[i]->c_str();
		aux= aux.substr( 0, aux.find_last_of('.') );
		aux= aux.substr( aux.find_last_of("\\/")+1 );
		Army *armytemp = Army::loadArmy(aux.c_str());
		if (armytemp)
			cmb_armys->addText(aux.c_str());
		delete armytemp;
	}

	Game::getGlobalGame()->setEditingArmy(NULL);

}

Create_Army::~Create_Army()
{
	delete btn_Next;
	delete btn_Back;
	delete btn_Load;

	delete txt_ArmyName;
	delete txt_GenName;

	delete lbl_ArmyName;
	delete lbl_Title;
	delete lbl_GenName;

	delete bx1;
	delete bx2;
	delete bx3;
	delete bx4;

	delete cmb_species;
	delete cmb_armys;

	delete st_box;
}

void Create_Army::onInputEvent(cGuiElement* element, INPUT_EVENT action, SDL_Keysym key, Uint8 button)
{
	if (element == btn_Back)
	{
		switch (action)
		{
			case MOUSE_RELEASED_EVENT:
				setNext(MENU);
				break;

			default:
				break;
		}
	}
	else if (element == btn_Next)
	{
		switch (action)
		{
			case MOUSE_RELEASED_EVENT:
				if (Game::getGlobalGame()->getEditingArmy() == NULL)
				{
					if (txt_ArmyName->getText() != "")
					{
						if (Game::getGlobalGame()->getDictionary(cmb_species->getText()) != NULL)
						{
							if (Game::getGlobalGame()->getEditingArmy()==NULL)
							{
								Game::getGlobalGame()->setEditingArmy(
							        new Army(txt_ArmyName->getText(), Game::getGlobalGame()->getDictionary(cmb_species->getText())));
							}
							else
							{
								Game::getGlobalGame()->getEditingArmy()->setArmyName(txt_ArmyName->getText());
								Game::getGlobalGame()->getEditingArmy()->setDictionary(Game::getGlobalGame()->getDictionary(cmb_species->getText()));
							}

							setNext(UNIT_SETUP);
						}
					}
				}
				else
					setNext(UNIT_SETUP);

				break;

			default:
				break;
		}
	}
	else if (element == btn_Load)
	{
		switch (action)
		{
			case MOUSE_RELEASED_EVENT:
				if (cmb_armys->getSelectedIndex() != -1)
					txt_ArmyName->setText(cmb_armys->getText());
				Game::getGlobalGame()->setEditingArmy(Army::loadArmy(txt_ArmyName->getText().c_str()));
                cmb_species->setSelected(Game::getGlobalGame()->getEditingArmy()->getDictionary()->title.c_str());

				break;

			default:
				break;
		}
	}
	else if (element == cmb_species)
	{
		switch (action)
		{
			case MOUSE_RELEASED_EVENT:
				dct = Game::getGlobalGame()->getDictionary(cmb_species->getSelectedIndex());
				lbl_Descr->setText(dct->description);
				break;

			default:
				break;
		}
	}
	if (element == cmb_armys)
		{
			switch (action)
			{
				case MOUSE_RELEASED_EVENT:
					break;

				default:
					break;
			}
		}
}

void Create_Army::Logic()
{
	updateGuiElements();
}

void Create_Army::Render()
{
	int scrWidth = Game::getGlobalGame()->getWidth();
	int scrHeight = Game::getGlobalGame()->getHeight();

	Game::getGlobalGame()->setBackgroundColor(255, 0, 0);
	SDL_Renderer* renderer = Game::getGlobalGame()->getRenderer();

	imgBackground->DrawImage(renderer);
	drawGuiElements();
	if (bx1->hover())
	{
		st_box->update(scrWidth * 0.2, scrHeight * 0.4, dct->getInfoFor(0));
		st_box->setVisible(true);
	}
	else if (bx2->hover())
	{
		st_box->update(scrWidth * 0.3, scrHeight * 0.4, dct->getInfoFor(1));
		st_box->setVisible(true);
	}
	else if (bx3->hover())
	{
		st_box->update(scrWidth * 0.4, scrHeight * 0.4, dct->getInfoFor(2));
		st_box->setVisible(true);
	}
	else if (bx4->hover())
	{
		st_box->update(scrWidth * 0.5, scrHeight * 0.4, dct->getInfoFor(3));
		st_box->setVisible(true);
	}
	else
		st_box->setVisible(false);

}

void Create_Army::Clean()
{

}
