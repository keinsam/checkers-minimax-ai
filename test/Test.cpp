#include "../src/Modele/Jeu.hpp"
#include "../src/Screen.hpp"
#include <chrono>
#include <thread>

int main() {
	Screen* app = new Screen{2000, 2000};

	while (app->isOpen()) {
		switch (app->getCurrentPhase()) {
			case GamePhase::Choixdujeu :
				app->draw_Choixdujeu();
				app->handle_Choixdujeu();
				break;
			case GamePhase::Configuration :
				app->draw_Config();
				app->handle_Config();
				break;

			case::GamePhase::Game:
				app->draw_Plateau();
				app->handle_Game();
				break;

			case::GamePhase::GameIncognito:
				app->draw_Plateau();
				app->handle_I2();
				break;

			case GamePhase::GameSafari :
				app->draw_Plateau();
				app->handle_S2();
				break;

			case GamePhase::GameOver :
				app->affiche_gagnant();
				app->display();
				chrono::seconds duration(5);
				this_thread::sleep_for(duration);
				app->Close();
				break;

		}
		app->display();
	}

	delete app;
}
