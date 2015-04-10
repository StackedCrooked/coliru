int score = 0; //Score

//Delete remaining enemies and existing bullets
void GameOver(){
    time = 0; //Reset time

	for (int k = 0; k < numberOfInvaderBullets; k++){ //Delete all bullets invader bullets
		if (invaderBullets[k] != nullptr){ //Delete only the existing bullets
			invaderBullets[k] = nullptr;
			delete invaderBullets[k];
		}
	}

	for (int k = 0; k < numberOfBullets; k++){ //Delete all existing Main Character bullets
		if (bullets[k] != nullptr){
			bullets[k] = nullptr; //Set it to be null pointer
			delete bullets[k]; //Free up memory
		}
	}

	for (int i = 0; i < numberOfEnemies; i++){ //Delete all the invaders
		if (enemies[i] != nullptr){
			enemies[i] = nullptr;
			delete enemies[i];
		}
	}
	if (HighScores.is_open == true){
		HighScores << score << std::endl; //Add score to the score file //////////////////////////////////////////////////////// THIS DOES NOT WORK FOR SOME REASON
	}
	AddScoreToVector(); //Adds current score to the list of high scores	
}

void CollisionDetectionInvaders(){
    float offsetX = invaderSize + bulletSize/2; //Offset for the hitbox from the center point of the invader (includes the bullet size)
	float offsetY = invaderSize * 0.66 + bulletSize / 2; //The space invader fills rouhgly 66% of the square image in Y coordinate
	for (int i = 0; i < numberOfEnemies; i++){ //Loop through all the invaders
		for (int j = 0; j < numberOfBullets; j++){ //Loop through all the bullets
			if (bullets[j] != nullptr && enemies[i] != nullptr){ //If the bullet and the small invader exist
				if (enemies[i]->positionX >= bullets[j]->positionX - offsetX && enemies[i]->positionX <= bullets[j]->positionX + offsetX){ //Checking for x with offsetX
					if (enemies[i]->positionY >= bullets[j]->positionY - offsetY && enemies[i]->positionY <= bullets[j]->positionY + offsetY){ //Checking for y with offsetY
						
						bullets[j] = nullptr; //Set this particular bullet to be null pointer
						delete bullets[j]; //Free up memory

						enemies[i]->explode = true;	
						score += 1;
					}
				}
			}
		}
	}
}

//Collision Detection between invader bullets and Main Character
void CollisionInvaderBullets(float MainCharacterX, float MainCharacterY){
    float offsetX = 50 + bulletSize / 2; //Offset for the hitbox from the center point of the Main Character (includes the bullet size)
	float offsetY = 40 + bulletSize / 2; //Main Character is 550 untis wide Y

	for (int i = 0; i < numberOfInvaderBullets; i++){ //Loop through all the invaders
		if (invaderBullets[i] != nullptr){ //If the bullet exists
			if (MainCharacterX >= invaderBullets[i]->positionX - offsetX && MainCharacterX <= invaderBullets[i]->positionX + offsetX){
				if (MainCharacterY >= invaderBullets[i]->positionY - offsetY && MainCharacterY <= invaderBullets[i]->positionY + offsetY){
					//for (int k = 0; k < numberOfInvaderBullets; k++){ //Delete all bullets invader bullets
					//	if (invaderBullets[k] != nullptr){ //Delete only the existing bullets
					//		invaderBullets[k] = nullptr;
					//		delete invaderBullets[k];
					//	}
					//}
					startGame = false; //Go back to the menu
					GameOver();
				}
			}
		}
	}
}

//Sort the High Scores
void SortHighScores(){
    std::sort(HighScoresLoaded.begin(), HighScoresLoaded.end(), std::greater<int>());
}

//Load in high scores from the HighScores.txt file
void LoadHighScores(){
    int number; //For loading in numbers

	if (HighScores.is_open() == true){ //Make sure the file is open 
		while (HighScores >> number){ //Load in all the numbers
			HighScoresLoaded.push_back(number);
		}
	}
}


void Game()
{
    //Load and initialise everything, when the application is launched. 
	HighScores.open("gfx/HighScores.txt"); //Open 
	LoadHighScores(); //Load high scores
	SortHighScores();
}