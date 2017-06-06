#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <unistd.h>  
#include <stdio.h>
#include <time.h>
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
		if(!CTRL->LostLife(*BigS)){
			if(CTRL->HasFood(*BigS, *Beans)){
				Beans->EatenBy(*BigS);
				CTRL->AddSCORE(*BigS, *Beans);
				// BigS->Show();
				Beans->RandomPlace(*BigS);
			}
			else
				CTRL->SnakeMove(*BigS); 
		}
		else{
			if(CTRL->GetLIFE() <= 0){
				char buf[100];
				sprintf(buf, GAMEOVER_INFO, CTRL->GetSCORE());
				glutSetWindowTitle(buf);
				CTRL->state(buf);  
				
				// But you can also play it :)			
				if (!CTRL->GetHiddenMode()){
					sleep(3);
					glutSetWindowTitle(BYEBYE);
					CTRL->state(BYEBYE);
					sleep(1);
					exit(0);
				}
			}
		}
	}	

	if(CTRL->GetSCORE() <= 120){
		CTRL->SpeedUp();
	}

	glutSwapBuffers();
	glutTimerFunc(CTRL->GetTIMER(), OnTimer, 1);
}

void Reshape(int x, int y){
	CTRL->Reshape(x, y);
}
void Display(){
	CTRL->Display(*BigS, *Beans);
}

void OnKeyPressed(unsigned char key, int x, int y){
	// state("[Debug] key: "+(key));
    switch(key){
		case 'w':
			if(CTRL->GetMOVE() != DIR_DOWN) 
				CTRL->ChangeDIR(DIR_UP);
			break;
		case 's':
			if(CTRL->GetMOVE() != DIR_UP)
				CTRL->ChangeDIR(DIR_DOWN);
			break;
		case 'a':
			if(CTRL->GetMOVE() != DIR_RIGHT)
				CTRL->ChangeDIR(DIR_LEFT);
			break;
		case 'd':
			if(CTRL->GetMOVE() != DIR_LEFT)
				CTRL->ChangeDIR(DIR_RIGHT);
			break;
    	case KEY_SPACE:
    		CTRL->ChangePAUSE();
    		break;
    	case KEY_ESCAPE:
			exit(0);
		case 'o':
			CTRL->OpenHiddenMode();
			break;
		case '+':
			CTRL->AddSpeed(1);
			break;
		case '-':
			CTRL->AddSpeed(-1);
			break;
		default:
			break;
    }
}

void OnDirection(int key, int x, int y){
	if (CTRL->GetPAUSE()) return;
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

void welcome(void){
	system("clear");
	cout << " +----------------------------------------------------+" << endl;
	cout << " |              Welcome to TaQini's Game              |" << endl;
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
	cout << " |            Your Goal: Score up to 1000             |" << endl;
	cout << " |               Press SPACE to START !!              |" << endl;
	cout << " +----------------------------------------------------+" << endl;
}

int main(int argc, char ** argv) {
	CTRL = new Control(DIR_RIGHT);
	BigS = new Snake(4);
	Beans = new Food;
	// BigS->Show();
	Beans->RandomPlace(*BigS);

	glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(960, 1200);
	glutInitWindowPosition(1000, 1000);
	glutCreateWindow("TaQini\'s Snake");// Title
	welcome();
	
	// Draw and Display
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
    glutTimerFunc(CTRL->GetTIMER(), OnTimer, 1);	
	glutKeyboardFunc(OnKeyPressed);
	glutSpecialFunc(OnDirection);

	glutMainLoop(); // Loop

	return(0);
}
