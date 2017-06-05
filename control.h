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
	string Conv(int n, int i);
	void state(char *msg);
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
	// //cout << p->GetX() << "," << p->GetY() << endl;
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

    // //cout << "Dir: " << MoveX() << "," << MoveY() << endl;
    // //cout << "Next: " << p->GetX()+MoveX() << "," << p->GetY()+MoveY() << endl << endl;
    // //cout << "Head: " << p->GetX() << "," << p->GetY() << endl;
    // //cout << "Food: " << F.GetX() << "," << F.GetY() << endl << endl;
    
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
		state("SPEED UP !!");
		//cout << "SPEED UP !!"<< endl;
		tmp = TIMER;
	}
	if (SCORE == 60){
		glutSetWindowTitle("MAX SPEED !!");
		SCORE += 5;
		LIFE += 3;
		state("MAX SPEED !!");
		//cout << "MAX SPEED !!" << endl;
		//cout << "Score +5  Life +3" << endl;
		TIMER = 100;
	}
	if (SCORE > 60){
		TIMER = 100;
	}
	if (SCORE == 120){
		glutSetWindowTitle("CRAZY MODE !!");
		SCORE += 10;
		LIFE += 5;
		state("CRAZY MODE !!");
		//cout << "CRAZY MODE !!" << endl;
		//cout << "Score +10  Life +5" << endl;
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
        	state(buf);
			glutSetWindowTitle(buf);  
			//cout << buf << endl;

        	if (LIFE > 0) return 0; // can pass yourself :)
        	else return 1; // if life <= 0 , can't pass 

		}
		else if( S.GetHead()->GetFD()->GetX() + MoveX() == -1 || S.GetHead()->GetFD()->GetY() + MoveY() == -1 
			|| S.GetHead()->GetFD()->GetX() + MoveX() == MAP_WIDHT || S.GetHead()->GetFD()->GetY() + MoveY() == MAP_HEIGHT){
			char buf[100];
			SubLife(1);
			sprintf(buf, "Crash The Wall :)  -1s  Life: %d", LIFE);
        	state(buf); 
			glutSetWindowTitle(buf);  
			//cout << buf << endl;
        	// //cout << "Wall!!" << endl;
        	return 1; // Can't move it crash wall
		}
		else{
			char buf[100];
			sprintf(buf,"Life: %d   Score: %d", LIFE, SCORE);
			glutSetWindowTitle(buf);
			// //cout << buf << endl;
		}
	}
	// //cout << "continue" << endl;
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

	// Food
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);  
	glBegin(GL_QUADS);
	glColor3f(F.GetR(), F.GetG(), F.GetB());

    glVertex3f((F.GetY()  ) * unit_x, -(F.GetX()  ) * unit_y, 0.0f);
    glVertex3f((F.GetY()+1) * unit_x, -(F.GetX()  ) * unit_y, 0.0f);
    glVertex3f((F.GetY()+1) * unit_x, -(F.GetX()+1) * unit_y, 0.0f);
    glVertex3f((F.GetY()  ) * unit_x, -(F.GetX()+1) * unit_y, 0.0f);
	glEnd();
	// glutSwapBuffers();

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
		state("[Y] Score +1");
	}
	else if(F.CmpColor(BLUE)){
		S.Delete();
		int p = F.RandInt(100);
		SCORE += 3;
		if(S.GetLength() > 2){
			S.Delete();
			if (p & 1) {
				S.Delete();
				LIFE += 1;
				state("[B] Score +3, Life +1, Length -2");
			}
			else{
				state("[B] Score +3, Length -1");
			}
		}
		else{
			LIFE += 2;
			state("Length is too small! Life +2");
		}
	}
	else if(F.CmpColor(RED)){
		S.Delete();
		int p = F.RandInt(100);
		if( p < 30){
			LIFE += 3;
			SCORE += 5;
			state("[R] Score +5, Life +3 ");
		}
		else if( p < 70){
			LIFE += 10;
			state("[R] Life +10 ");
		}
		else{
			if(S.GetLength() > p%10+1){
				for(int i=0; i<p%10+1; i++){
					S.Delete();
				}
				char buf[100];
				sprintf(buf, "[R] Length -%d ",p%10+1);
				state(buf);
			}
			else{
				LIFE += 5;
				SCORE += 5;
				state("Length is too small! Score +5, Life +5");
			}
		}
	}
	else if(F.CmpColor(ORANGE)){
		for(int i=S.GetLength(); i > 2; i--){
			S.Delete();
		}
		LIFE += 10;
		state("[*] Length will be Back to 2 ,Life +10! ");
	}
}


string Control::Conv(int n, int i){
	switch (n){
		case 0:
			switch (i){
				case 0: return C00;
				case 1: return C01;
				case 2: return C02;
				case 3: return C03;
				case 4: return C04;
				case 5: return C05;
			}
		case 1:
			switch (i){
				case 0: return C10;
				case 1: return C11;
				case 2: return C12;
				case 3: return C13;
				case 4: return C14;
				case 5: return C15;
			}
		case 2:
			switch (i){
				case 0: return C20;
				case 1: return C21;
				case 2: return C22;
				case 3: return C23;
				case 4: return C24;
				case 5: return C25;
			}
		case 3:
			switch (i){
				case 0: return C30;
				case 1: return C31;
				case 2: return C32;
				case 3: return C33;
				case 4: return C34;
				case 5: return C35;
			}
		case 4:
			switch (i){
				case 0: return C40;
				case 1: return C41;
				case 2: return C42;
				case 3: return C43;
				case 4: return C44;
				case 5: return C45;
			}
		case 5:
			switch (i){
				case 0: return C50;
				case 1: return C51;
				case 2: return C52;
				case 3: return C53;
				case 4: return C54;
				case 5: return C55;
			}
		case 6:
			switch (i){
				case 0: return C60;
				case 1: return C61;
				case 2: return C62;
				case 3: return C63;
				case 4: return C64;
				case 5: return C65;
			}
		case 7:
			switch (i){
				case 0: return C70;
				case 1: return C71;
				case 2: return C72;
				case 3: return C73;
				case 4: return C74;
				case 5: return C75;
			}
		case 8:
			switch (i){
				case 0: return C80;
				case 1: return C81;
				case 2: return C82;
				case 3: return C83;
				case 4: return C84;
				case 5: return C85;
			}
		case 9:
			switch (i){
				case 0: return C90;
				case 1: return C91;
				case 2: return C92;
				case 3: return C93;
				case 4: return C94;
				case 5: return C95;
			}
	}
}
void Control::state(char *msg){
	system("clear");
	cout << " +-------------------------+--------------------------+" << endl;
	cout << " |                         |                          |" << endl;
	cout << " |          Life           |          Score           |" << endl;
	cout << " |                         |                          |" << endl;
	cout << " +----------------------------------------------------+" << endl;

	int l0 = LIFE / 100 % 10;
	int l1 = LIFE / 10 % 10;
	int l2 = LIFE / 1 % 10;

	int s0 = SCORE / 100 % 10;
	int s1 = SCORE / 10 % 10;
	int s2 = SCORE / 1 % 10;

	for(int i=0;i<6;i++){
		cout << " |" + Conv(l0,i) + Conv(l1,i) + Conv(l2,i) + " | " + Conv(s0,i) + Conv(s1,i) + Conv(s2,i) + " | " << endl;
	}

	cout << " |                         |                          |" << endl;
	cout << " +-------------------------+--------------------------+" << endl;
	cout << " |             __________________________             |" << endl;
	cout << " |                                   __               |" << endl;
	cout << " |                 /     ,         /    )             |" << endl;
	cout << " |             ---/__--------__----\\-----             |" << endl;
	cout << " |               /   ) /   /   )    \\                 |" << endl;
	cout << " |             _(___/_/___(___/_(____/___             |" << endl;
	cout << " |                           /                        |" << endl;
	cout << " |                       (_ /                         |" << endl;
	cout << " |                                                    |" << endl;
	cout << " +----------------------------------------------------+" << endl;
	cout << endl << "    " << msg << endl;
}
#endif

/*
+---------------------+----------------------+
|                     |                      |
|        Life         |        Score         |
|                     |                      |
+--------------------------------------------+
|   ___   __   ___    |    ___   __   ___    |
|  / _ \ /_ | |__ \   |   / _ \ /_ | |__ \   |
| | | | | | |    ) |  |  | | | | | |    ) |  |
| | | | | | |   / /   |  | | | | | |   / /   |
| | |_| | | |  / /_   |  | |_| | | |  / /_   |
|  \___/  |_| |____|  |   \___/  |_| |____|  |
|                     |                      |
+---------------------+----------------------+
 */