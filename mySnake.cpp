#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include <ctime>
#include <iostream>
using namespace std;

// MAP SIZE
#define MAP_WIDHT  16
#define MAP_HEIGHT 16

// DIRECTOR
#define DIR_UP         0  
#define DIR_DOWN       1  
#define DIR_LEFT       2  
#define DIR_RIGHT      3  

// COLOR
#define WHITE	1.0f,1.0f,1.0f
#define YELLOW 	1.0f,1.0f,0.0f
#define GREEN	0.0f,1.0f,0.0f

// CLASS POS
class POS{
private:
	int X,Y;
public:
	void SetPosition(int x, int y){	X = x; Y = y;}
	int GetX() { return X;}
	int GetY() { return Y;}
};

// CLASS RGB
class RGB{
private:
	float R,G,B;
public:
	void SetColor(float r, float g, float b){ R = r; G = g; B = b;}
};

// CLASS NODE
class Node : public RGB, public POS{
private:
	Node *fd;
	Node *bk;
public:
	Node();
	Node(int x, int y);
	Node(float r, float g, float b);
	Node(Node *fd, Node *bk);
	void SetFD(Node *p);
	void SetBK(Node *p);
	Node *GetFD();
	Node *GetBK();
};
Node::Node(){
	SetFD(NULL);
	SetBK(NULL);
};
Node::Node(int x, int y){
	SetPosition(x,y);
	SetFD(NULL);
	SetBK(NULL);
}
Node::Node(float r, float g, float b){
	SetColor(r,g,b);
	SetFD(NULL);
	SetBK(NULL);
}
Node::Node(Node *fd, Node *bk){
	SetFD(fd);
	SetBK(bk);
}

void Node::SetFD(Node *p){
	fd = p;
}
Node *Node::GetFD(){
	return fd;
}
Node *Node::GetBK(){
	return bk;
}

void Node::SetBK(Node *p){
	bk = p;
}

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
	
	void Show(){
		Node *p = new(Node);
		p = head;
		while(p){
			cout << p->GetX() << "," << p->GetY() << endl;
			p = p->GetFD();
		}
	}
};

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
private:
public:
	void RandomPlace(void);
	void CheckPos(Snake &S);
};
// void Food::CheckPos(Snake &S){

// }

void Food::RandomPlace(void){
    srand(time(NULL));
    // do{
	SetPosition(rand() % MAP_WIDHT, rand() % MAP_HEIGHT);
    // }while (!CheckPos(x,y))
    cout << GetX() << "," << GetY() << endl;
}

// CLASS DIR
class Director{

};



int main(int argc, char **argv){
	Snake BigS(8);
	BigS.Show();
	cout << "2333" << endl;
	Food Beans;
	Beans.RandomPlace();
	// BigS.Initilize(5);
	// Beans.RandomPlace();

	// printf("%d\n",RAND_MAX);
}
