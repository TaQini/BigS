#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "conf.hpp"
#include "node.hpp"
using namespace std;

// CLASS SNAKE
class Snake{
private:
	Node *head;
	Node *tail;
	int length;
public:
	Snake(int n);
	void Insert(Node *head, Node *p);
	// void Delete(int n); In ver.2: Eat special bean then cut down the length of snake	
	void Move(/*DIR?*/);
	int CheckPos(int x, int y);
	Node* GetHead(){ return head;}
	Node* GetTail(){ return tail;}
	void Show(){
		Node *p = new(Node);
		p = head;
		while(p){
			cout << p->GetX() << "," << p->GetY() << endl;
			p = p->GetFD();
		}
	}
};

int Snake::CheckPos(int x, int y){
	Node* p = new(Node);
	for(p = head->GetFD(); p->GetX() != -1; p = p->GetFD()){
		if( p->GetX() == x && p->GetY() == y ) return 0;
	}
	return 1;
}

Snake::Snake(int n){
	length = n;
	head = new(Node);
	tail = new(Node);
	head->SetPosition(MAP_WIDHT/2,MAP_HEIGHT/2);
	head->SetColor(WHITE);
	head->SetFD(tail);
	head->SetBK(NULL);
	tail->SetFD(NULL);
	tail->SetBK(head);
	for (int i=length-1; i>=0; --i){
		Node *node = new(Node);
		node->SetPosition(head->GetX(),head->GetY()-i);
		Insert(head,node);
	}
	head->SetPosition(0,-1);
	tail->SetPosition(-1,0);
	/* Init snake
	[H] 0,-1
	 => 8,8
		8,7
		8,6
		8,5
		8,4
	[T] -1,0
	 */
}

void Snake::Insert(Node *head, Node *p){
    p->SetBK(head);
    p->SetFD(head->GetFD());
    head->SetFD(p);
    p->GetFD()->SetBK(p);
}


class Food : public POS, public RGB{
// private:
	// int seed;
public:
	void RandomPlace(Snake &S);
	Food(){	}
	int RandInt(int sz);
};

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
    cout << GetX() << "," << GetY() << endl;
}

// CLASS DIR
class Control{
private:
	int DIR;
	int MOVE;
	// int _dir_x[4] = {-1, 1, 0, 0};
	// int _dir_y[4] = { 0, 0,-1, 1};  
	int TIMER;
	int OVER;  
	int PAUSE;  

public:
	Control(int d){ 
		ChangeDir(d); 
		TIMER = TIME_BASE;
		OVER = 0;
		PAUSE = 0;
	}
	void ChangeDir(int d){ DIR = d;}
	int GetDir(){ return DIR;}
	void SpeedUp();

};
void Control::SpeedUp(){
	if (TIMER >= TIME_MIN){
		TIMER += TIME_UPUNIT;
	}
}

int main(int argc, char **argv){
	Snake BigS(INIT_LENGTH);
	BigS.Show();
	cout << "2333" << endl;
	Food Beans;
	Beans.RandomPlace(BigS);
	Control Direction(DIR_RIGHT);

	// CheckPos(BigS);
	// Beans.RandomPlace();
	// BigS.Initilize(5);
	// Beans.RandomPlace();

	// printf("%d\n",RAND_MAX);
}
