#ifndef _Snake_H_
#define _Snake_H_ 
// CLASS Snake
class Snake{
private:
	Node *head; // head_mark of snake head
	Node *tail; // tail_mark of snake tail
	int length; // length of snake
	int role;   // use to change snake's color
public:
	Snake(int n); // Initilize Snake
	void Insert(Node *p); // Insert node after head
	void Delete(); // delete node before tail
	int CheckPos(int x, int y); // check if (x,y) in snake's body
	Node* GetHead(){ return head;}
	Node* GetTail(){ return tail;}
	int GetLength(){ return length;}
	void SetLength(int n){ length = n;}
	void ChangeRole(){ role = !role;} 
};
// CLASS SNAKE
int Snake::CheckPos(int x, int y){
	Node* p = new(Node);
	for(p = head->GetFD(); p->GetX() != -1; p = p->GetFD()){
		if( p->GetX() == x && p->GetY() == y ) return 0;
	}
	return 1;
}

Snake::Snake(int n){
	length = 0;
	role = time(NULL) & 1;
	head = new(Node);
	tail = new(Node);
	head->SetPosition(MAP_WIDTH/2,MAP_HEIGHT/2);
	head->SetFD(tail);
	head->SetBK(NULL);
	tail->SetFD(NULL);
	tail->SetBK(head);
	for (int i=n-1; i>=0; --i){
		Node *p = new(Node);
		p->SetPosition(head->GetX(),head->GetY()-i); // initilize a snake
		Insert(p);
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

void Snake::Insert(Node *p){
	//Insert p after head
    p->SetBK(head);
    p->SetFD(head->GetFD());
    head->SetFD(p);
    p->GetFD()->SetBK(p);
    length += 1;
    if(!role){
	    head->GetFD()->SetColor(DARK_GREEN);
	    head->GetFD()->GetFD()->SetColor(GREEN);
	}
	else{
		head->GetFD()->SetColor(DARK_PINK);
	    head->GetFD()->GetFD()->SetColor(PINK);	
	}
}

void Snake::Delete(){
	// Delete p before tail
	Node* p = tail->GetBK();
	tail->SetBK(p->GetBK());
	p->GetBK()->SetFD(tail);
	delete p;
	length -= 1;
}
#endif