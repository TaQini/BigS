// CLASS Snake
class Snake{
private:
	Node *head; // head_mark of snake head
	Node *tail; // tail_mark of snake tail
	int length; // length of snake
public:
	Snake(int n); // Initilize Snake
	void Insert(Node *head, Node *p); // Insert node after head
	void Delete(); // delete node before tail
	void Move(/*Control &C*/);
	int CheckPos(int x, int y);
	Node* GetHead(){ return head;}
	Node* GetTail(){ return tail;}
	int GetLength(){ return length;}
	void SetLength(int n){ length = n;}
	void Show(){Node *p = new(Node); p = head;while(p){cout << p->GetX() << "," << p->GetY() << endl;p = p->GetFD();} } 
};