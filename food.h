#ifndef _Food_H_
#define _Food_H_ 
// CLASS Food
class Food : public POS, public RGB{
public:
	void RandomPlace(Snake &S); // generate a random bean
	Food(){} // ctor
	void EatenBy(Snake &S); // add bean's node to snake 
	int RandInt(int sz); // generate a random integer
};

void Food::EatenBy(Snake &S){
	Node* p = new Node(GetX(),GetY());
	S.Insert(p); 
}

int Food::RandInt(int sz){
	char buf[4];
	int fd = open("/dev/urandom",O_RDONLY,0); // use urandom file to generate randint
	read(fd,buf,4);
	close(fd);
	return *(unsigned int*)buf % sz;
}

void Food::RandomPlace(Snake &S){
    do{ // Place a Bean where is not on the body of snake
		SetPosition( RandInt(MAP_WIDTH),RandInt(MAP_HEIGHT));
    }while (!S.CheckPos(GetX(),GetY()));
    
    int p = RandInt(100);
    // cout << "random int : " << p << endl; // Debug
    
    // set color of bean
    if( p < 12 ){ // 12%
    	SetColor(BLUE); 
    }
    else if( p > 25 && p < 30 ){ // 4%
    	SetColor(RED);
    }
    else if( p == 66 ){ // 1%
    	SetColor(ORANGE);
    }
    else if( p > 95){ // 4%
    	SetColor(WHITE);
    }
    else{ // 79%
    	SetColor(YELLOW);
    }
}

#endif