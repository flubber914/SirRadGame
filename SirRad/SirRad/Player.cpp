#include "Player.h"
#include "GameEngine.h"

Player::Player()
{
}

Player::Player(int _size[2], int _position[2], int* _speed, string _ImagePath) : Character(_size, _position, _speed, _ImagePath)
{
	speedUp = 0;
	MoveZone = 1;
}

Player::~Player()
{
}
/// <summary>
/// The player moves from left to right taking into account it's x value to determine it's direction and rotation
/// </summary>
/// <param name="moveRight">whether the characters input direction is right or not</param>
/// <returns>whether the character was able to move</returns>
bool Player::Move(bool moveRight)
{
	ChangeDirection(0);
	position[0] += speed;
	position[1] -= speedUp;
	return false;
}

void Player::Movement(bool moveLeft, bool moveRight)
{
	//cout << position[1] << endl;
	if (position[1] > parent->GWindow.GetRampTop()) {
		if (position[0] < parent->GWindow.GetMiddleW() + parent->GWindow.GetEighthW() && position[0] > parent->GWindow.GetMiddleW() - parent->GWindow.GetEighthW()) {///////////MIDDLE
			ChangeMoveZone(0);
			if (moveRight) {
				speed += 1;
			}
			else if (!moveLeft && speed > 0 && rand() % 3 <= 1) {
				speed -= 1;
			}
			if (moveLeft) {
				speed -= 1;
			}
			else if (!moveRight && speed < 0 && rand() % 3 <= 1) {
				speed += 1;
			}
			position[1] = 350;
			speedUp = 0;
		}
		if (position[0] > parent->GWindow.GetMiddleW() + (parent->GWindow.GetEighthW()/2) && position[1]) /////////Right Side
		{
			ChangeMoveZone(1);
			cout << EntrySpeed << endl;
			cout << "hi" << endl;
			if (speed > 0) {
				//cout << speedUp << endl;
				speedUp = speedUp + 1;
				speed -= 1;
			}
			if (speedUp < 0) {
				speedUp = speedUp + 1;
				if (abs(speedUp) <= EntrySpeed) {
					speed -= 1;
				}
			}
		}
		if (position[0] < parent->GWindow.GetMiddleW() - (parent->GWindow.GetEighthW()/2)) { /////////////////////LEFT SIDE
			ChangeMoveZone(1);
			cout << EntrySpeed << endl;
			cout << "hi" << endl;
			if (speed < 0) {
				//cout << speedUp << endl;
				speedUp = speedUp + 1;
				speed += 1;
			}
			if (speedUp < 0) {
				speedUp = speedUp + 1;
				if (abs(speedUp) <= abs(EntrySpeed)) {
					speed += 1;
				}
			}
		}
	}
	else {
		speedUp -= 0.5f;
		speed = 0;
	}
}

void Player::ChangeDirection(int _direction)
{
}

void Player::ChangeMoveZone(int newZone)
{
	if (newZone != MoveZone) {
		EntrySpeed = speed;
		MoveZone = newZone;
	}
}
