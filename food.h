// CLASS Food
class Food : public POS, public RGB{
public:
	void RandomPlace(Snake &S);
	Food(){	}
	void EatenBy(Snake &S);
	int RandInt(int sz);
	int CheckPos(int x, int y);
};