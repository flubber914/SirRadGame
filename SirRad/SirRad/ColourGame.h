#ifndef COLOURGAME_H
#define COLOURGAME_H
class ColourGame
{
public:
	ColourGame();
	~ColourGame();
	void StartGame();
	void RecieveInput(int value);
private:
	enum colour {Red, Orange, Yellow, Green, Blue, White};
	colour question;
	colour answer;
	void SetColour(colour colour);
};

#endif