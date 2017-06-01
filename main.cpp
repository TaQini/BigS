static Snake* BigS = 0;
static Food* Beans = 0;
static Control* CTRL = 0;

void OnTimer(int value){
	glClearColor(0.0, 0.0, 0.0, 1.0);//000黑色,111白色
	glClear(GL_COLOR_BUFFER_BIT);

	if(!CTRL->PAUSE){
		if(BigS->HasFood()){
			BigS->Eat();
			Beans->RandomPlace();
		}
		if(!GameOver()){
			BigS->Move();//蛇身的移动要更新board矩阵
		}
	}
	glutSwapBuffers();
	glutTimerFunc(500, OnTimer, 1);//需要在函数中再调用一次，才能保证循环  
}

void myReshape(int x, int y){

}
void myDisplay(){
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

void OnKeyPressed(int key, int x, int y){
    switch(key){
    	case KEY_SPACE:
    		PAUSE = !PAUSE;
    		if(!PAUSE)
	            glutTimerFunc(TIMER, OnTimer, OVER);
    		break;
    	case KEY_ESCAPE:
			glutDestroyWindow(window);
			exit(0);
		default:
			break;
    }
}

void OnDirection(int key, int x, int y){
	if (PAUSE) return;
	switch(key){
		case GLUT_KEY_UP:
			if(MOVE != DIR_DOWN) 
				DIR = DIR_UP;
			break;
		case GLUT_KEY_DOWN:
			if(MOVE != DIR_UP)
				DIR = DIR_DOWN;
			break;
		case GLUT_KEY_LEFT:
			if(MOVE != DIR_RIGHT)
				DIR = DIR_LEFT;
			break;
		case GLUT_KEY_RIGHT:
			if(MOVE != DIR_LEFT)
				DIR = DIR_RIGHT;
			break;
		default:
			break;
	}
}

// int main(int argc, char ** argv) {
// 	CTRL = new Control;
// 	BigS = new Snake;
// 	Beans = new Food;

// 	glutInit(&argc, argv);
// 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//双缓冲、RGB模式
// 	glutInitWindowSize(500, 500);
// 	glutInitWindowPosition(100, 100);
// 	glutCreateWindow("Gluttonous Snake");//窗口标题
// 	glShadeModel(GL_SMOOTH);//设置为光滑明暗模式
// 							/*绘制与显示*/
// 	glutReshapeFunc(myReshape);//窗口大小发生改变时采取的行为
// 	glutDisplayFunc(myDisplay);//显示绘制图形
// 	glutTimerFunc(500, timerProc, 1);
// 	glutKeyboardFunc(KeyDown);
// 	//glutMouseFunc(mouse);
// 	//glutIdleFunc(myDisplay);
// 	glutMainLoop();//循环

// 	// delete draw;
// 	// delete board;
// 	// delete snake;
// 	// delete key_event;
// 	return(0);
// }

