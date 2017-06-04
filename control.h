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
	void AddSCORE(Snake &S, Food &F);
	int GetStartTime(){ return START_TIME;}
};

Control::Control(int d){
	ChangeDIR(d); 
	TIMER = TIME_BASE;
	PAUSE = 1;
	LIFE = INIT_LIFE;
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

    // cout << "Dir: " << MoveX() << "," << MoveY() << endl;
    // cout << "Next: " << p->GetX()+MoveX() << "," << p->GetY()+MoveY() << endl << endl;
    // cout << "Head: " << p->GetX() << "," << p->GetY() << endl;
    // cout << "Food: " << F.GetX() << "," << F.GetY() << endl << endl;
    
    if(p->GetX() + MoveX() == F.GetX()
        && p->GetY() + MoveY() == F.GetY() ){
        return 1;
    }

    return 0;
}
void Control::SpeedUp(){
	int tmp = TIMER;
	if (TIMER >= TIME_MIN && SCORE < 60){
		TIMER = TIME_BASE - TIME_UPUNIT*(SCORE / 10);
	}
	if (TIMER != tmp){
		glutSetWindowTitle("SPEED UP !!");
		cout << "SPEED UP !!"<< endl;
		tmp = TIMER;
	}
	if (SCORE == 60){
		glutSetWindowTitle("MAX SPEED !!");
		SCORE += 5;
		LIFE += 3;
		cout << "MAX SPEED !!" << endl;
		cout << "Score +5  Life +3" << endl;
		TIMER = 100;
	}
	if (SCORE > 60){
		TIMER = 100;
	}
	if (SCORE == 120){
		glutSetWindowTitle("CRAZY MODE !!");
		SCORE += 10;
		LIFE += 5;
		cout << "CRAZY MODE !!" << endl;
		cout << "Score +10  Life +5" << endl;
		TIMER = 75;
	}
	if (SCORE > 120){
		TIMER = 75;
	}
}

int Control::LostLife(Snake &S){
	Node* p = new(Node);
	for(p = S.GetHead()->GetFD(); p->GetX() != -1; p=p->GetFD()){
		if( p->GetX() == S.GetHead()->GetFD()->GetX() + MoveX()
			&& p->GetY() == S.GetHead()->GetFD()->GetY() + MoveY()){
			char buf[100];
        	SubLife(1);
			sprintf(buf, "You crash yourself :)  -1s  Life: %d", LIFE);
			glutSetWindowTitle(buf);  
			cout << buf << endl;

        	if (LIFE > 0) return 0; // can pass yourself :)
        	else return 1; // if life <= 0 , can't pass 

		}
		else if( S.GetHead()->GetFD()->GetX() + MoveX() == -1 || S.GetHead()->GetFD()->GetY() + MoveY() == -1 
			|| S.GetHead()->GetFD()->GetX() + MoveX() == MAP_WIDHT || S.GetHead()->GetFD()->GetY() + MoveY() == MAP_HEIGHT){
			char buf[100];
			SubLife(1); 
			sprintf(buf, "Crash The Wall :)  -1s  Life: %d", LIFE);
			glutSetWindowTitle(buf);  
			cout << buf << endl;
        	// cout << "Wall!!" << endl;
        	return 1; // Can't move it crash wall
		}
		else{
			char buf[100];
			sprintf(buf,"Life: %d   Score: %d", LIFE, SCORE);
			glutSetWindowTitle(buf);
			// cout << buf << endl;
		}
	}
	// cout << "continue" << endl;
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
	glClearColor(DARK_GREY, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer  
	
	glLoadIdentity(); // Reset The View
	glTranslatef(-1.0f, 1.0f, 0.0f);

	double unit_x = 2.0f/MAP_WIDHT;
	double unit_y = 2.0f/MAP_HEIGHT;
//unit
/*  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_QUADS);
    glColor3f(WHITE);
	for (int i = 0; i < MAP_HEIGHT; ++i){
    	// draw unit
        for (int j = 0; j < MAP_WIDHT; ++j){
            glVertex3f((j+0) * unit_x, -(i+0) * unit_y, 0.0f);
            glVertex3f((j+1) * unit_x, -(i+0) * unit_y, 0.0f);
            glVertex3f((j+1) * unit_x, -(i+1) * unit_y, 0.0f);
            glVertex3f((j+0) * unit_x, -(i+1) * unit_y, 0.0f);
        }
    }
	glEnd(); */	
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
        glVertex3f((p->GetY()  ) * unit_x, -(p->GetX()  ) * unit_y, 0.0f);  
        glVertex3f((p->GetY()+1) * unit_x, -(p->GetX()  ) * unit_y, 0.0f);  
        glVertex3f((p->GetY()+1) * unit_x, -(p->GetX()+1) * unit_y, 0.0f);  
        glVertex3f((p->GetY()  ) * unit_x, -(p->GetX()+1) * unit_y, 0.0f);  
		glEnd();
		p = p->GetBK();
	}
	glutSwapBuffers();
}

void Control::AddSCORE(Snake &S, Food &F){
	if (F.CmpColor(YELLOW)){
		SCORE += 1;
		cout << "[Y] Score +1  ";
	}
	else if(F.CmpColor(BLUE)){
		S.Delete();
		int p = F.RandInt(100);
		SCORE += 3;
		cout << "[B] Score +3 " << endl;
		if(S.GetLength() > 2){
			S.Delete();
			cout << "Length -1" << endl;
			if (p & 1) {
				S.Delete();
				LIFE += 1;
				cout << "[!] Life +1, Length -1" << endl;
			}
		}
		else{
			LIFE += 2;
		}
	}
	else if(F.CmpColor(RED)){
		S.Delete();
		int p = F.RandInt(100);
		if( p < 30){
			LIFE += 3;
			SCORE += 5;
			cout << "[R] Score +5, Life +3 " << endl;
		}
		else if( p < 70){
			LIFE += 10;
			cout << "[R] Life +10 " << endl;
		}
		else{
			if(S.GetLength() > p%10+1){
				for(int i=0; i<p%10+1; i++){
					S.Delete();
				}
			cout << "[R] Length -" << p%10+1 << " " << endl;
			}
			else{
				LIFE += 5;
				SCORE += 5;
				cout << "Length is too small! Score +5, Life +5" << endl;
			}
		}
	}
	else if(F.CmpColor(ORANGE)){
		for(int i=S.GetLength(); i > 2; i--){
			S.Delete();
		}
		LIFE += 10;
		cout << "[*] Length will be Back to 2 " << endl;
		cout << "[*] Life +10! " << endl;
	}
	cout << "Life: " << LIFE << "  Score: " << SCORE << endl << endl;		
}
#endif
