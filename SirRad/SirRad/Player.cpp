#include "Player.h"
#include "GameEngine.h"

Player::Player()
{
}

Player::Player(int _size[2], int _position[2], int* _speed, string _ImagePath) : Character(_size, _position, _speed, _ImagePath)
{
	speedUp = 0;
	MoveZone = 1;
	velocity.X = 8;
	velocity.Y = 8;
	cout << velocity.magnitude() << endl;
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
			if (moveRight) {
				velocity.X += 1;
			}
			else if (!moveLeft && velocity.X > 0 && rand() % 3 <= 1) {
				velocity.X -= 1;
			}
			if (moveLeft) {
				velocity.X -= 1;
			}
			else if (!moveRight && velocity.X < 0 && rand() % 3 <= 1) {
				velocity.X += 1;
			}
			position[1] = 350;
			velocity.Y = 0;
		}
		if (position[0] > parent->GWindow.GetMiddleW() + (parent->GWindow.GetEighthW()/2) && position[1]) /////////Right Side
		{
			ChangeMoveZone(1);
			if (velocity.X > 0) {
				//cout << speedUp << endl;
				cout << "next frame" << endl;
				cout << abs(parent->GWindow.GetFloor() - position[1]) << endl;
				cout << (1.0f / 15) * pow(position[0] - (parent->GWindow.GetMiddleW() + (parent->GWindow.GetEighthW() / 2)), 2) << endl;
				if (abs(parent->GWindow.GetFloor() - position[1]) < (1.0f / 15) * pow(position[0] - (parent->GWindow.GetMiddleW() + (parent->GWindow.GetEighthW() / 2)), 2)) { ////////////////////////implement a line for the ramp
					velocity.Y = velocity.Y + 1;
					velocity.X -= 1;
				}
			}
			if (velocity.Y < 0) {
				velocity.Y = velocity.Y + 1;
				if (abs(velocity.Y) <= EntrySpeed) {
					if (abs(parent->GWindow.GetFloor() - position[1]) < (1.0f / 15) * pow(position[0] - (parent->GWindow.GetMiddleW() + (parent->GWindow.GetEighthW() / 2)), 2)) {
						velocity.X -= 1;
					}
				}
			}
		}
		if (position[0] < parent->GWindow.GetMiddleW() - (parent->GWindow.GetEighthW()/2)) { /////////////////////LEFT SIDE
			ChangeMoveZone(1);
			cout << EntrySpeed << endl;
			cout << "hi" << endl;
			if (velocity.X < 0) {
				//cout << speedUp << endl;
				velocity.Y = velocity.Y + 1;
				velocity.X += 1;
			}
			if (velocity.Y < 0) {
				velocity.Y = velocity.Y + 1;
				if (abs(velocity.Y) <= abs(EntrySpeed)) {
					velocity.X += 1;
				}
			}
		}
	}
	else {
		velocity.Y -= 1;
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
