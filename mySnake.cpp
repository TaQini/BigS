#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "conf.hpp"
#include "node.hpp"
using namespace std;

void Control::ReSizeGLScene(int w, int h) {  
	if (h == 0) // Prevent A Divide By Zero If The Window Is Too Small  
		h = 1;
	glViewport(0, 0, w, h); // Reset The Current Viewport And Perspective Transformation  

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0f, (GLdouble)w, 0.0f, (GLdouble)h);  
}
Control::Control(int d){
	ChangeDir(d); 
	TIMER = TIME_BASE;
	OVER = 0;
	PAUSE = 0;
}

// void Control::OnKeyPressed(int key, int x, int y){
//     switch(key){
//     	case KEY_SPACE:
//     		PAUSE = !PAUSE;
//     		if(!PAUSE)
// 	            glutTimerFunc(TIMER, OnTimer, OVER);
//     		break;
//     	case KEY_ESCAPE:
// 			glutDestroyWindow(window);
// 			exit(0);
// 		default:
// 			break;
//     }
// }
// void Control::OnDirection(int key, int x, int y){
// 	if (PAUSE) return;
// 	switch(key){
// 		case GLUT_KEY_UP:
// 			if(MOVE != DIR_DOWN) 
// 				DIR = DIR_UP;
// 			break;
// 		case GLUT_KEY_DOWN:
// 			if(MOVE != DIR_UP)
// 				DIR = DIR_DOWN;
// 			break;
// 		case GLUT_KEY_LEFT:
// 			if(MOVE != DIR_RIGHT)
// 				DIR = DIR_LEFT;
// 			break;
// 		case GLUT_KEY_RIGHT:
// 			if(MOVE != DIR_LEFT)
// 				DIR = DIR_RIGHT;
// 			break;
// 		default:
// 			break;
// 	}
// }
int Control::MoveX(){
	switch (DIR){
		case 0:
			return -1;
		case 1:
			return 1;
		default:
			return 0;
	}
}
int Control::MoveY(){
	switch (DIR){
		case 2:
			return -1;
		case 3:
			return 1;
		default:
			return 0;
	}
}
void Control::Move(Snake &S){
	Node *p = new(Node);
	p->SetPosition(S.GetHead()->GetFD()->GetX()+MoveX(),S.GetHead()->GetFD()->GetY()+MoveY());
	// p->SetColor(WHITE);
	S.Insert(S.GetHead(),p);
	S.Delete();
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

int main(int argc, char **argv){
	Control CTRL(DIR_RIGHT);
	Snake BigS(INIT_LENGTH);
	Food Beans;
	BigS.Show();
	// cout << CTRL.GetDir() << endl;
	cout << endl;
	CTRL.Move(BigS);
	// cout << CTRL.MoveX() << "," << CTRL.MoveY() << endl;
	// cout << "2333" << endl;
	// Beans.RandomPlace(BigS);
	// Beans.EatenBy(BigS);
	// BigS.Delete();
	// BigS.Delete();
	// BigS.Delete();
	// BigS.Delete();

	BigS.Show();
	// glutInit(&argc, argv);    
	// glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);    
	// glutInitWindowSize(500, 500);    
	// glutInitWindowPosition(0, 0);    
	// glutCreateWindow("<>>>>><><><><><><><><<<<<<<<>>>>>>>>>>>>>>>>><<<<");    
	// glutDisplayFunc(& CTRL.DrawGLScene);    
	// glutIdleFunc(& CTRL.DrawGLScene);   
	// glutReshapeFunc(& CTRL.ReSizeGLScene);  
	// glutKeyboardFunc(& CTRL.keyPressed);  
	// glutSpecialFunc(CTRL.OnDirection);  
	// glutTimerFunc(CTRL.TIMER, CTRL.OnTimer, CTRL.OVER);  
	// InitGL(500, 500);  
	// glutMainLoop();    
	// CheckPos(BigS);
	// Beans.RandomPlace();
	// BigS.Initilize(5);
	// Beans.RandomPlace();

	// printf("%d\n",RAND_MAX);
}