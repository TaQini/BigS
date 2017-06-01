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
	head = new(Node);
	tail = new(Node);
	head->SetPosition(MAP_WIDHT/2,MAP_HEIGHT/2);
	head->SetColor(WHITE);
	head->SetFD(tail);
	head->SetBK(NULL);
	tail->SetFD(NULL);
	tail->SetBK(head);
	for (int i=n-1; i>=0; --i){
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
	//Insert p after head
    p->SetBK(head);
    p->SetFD(head->GetFD());
    head->SetFD(p);
    p->GetFD()->SetBK(p);
    length += 1;
}
void Snake::Delete(){
	// Delete p before tail
	Node* p = tail->GetBK();
	tail->SetBK(p->GetBK());
	p->GetBK()->SetFD(tail);
	delete p;
	length -= 1;
}