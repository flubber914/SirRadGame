#include "Player.h"
#include "GameEngine.h"

Player::Player()
{
}

Player::Player(int _size[2], int _position[2], int* _speed, string _ImagePath) : Character(_size, _position, _speed, _ImagePath, 2)
{
	speedUp = 0;
	MoveZone = 1;
	velocity.X = 0;
	velocity.Y = 0;
}

Player::~Player()
{
}
/// <summary>
/// The player moves from left to right taking into account it's x value to determine it's direction and rotation
/// </summary>
/// <param name="moveRight">whether the characters input direction is right or not</param>
/// <returns>whether the character was able to move</returns>
bool Player::Move()
{
	position[0] += velocity.X;
	position[1] -= velocity.Y;
	return false;
}

void Player::Movement(bool moveLeft, bool moveRight)
{
	//cout << position[1] << endl;
	if (position[1] > parent->GWindow.GetRampTop()) {
		if (position[0] < parent->GWindow.GetMiddleW() + parent->GWindow.GetEighthW() && position[0] > parent->GWindow.GetMiddleW() - parent->GWindow.GetEighthW()) {///////////MIDDLE
			ChangeMoveZone(0);
			if (moveRight && velocity.X < 15) {
				velocity.X += 1;
			}
			else if (!moveLeft && velocity.X > 0 && rand() % 10 <= 1) {
				velocity.X -= 1;
			}
			if (moveLeft && velocity.X > -15) {
				velocity.X -= 1;
			}
			else if (!moveRight && velocity.X < 0 && rand() % 10 <= 1) {
				velocity.X += 1;
			}
			position[1] = parent->ImageRender.GetSurface()->h - (parent->ImageRender.GetSurface()->h / 8);
			velocity.Y = 0;
		}
		if (position[0] > parent->GWindow.GetMiddleW() + (parent->GWindow.GetEighthW()/2)) /////////Right Side
		{
			ChangeMoveZone(1);
			if (velocity.X > 0) {
				//cout << speedUp << endl;
				velocity.Y = velocity.Y + 1;
				velocity.X -= 1;
			}
			else if (velocity.Y >= 0) {
				velocity.Y = velocity.Y - 1;
			}
			if (velocity.Y < 0) {
				if (abs((velocity.Y + (velocity.Y * (velocity.Y - 1)))/2) >= abs(position[1] - parent->GWindow.GetFloor())) {
					velocity.Y = velocity.Y + 1;
					velocity.X = velocity.X - 1;
				}
				else {
					velocity.Y = velocity.Y - 1;
				}
			}
		}
		if (position[0] < parent->GWindow.GetMiddleW() - (parent->GWindow.GetEighthW()/2)) { /////////////////////LEFT SIDE
			ChangeMoveZone(1);
			if (velocity.X < 0) {
				//cout << speedUp << endl;
				velocity.Y = velocity.Y + 1;
				velocity.X += 1;
			}
			else if (velocity.Y >= 0) {
				velocity.Y = velocity.Y - 1;
			}
			if (velocity.Y < 0) {
				if (abs((velocity.Y + (velocity.Y * (velocity.Y - 1))) / 2) >= abs(position[1] - parent->GWindow.GetFloor())) {
					velocity.Y = velocity.Y + 1;
					velocity.X = velocity.X + 1;
				}
				else {
					velocity.Y = velocity.Y - 1;
				}
			}
		}
	}
	else {
		velocity.Y -= 0.5f;
		velocity.X = 0;
	}
}

void Player::ChangeDirection(int _direction)
{
}

void Player::ChangeMoveZone(int newZone)
{
	if (newZone != MoveZone) {
		EntrySpeed = velocity.X;
		MoveZone = newZone;
	}
}
