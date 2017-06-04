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
				// cout << "ok!! GOT 1 point!" << endl << endl;
				Beans->RandomPlace(*BigS);
			}
			else
				CTRL->SnakeMove(*BigS); 
		}
		else{
			if(CTRL->GetLIFE() <= 0){
				char buf[100];
				sprintf(buf, "GAME OVER !!  Final SCORE: %d", CTRL->GetSCORE());
				glutSetWindowTitle(buf);  
				cout << buf << endl;
				// But you can also play it :)			
				sleep(3);
				glutSetWindowTitle("BYE BYE !!");
				cout << "BYE BYE !!" << endl;
				sleep(1);
				exit(0);
			}
		}
	}	

	CTRL->SpeedUp();

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
	// cout << "[Debug] key: " << (int)(key) << endl;
    switch(key){
    	case KEY_SPACE:
    		CTRL->ChangePAUSE();
    		// Hidden function : Once Press PAUSE, speed *= 2
    		// if(!CTRL->GetPAUSE())
			    // glutTimerFunc(CTRL->GetTIMER(), OnTimer, 1);
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

void welcome(void){
	system("clear");

	cout << "    Welcome to TaQini's Game \n        -- Snake Eat Beans !" << endl;
	cout << endl;
	cout << "You will control a snake to eat Beans." << endl;
	cout << endl;
	cout << "* Blue and Red Beans have some special function :)" << endl;
	cout << endl;
	cout << "When your score is up to 1000, You WIN the Game!" << endl;
	cout << endl << endl;
	cout << "This window will show some info 4 u~" << endl;
	cout << endl;
	cout << "Good Luck!" << endl;
	cout << endl;
	cout << "Press \"SPACE\" to START !!" << endl;
	cout << endl;
}
int main(int argc, char ** argv) {
	CTRL = new Control(DIR_RIGHT);
	BigS = new Snake(4);
	Beans = new Food;
	// BigS->Show();
	Beans->RandomPlace(*BigS);

	glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);    

	// glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
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
