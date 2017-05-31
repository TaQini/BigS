// CLASS POS
class POS{
private:
	int X,Y;
public:
	void SetPosition(int x, int y){	X = x; Y = y;}
	void SetX(int x) { X = x;}
	void SetY(int y) { Y = y;}
	int GetX() { return X;}
	int GetY() { return Y;}
};

// CLASS RGB
class RGB{
private:
	float R,G,B;
public:
	void SetColor(float r, float g, float b){ R = r; G = g; B = b;}
	RGB GetColor() {return *this;}
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
	void SetFD(Node *p){ fd = p;}
	void SetBK(Node *p){ bk = p;}
	Node* GetFD(){ return fd;}
	Node* GetBK(){ return bk;}
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
