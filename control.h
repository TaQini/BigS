#ifndef _Control_H_
#define _Control_H_ 
class Control{
private:
	int DIR;
	int MOVE;
	int TIMER;
	int OVER;
	int PAUSE;
public:
	Control(int d);

	int GetDIR(){ return DIR;}
	int GetMOVE(){ return MOVE;}
	int GetTIMER(){ return TIMER;}
	int GetOVER(){ return OVER;}
	void SetOVER(int o){ OVER = o;}
	int GetPAUSE(){ return PAUSE;}

	void ChangeDIR(int d){ DIR = d;}
	void ChangePAUSE(){ PAUSE = !PAUSE;}
	int MoveX();
	int MoveY();
	void SnakeEat(Snake &S, Food &F);
	void SnakeMove(Snake &S);
	// void Move(Snake &S);
	// void SpeedUp();
	int GameOver(Snake &S);
	void Reshape(int w, int h);
	void Display(void);
	int HasFood(Snake &S, Food &F);
};

Control::Control(int d){
	ChangeDIR(d); 
	TIMER = TIME_BASE;
	OVER = 0;
	PAUSE = 0;
}

void Control::SnakeMove(Snake &S){
	Node *p = new(Node);
	p->SetPosition(S.GetHead()->GetFD()->GetX(),S.GetHead()->GetFD()->GetY());
	// p = S.GetHead()->GetFD();
	p->SetPosition(p->GetX()+MoveX(),p->GetY()+MoveY());
	cout << p->GetX() << "," << p->GetY() << endl;
	sleep(1);
	p->SetColor(WHITE);
	int i;
	cin >> i;
	S.Insert(p);
	S.Delete();
	MOVE = DIR;

	S.Show();
}

int Control::MoveX(){
	if(DIR == 0) return -1;
	else if(DIR == 1) return 1;
	else return 0;
}
int Control::MoveY(){
	if(DIR == 2) return -1;
	else if(DIR == 3) return 1;
	else return 0;
}

int Control::HasFood(Snake &S, Food &F){
	Node *p = new(Node);
	p = S.GetHead()->GetFD();

    cout << "Dir: " << MoveX() << "," << MoveY() << endl;
    cout << "Next: " << p->GetX()+MoveX() << "," << p->GetY()+MoveY() << endl << endl;
    cout << "Head: " << p->GetX() << "," << p->GetY() << endl;
    cout << "Food: " << F.GetX() << "," << F.GetY() << endl << endl;
    
    // F.SetPosition(7,8);
    if(p->GetX() + MoveX() == F.GetX()
        && p->GetY() + MoveY() == F.GetY() ){
        return 1;
    }
  //   while(p){
  //       if(p->GetX() == F.GetX() && p->GetY() == F.GetY()){
  //           return 1;
  //       }
		// p->SetFD(p->GetFD());
  //   }
    return 0;
}
// void Control::SpeedUp(){
// 	if (TIMER >= TIME_MIN){
// 		TIMER += TIME_UPUNIT;
// 	}
// }
int Control::GameOver(Snake &S){
	Node* p = new(Node);
	for(p = S.GetHead()->GetFD(); p->GetX() != -1; p=p->GetFD()){
		if( p->GetX() == S.GetHead()->GetFD()->GetX() + MoveX()
			&& p->GetY() == S.GetHead()->GetFD()->GetY() + MoveY()){
            glutSetWindowTitle("  FINISHED !!");  
        	cout << "GameOver" << endl;
        	return 1;
		}
	}
	cout << "continue" << endl;
	return 0;
}

void Control::Reshape(int w, int h) {  
	if (h == 0) // Prevent A Divide By Zero If The Window Is Too Small  
		h = 1;
	glViewport(0, 0, w, h); // Reset The Current Viewport And Perspective Transformation  

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0f, (GLdouble)w, 0.0f, (GLdouble)h);  
}

void Control::Display(){
	glClearColor(BLACK, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer  
	
	glLoadIdentity(); // Reset The View
	glTranslatef(-1.0f, 1.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_QUADS);
    glColor3f(WHITE);
	double unit_x = 2.0f/MAP_WIDHT;
	double unit_y = 2.0f/MAP_HEIGHT;
    for (int i = 0; i < MAP_HEIGHT; ++i){
    	// draw unit
        for (int j = 0; j < MAP_WIDHT; ++j){
            glVertex3f((j+0) * unit_x, -(i+0) * unit_y, 0.0f);
            glVertex3f((j+1) * unit_x, -(i+0) * unit_y, 0.0f);
            glVertex3f((j+1) * unit_x, -(i+1) * unit_y, 0.0f);
            glVertex3f((j+0) * unit_x, -(i+1) * unit_y, 0.0f);
        }
    }
	glEnd();

	glutSwapBuffers();
}

#endif