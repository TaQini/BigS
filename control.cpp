
Control::Control(int d){
	ChangeDir(d); 
	TIMER = TIME_BASE;
	OVER = 0;
	PAUSE = 0;
}

void Control::SpeedUp(){
	if (TIMER >= TIME_MIN){
		TIMER += TIME_UPUNIT;
	}
}
int Control::GameOver(Snake &S){
	Node* p = new(Node);
	for(p = S.GetHead()->GetFD(); p->GetX() != -1; p=p->GetFD()){
		if( p->GetX() == S.GetHead()->GetFD()->GetX() + GetDir()
			&& p->GetY() == S.GetHead()->GetFD()->GetY() + GetDir()){
            glutSetWindowTitle("  FINISHED !!");  
        	return 1;
		}
	}
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
	glClearColor(0.0, 0.0, 0.0, 1.0); //000 Black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // Clear The Screen And The Depth Buffer  
	
	glutSwapBuffers();  
}  