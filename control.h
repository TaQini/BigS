class Control{
private:
	int DIR;
	int MOVE;
	int TIMER;
	int OVER;
	int PAUSE;
public:
	Control(int d);
	void OnKeyPressed(int key, int x, int y);
	void OnDirection(int key, int x, int y);
	void OnTimer(int value);

	void ChangeDir(int d){ DIR = d;}
	int MoveX();
	int MoveY();
	void Move(Snake &S);
	int GetDir(){ return DIR;}
	void SpeedUp();
	int GameOver(Snake &S);
	void Reshape(int w, int h);
	void Display(void);
};
