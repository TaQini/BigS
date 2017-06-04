#ifndef _Control_H_
#define _Control_H_ 
class Control{
private:
	int DIR;
	int MOVE;
	int TIMER;
	int PAUSE;
	int LIFE;
	int SCORE;
	int START_TIME;
public:
	Control(int d);
	int GetDIR(){ return DIR;}
	int GetMOVE(){ return MOVE;}
	int GetTIMER(){ return TIMER;}
	int GetPAUSE(){ return PAUSE;}

	void ChangeDIR(int d){ DIR = d;}
	void ChangePAUSE(){ PAUSE = !PAUSE;}
	int MoveX();
	int MoveY();
	void SnakeEat(Snake &S, Food &F);
	void SnakeMove(Snake &S);
	int LostLife(Snake &S);
	void Reshape(int w, int h);
	void Display(Snake &S, Food &F);
	int HasFood(Snake &S, Food &F);
	void SubLife(int n){ LIFE -= n;}
	void SpeedUp();
	int GetLIFE(){ return LIFE;}
	int GetSCORE(){ return SCORE;}
	void AddSCORE(int n){ SCORE += n;}
	int GetStartTime(){ return START_TIME;}
};

Control::Control(int d){
	ChangeDIR(d); 
	TIMER = TIME_BASE;
	PAUSE = 0;
	LIFE = 100;
	SCORE = 0;
	START_TIME = time(NULL);
}

void Control::SnakeMove(Snake &S){
	Node *p = new(Node);
	p->SetPosition(S.GetHead()->GetFD()->GetX(),S.GetHead()->GetFD()->GetY());
	p->SetPosition(p->GetX()+MoveX(),p->GetY()+MoveY());
	// Debug
	// cout << p->GetX() << "," << p->GetY() << endl;
	// int i;
	// cin >> i;
	S.Insert(p);
	S.Delete();
	MOVE = DIR;

	// S.Show();
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
    
    if(p->GetX() + MoveX() == F.GetX()
        && p->GetY() + MoveY() == F.GetY() ){
        return 1;
    }

    return 0;
}
void Control::SpeedUp(){
	int tmp = TIMER;
	if (TIMER >= TIME_MIN){
		TIMER = TIME_BASE - TIME_UPUNIT*(SCORE / 3);
	}
	if (TIMER != tmp){
		glutSetWindowTitle("  SPEED UP !!  ");
		tmp = TIMER;
	}
	if (SCORE == 30){
		glutSetWindowTitle("  CRAZY MODE !!  ");
		TIMER = 100;
		tmp = TIMER;
	}
	if (SCORE == 50){
		glutSetWindowTitle("  HENTAI MODE !!  ");
		TIMER = 75;
		tmp = TIMER;
	}


}
int Control::LostLife(Snake &S){
	Node* p = new(Node);
	for(p = S.GetHead()->GetFD(); p->GetX() != -1; p=p->GetFD()){
		if( p->GetX() == S.GetHead()->GetFD()->GetX() + MoveX()
			&& p->GetY() == S.GetHead()->GetFD()->GetY() + MoveY()){
			char buf[100];
        	SubLife(1);
			sprintf(buf, " You crash yourself :)  -1s  Life: %d", LIFE);
			glutSetWindowTitle(buf);  

        	if (LIFE > 0) return 0; // can pass yourself :)
        	else return 1; // if life <= 0 , can't pass 

		}
		else if( S.GetHead()->GetFD()->GetX() + MoveX() == -1 || S.GetHead()->GetFD()->GetY() + MoveY() == -1 
			|| S.GetHead()->GetFD()->GetX() + MoveX() == MAP_WIDHT || S.GetHead()->GetFD()->GetY() + MoveY() == MAP_HEIGHT){
			char buf[100];
			SubLife(1); 
			sprintf(buf, " Crash The Wall :)  -1s  Life: %d", LIFE);
			glutSetWindowTitle(buf);  
        	// cout << "Wall!!" << endl;
        	return 1; // Can't move it crash wall
		}
		else{
			char buf[100];
			sprintf(buf," Life: %d   Score: %d", LIFE, SCORE);
			glutSetWindowTitle(buf);
		}
	}
	cout << "continue" << endl;
	return 0;
}

void Control::Reshape(int w, int h) {  
	if (h == 0) h = 1;
	// Prevent A Divide By Zero If The Window Is Too Small  

	glViewport(0, 0, w, h); // Reset The Current Viewport And Perspective Transformation  

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0f, (GLdouble)w, 0.0f, (GLdouble)h);  
}

void Control::Display(Snake &S, Food &F){
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
	// Food
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);  
	glBegin(GL_QUADS);
	glColor3f(F.GetR(), F.GetG(), F.GetB());

    glVertex3f((F.GetY()  ) * unit_x, -(F.GetX()  ) * unit_y, 0.0f);
    glVertex3f((F.GetY()+1) * unit_x, -(F.GetX()  ) * unit_y, 0.0f);
    glVertex3f((F.GetY()+1) * unit_x, -(F.GetX()+1) * unit_y, 0.0f);
    glVertex3f((F.GetY()  ) * unit_x, -(F.GetX()+1) * unit_y, 0.0f);
	glEnd();

	// Snake
	Node* p = S.GetTail()->GetBK();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	while (p->GetY() != -1){
		glBegin(GL_QUADS);
		glColor3f(p->GetR(), p->GetG(), p->GetB());
		// glColor3f(GREEN);
        glVertex3f((p->GetY()  ) * unit_x, -(p->GetX()  ) * unit_y, 0.0f);  
        glVertex3f((p->GetY()+1) * unit_x, -(p->GetX()  ) * unit_y, 0.0f);  
        glVertex3f((p->GetY()+1) * unit_x, -(p->GetX()+1) * unit_y, 0.0f);  
        glVertex3f((p->GetY()  ) * unit_x, -(p->GetX()+1) * unit_y, 0.0f);  
		glEnd();
		p = p->GetBK();
	}
	// 
	glutSwapBuffers();
}

#endif
