#ifndef _Food_H_
#define _Food_H_ 
// CLASS Food
class Food : public POS, public RGB{
public:
	void RandomPlace(Snake &S);
	Food(){}
	void EatenBy(Snake &S);
	int RandInt(int sz);
	int CheckPos(int x, int y);
};

int Food::CheckPos(int x, int y){
	if(GetX() == x && GetY() == y){
		return 0;
	}
	return 1;
}

void Food::EatenBy(Snake &S){
	Node* p = new Node(GetX(),GetY());
	p->SetColor(GetR(),GetG(),GetB());
	S.Insert(p);
	// cout << S.GetLength() << endl;
}

int Food::RandInt(int sz){
	char buf[4];
	int fd = open("/dev/urandom",O_RDONLY,0); 
	read(fd,buf,4);
	close(fd);
	return *(unsigned int*)buf % sz;
}

void Food::RandomPlace(Snake &S){
    do{
		SetPosition( RandInt(MAP_WIDHT),RandInt(MAP_HEIGHT));
    }while (!S.CheckPos(GetX(),GetY()));
    int p = RandInt(100);
    if( p < 20 ){
    	SetColor(BLUE);
    }
    else if( p < 30 ){
    	SetColor(RED);
    }
    else if( p < 33 ){
    	SetColor(ORANGE);
    }
    else{
    	SetColor(YELLOW);
    }
}

#endif