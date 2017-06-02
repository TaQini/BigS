#include <iostream>
using namespace std;
#include <GL/glut.h>    // Header File For The GLUT Library   
#include <GL/gl.h>    // Header File For The OpenGL32 Library  
#include <GL/glu.h>   // Header File For The GLu32 Library  
#include <unistd.h>     // Header file for sleeping.  
#include <fcntl.h>
#include "conf.h"
#include "node.h"
#include "snake.h"
#include "food.h"
#include "control.h"

static Snake* BigS = 0;
static Food* Beans = 0;
static Control* CTRL = 0;

void OnTimer(int value){
	glClearColor(BLACK, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(!CTRL->GetPAUSE()){
		if(CTRL->HasFood(*BigS, *Beans)){
			
			Beans->EatenBy(*BigS);
			BigS->Show();
			cout << "ok!! GOT 1 point!" << endl << endl;
			Beans->RandomPlace(*BigS);
		}
		if(!CTRL->GameOver(*BigS)){
			CTRL->SnakeMove(*BigS); 
			sleep(1);
		}
		else{
			CTRL->SetOVER(1);
		}

	}

	glutSwapBuffers();
	glutTimerFunc(500, OnTimer, 1);//需要在函数中再调用一次，才能保证循环  
}

void Reshape(int x, int y){
	CTRL->Reshape(x, y);
}
void Display(){
	CTRL->Display();
}

void OnKeyPressed(unsigned char key, int x, int y){
	cout << "[Debug] key: " << (int)(key) << endl;
    switch(key){
    	case KEY_SPACE:
    		CTRL->ChangePAUSE();
    		if(!CTRL->GetPAUSE())
	            glutTimerFunc(CTRL->GetTIMER(), OnTimer, CTRL->GetOVER());
    		break;
    	case KEY_ESCAPE:
			exit(0);
		default:
			break;
    }
}

void OnDirection(int key, int x, int y){
	if (CTRL->GetPAUSE()) return;
	// cout << "MOVE::" << CTRL->GetMOVE() << endl;
	switch(key){
		case GLUT_KEY_UP:
			if(CTRL->GetMOVE() != DIR_DOWN) 
				CTRL->ChangeDIR(DIR_UP);
			break;
		case GLUT_KEY_DOWN:
			if(CTRL->GetMOVE() != DIR_UP)
				CTRL->ChangeDIR(DIR_DOWN);
			break;
		case GLUT_KEY_LEFT:
			if(CTRL->GetMOVE() != DIR_RIGHT)
				CTRL->ChangeDIR(DIR_LEFT);
			break;
		case GLUT_KEY_RIGHT:
			if(CTRL->GetMOVE() != DIR_LEFT)
				CTRL->ChangeDIR(DIR_RIGHT);
			break;
		default:
			break;
	}
}

int main(int argc, char ** argv) {
	CTRL = new Control(DIR_RIGHT);
	BigS = new Snake(4);
	Beans = new Food;
	BigS->Show();
	Beans->RandomPlace(*BigS);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TaQini\'s Snake");//窗口标题
	
	// Draw and Display
	glutReshapeFunc(Reshape);//窗口大小发生改变时采取的行为
	glutDisplayFunc(Display);//显示绘制图形
	glutIdleFunc(Display);
    glutTimerFunc(CTRL->GetTIMER(), OnTimer, CTRL->GetOVER());	
	glutKeyboardFunc(OnKeyPressed);
	glutSpecialFunc(OnDirection);

	glutMainLoop(); // Loop

	return(0);
}