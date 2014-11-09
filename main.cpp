
#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include "imageloader.h"
#include <bits/stdc++.h>

using namespace std;

struct object{
	float x;
	float y;
	float z;

	float angle;
	float radius;
	float velocity;
};

#define PI 3.14159265

float shoulder = 0,shoulder2 = 0, elbow = 0,elbow2=0, bulb=0.0,ballAng=0.0;
float shoulder_2 = 0,shoulder2_2 = 0, elbow_2 = 0,elbow2_2=0, bulb_2=0.0;


float ground=-1.0;
float ballX=8.0, ballY=ground+0.3, ballZ=0.0;
int lampTimer=0;
bool lampRotationClock=false;
bool lampRotationAnticlock=false;

int lampTimer_2=0;
bool lampRotationClock_2=false;
bool lampRotationAnticlock_2=false;



object base={-5.0,ground+0.0,-1.0,0.0,0.6,0.0};
object rod1={-5.0,ground+0.2,-1.0,0.0,0.07,0.0};
object rod2={-5.0,ground+1.2,-1.0,0.0,0.07,0.0};
object lamp={-5.0,ground+2.2,-1.0,0.0,0.35,0.0};

object base_2={9.0,ground+0.0,0.0,0.0,0.6,0.0};
object rod1_2={9.0,ground+0.2,0.0,0.0,0.07,0.0};
object rod2_2={9.0,ground+1.2,0.0,0.0,0.07,0.0};
object lamp_2={9.0,ground+2.2,0.0,0.0,0.35,0.0};

object ball={8.0,ground+0.3,0.0,0.0,0.2,-0.01};



float myTime=0.0;
float baseX=-5.0;
float baseY=ground;
float baseZ=-1.0;
bool inAir=false;
bool rightDir=true;
bool jump=false;

float baseX_2=9.0;
float baseY_2=ground;
float baseZ_2=0.0;
bool inAir_2=false;
bool rightDir_2=true;
bool jump_2=false;

float g=-0.0005;
float vel=0.015/1.73;
float vel_2=0.015/1.73;

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width, image->height,0,GL_RGB,GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

GLuint _textureId;

void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_FLAT);
}

void initRendering() {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    	Image* image = loadBMP("download.bmp");
    	_textureId = loadTexture(image);
    	delete image;

}

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	GLfloat ambientColor[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = {0.3f, 0.3f, 0.3f, 0.5f};
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	GLfloat lightColor1[] = { 0.3f,  0.3f,  0.3f, 1.0f};
	GLfloat lightPos1[] = {-2.0f, 2.0f, 2.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	GLfloat lightColor2[] = { 0.3f,  0.3f,  0.3f, 1.0f};
	GLfloat lightPos2[] = {0.0f, 0.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

	GLfloat mat[] = {0.19225f, 0.19225f, 0.19225f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	mat[0] = 0.50754 ;
	mat[1] = 0.50754 ;
	mat[2] = 0.50754 ;

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
	mat[0] = 0.508273 ;
	mat[1] = 0.508273 ;
	mat[2] = 0.508273 ;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.4*128.0);

	glColor3f(1.0,1.0,1.0);


glPushMatrix();
glRotatef (10.0, 1.0, 0.0, 0.0);
glTranslatef (base.x,base.y, base.z);
glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

glTranslatef (0.0, 0.0, 0.0);

glPushMatrix();

glRotatef (-90.0, 1.0, 0.0, 0.0);
glColor3f(0.7,0.7,0.7);
GLUquadricObj *disk;
disk = gluNewQuadric();
gluCylinder(disk , 0.6f , 0.5f , 0.2f , 32 ,32 ) ;
glPopMatrix();
glTranslatef (0.0, 0.20, 0.0);

glPushMatrix();
glRotatef (-90.0, 1.0, 0.0, 0.0);
glColor3f(1.0,0.0,0);
disk = gluNewQuadric();
gluDisk(disk, 0, 0.5f, 32, 32);
glPopMatrix();

glPushMatrix();
glColor3f(0.0,0.0,0.0);
glutSolidSphere(0.1f,64,64) ;

glPopMatrix();

glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);

glPushMatrix();

	glRotatef (-90.0, 1.0, 0.0, 0.0);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glColor3f(1.0,1.0,1.0);
	gluCylinder(quadratic,0.07f,0.07,1.0f,32,32);
glPopMatrix();
glTranslatef (0.0, 1.0, 0.0);

glRotatef ((GLfloat) elbow2, 0.0, 0.0, 1.0);

glPushMatrix();
glColor3f(0.0,0.0,0.0);
	    glTranslatef (0.0, 0.07, 0);
	    glutSolidSphere(0.1f,64,64) ;

glPopMatrix();

glPushMatrix();

	glRotatef (-90.0, 1.0, 0.0, 0.0);
	GLUquadricObj *quadratic2;
	quadratic2 = gluNewQuadric();
	glColor3f(1,1,1);
	gluCylinder(quadratic2,0.07f,0.07,1.0f,100,100);
glPopMatrix();

glTranslatef (0.0, 1.0, 0.0);
glPushMatrix();
glColor3f(0.0,0.0,0.0);
	    glutSolidSphere(0.1f,64,64) ;
glPopMatrix();

glRotatef ((GLfloat) bulb, 0.0, 0.0, 1.0);
glRotatef ((GLfloat) shoulder2, 0.0, 1.0, 0.0);

glPushMatrix();

glRotatef (-90.0, 1.0, 0.0, 0.0);

	GLUquadricObj *quadratic3;
	quadratic3 = gluNewQuadric();
	glColor3f(0.7,0.7,0.7);
	gluCylinder(quadratic3,0.09f,0.4,0.40f,100,100);
	glTranslatef (0.0, 0.0,0.05);
	GLfloat lightColor4[] = {1.0f, 1.0f,0.0f, 1.0f};

	glMaterialfv(GL_FRONT,GL_EMISSION,lightColor4);

	glutSolidSphere(0.1f,32,32) ;

	GLfloat lightColor5[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glMaterialfv(GL_FRONT,GL_EMISSION,lightColor5);
glPopMatrix();

glPopMatrix();


//2nd Lamp


glPushMatrix();
glRotatef (10.0, 1.0, 0.0, 0.0);
glTranslatef (base_2.x,base_2.y, base_2.z);
glRotatef ((GLfloat) shoulder_2, 0.0, 0.0, 1.0);

glTranslatef (0.0, 0.0, 0.0);

glPushMatrix();
glRotatef (-90.0, 1.0, 0.0, 0.0);
glColor3f(0.7,0.7,0.7);
disk = gluNewQuadric();
gluCylinder(disk , 0.6f , 0.5f , 0.2f , 32 ,32 ) ;
glPopMatrix();

glTranslatef (0.0, 0.20, 0.0);

glPushMatrix();
glRotatef (-90.0, 1.0, 0.0, 0.0);
glColor3f(1.0,0.0,0.0);
disk = gluNewQuadric();
gluDisk(disk, 0, 0.5f, 32, 32);
glPopMatrix();

glPushMatrix();
glColor3f(0.0,0.0,0.0);
glutSolidSphere(0.1f,64,64) ;
glPopMatrix();

glRotatef ((GLfloat) elbow_2, 0.0, 0.0, 1.0);

glPushMatrix();

glRotatef (-90.0, 1.0, 0.0, 0.0);
	GLUquadricObj *quadratic_2;
	quadratic_2 = gluNewQuadric();
	glColor3f(1.0,1.0,1.0);
	gluCylinder(quadratic_2,0.07f,0.07,1.0f,32,32);
glPopMatrix();
glTranslatef (0.0, 1.0, 0.0);

glRotatef ((GLfloat) elbow2_2, 0.0, 0.0, 1.0);

glPushMatrix();
glColor3f(0.0,0.0,0.0);
	    glTranslatef (0.0, 0.07, 0);
	    glutSolidSphere(0.1f,64,64) ;

glPopMatrix();


glPushMatrix();
	glRotatef (-90.0, 1.0, 0.0, 0.0);
	GLUquadricObj *quadratic2_2;
	quadratic2_2 = gluNewQuadric();
	glColor3f(1.0,1.0,1.0);
	gluCylinder(quadratic2_2,0.07f,0.07,1.0f,100,100);
glPopMatrix();

glTranslatef (0.0, 1.0, 0.0);

glPushMatrix();
glColor3f(0.0,0.0,0.0);
glutSolidSphere(0.1f,64,64) ;
glPopMatrix();


glRotatef ((GLfloat) bulb_2, 0.0, 0.0, 1.0);
glRotatef ((GLfloat) shoulder2_2, 0.0, 1.0, 0.0);
glPushMatrix();
	glRotatef (-90.0, 1.0, 0.0, 0.0);
	GLUquadricObj *quadratic3_2;
	quadratic3_2 = gluNewQuadric();
	glColor3f(0.7,0.7,0.7);
	gluCylinder(quadratic3_2,0.09f,0.4,0.40f,100,100);
	glColor3f(1.0,1.0,0.0);
	glTranslatef (0.0, 0.0,0.05);
	glMaterialfv(GL_FRONT,GL_EMISSION,lightColor4);
	glutSolidSphere(0.1f,32,32) ;
	glMaterialfv(GL_FRONT,GL_EMISSION,lightColor5);

glPopMatrix();

glPopMatrix();

///////////////////////////////////////////////////////////////////////


glPushMatrix();
	glRotatef (10.0, 1.0, 0.0, 0.0);
	glTranslatef(ball.x,ball.y,ball.z);
	glRotatef(ballAng,0.0,0.0,1.0);
	glutSolidSphere(0.30,20,10);
glPopMatrix();

glPushMatrix();
glTranslatef(0.0,-1.0,0.0);
glRotatef (10.0, 1.0, 0.0, 0.0);
glRotatef (-90.0, 1.0, 0.0, 0.0);
glTranslatef(0.0,-2.0,0.0);

glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glColor3f(1.0,1.0,1.0);
	for(float image_x=-15;image_x<15;image_x++){
		for(float image_y=-10;image_y<10;image_y++){
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, image_y, 0.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, image_y + 1, 0.0);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x+1, image_y + 1, 0.0);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x+1, image_y, 0.0);
			glEnd();
		}

	}
glDisable(GL_TEXTURE_2D);

glColor3f(1.0,1.0,1.0);

 glEnd();
glPopMatrix();

glutSwapBuffers();
}
void reshape (int w, int h)
{

glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 2000.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef (0.0, 0.0, -5.0);

}

void baseUpDown(int id){
	if(id==1){
		jump=true;
		if(!inAir){
			inAir=true;
			vel=0.02/1.73;
		}
	}
	else {
		jump_2=true;
		if(!inAir_2){
			inAir_2=true;
			vel_2=0.02/1.73;
		}

	}
}

void baseMoveRight(int id){
	if(id==1){
		rightDir=true;
		jump=false;
		if(!inAir){
			base.velocity=0.02;
			lamp.velocity+=0.02;
			inAir=true;
			vel=0.02/1.73;
		}
	}
	else {
		rightDir_2=true;
		jump_2=false;
		if(!inAir_2){
			base_2.velocity=0.02;
			lamp_2.velocity+=0.02;
			inAir_2=true;
			vel_2=0.02/1.73;
		}

	}
}

void baseMoveLeft(int id){
	if(id==1){
		rightDir=false;
		jump=false;
		if(!inAir){
			base.velocity=-0.02;
			lamp.velocity-=0.02;
			inAir=true;
			vel=0.02/1.73;
			}
	}
	else{
		rightDir_2=false;
		jump_2=false;
		if(!inAir_2){
			base_2.velocity=-0.02;
			lamp_2.velocity-=0.02;
			inAir_2=true;
			vel_2=0.02/1.73;
		}
	}


}

void lampAntiClock(int id,float v){
	if(id==1){
		 bulb = (bulb + 5.0+v) ;
		 lamp.angle=lamp.angle-5.0-v;
	}
	else{
		  bulb_2 = (bulb_2 + 5.0+v) ;
		  lamp_2.angle=lamp_2.angle-5.0-v;
	}
}

void lampShotClock(int id,float v){
	if(id==1){
		 bulb = (bulb - 30.0-v);
		 lamp.angle=lamp.angle+30.0+v;
		 lampRotationClock=true;
	}
	else{
		bulb_2 = (bulb_2 - 30.0-v);
		lamp_2.angle=lamp_2.angle+30.0+v;
		lampRotationClock_2=true;
	}
}

void lampShotAntiClock(int id,float v){
	if(id==1){
		 bulb = (bulb + 30.0+v);
		 lamp.angle=lamp.angle-30.0-v;
		 lampRotationAnticlock=true;
	}
	else{
		bulb_2 = (bulb_2 + 30.0+v);
		lamp_2.angle=lamp_2.angle-30.0-v;
		lampRotationAnticlock_2=true;
	}
}

void lampClock(int id,float v){
	if(id==1){
		bulb = (bulb - 5.0 -v);
	    lamp.angle=lamp.angle+5.0+v;
	}
	else{
		bulb_2 = (bulb_2 - 5.0 -v);
	    lamp_2.angle=lamp_2.angle+5.0+v;
	}
}

void arm2AntiClock(int id,int v){
	if(id==1){
		elbow2 = (elbow2 + 5.0+v);
		float newAng=rod2.angle+rod1.angle-5.0-v;
		lamp.x=rod2.x+sin(newAng* PI / 180.0 );
		lamp.y=rod2.y+cos(newAng* PI / 180.0 );
		rod2.angle=rod2.angle-5.0-v;
	}
	else{
		 elbow2_2 = (elbow2_2 + 5.0+v);
		      	  float newAng_2=rod2_2.angle+rod1_2.angle-5.0-v;
		    	  lamp_2.x=rod2_2.x+sin(newAng_2* PI / 180.0 );
		    	  lamp_2.y=rod2_2.y+cos(newAng_2* PI / 180.0 );
		    	  rod2_2.angle=rod2_2.angle-5.0-v;
	}
}

void arm2Clock(int id,int v){
	if(id==1){
		  elbow2 = (elbow2 - 5.0-v);
		  float newAng=5.0+v+rod2.angle+rod1.angle;
		  lamp.x=rod2.x+sin(newAng* PI / 180.0 );
		  lamp.y=rod2.y+cos(newAng* PI / 180.0 );
		  rod2.angle=5.0+v+rod2.angle;
	}
	else{
		elbow2_2 = (elbow2_2 - 5.0-v);
		      	  float newAng_2=5.0+v+rod2_2.angle+rod1_2.angle;
		    	  lamp_2.x=rod2_2.x+sin(newAng_2* PI / 180.0 );
		    	  lamp_2.y=rod2_2.y+cos(newAng_2* PI / 180.0 );
		    	  rod2_2.angle=5.0+v+rod2_2.angle;
	}
}
void arm1AntiClock(int id,int v){
	if(id==1){
		  elbow = (elbow + 5.0+v);
		  float newAng=rod1.angle-5.0-v;
		  rod2.x=rod1.x+sin(newAng* PI / 180.0 );
		  rod2.y=rod1.y+cos(newAng* PI / 180.0 );
		  rod1.angle=newAng;

		  newAng=rod1.angle+rod2.angle;
		  lamp.x=rod2.x+sin(newAng* PI / 180.0 );
		  lamp.y=rod2.y+cos(newAng* PI / 180.0 );

	}
	else{
		 elbow_2 = (elbow_2 + 5.0+v);
		    	  float newAng_2=rod1_2.angle-5.0-v;
		    	  rod2_2.x=rod1_2.x+sin(newAng_2* PI / 180.0 );
		    	  rod2_2.y=rod1_2.y+cos(newAng_2* PI / 180.0 );
		    	  rod1_2.angle=newAng_2;

		    	  newAng_2=rod1_2.angle+rod2_2.angle;
		    	  lamp_2.x=rod2_2.x+sin(newAng_2* PI / 180.0 );
		    	  lamp_2.y=rod2_2.y+cos(newAng_2* PI / 180.0 );
	}
}
void arm1Clock(int id,int v){
	if(id==1){
		  elbow = (elbow - 5.0-v) ;
		  float newAng=5.0+v+rod1.angle;
		  rod2.x=rod1.x+sin(newAng* PI / 180.0 );
		  rod2.y=rod1.y+cos(newAng* PI / 180.0 );
		  rod1.angle=newAng;

		  newAng=rod1.angle+rod2.angle;
		  lamp.x=rod2.x+sin(newAng* PI / 180.0 );
		  lamp.y=rod2.y+cos(newAng* PI / 180.0 );
	}
	else{
		elbow_2 = (elbow_2 - 5.0-v) ;
		    	  float newAng_2=5.0+v+rod1_2.angle;
		    	  rod2_2.x=rod1_2.x+sin(newAng_2* PI / 180.0 );
		    	  rod2_2.y=rod1_2.y+cos(newAng_2* PI / 180.0 );
		    	  rod1_2.angle=newAng_2;

		    	  newAng_2=rod1_2.angle+rod2_2.angle;
		    	  lamp_2.x=rod2_2.x+sin(newAng_2* PI / 180.0 );
		    	  lamp_2.y=rod2_2.y+cos(newAng_2* PI / 180.0 );
	}
}


void keyboard(unsigned char key, int x, int y) {
    if(key==27){
        exit(0);
        }
      else if(key==122){
    	  arm1Clock(2,0);
    	  glutPostRedisplay();

          }
      else if(key==120){
    	  arm1AntiClock(2,0);
    	  glutPostRedisplay();

             }
      else if(key==99){
    	  arm2Clock(2,0);
      	  glutPostRedisplay();

            }
      else if(key==118){
        	arm2AntiClock(2,0);
      	  glutPostRedisplay();

               }
        else if(key==98){
			lampClock(2,0);
			glutPostRedisplay();

        }
		else if(key==110){
		  lampAntiClock(2,0);
		  glutPostRedisplay();

		 }

        else if (key == 115){
        	baseMoveRight(2);
        }


        else if (key == 97){
        	baseMoveLeft(2);
        }

        else if (key == 100){

        	lampShotClock(2,0);
			glutPostRedisplay();

		   }
        else if (key == 102){
        	lampShotAntiClock(2,0);
				glutPostRedisplay();
          }

        glutPostRedisplay();


}



void specialKeys( int key, int x, int y ) {

  if(key==GLUT_KEY_F1){
	  glutPostRedisplay();
    }
  else if(key==GLUT_KEY_F2){
	  glutPostRedisplay();

      }
  else if(key==GLUT_KEY_F3){
	  arm1Clock(1,0);
	  glutPostRedisplay();

      }
  else if(key==GLUT_KEY_F4){
	  arm1AntiClock(1,0);

	  glutPostRedisplay();

         }
  else if(key==GLUT_KEY_F5){

	  arm2Clock(1,0);
  	  glutPostRedisplay();

        }
    else if(key==GLUT_KEY_F6){
    	arm2AntiClock(1,0);
  	  glutPostRedisplay();

           }
    else if(key==GLUT_KEY_F7){
    		lampClock(1,0);
      	  glutPostRedisplay();

            }
        else if(key==GLUT_KEY_F8){
        	lampAntiClock(1,0);
      	  glutPostRedisplay();

               }
        else if(key==GLUT_KEY_F9){
        	baseUpDown(1);

             }
    else if (key == GLUT_KEY_RIGHT){
    	baseMoveRight(1);

    }


    else if (key == GLUT_KEY_LEFT){
    	baseMoveLeft(1);
    }

    else if (key == GLUT_KEY_UP){
    	lampShotAntiClock(1,0);
         glutPostRedisplay();
    }


    else if (key == GLUT_KEY_DOWN){
    	lampShotClock(1,0);
    	 glutPostRedisplay();
    }



  glutPostRedisplay();

}


void collision(){

	float cx=ball.x;
	float cz=ball.z;
	float cy=ball.y;
	float Ang=rod1.angle+rod2.angle+lamp.angle;
	float lampCx=lamp.x+0.2*sin(Ang* PI / 180.0 );
	float lampCy=lamp.y+0.2*cos(Ang* PI / 180.0 );

	float Ang_2=rod1_2.angle+rod2_2.angle+lamp_2.angle;
	float lampCx_2=lamp_2.x+0.2*sin(Ang_2* PI / 180.0 );
	float lampCy_2=lamp_2.y+0.2*cos(Ang_2* PI / 180.0 );

	if((cx-base.x)*(cx-base.x)+(cz-base.z)*(cz-base.z)<=(base.radius+ball.radius)*(base.radius+ball.radius)){
		ball.velocity=base.velocity-(ball.velocity*0.5);
		if(ball.x>base.x){
			ball.x=ball.x+0.02;
		}
		else{
			ball.x=ball.x-0.02;
		}

	}
	else if((cx-lampCx)*(cx-lampCx)+(cy-lampCy)*(cy-lampCy)<=(lamp.radius+ball.radius)*(lamp.radius+ball.radius)){
		ball.velocity=lamp.velocity-(ball.velocity*0.5);
		if(ball.x>lamp.x){
			ball.x=ball.x+0.02;
		}
		else{
			ball.x=ball.x-0.02;
		}

	}

	else if((cx-base_2.x)*(cx-base_2.x)+(cz-base_2.z)*(cz-base_2.z)<=(base_2.radius+ball.radius)*(base_2.radius+ball.radius)){
			ball.velocity=base_2.velocity-(ball.velocity*0.5);
			if(ball.x>base_2.x){
				ball.x=ball.x+0.02;
			}
			else{
				ball.x=ball.x-0.02;
			}

		}
		else if((cx-lampCx_2)*(cx-lampCx_2)+(cy-lampCy_2)*(cy-lampCy_2)<=(lamp_2.radius+ball.radius)*(lamp_2.radius+ball.radius)){
			ball.velocity=lamp_2.velocity-(ball.velocity*0.5);
			if(ball.x>lamp_2.x){
				ball.x=ball.x+0.02;
			}
			else{
				ball.x=ball.x-0.02;
			}

		}

	if((base.x-base_2.x)*(base.x-base_2.x)+(base.z-base_2.z)*(base.z-base_2.z)<=(base_2.radius+base.radius)*(base_2.radius+base.radius)){
		base.velocity=0;
		base_2.velocity=0;
		if(base.x<base_2.x){
			baseMoveLeft(1);
			baseMoveRight(2);
		}
		else{
			baseMoveRight(1);
			baseMoveLeft(2);
		}
	}

	if((lampCx-lampCx_2)*(lampCx-lampCx_2)+(lampCy-lampCy_2)*(lampCy-lampCy_2)<=(lamp_2.radius+lamp.radius)*(lamp_2.radius+lamp.radius)){
				cout<<"lamp lamp"<<endl;
			base.velocity=0;
			base_2.velocity=0;
			if(base.x<base_2.x){
				baseMoveLeft(1);
							baseMoveRight(2);
			}
			else{
				baseMoveRight(1);
							baseMoveLeft(2);
			}
		}


}

void script(){
		if(myTime>0.0 && myTime<0.008){
			arm1AntiClock(1,0);
			arm2Clock(1,0);
			arm2Clock(1,0);
			lampClock(1,0);
			lampClock(1,0);

			arm1Clock(2,0);
			arm2AntiClock(2,0);
			arm2AntiClock(2,0);
			lampAntiClock(2,0);
			lampAntiClock(2,0);
		}

		else if(myTime>0.01 && myTime<0.2){
			baseMoveRight(1);
		}
		if(myTime>0.0&& myTime<=2.0){
		}
		if(myTime>0.54 && myTime<1.25){
			lampClock(1,-4.8);
		}
		if(myTime>1.5 && myTime<1.530){
			lampAntiClock(1,0);
		}
		if(myTime>1.54 && myTime<1.6){
			baseMoveLeft(1);
		}
		if(myTime>1.530 && myTime<1.9){
			baseMoveLeft(2);
		}
		if(myTime>1.9&& myTime<1.92){
			lampAntiClock(2,0);
		}
		if(myTime>1.92&& myTime<1.94){
					lampClock(2,0);
				}
		if(myTime>1.94&& myTime<1.96){
					lampAntiClock(2,0);
				}
		if(myTime>1.96&& myTime<1.98){
					lampClock(2,0);
				}

		if(myTime>1.99&& myTime<2.01){
					lampAntiClock(1,-3.5);
				}
		if(myTime>2.01&& myTime<2.03){
					lampClock(1,-4.0);
				}
		if(myTime>2.03&& myTime<2.05){
					lampAntiClock(1,-3.5);
				}
		if(myTime>2.05&& myTime<2.07){
					lampClock(1,-3.5);
				}
		if(myTime>2.2 && myTime<2.216){
			arm1Clock(1,0);
			arm2AntiClock(1,0);
			arm2AntiClock(1,0);
			lampAntiClock(1,0);
			lampAntiClock(1,0);
		}
		if(myTime>2.28 && myTime<2.6){
			baseMoveLeft(1);
			cout<<base.x<<endl;
		}
		if(myTime>3.0 && myTime<3.016){
			arm1AntiClock(1,0);
			arm2Clock(1,0);
			arm2Clock(1,0);
			lampClock(1,1.5);
			lampClock(1,0);
			base.z=0.0;
			rod1.z=0.0;
			rod2.z=0.0;
			lamp.z=0.0;
			baseZ=0.0;
			ball.x=-8.0;
			ball.velocity=0.01;
		}

		if(myTime>3.1 && myTime<3.36){
			baseMoveRight(1);
		}
		if(myTime>3.2&& myTime<3.62){
			baseUpDown(2);
		}

		if(myTime>3.2&& myTime<3.24){
					lampAntiClock(2,-3);
				}
		if(myTime>3.24&& myTime<3.28){
					lampClock(2,-3);
				}
		if(myTime>3.28&& myTime<3.32){
					lampAntiClock(2,-3);
				}
		if(myTime>3.32&& myTime<3.36){
					lampClock(2,-3);
				}
		if(myTime>3.36&& myTime<3.4){
					lampAntiClock(2,-3);
				}
		if(myTime>3.4&& myTime<3.44){
					lampClock(2,-3);
				}
		if(myTime>3.44&& myTime<3.48){
					lampAntiClock(2,-3);
				}
		if(myTime>3.48&& myTime<3.52){
					lampClock(2,-3);
				}
		if(myTime>3.8 && myTime<3.9){
					baseMoveRight(2);
				}
		if(myTime>3.85 && myTime<3.92){
				arm1Clock(1,-4);
		}
		if(myTime>3.91 && myTime<3.92){
				arm2Clock(1,-4);
		}

		if(myTime>3.9 && myTime<3.93){
			lampClock(1,-4.5);
		}
		if(myTime>3.94 && myTime<3.941){
			lampShotAntiClock(1,0);
		}
		if(myTime>3.95 && myTime<4.02){
				arm1AntiClock(1,-4);
			}
		if(myTime>3.95 && myTime<3.96){
				arm2AntiClock(1,-4);
		}




		if(myTime>3.93 && myTime<4.0){
						arm1AntiClock(2,-4);
					}
				if(myTime>3.98 && myTime<3.99){
						arm2AntiClock(2,-4);
				}

				if(myTime>3.97 && myTime<4.0){
					lampAntiClock(2,-4.5);
				}
				if(myTime>4.1650 && myTime<4.166){
					lampShotClock(2,0);
				}
				if(myTime>4.26 && myTime<4.33){
								arm1Clock(2,-4);
							}
				if(myTime>4.26 && myTime<4.27){
						arm2Clock(2,-4);
				}



}

void update(int value) {
	if(lampRotationClock){
		lampTimer++;
		lamp.velocity=base.velocity-0.02;
	}
	if(lampRotationAnticlock){
			lampTimer++;
			lamp.velocity=base.velocity+0.02;
		}
	if(lampTimer>5.0){
		lampRotationClock=false;
		lampRotationAnticlock=false;
		lampTimer=0;
		lamp.velocity=base.velocity;
	}

	if(lampRotationClock_2){
		lampTimer_2++;
		lamp_2.velocity=base_2.velocity-0.02;
	}
	if(lampRotationAnticlock_2){
			lampTimer_2++;
			lamp_2.velocity=base_2.velocity+0.02;
		}
	if(lampTimer_2>5.0){
		lampRotationClock_2=false;
		lampRotationAnticlock_2=false;
		lampTimer_2=0;
		lamp_2.velocity=base_2.velocity;
	}
	ball.x+=ball.velocity;
	if(inAir){
			float incrementX;
			if(rightDir){
				incrementX=0.02;
			}
			else{
				incrementX=-0.02;
			}
			if(jump){
				incrementX=0.0;
			}

			vel+=g;
			base.x+=base.velocity;
			rod1.x+=base.velocity;
			rod2.x+=base.velocity;
			lamp.x+=base.velocity;

			base.y+=vel;
			rod1.y+=vel;
			rod2.y+=vel;
			lamp.y+=vel;

			if(base.y<ground){
				vel=-vel;
				lamp.velocity-=base.velocity;
				base.velocity=0.0;
				inAir=false;
			}
		}
	if(inAir_2){
				float incrementX_2;
				if(rightDir_2){
					incrementX_2=0.02;
				}
				else{
					incrementX_2=-0.02;
				}
				if(jump_2){
					incrementX_2=0.0;
				}
				vel_2+=g;

				base_2.x+=base_2.velocity;
				rod1_2.x+=base_2.velocity;
				rod2_2.x+=base_2.velocity;
				lamp_2.x+=base_2.velocity;

				base_2.y+=vel_2;
				rod1_2.y+=vel_2;
				rod2_2.y+=vel_2;
				lamp_2.y+=vel_2;

				if(base_2.y<ground){
					vel_2=-vel_2;
					lamp_2.velocity-=base_2.velocity;
					base_2.velocity=0.0;

					inAir_2=false;
				}
			}
	collision();
	myTime+=0.001;
	script();

	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
//glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
initRendering();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutSpecialFunc(specialKeys);
glutTimerFunc(2, update, 0)	;
cout<<rod1.x<<" "<<rod1.y<<" "<<rod1.z<<" "<<rod1.angle<<endl;
glutMainLoop();
return 0;
}
