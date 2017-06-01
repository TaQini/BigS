int Food::CheckPos(int x, int y){
	if(GetX() == x && GetY() == y){
		return 0;
	}
	return 1;
}

void Food::EatenBy(Snake &S){
	Node* p = new Node(GetX(),GetY());
	p->SetColor(YELLOW);
	S.Insert(S.GetHead(), p);
	cout << S.GetLength() << endl;
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
    cout << GetX() << "," << GetY() << endl;
}