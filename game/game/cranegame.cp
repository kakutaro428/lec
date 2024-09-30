#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GLUT/glut.h>
#include <unistd.h>




// グローバル変数
static bool KeyUpON    = false;	// 矢印キーの状態フラグ
static bool KeyDownON  = false;	// 矢印キーの状態フラグ
static bool KeyLeftON  = false;	// 矢印キーの状態フラグ
static bool KeyRightON = false;	// 矢印キーの状態フラグ

static bool KeyUpON1 = false;	// 矢印キーの状態フラグ
static bool KeyDownON1 = false;	// 矢印キーの状態フラグ
static bool KeyLeftON1 = false;	// 矢印キーの状態フラグ
static bool KeyRightON1 = false;	// 矢印キーの状態フラグ

static int MouseX = 0;	// マウスX座標
static int MouseY = 0;	// マウスY座標
static float SpinX = 0;	// X軸周りの回転量
static float SpinY = 0;	// Y軸周りの回転量

static float MoveX = 0;	// X軸方向の移動量
static float MoveZ = 0;	// Y軸方向の移動量
static float Scale = 1.0; // 拡大量

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define PI 3.1415926535
#define FIELD_SIZE 20.0f
#define SHIP_NUM 2
#define DEFAULT_LIFE 1



// 自機の情報を格納する構造体
typedef struct _MyShip{
	int Life;   // 自機が生きてるか？
	float x;  // 自機のx座標
    float y;
	float z;  // 自機のz座標
    float vy=0.1;
    int down=0;
    float rot=0;
	float theta;  // 自機の向き
} MyShip;

MyShip ship[SHIP_NUM]; // 自機の構造体を作成

// キーボード入力(スペースキーで弾を発射)
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case ' ':
	  //printf("(%3d,%3d)でスペースが押されました\n", x, y);
			  if (ship[0].down == 0) {
                  system("afplay /Users/kakutaro/Desktop/埼玉大学/3年前期/プログラミング演習Ⅲ/game/game/se_ge-sen01.mp3 &");
				  ship[0].down = 1;



			  }
	  
	  break;



  case 'w':
	  //printf("(%3d,%3d)で[↑]が押されました\n", x, y);
	  KeyUpON = true;
	  break;
  case 's':
	  //printf("(%3d,%3d)で[↓]が押されました\n", x, y);
	  KeyDownON = true;
	  break;
  case 'a':
	  //printf("(%3d,%3d)で[←]が押されました\n", x, y);
	  KeyLeftON = true;
	  break;
  case 'd':
	  //printf("(%3d,%3d)で[→]が押されました\n", x, y);
	  KeyRightON = true;
	  break;

  case 'r':
	  for (int j = 0; j<SHIP_NUM; j++) {
		  // 自機の構造体データを初期化
		  ship[j].x = rand()%20;	// 自機の初期位置(X座標)
          ship[0].y = 5.0;
          ship[1].y=0;
		  ship[j].z = rand() % 20;	// 自機の初期位置(Z座標)
		  ship[j].theta = rand() % 360;	// 自機の初期位置(Z座標)
          ship[j].down =0;
          ship[0].rot=0;
		  ship[j].Life = DEFAULT_LIFE;	// 自機は生きている


	  }
	  break;
  }
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		//printf("(%3d,%3d)で[↑]が離されました\n", x, y);
		KeyUpON = false;
		break;
	case 's':
		//printf("(%3d,%3d)で[↓]が離されました\n", x, y);
		KeyDownON = false;
		break;
	case 'a':
		//printf("(%3d,%3d)で[←]が離されました\n", x, y);
		KeyLeftON = false;
		break;
	case 'd':
		//printf("(%3d,%3d)で[→]が離されました\n", x, y);
		KeyRightON = false;
		break;
	}
}



void timer(int t)             // 指定時間後に呼び出される関数（Timerコールバック関数）
{
	// 矢印キーを押し続けている間は自機を移動
	if (KeyUpON == 1) { 
		ship[0].z += 0.2*cos(ship[0].theta /180.0*PI);
		ship[0].x += 0.2*sin(ship[0].theta / 180.0*PI);
	}
	if (KeyDownON == 1) {
		ship[0].z -= 0.2*cos(ship[0].theta / 180.0*PI);
		ship[0].x -= 0.2*sin(ship[0].theta / 180.0*PI);
	}
	if (KeyLeftON == 1) {
		ship[0].theta += 1;
	}
	if (KeyRightON == 1) {
		ship[0].theta -= 1;
	}



    if(ship[0].down==1){
				ship[0].y -= ship[0].vy;
        if(ship[0].y<0.5){
            ship[0].down=2;
        }
    }
    if(ship[0].down==2){
            ship[0].rot+=1;

        if(ship[0].rot>30){
            ship[0].down=3;
        }
    }


            
    
    if(ship[0].down==3){
        if ((ship[0].x - ship[1].x)<1.0&&(ship[0].x - ship[1].x)>-1.0&&
            (ship[0].y - ship[1].y)<0.5&&(ship[0].y - ship[1].y)>-0.5&&
            (ship[0].z - ship[1].z)<1.0&&(ship[0].z - ship[1].z)>-1.0 ) {
            ship[1].down=1;
        }
                ship[0].y += ship[0].vy;
        if(ship[0].y>5){
            ship[0].down=4;
            //printf("%d",ship[1].down);
        }
    }
    if(ship[0].down==4){
            ship[0].rot-=1;

        if(ship[0].rot==0){
            ship[0].down=0;
        }
    }
    if(ship[1].down==1){
        ship[1].y+=ship[0].vy;
        if(ship[1].y>5){
            ship[1].down=2;
            system("afplay /Users/kakutaro/Desktop/埼玉大学/3年前期/プログラミング演習Ⅲ/game/game/se_itemget_004.wav &");
            ship[1].Life--;
            ship[0].Life--;
            printf("%f",ship[1].y);
        }
    }
    




	glutPostRedisplay();          // 画面の再描画
	glutTimerFunc(20, timer, 20); // 次回のタイマー関数の呼び出しをセット
}

//カメラの視点変更
void setGluLookAt(int shipid =1) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (shipid == 1) {
		float cosTheta = cos(ship[0].theta / 180.0*PI);
		float sinTheta = sin(ship[0].theta / 180.0*PI);
		gluLookAt(ship[0].x + (-10.0)*sinTheta, 5.0, ship[0].z + cosTheta*(-10.0),
			ship[0].x + sinTheta * (100.0), 0.0, ship[0].z + 100.0 * cosTheta,
			0.0, 1.0, 0.0);
	}
	else if (shipid == 2) {
		float cosTheta = cos(ship[1].theta / 180.0*PI);
		float sinTheta = sin(ship[1].theta / 180.0*PI);
		gluLookAt(ship[1].x + (-10.0)*sinTheta, 4.0, ship[1].z + cosTheta*(-10.0),
			ship[1].x + sinTheta * (100.0), 0.0, ship[1].z + 100.0 * cosTheta,
			0.0, 1.0, 0.0);

	}
}

void reshape(int w, int h)    // ウインドウサイズ変更時に呼び出される関数（Reshapeコールバック関数）
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (double)w/h, 1.0, 1000.0);
	setGluLookAt();
}


void DrawSurface(void) { // 地面を描画
	glPushMatrix();
	GLfloat mat0ambi[] = { 0.8,  0.6, 0.6, 1.0 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0ambi); //環境光の反射率を設定
	GLfloat mat0diff[] = { 0.8,  0.6, 0.6, 1.0 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat0diff); //拡散光の反射率を設定
	GLfloat mat0spec[] = { 0.992157,  0.941176, 0.807843, 1.0 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat0spec); //鏡面光の反射率を設定

	glNormal3f(0.0, 1.0, 0.0); //法線方向の設定

	glTranslatef(0.0, -0.5, 0.0);
	glScalef(FIELD_SIZE, FIELD_SIZE, FIELD_SIZE);
	glBegin(GL_QUADS);
	glVertex3f( 1.0f, 0.0f,  1.0f);
	glVertex3f(-1.0f, 0.0f,  1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f( 1.0f, 0.0f, -1.0f);
	glEnd();
	glPopMatrix();

}


// 自機の描画1
void DrawMyShip(void)
{
	glPushMatrix();
	GLfloat mat0ambi[] = {0.329412,  0.223529, 0.027451, 1.0};//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  mat0ambi); //環境光の反射率を設定
	GLfloat mat0diff[] = {0.780392,  0.568627, 0.113725, 1.0};//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat0diff); //拡散光の反射率を設定
	GLfloat mat0spec[] = {0.992157,  0.941176, 0.807843, 1.0};//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat0spec); //鏡面光の反射率を設定
	GLfloat mat0shine[] ={ 27.89743616};//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat0shine);
	
	//自機の描画
	glTranslatef(ship[0].x, ship[0].y, ship[0].z);
    glTranslated(-0.2, 0, 0);
    glRotatef(-80, 0.0, 0.0, 1.0);
    glScalef(0.1, 1.0, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
    
    glPushMatrix();
    glTranslatef(ship[0].x, ship[0].y, ship[0].z);
    glTranslated(0.2, 0, 0);
    glRotatef(80, 0.0, 0.0, 1.0);
    glScalef(0.1, 1.0, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(ship[0].x, ship[0].y, ship[0].z);
    glTranslated(-0.6, -0.4, 0);
    glRotatef(10, 0.0, 0.0, 1.0);
    glRotatef(ship[0].rot, 0.0, 0.0, 1.0);
    glScalef(0.1, 0.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(ship[0].x, ship[0].y, ship[0].z);
    glTranslated(0.6, -0.4, 0);
    glRotatef(-10, 0.0, 0.0, 1.0);
    glRotatef(-ship[0].rot, 0.0, 0.0, 1.0);
    glScalef(0.1, 0.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
	}


// 自機の描画2
void DrawMyShip2(void)
{
	glPushMatrix();
	GLfloat mat0ambi[] = { 0.329412,  0.223529, 0.027451, 1.0 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0ambi); //環境光の反射率を設定
	GLfloat mat0diff[] = { 0.4380392,  0.368627, 0.913725, 1.0 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat0diff); //拡散光の反射率を設定
	GLfloat mat0spec[] = { 0.992157,  0.441176, 0.407843, 1.0 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat0spec); //鏡面光の反射率を設定
	GLfloat mat0shine[] = { 27.89743616 };//真鍮
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat0shine);

	//自機の描画
	glTranslatef(ship[1].x, ship[1].y, ship[1].z); //X軸方向にMoveX，Y軸方向にMoveYだけ移動
	glRotatef(ship[1].theta - 90, 0.0, 1.0, 0.0);  //Y軸周りに90度回転
	glutSolidTeapot(0.6);            //自機はティーポット(笑)
	glPopMatrix();


}



void DrawAxis() {
	//軸の描画
	glPushMatrix();	// X軸
	GLfloat mat1diff[] = { 0.6, 0.2, 0.2, 1.0 }; //環境光と拡散光の反射率をまとめて設定
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat1diff);
	glNormal3f(0.0, 1.0, 0.0); //法線方向の設定
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();	// Y軸
	GLfloat mat2diff[] = { 0.2, 0.6, 0.2, 1.0 }; //環境光と拡散光の反射率をまとめて設定
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat2diff);
	glNormal3f(0.0, 1.0, 0.0); //法線方向の設定
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();	// Z軸
	GLfloat mat3diff[] = { 0.2, 0.2, 0.6, 1.0 }; //環境光と拡散光の反射率をまとめて設定
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat3diff);
	glNormal3f(0.0, 1.0, 0.0); //法線方向の設定
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

};
void display1(int x, int y, int w, int h) {

	glViewport(x, y, w, h); //ビューポート変換
	setGluLookAt();

	//地面
	DrawSurface();

	// 自機が死んでいたらGame Overを表示する
	if (ship[0].Life == 1) {
        DrawMyShip();
    }
    
	if (ship[1].Life < 1) {
		// 文字列の描画
		glPushMatrix();
		GLfloat matString[] = { 0.8, 0.0, 0.2, 1.0 }; //環境光と拡散光の反射率をまとめて設定
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matString);
		glRasterPos3f(-1.0f + ship[0].x, 5.0f, 0.0f + ship[0].z);
		char *str = "Get";
		while (*str) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);
			++str;
		}
		glPopMatrix();
	}
	else {
		DrawMyShip2();
	}
	// 座標軸の描画
	DrawAxis();
	
}

void display2(int x, int y, int w, int h) {

	glViewport(x, y, w, h); //ビューポート変換
	setGluLookAt(2);

	//地面
	DrawSurface();

	// 自機が死んでいたらGame Overを表示する
    if (ship[0].Life == 1) {
        DrawMyShip();
    }
    
    if (ship[1].Life < 1) {
        // 文字列の描画
        glPushMatrix();
        GLfloat matString[] = { 0.8, 0.0, 0.2, 1.0 }; //環境光と拡散光の反射率をまとめて設定
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matString);
        glRasterPos3f(-1.0f + ship[0].x, 5.0f, 0.0f + ship[0].z);
        char *str = "Get";
        while (*str) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);
            ++str;
        }
        glPopMatrix();
    }
    else {
        DrawMyShip2();      
    }
	// 座標軸の描画
	DrawAxis();
}
void display(void)            // 描画時に呼び出される関数（Displayコールバック関数）
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // 画面クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 画面バッファクリア
	glEnable(GL_DEPTH_TEST); // 隠面消去を有効

	display1(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); //プレイヤ１の画面描画
	display2(WINDOW_WIDTH+10, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  //プレイヤ2の画面描画

	glutSwapBuffers(); // 描画実行
}

void lightInit(void)        // 光源の初期設定(まとめて関数にしているだけ)
{
	glEnable(GL_LIGHTING);  //光源の設定を有効にする
	glEnable(GL_LIGHT0);    //0番目の光源を有効にする(8個まで設定可能)
	glEnable(GL_NORMALIZE); //法線ベクトルの自動正規化を有効

	GLfloat light0pos[] = { 0.0, 10.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos); //光源0の位置を設定

	GLfloat light0ambi[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0ambi); //光源0の環境光の色を設定
	GLfloat light0diff[] = { 0.8, 0.8, 0.8, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0diff); //光源0の拡散光の色を設定
	GLfloat light0spec[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0spec); //光源0の鏡面光の色を設定

	glShadeModel(GL_SMOOTH); //スムーズシェーディングに設定
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);          // GLUT初期化

	// Windowの設定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH*2+10, WINDOW_HEIGHT);   // ウィンドウサイズの指定
	glutCreateWindow("window");     // 表示ウィンドウ作成
	glutReshapeFunc(reshape);       // Reshapeコールバック関数の指定
	glutDisplayFunc(display);       // Displayコールバック関数の指定

	glutKeyboardFunc(keyboard);     // 通常キーコールバック関数の指定(押したとき)
	glutKeyboardUpFunc(keyboardUp);     // 通常キーコールバック関数の指定(押したとき)

	glutTimerFunc(20, timer, 20);   // 定期的に呼び出される関数の指定

	//ランドの初期化
	srand(time(NULL));
	

	// 自機の構造体データを初期化
	for (int j = 0; j < SHIP_NUM; j++) {
		ship[j].x = rand()% 20;	// 自機の初期位置(X座標)
		ship[j].z = rand() % 20;	// 自機の初期位置(Z座標)
		ship[j].theta = rand() % 360;	// 自機の初期角度
		ship[j].Life = DEFAULT_LIFE;	// 自機は生きている


	}
    ship[0].y=5.0;
    ship[1].y=0;
	
	lightInit();    // 光源の初期設定(まとめて関数にしているだけ)
	glutMainLoop(); // メインループへ

	return 0;
}
