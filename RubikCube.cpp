/****************************************************************************
*																			*
*				Projeto Final de Manuel Madeira Amado						*
*					2006131202 - 20/06/2017									*
*																			*
*							TO DO LIST										*
*													OG	ALM	DONE			*
*		OBJECTIVOS: 	Transformações Push e Pop 	[X]	[X]	[X]				*
*						Projecções					[X]	[X]	[X]				*
*						Texturas					[X]	[X]	[X]				*
*						Viewport					[X]	[X]	[X]				*
*						Modelos de cor				[X]	[X]	[X]				*
*						Iluminação Foco				[X]	[X]	[X]				*
*						Iluninação Ambiente			[X]	[X]	[X]				*
*						Transparência				[X]	[X]	[X]				*
*						Reflexões					[X]	[X]	[X]				*
*						Extras(Deteção de colisão)	[X]	[X]	[X]				*
*						Sombras fora do baralho- não consigo fazer Resultar	*
*																			*
*	Baseado em código dos professores de Computação Gráfica					*
*	Departamento de Engenharia Informática - Universidade de Coimbra		*
*																			*
****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "materiais.h"
#include "RgbImage.h"


//==================================================================== Definir cores
#define AZUL     0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO  1.0, 1.0, 0.0, 1.0
#define VERDE    0.0, 1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY1    0.2, 0.2, 0.2, 1.0
#define GRAY2    0.93, 0.93, 0.93, 1.0
#define PI	3.14159

//=========================================================== Variáveis Globais

GLfloat passoDemo = 0;
GLfloat rotacaoB = 600;
GLint active = 0;
GLfloat demoCamera[] = {25,25,25};
GLfloat demoAng = 0.0001;
GLfloat demoFocoVisao[] = {0,0,0};
GLint volta = 0;
GLint demoEndX = 0;
GLint demoEndY = 0;
GLint demoEndZ = 0;


GLfloat posNave = 0; //posição da nave do Galaxian
GLfloat posAlien = 0;	//posição dos Aliens do Galaxian
GLfloat temp = 0;
GLint flag = 0;
GLint contador = 0;
GLint i,j;

GLfloat intensidadeCor[4]={ 1, 1, 1, 1};
GLfloat direccao[] = { -1, -1, -1 };

//LUZES
GLint luz1 = 0;
GLint luz2 = 0;
GLint luz3 = 0;
GLint luz4 = 0;
GLint luz5 = 0;

//BlocoA
GLfloat aRX = 0;
GLfloat aRY = 0;
GLfloat aRZ = 0;


//--------------------------------------------------------- Sistema Coordenadas
GLfloat  xC=16.0, yC=20.0, zC=15.0;
GLint    wScreen=600, hScreen=500;
char     texto[30];

//------------------------------------------------------------ Observador
GLfloat  rVisao=3.0, aVisao=PI-0.8, incVisao=0.1;
GLfloat  obsPini[] ={17, 5, xC+1};
GLfloat  obsPfin[] ={obsPini[0]+rVisao*cos(aVisao), 5, obsPini[2]-rVisao*sin(aVisao)};

//---------------------------------------------------------- Texturas e Rotacao
GLfloat   quadS   = 4.0;
GLfloat   quadP[] = {-2, 0, -8};
GLfloat  incBule = 1; //variáveis para a rotação dos cubos
GLfloat  angBule = 0;
GLint    repete=1;
GLfloat    rr=1;
GLint    maxR  =20;
GLint    numQuadro =5;
GLint    msec=10;		//.. definicao do timer (actualizacao)
GLuint  texture[10];
GLuint  tex;
RgbImage imag;

//------------------------------------------------------------------- Nevoeiro
GLfloat nevoeiroCor[] = {0.0, 0.0, 0.0, 1.0}; //definicao da cor do nevoeiro

//------------------------------------------------------------ Iluminacao
//---luz ambiente----------------------------------------------------------
GLint   noite=0;
GLfloat luzGlobalCor[4]={0.3,0.3,0.3,1.0};   //
//---luz ambiente (LOCAL)--------------------------------------------------
GLint   ligaLuz=1;
GLfloat localCor[4] ={0.1,0.1,0.1,1.0};
GLfloat localCorDif[4] ={ 1, 1, 1, 1.0};
GLfloat localPos[4] ={10.0, 20.0, 10.0, 1.0};
GLfloat localAttCon =1.0;
GLfloat localAttLin =0.05;
GLfloat localAttQua =0.0;
//---lanterna (LOCAL)--------------------------------------------------
GLint   ligaFoco  = 0;
GLfloat rFoco=1.1, aFoco=(PI/2)-0.8;
GLfloat incH =0.0, incV=0.0;
GLfloat incMaxH =0.5, incMaxV=0.35;
GLfloat focoPini[]= { obsPini[0], obsPini[1], obsPini[2], 1.0 };
GLfloat focoPfin[]={ obsPini[0]-rFoco*cos(aFoco), obsPini[1], obsPini[2]-rFoco*sin(aFoco), 1.0};
GLfloat focoDir[] = { focoPfin[0]-focoPini[0], 0, focoPfin[2]-focoPini[2]};
GLfloat focoExp   = 10.0;
GLfloat focoCut   = 15.0;
GLfloat focoCorEsp[4] ={ 1.0 ,  1.0, 1.0, 1.0};
GLfloat focoCorDif[4] ={ 0.85, 0.85,0.85, 1.0};
//---luz da terra - direcional---------------------------------------------
GLfloat lightColorTerra[] = {0.2f, 0.4f, 1.0f, 1.0f};
GLfloat lightPosTerra[] = {10.0f, 0.0f, 0.0f, 0.0f};
//---luz da estrela - direcional-------------------------------------------
GLfloat lightColorEstrela[] = {1.0f, 0.9f, 0.9f, 1.0f};
GLfloat lightPosEstrela[] = {-1.0f, 0.2f, -0.2f, 0.0f};
//---luz projetor 1 - foco----------------------------------------------
GLfloat concentracao1 = 10.0;
GLfloat angulo1 = 150.0;
GLfloat lightColorProj1[] = { 1.0f, 1.0f,1.0f, 1.0f};
GLfloat lightPosProj1[] = {0.0f, 20.0f, 20.0f, 1.0f};
GLfloat focoDirProj1[] = { -1.0f, 1.0f, -1.0f};
GLfloat focoCorEspProj1[4] ={ 1.0 ,  1.0, 1.0, 1.0};
GLfloat focoCorDifProj1[4] ={ 0.85, 0.85,0.85, 1.0};
//---luz projetor 2 - foco----------------------------------------------
GLfloat concentracao2 = 10.0;
GLfloat angulo2 = 150.0;
GLfloat lightColorProj2[] = { 1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPosProj2[] = {20.0f, 20.0f, 0.0f, 1.0f};
GLfloat focoDirProj2[] = { 1.0f, -1.0f, -1.0f};
GLfloat focoCorEspProj2[4] ={ 1.0 ,  1.0, 1.0, 1.0};
GLfloat focoCorDifProj2[4] ={ 0.85, 0.85,0.85, 1.0};



//Nevoeiro
GLint linear=1;

GLfloat x = 0;
GLfloat y = 0;

GLfloat width = 20;
GLfloat height = 20;

GLint dim = 64;


/********************************************************
*					DEFINIÇÃO DE TEXTURAS				*
*														*
********************************************************/
void criaDefineTexturas(){

	//----------------------------------------- UP - estrela
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("cwd_up.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- DWN
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("cwd_rt.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- espaço
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("cwd_lf.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- terra
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("cwd_ft.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- espaço
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("cwd_dn.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- espaço
	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("cwd_bk.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}


void initLights(void){
	//Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, 		luzGlobalCor);
	//Tecto
	glLightfv(GL_LIGHT0, GL_POSITION,				localPos );
	glLightfv(GL_LIGHT0, GL_AMBIENT,				localCor );
	glLightfv(GL_LIGHT0, GL_DIFFUSE,				localCorDif );
	glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION,	localAttCon);
	glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, 	localAttLin) ;
	glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,	localAttQua) ;
	//Foco
	glLightfv(GL_LIGHT1, GL_POSITION,      		focoPini );
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,		focoDir );
	glLightf (GL_LIGHT1, GL_SPOT_EXPONENT ,		focoExp);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,   		focoCut);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,       		focoCorDif );
	glLightfv(GL_LIGHT1, GL_SPECULAR,      		focoCorEsp  );
	//---luz da terra - direcional---------------------------------------------
    glLightfv(GL_LIGHT3, GL_DIFFUSE, 			lightColorTerra);
    glLightfv(GL_LIGHT3, GL_POSITION, 			lightPosTerra);
    //---luz da estrela - direcional-------------------------------------------
    glLightfv(GL_LIGHT4, GL_DIFFUSE, 			lightColorEstrela);
    glLightfv(GL_LIGHT4, GL_POSITION,			lightPosEstrela);
	//---luz projetor 1 - foco----------------------------------------------
 	glLightfv(GL_LIGHT2, GL_POSITION,			lightPosProj1);
 	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,		focoDirProj1);
    glLightf (GL_LIGHT2, GL_SPOT_EXPONENT ,		concentracao1);
    glLightf (GL_LIGHT2, GL_SPOT_CUTOFF,		angulo1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,			focoCorDifProj1);
	glLightfv(GL_LIGHT2, GL_SPECULAR,			focoCorEspProj1);
    //---luz projetor 2 - foco----------------------------------------------
 	glLightfv(GL_LIGHT5, GL_POSITION,			lightPosProj2);
 	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION,		focoDirProj2);
    glLightf (GL_LIGHT5, GL_SPOT_EXPONENT ,		concentracao2);
    glLightf (GL_LIGHT5, GL_SPOT_CUTOFF,		angulo2);
    glLightfv(GL_LIGHT5, GL_DIFFUSE,			focoCorDifProj2);
	glLightfv(GL_LIGHT5, GL_SPECULAR,			focoCorEspProj2);
}

void initMaterials(int material)
{
	switch (material){
		case 0: //esmerald
			glMaterialfv(GL_FRONT,GL_AMBIENT,  esmeraldAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  esmeraldDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, esmeraldSpec);
			glMateriali (GL_FRONT,GL_SHININESS,esmeraldCoef);
			break;
		case 1: //jade
			glMaterialfv(GL_FRONT,GL_AMBIENT,  jadeAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  jadeDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, jadeSpec);
			glMateriali (GL_FRONT,GL_SHININESS,jadeCoef);
			break;
	       case 2: //obsidian
			glMaterialfv(GL_FRONT,GL_AMBIENT,  obsidianAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  obsidianDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, obsidianSpec);
			glMateriali (GL_FRONT,GL_SHININESS,obsidianCoef);
			break;
		case 3: //pearl
			glMaterialfv(GL_FRONT,GL_AMBIENT,  pearlAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  pearlDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, pearlSpec);
			glMateriali (GL_FRONT,GL_SHININESS,pearlCoef);
			break;
		case 4: //ruby
			glMaterialfv(GL_FRONT,GL_AMBIENT,  rubyAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  rubyDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, rubySpec);
			glMateriali (GL_FRONT,GL_SHININESS,rubyCoef);
			break;
	         case 5: //turquoise
			glMaterialfv(GL_FRONT,GL_AMBIENT,  turquoiseAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  turquoiseDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, turquoiseSpec);
			glMateriali (GL_FRONT,GL_SHININESS,turquoiseCoef);
			break;
		case 6: //brass
			glMaterialfv(GL_FRONT,GL_AMBIENT,  brassAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  brassDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, brassSpec);
			glMateriali (GL_FRONT,GL_SHININESS,brassCoef);
			break;
		case 7: //bronze
			glMaterialfv(GL_FRONT,GL_AMBIENT,  bronzeAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  bronzeDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, bronzeSpec);
			glMateriali (GL_FRONT,GL_SHININESS,bronzeCoef);
			break;
		case 8: //chrome
			glMaterialfv(GL_FRONT,GL_AMBIENT,  chromeAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  chromeDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, chromeSpec);
			glMateriali (GL_FRONT,GL_SHININESS,chromeCoef);
			break;
	         case 9: //copper
			glMaterialfv(GL_FRONT,GL_AMBIENT,  copperAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  copperDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, copperSpec);
			glMateriali (GL_FRONT,GL_SHININESS,copperCoef);
			break;
	         case 10: //gold
			glMaterialfv(GL_FRONT,GL_AMBIENT,  goldAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  goldDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, goldSpec);
			glMateriali (GL_FRONT,GL_SHININESS,goldCoef);
			break;
		case 11: //silver
			glMaterialfv(GL_FRONT,GL_AMBIENT,  silverAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  silverDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, silverSpec);
			glMateriali (GL_FRONT,GL_SHININESS,silverCoef);
			break;
		case 12: //blackPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  blackPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, blackPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,blackPlasticCoef);
			break;
		case 13: //cyankPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, cyanPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,cyanPlasticCoef);
			break;
		case 14: //greenPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  greenPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, greenPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,greenPlasticCoef);
			break;
		case 15: //redPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  redPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  redPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, redPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,redPlasticCoef);
			break;
	        case 16: //yellowPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  whitePlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  whitePlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, whitePlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,whitePlasticCoef);
			break;
		case 17: //yellowPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, yellowPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,yellowPlasticCoef);
			break;
	        case 18: //blackRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  blackRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, blackRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,blackRubberCoef);
			break;
		case 19: //cyanRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, cyanRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,cyanRubberCoef);
			break;
		case 20: //greenRubber

			glMaterialfv(GL_FRONT,GL_AMBIENT,  greenRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, greenRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,greenRubberCoef);
			break;
		case 21: //redRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  redRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  redRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, redRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,redRubberCoef);
			break;
		case 22: //redRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  whiteRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  whiteRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, whiteRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,whiteRubberCoef);
			break;
		case 23: //redRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, yellowRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,yellowRubberCoef);
			break;
	}


}


//--------------------- NOVO - Definicoes do nevoeiro
void initNevoeiro(void){
	glFogfv(GL_FOG_COLOR, nevoeiroCor); //Cor do nevoeiro
	glFogi(GL_FOG_MODE, GL_LINEAR); //Equacao do nevoeiro - linear
	glFogf(GL_FOG_START, 45.0); // Distancia a que tera' inicio o nevoeiro
	glFogf(GL_FOG_END, 75.0); // Distancia a que o nevoeiro terminara'
	glFogf (GL_FOG_DENSITY, 0.1); //Densidade do nevoeiro - nao se especifica quando temos "nevoeiro linear"


}
void init(void)
{
	glClearColor(WHITE);
	glShadeModel(GL_SMOOTH);

	criaDefineTexturas();
	glEnable(GL_TEXTURE_2D);

	//Activa o nevoeiro - Não combina bem
	//glEnable(GL_FOG);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

	initMaterials(1);
	initLights();
	//initNevoeiro();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
}


//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
	glRasterPos3f(x,y,z);
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}



/********************************************************
*				DESENHA A SKYBOX ESPACIAL				*
*						-50 50							*
********************************************************/
void desenhaMundo(){

	glPushMatrix();
		glTranslatef( -50, -50, -50);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[1]);
			glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f); glVertex3i( 0, 0, 0);
				glTexCoord2f(1.0f,0.0f); glVertex3i( 100, 0, 0);
				glTexCoord2f(1.0f,1.0f); glVertex3i( 100, 100, 0);
				glTexCoord2f(0.0f,1.0f); glVertex3i( 0, 100, 0);
			glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[2]);
			glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f); glVertex3i( 0, 0, 100);
				glTexCoord2f(1.0f,0.0f); glVertex3i( 100, 0, 100);
				glTexCoord2f(1.0f,1.0f); glVertex3i( 100, 100, 100);
				glTexCoord2f(0.0f,1.0f); glVertex3i( 0, 100, 100);
			glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[3]);
			glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f); glVertex3i( 0, 0, 0);
				glTexCoord2f(1.0f,0.0f); glVertex3i( 0, 0, 100);
				glTexCoord2f(1.0f,1.0f); glVertex3i( 0, 100, 100);
				glTexCoord2f(0.0f,1.0f); glVertex3i( 0, 100, 0);
			glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
			glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f); glVertex3i( 100, 0, 0);
				glTexCoord2f(1.0f,0.0f); glVertex3i( 100, 100, 0);
				glTexCoord2f(1.0f,1.0f); glVertex3i( 100, 100, 100);
				glTexCoord2f(0.0f,1.0f); glVertex3i( 100, 0, 100);
			glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[4]);
			glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f); glVertex3i( 0, 0, 0);
				glTexCoord2f(1.0f,0.0f); glVertex3i( 100, 0, 0);
				glTexCoord2f(1.0f,1.0f); glVertex3i( 100, 0, 100);
				glTexCoord2f(0.0f,1.0f); glVertex3i( 0, 0, 100);
			glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[5]);
			glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f); glVertex3i( 0, 100, 0);
				glTexCoord2f(1.0f,0.0f); glVertex3i( 0, 100, 100);
				glTexCoord2f(1.0f,1.0f); glVertex3i( 100, 100, 100);
				glTexCoord2f(0.0f,1.0f); glVertex3i( 100, 100, 0);
			glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

/********************************************************
*					PRIMITIVA CUBO						*
*	RECEBE A RELOCALIZAÇÃO DOS PONTOS E DESENHA 1 CUBO	*
********************************************************/
void desenhaCubo(GLfloat a,GLfloat b,GLfloat c, GLint rfl){

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Cubo

switch (rfl){
		case 0:
 		//face de baixo
		glBegin(GL_POLYGON);
			glColor4f(WHITE);
			glNormal3f(0,0,-1);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face de cima
		glBegin(GL_POLYGON);
			glColor4f(AMARELO);
			glNormal3f(0,0,1);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
		glEnd();

		//face esquerda
		glBegin(GL_POLYGON);
			glColor4f(AZUL);
			glNormal3f(-1,0,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face direita
		glBegin(GL_POLYGON);
			glColor4f(VERDE);
			glNormal3f(1,0,0);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();

		//face de trás
		glBegin(GL_POLYGON);
			glColor4f(VERMELHO);
			glNormal3f(0,-1,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 1+c);
		glEnd();
		//face da frente
		glBegin(GL_POLYGON);
			glColor4f(LARANJA);
			glNormal3f(0,1,0);
			glVertex3i( 1+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();
		break;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Espelho Baixo Cubo
		case 1:
 		//face de baixo
		glBegin(GL_POLYGON);
			glColor4f(WHITE);
			glNormal3f(0,0,-1);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face de cima
		glBegin(GL_POLYGON);
			glColor4f(AMARELO);
			glNormal3f(0,0,1);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
		glEnd();

		//face esquerda
		glBegin(GL_POLYGON);
			glColor4f(AZUL);
			glNormal3f(-1,0,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face direita
		glBegin(GL_POLYGON);
			glColor4f(VERDE);
			glNormal3f(1,0,0);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();

		//face de trás
		glBegin(GL_POLYGON);
			glColor4f(LARANJA);
			glNormal3f(0,-1,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 1+c);
		glEnd();
		//face da frente
		glBegin(GL_POLYGON);
			glColor4f(VERMELHO);
			glNormal3f(0,1,0);
			glVertex3i( 1+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();
		break;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Espelho Parede Cubo
		case 2:
 		//face de baixo
		glBegin(GL_POLYGON);
			glColor4f(AMARELO);
			glNormal3f(0,0,-1);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face de cima
		glBegin(GL_POLYGON);
			glColor4f(WHITE);
			glNormal3f(0,0,1);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
		glEnd();

		//face esquerda
		glBegin(GL_POLYGON);
			glColor4f(AZUL);
			glNormal3f(-1,0,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face direita
		glBegin(GL_POLYGON);
			glColor4f(VERDE);
			glNormal3f(1,0,0);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();

		//face de trás
		glBegin(GL_POLYGON);
			glColor4f(VERMELHO);
			glNormal3f(0,-1,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 1+c);
		glEnd();
		//face da frente
		glBegin(GL_POLYGON);
			glColor4f(LARANJA);
			glNormal3f(0,1,0);
			glVertex3i( 1+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();
		break;
		case 3:
 		//face de baixo
		glBegin(GL_POLYGON);
			glColor4f(WHITE);
			glNormal3f(0,0,-1);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face de cima
		glBegin(GL_POLYGON);
			glColor4f(AMARELO);
			glNormal3f(0,0,1);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
		glEnd();

		//face esquerda
		glBegin(GL_POLYGON);
			glColor4f(VERDE);
			glNormal3f(-1,0,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		//face direita
		glBegin(GL_POLYGON);
			glColor4f(AZUL);
			glNormal3f(1,0,0);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();

		//face de trás
		glBegin(GL_POLYGON);
			glColor4f(LARANJA);
			glNormal3f(0,-1,0);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 1+c);
		glEnd();
		//face da frente
		glBegin(GL_POLYGON);
			glColor4f(VERMELHO);
			glNormal3f(0,1,0);
			glVertex3i( 1+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();

	}
}

/********************************************************
*				PRIMITIVA GRELHA CUBO					*
*	RECEBE A RELOCALIZAÇÃO DOS PONTOS E DESENHA 1 CUBO	*
********************************************************/
void desenhaGrelha(GLfloat a,GLfloat b,GLfloat c){

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Grelha do Cubo

	glColor4f(BLACK);
		glBegin(GL_LINES);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		glBegin(GL_LINES);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
		glEnd();
		glBegin(GL_LINES);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 1+a, 1+b, 2+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 1+a, 2+b, 1+c);
		glEnd();
		glBegin(GL_LINES);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 2+b, 1+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 1+b, 2+c);
		glEnd();
		glBegin(GL_LINES);
			glVertex3i( 1+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 1+c);
			glVertex3i( 2+a, 1+b, 2+c);
			glVertex3i( 1+a, 1+b, 2+c);
		glEnd();
		glBegin(GL_LINES);
			glVertex3i( 1+a, 2+b, 1+c);
			glVertex3i( 1+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 2+c);
			glVertex3i( 2+a, 2+b, 1+c);
		glEnd();
}

/********************************************************
*			DESENHA O CUBO DE RUBIK						*
*	RECEBE:	TIX - translação inicial x					*
*			TIY - translação inicial y					*
*			TIZ - translação inicial z					*
*			TFX - translação final x					*
*			TFY - translação final y					*
*			TFZ - translação final z					*
*			ERX - eixo de rotação x (0v1)				*
*			ERY - eixo de rotação y (0v1)				*
*			ERZ - eixo de rotação z (0v1)				*
*			ASU - angulo para somar (espelhos)			*
*			SLO - solo (espelho)						*
********************************************************/
void desenhaCuboRubik(GLfloat tix,GLfloat tiy,GLfloat tiz, GLfloat tfx,GLfloat tfy,GLfloat tfz, GLfloat erx,GLfloat ery,GLfloat erz, GLfloat asu, GLfloat slo){

	//---CUBO---
	glPushMatrix();
		glTranslatef( tfx, tfy, tfz);
		glRotatef (angBule+asu, erx, ery, erz);
		glTranslatef( tix, tiy, tiz);
		if(passoDemo > 40){
			glPushMatrix();
				if(passoDemo <  rotacaoB){
					glTranslatef( 2.5, 2.5, 2.5);
					glRotatef (angBule, 0, 0, 1);
					glTranslatef( -2.5, -2.5,- 2.5);
				}
					desenhaCubo(0,0,0,slo); //canto 1

				desenhaGrelha(0,0,0);
			glPopMatrix();
		}
		if(passoDemo > 320){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(1,0,0,slo);
			desenhaGrelha(1,0,0);
		glPopMatrix();
		}
		if(passoDemo > 60){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(2,0,0,slo);  //canto 2
			desenhaGrelha(2,0,0);
		glPopMatrix();
		}
		if(passoDemo > 340){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(0,1,0, slo);
			desenhaGrelha(0,1,0);
		glPopMatrix();
		}
		if(passoDemo > 220){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(1,1,0, slo); //baixo
			desenhaGrelha(1,1,0);
		glPopMatrix();
		}
		if(passoDemo > 360){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(2,1,0,slo);
			desenhaGrelha(2,1,0);
		glPopMatrix();
		}
		if(passoDemo > 80){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(0,2,0,slo);  //Canto 3
			desenhaGrelha(0,2,0);
		glPopMatrix();
		}
		if(passoDemo > 380){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(1,2,0,slo);
			desenhaGrelha(1,2,0);
		glPopMatrix();
		}
		if(passoDemo > 100){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
			desenhaCubo(2,2,0,slo);  //canto 4
			desenhaGrelha(2,2,0);
		glPopMatrix();
		}

		if(passoDemo > 400){
			desenhaCubo(0,0,1,slo);
			desenhaGrelha(0,0,1);
		}
		if(passoDemo > 300){
			desenhaCubo(1,0,1,slo);
			desenhaGrelha(1,0,1);
		}
		if(passoDemo > 420){
			desenhaCubo(2,0,1,slo);
			desenhaGrelha(2,0,1);
		}
		if(passoDemo > 240){
			desenhaCubo(0,1,1,slo); //esquerda
			desenhaGrelha(0,1,1);
		}
		if(passoDemo > 20){
			desenhaCubo(1,1,1,slo); //centro
			desenhaGrelha(1,1,1);
		}
		if(passoDemo > 260){
			desenhaCubo(2,1,1,slo); //direita
			desenhaGrelha(2,1,1);
		}
		if(passoDemo > 460){
			desenhaCubo(0,2,1,slo);
			desenhaGrelha(0,2,1);
		}
		if(passoDemo > 280){
			desenhaCubo(1,2,1,slo);
			desenhaGrelha(1,2,1);
		}
		if(passoDemo > 480){
			desenhaCubo(2,2,1,slo);
			desenhaGrelha(2,2,1);
		}


		if(passoDemo > 120){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(0,0,2,slo);  // canto 5
		desenhaGrelha(0,0,2);
		glPopMatrix();
		}
		if(passoDemo > 500){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(1,0,2,slo);
		desenhaGrelha(1,0,2);
		glPopMatrix();
		}
		if(passoDemo > 140){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(2,0,2,slo); // canto
		desenhaGrelha(2,0,2);
		glPopMatrix();
		}
		if(passoDemo > 520){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(0,1,2,slo);
		desenhaGrelha(0,1,2);
		glPopMatrix();
		}
		if(passoDemo > 200){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(1,1,2,slo); //cima
		desenhaGrelha(1,1,2);
		glPopMatrix();
		}
		if(passoDemo > 540){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(2,1,2,slo);
		desenhaGrelha(2,1,2);
		glPopMatrix();
		}
		if(passoDemo > 160){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(0,2,2,slo); //canto7
		desenhaGrelha(0,2,2);
		glPopMatrix();
		}
		if(passoDemo > 560){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(1,2,2,slo);
		desenhaGrelha(1,2,2);
		glPopMatrix();
		}
		if(passoDemo > 180){
		glPushMatrix();
			if(passoDemo <  rotacaoB){
				glTranslatef( 2.5, 2.5, 2.5);
				glRotatef (-angBule, 0, 0, 1);
				glTranslatef( -2.5, -2.5,- 2.5);
			}
		desenhaCubo(2,2,2,slo);  // Canto 6
		desenhaGrelha(2,2,2);
		glPopMatrix();
		}

	glPopMatrix();
}


/********************************************************
*		DESENHA A NAVE JÁ POSICIONADA E COM				*
*					MOVIMENTO DEFINIDO					*
********************************************************/
void desenhaNave(GLfloat a,GLfloat b,GLfloat c){

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Nave
	glPushMatrix();
	glTranslatef( 0, -40, -49);
	glRotatef (180, 0, 0, 1);
	//glTranslatef( -2.5, -2.5, -2.5);
	glScaled(0.3,0.3,0.3);
	glColor4f(AMARELO);
		//----Bico------
		glBegin(GL_POLYGON);
			glVertex3i( 7+a, 0+b, 0+c);
			glVertex3i( 8+a, 0+b, 0+c);
			glVertex3i( 8+a, 1+b, 0+c);
			glVertex3i( 7+a, 1+b, 0+c);
		glEnd();
		//---Balázio---------
		if(contador == 0){
		glBegin(GL_POLYGON);
			glVertex3i( 7+a, 0, 0+c);
			glVertex3i( 8+a, 0, 0+c);
			glVertex3i( 8+a, 1, 0+c);
			glVertex3i( 7+a, 1, 0+c);
		glEnd();
		temp = a;
		}else{
		glBegin(GL_POLYGON);
			glVertex3i( 7+temp, 0-contador, 0+c);
			glVertex3i( 8+temp, 0-contador, 0+c);
			glVertex3i( 8+temp, 1-contador, 0+c);
			glVertex3i( 7+temp, 1-contador, 0+c);
		glEnd();
		}

		glBegin(GL_POLYGON);
			glVertex3i( 7+a, 1+b, 0+c);
			glVertex3i( 8+a, 1+b, 0+c);
			glVertex3i( 8+a, 2+b, 0+c);
			glVertex3i( 7+a, 2+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 7+a, 2+b, 0+c);
			glVertex3i( 8+a, 2+b, 0+c);
			glVertex3i( 8+a, 3+b, 0+c);
			glVertex3i( 7+a, 3+b, 0+c);
		glEnd();

		//-----Corpo-------
		glColor4f(VERMELHO);
		glBegin(GL_POLYGON);
			glVertex3i( 6+a, 3+b, 0+c);
			glVertex3i( 9+a, 3+b, 0+c);
			glVertex3i( 9+a, 4+b, 0+c);
			glVertex3i( 6+a, 4+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 5+a, 4+b, 0+c);
			glVertex3i( 10+a, 4+b, 0+c);
			glVertex3i( 10+a, 5+b, 0+c);
			glVertex3i( 5+a, 5+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 4+a, 5+b, 0+c);
			glVertex3i( 11+a, 5+b, 0+c);
			glVertex3i( 11+a, 7+b, 0+c);
			glVertex3i( 4+a, 7+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 4+a, 7+b, 0+c);
			glVertex3i( 5+a, 7+b, 0+c);
			glVertex3i( 5+a, 8+b, 0+c);
			glVertex3i( 4+a, 8+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 10+a, 7+b, 0+c);
			glVertex3i( 11+a, 7+b, 0+c);
			glVertex3i( 11+a, 8+b, 0+c);
			glVertex3i( 10+a, 8+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 7+a, 7+b, 0+c);
			glVertex3i( 8+a, 7+b, 0+c);
			glVertex3i( 8+a, 15+b, 0+c);
			glVertex3i( 7+a, 15+b, 0+c);
		glEnd();

		//-----Estrutura-------
		glColor4f(AZUL);
		glBegin(GL_POLYGON);
			glVertex3i( 6+a, 8+b, 0+c);
			glVertex3i( 7+a, 8+b, 0+c);
			glVertex3i( 7+a, 17+b, 0+c);
			glVertex3i( 6+a, 17+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 5+a, 11+b, 0+c);
			glVertex3i( 6+a, 11+b, 0+c);
			glVertex3i( 6+a, 14+b, 0+c);
			glVertex3i( 5+a, 14+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 4+a, 12+b, 0+c);
			glVertex3i( 5+a, 12+b, 0+c);
			glVertex3i( 5+a, 15+b, 0+c);
			glVertex3i( 4+a, 15+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 3+a, 13+b, 0+c);
			glVertex3i( 4+a, 13+b, 0+c);
			glVertex3i( 4+a, 14+b, 0+c);
			glVertex3i( 3+a, 14+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 2+a, 11+b, 0+c);
			glVertex3i( 3+a, 11+b, 0+c);
			glVertex3i( 3+a, 17+b, 0+c);
			glVertex3i( 2+a, 17+b, 0+c);
		glEnd();

		//-----Asas-------
		glBegin(GL_POLYGON);
			glVertex3i( 8+a, 8+b, 0+c);
			glVertex3i( 9+a, 8+b, 0+c);
			glVertex3i( 9+a, 17+b, 0+c);
			glVertex3i( 8+a, 17+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 9+a, 11+b, 0+c);
			glVertex3i( 10+a, 11+b, 0+c);
			glVertex3i( 10+a, 14+b, 0+c);
			glVertex3i( 9+a, 14+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 10+a, 12+b, 0+c);
			glVertex3i( 11+a, 12+b, 0+c);
			glVertex3i( 11+a, 15+b, 0+c);
			glVertex3i( 10+a, 15+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 11+a, 13+b, 0+c);
			glVertex3i( 12+a, 13+b, 0+c);
			glVertex3i( 12+a, 14+b, 0+c);
			glVertex3i( 11+a, 14+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 12+a, 11+b, 0+c);
			glVertex3i( 13+a, 11+b, 0+c);
			glVertex3i( 13+a, 17+b, 0+c);
			glVertex3i( 12+a, 17+b, 0+c);
		glEnd();

		glColor4f(WHITE);
		glBegin(GL_POLYGON);
			glVertex3i( 3+a, 10+b, 0+c);
			glVertex3i( 4+a, 10+b, 0+c);
			glVertex3i( 4+a, 13+b, 0+c);
			glVertex3i( 3+a, 13+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 3+a, 14+b, 0+c);
			glVertex3i( 4+a, 14+b, 0+c);
			glVertex3i( 4+a, 18+b, 0+c);
			glVertex3i( 3+a, 18+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 2+a, 8+b, 0+c);
			glVertex3i( 3+a, 8+b, 0+c);
			glVertex3i( 3+a, 11+b, 0+c);
			glVertex3i( 2+a, 11+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 2+a, 17+b, 0+c);
			glVertex3i( 3+a, 17+b, 0+c);
			glVertex3i( 3+a, 19+b, 0+c);
			glVertex3i( 2+a, 19+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 1+a, 10+b, 0+c);
			glVertex3i( 2+a, 10+b, 0+c);
			glVertex3i( 2+a, 18+b, 0+c);
			glVertex3i( 1+a, 18+b, 0+c);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3i( 11+a, 10+b, 0+c);
			glVertex3i( 12+a, 10+b, 0+c);
			glVertex3i( 12+a, 13+b, 0+c);
			glVertex3i( 11+a, 13+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 11+a, 14+b, 0+c);
			glVertex3i( 12+a, 14+b, 0+c);
			glVertex3i( 12+a, 18+b, 0+c);
			glVertex3i( 11+a, 18+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 12+a, 8+b, 0+c);
			glVertex3i( 13+a, 8+b, 0+c);
			glVertex3i( 13+a, 11+b, 0+c);
			glVertex3i( 12+a, 11+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 12+a, 17+b, 0+c);
			glVertex3i( 13+a, 17+b, 0+c);
			glVertex3i( 13+a, 19+b, 0+c);
			glVertex3i( 12+a, 19+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 13+a, 10+b, 0+c);
			glVertex3i( 14+a, 10+b, 0+c);
			glVertex3i( 14+a, 18+b, 0+c);
			glVertex3i( 13+a, 18+b, 0+c);
		glEnd();


	glPopMatrix();
}
/********************************************************
*		PRIMITIVA DO ALIEN SEM PUSH E POP				*
*														*
********************************************************/
void desenhaAlien(GLfloat a,GLfloat b,GLfloat c){

		glBegin(GL_POLYGON);
			glVertex3i( 4+a, 0+b, 0+c);
			glVertex3i( 5+a, 0+b, 0+c);
			glVertex3i( 5+a, 2+b, 0+c);
			glVertex3i( 4+a, 2+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 6+a, 0+b, 0+c);
			glVertex3i( 7+a, 0+b, 0+c);
			glVertex3i( 7+a, 2+b, 0+c);
			glVertex3i( 6+a, 2+b, 0+c);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3i( 3+a, 2+b, 0+c);
			glVertex3i( 8+a, 2+b, 0+c);
			glVertex3i( 8+a, 6+b, 0+c);
			glVertex3i( 3+a, 6+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 4+a, 6+b, 0+c);
			glVertex3i( 7+a, 6+b, 0+c);
			glVertex3i( 7+a, 7+b, 0+c);
			glVertex3i( 4+a, 7+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 5+a, 7+b, 0+c);
			glVertex3i( 6+a, 7+b, 0+c);
			glVertex3i( 6+a, 8+b, 0+c);
			glVertex3i( 5+a, 8+b, 0+c);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3i( 0+a, 3+b, 0+c);
			glVertex3i( 1+a, 3+b, 0+c);
			glVertex3i( 1+a, 4+b, 0+c);
			glVertex3i( 0+a, 4+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 0+a, 4+b, 0+c);
			glVertex3i( 3+a, 4+b, 0+c);
			glVertex3i( 3+a, 5+b, 0+c);
			glVertex3i( 0+a, 5+b, 0+c);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3i( 10+a, 3+b, 0+c);
			glVertex3i( 11+a, 3+b, 0+c);
			glVertex3i( 11+a, 4+b, 0+c);
			glVertex3i( 10+a, 4+b, 0+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 8+a, 4+b, 0+c);
			glVertex3i( 11+a, 4+b, 0+c);
			glVertex3i( 11+a, 5+b, 0+c);
			glVertex3i( 8+a, 5+b, 0+c);
		glEnd();

		glColor4f(AZUL);
		glBegin(GL_POLYGON);
			glVertex3i( 1+a, 5+b, 1+c);
			glVertex3i( 4+a, 5+b, 1+c);
			glVertex3i( 4+a, 6+b, 1+c);
			glVertex3i( 1+a, 6+b, 1+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 0+a, 6+b, 1+c);
			glVertex3i( 3+a, 6+b, 1+c);
			glVertex3i( 3+a, 7+b, 1+c);
			glVertex3i( 0+a, 7+b, 1+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 0+a, 7+b, 1+c);
			glVertex3i( 2+a, 7+b, 1+c);
			glVertex3i( 2+a, 8+b, 1+c);
			glVertex3i( 0+a, 8+b, 1+c);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3i( 7+a, 5+b, 1+c);
			glVertex3i( 10+a, 5+b, 1+c);
			glVertex3i( 10+a, 6+b, 1+c);
			glVertex3i( 7+a, 6+b, 1+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 8+a, 6+b, 1+c);
			glVertex3i( 11+a, 6+b, 1+c);
			glVertex3i( 11+a, 7+b, 1+c);
			glVertex3i( 8+a, 7+b, 1+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 9+a, 7+b, 1+c);
			glVertex3i( 11+a, 7+b, 1+c);
			glVertex3i( 11+a, 8+b, 1+c);
			glVertex3i( 9+a, 8+b, 1+c);
		glEnd();

		glColor4f(AMARELO);
		glBegin(GL_POLYGON);
			glVertex3i( 4+a, 3+b, 1+c);
			glVertex3i( 5+a, 3+b, 1+c);
			glVertex3i( 5+a, 4+b, 1+c);
			glVertex3i( 4+a, 4+b, 1+c);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3i( 6+a, 3+b, 1+c);
			glVertex3i( 7+a, 3+b, 1+c);
			glVertex3i( 7+a, 4+b, 1+c);
			glVertex3i( 6+a, 4+b, 1+c);
		glEnd();
}
/********************************************************
*				DESENHA OS OBJECTOS NA CENA				*
*														*
********************************************************/
void drawScene(){


	//---Galaxian--------------------------------------------------------------
	//---Os objetos 2D não têm iluminação para dar o efeito anos 80---
	glDisable(GL_LIGHTING);

	//---desenha a nave em movimento---
	desenhaNave(posNave,0,0);

	//---ALIENS
	//---primeira linha Azul---
	glPushMatrix();
		glTranslatef( 0, -40, -49);
		glRotatef (180, 0, 0, 1);
		glScaled(0.3,0.3,0.3);
			glColor4f(AZUL);
			desenhaAlien(90+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(75+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(60+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(45+posAlien,-100,0);
			glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			desenhaAlien(20+posAlien,-100,0);
			glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			desenhaAlien(5+posAlien,-100,0);
			glColor4f(0.3f, 0.6f, 0.9f, 1.0f);;
			desenhaAlien(-10+posAlien,-100,0);
			glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			desenhaAlien(-25+posAlien,-100,0);
			glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			desenhaAlien(-40+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(-65+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(-80+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(-95+posAlien,-100,0);
			glColor4f(AZUL);
			desenhaAlien(-110+posAlien,-100,0);
	glPopMatrix();

	//---segunda linha Laranja---
	glPushMatrix();
		glTranslatef( 0, -40, -49);
		glRotatef (180, 0, 0, 1);
		glScaled(0.3,0.3,0.3);
		glColor4f(LARANJA);
			desenhaAlien(90+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(75+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(60+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(45+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(30+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(15+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(0+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-20+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-35+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-50+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-65+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-80+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-95+posAlien,-150,0);
			glColor4f(LARANJA);
			desenhaAlien(-110+posAlien,-150,0);
	glPopMatrix();

	//---terceira linha Vermelho e outros---
	glPushMatrix();
		glTranslatef( 0, -40, -49);
		glRotatef (180, 0, 0, 1);
		glScaled(0.3,0.3,0.3);
			glColor4f(0.59f, 0.0f, 0.55f, 1.0f);
			desenhaAlien(90+posAlien,-200,0);
			glColor4f(0.59f, 0.0f, 0.55f, 1.0f);
			desenhaAlien(75+posAlien,-200,0);

			glColor4f(0.35f, 0.9f, 0.2f, 1.0f);
			desenhaAlien(20+posAlien,-200,0);
			glColor4f(VERMELHO);
			desenhaAlien(5+posAlien,-200,0);
			glColor4f(VERMELHO);
			desenhaAlien(-10+posAlien,-200,0);
			glColor4f(VERMELHO);
			desenhaAlien(-25+posAlien,-200,0);
			glColor4f(0.35f, 0.9f, 0.2f, 1.0f);
			desenhaAlien(-40+posAlien,-200,0);

			glColor4f(0.59f, 0.0f, 0.55f, 1.0f);
			desenhaAlien(-95+posAlien,-200,0);
			glColor4f(0.59f, 0.0f, 0.55f, 1.0f);
			desenhaAlien(-110+posAlien,-200,0);
	glPopMatrix();

	//---Volta a ligar a iluminação para os cubos 3D e SkyBox---
	glEnable(GL_LIGHTING);

	//---Cubos do Galaxian---
	//---Linha de Baixo---
	desenhaCuboRubik(-2.5, -2.5, -2.5, -30, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -25, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -20, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -15, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -10, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -5, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 0, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 5, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 10, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 15, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 20, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 25, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 30, -5, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 35, -5, -48, 1, 1, 1, 0, 0);
	//---Linha de Cima---
	desenhaCuboRubik(-2.5, -2.5, -2.5, -30, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -25, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -20, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -15, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, -10, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 15, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 20, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 25, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 30, 10, -48, 1, 1, 1, 0, 0);
	desenhaCuboRubik(-2.5, -2.5, -2.5, 35, 10, -48, 1, 1, 1, 0, 0);

	//---SKYBOX----------------------------------------------------------------
	glDisable(GL_LIGHTING);
	desenhaMundo();
	glEnable(GL_LIGHTING);


	//---Desenha o Cubo de Rubik-----------------------------------------------
	desenhaCuboRubik(-2.5, -2.5, -2.5, 5.5, 5.5, 5.5, 0, 1, 0, 0, 0);

	//----Reflexo do cubo no chão----------------------------------------------
	glEnable(GL_STENCIL_TEST); //Liga ostencil buffer
	glColorMask(0, 0, 0, 0); //desliga o desenho no ecrã
	glDisable(GL_DEPTH_TEST); //desliga o teste
	glStencilFunc(GL_ALWAYS, 1, 1); //stencil test sempre positivo

	//----faz com que o stencil fique sempre 1 quando se desenha nele----
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//---desenha o chão no stencil buffer y=0---

	if(demoCamera[1]>=0){
		glPushMatrix();
		glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(0,1,0);
						glVertex3i( j,0,i);
						glVertex3i( j,0,i+1);
						glVertex3i( 1+j,0,i+1);
						glVertex3i( 1+j,0,i);
					glEnd();
				}
			}
		glPopMatrix();
	}
	if(demoCamera[2]>=0){
		glPushMatrix();
		glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(0,0,1);
						glVertex3i( j, i,0 );
						glVertex3i( 1+j, i,0 );
						glVertex3i( 1+j, i+1,0);
						glVertex3i( j,  i+1,0);
					glEnd();
				}
			}
		glPopMatrix();
	}
	if(demoCamera[0]>=0){
		glPushMatrix();
		glColor4f(0.3f, 0.6f, 0.9f, 1.0f);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(1,0,0);
						glVertex3i( 0,  j, i );
						glVertex3i( 0,  j,  i+1);
						glVertex3i( 0, 1+j, i+1);
						glVertex3i( 0, 1+j, i );
					glEnd();
				}
			}
		glPopMatrix();
	}
	glColorMask(1, 1, 1, 1); //Ativa a escrita no ecrã
	glEnable(GL_DEPTH_TEST); //Liga o depth testing
	glStencilFunc(GL_EQUAL, 1, 1); //Só desenha se o stencil estiver a 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Bloqueia o stencil

	//---Desenha o cudo refletido na imagem---
	if(demoCamera[1]>=0){
		desenhaCuboRubik(-2.5, -2.5, -2.5, 5.5, -5.5, 5.5, 0, 1, 0, 0, 1);//y=0
	}
	if(demoCamera[0]>=0){
		desenhaCuboRubik(-2.5, -2.5, -2.5, -5.5, 5.5, 5.5, 0, -1, 0, 0, 3);
	}
	if(demoCamera[2]>=0){
		desenhaCuboRubik(-2.5, -2.5, -2.5, 5.5, 5.5, -5.5, 0, -1, 0, 180, 3); //Z=0
	}
	glDisable(GL_STENCIL_TEST); //Desliga o stencil buffer

	//---Mistura o chão com o reflexo---
	glEnable(GL_BLEND);


	//---Desenha o Chão no ecrã y=0---
	if(demoCamera[1]>=0){
		glPushMatrix();
		glColor4f(0.3f, 0.6f, 0.9f, 0.7f);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(0,1,0);
						glVertex3i( j,0,i);
						glVertex3i( j,0,i+1);
						glVertex3i( 1+j,0,i+1);
						glVertex3i( 1+j,0,i);
					glEnd();
				}
			}
		glPopMatrix();
	}
	if(demoCamera[2]>=0){
		glPushMatrix();
		glColor4f(0.3f, 0.6f, 0.9f, 0.7f);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(0,0,1);
						glVertex3i( j, i,0 );
						glVertex3i( 1+j, i,0 );
						glVertex3i( 1+j, i+1,0);
						glVertex3i( j,  i+1,0);
					glEnd();
				}
			}
		glPopMatrix();
	}
	if(demoCamera[0]>=0){
		glPushMatrix();
		glColor4f(0.3f, 0.6f, 0.9f, 0.7f);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(1,0,0);
						glVertex3i( 0,  j, i );
						glVertex3i( 0,  j,  i+1);
						glVertex3i( 0, 1+j, i+1);
						glVertex3i( 0, 1+j, i );
					glEnd();
				}
			}
		glPopMatrix();
	}
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	if(demoCamera[1]<0){
		glPushMatrix();
		initMaterials(19);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(0,-1,0);
						glVertex3i( j,0,i);
						glVertex3i( j,0,i+1);
						glVertex3i( 1+j,0,i+1);
						glVertex3i( 1+j,0,i);
					glEnd();
				}
			}
		glPopMatrix();
	}
	if(demoCamera[2]<0){
		glPushMatrix();
		initMaterials(19);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(0,0,-1);
						glVertex3i( j, i,0 );
						glVertex3i( 1+j, i,0 );
						glVertex3i( 1+j, i+1,0);
						glVertex3i( j,  i+1,0);
					glEnd();
				}
			}
		glPopMatrix();
	}
	if(demoCamera[0]<0){
		glPushMatrix();
		initMaterials(19);
			for(i=0; i<yC; i++){
				for(j=0; j<yC; j++){
					glBegin(GL_QUADS);
						glNormal3f(-1,0,0);
						glVertex3i( 0,  j, i );
						glVertex3i( 0,  j,  i+1);
						glVertex3i( 0, 1+j, i+1);
						glVertex3i( 0, 1+j, i );
					glEnd();
				}
			}
		glPopMatrix();
	}
	glEnable(GL_COLOR_MATERIAL);

}

GLvoid resize(GLsizei width, GLsizei height)
{
	wScreen=width;
	hScreen=height;
	drawScene();
}

//======================================================================== ILUMINCCAO
void iluminacao(){

	if (ligaLuz)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	if (ligaFoco)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	if (luz1 == 0){
			glEnable(GL_LIGHT5);}
		else{
			glDisable(GL_LIGHT5);;
		}
	if (luz2 == 0){
			glEnable(GL_LIGHT1);}
		else{
			glDisable(GL_LIGHT1);;
		}
	if (luz3 == 0){
			glEnable(GL_LIGHT2);}
		else{
			glDisable(GL_LIGHT2);;
		}
	if (luz4 == 0){
			glEnable(GL_LIGHT3);}
		else{
			glDisable(GL_LIGHT3);;
		}
	if (luz5 == 0){
			glEnable(GL_LIGHT4);}
		else{
			glDisable(GL_LIGHT4);;
	}

	glLightfv(GL_LIGHT1, GL_POSITION,      focoPini);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,focoDir );
}

void drawOrientacao()
{
	glPushMatrix();
	glColor4f(VERDE);
	glTranslatef (obsPini[0],obsPini[1],obsPini[2]);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glColor4f(LARANJA);
	glTranslatef (obsPfin[0],obsPfin[1],obsPfin[2]);
	glutSolidCube(0.75);
	glPopMatrix();
	glPushMatrix();
	glColor4f(VERMELHO);
	glTranslatef (focoPfin[0],focoPfin[1],focoPfin[2]);
	glutSolidCube(0.75);
	glPopMatrix();
}

void display(void){

	if (noite)
		glClearColor(GRAY1);
	else
		glClearColor(GRAY2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if(active == 1){
	//================================================================= Viewport1

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glViewport (0, hScreen/6, wScreen/6, hScreen/6);
  		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho (-xC,xC, -xC,xC, -zC,zC);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt( 0, 10,0, 0,0,0, 0, 0, -1);


		//--------------------- desenha objectos
		drawScene();
		drawOrientacao();
		//--------------------- Informacao
		glColor3f(1,0,0);
		sprintf(texto, "Posição X - %f", obsPini[0]);
		desenhaTexto(texto,-12,1,-3);
		sprintf(texto, "Posição Z - %f", obsPini[2]);
		desenhaTexto(texto,-12,1,-6);
		if(luz1 == 1){
			sprintf(texto, "Luz1 - off");
			desenhaTexto(texto,-12,1,-10);
		}
		else{
			sprintf(texto, "Luz1 - ON");
			desenhaTexto(texto,-12,1,-10);
		}
		if(luz3 == 1){
			sprintf(texto, "Luz2 - off");
			desenhaTexto(texto,-12,1,-13);
		}else{
			sprintf(texto, "Luz2 - ON");
			desenhaTexto(texto,-12,1,-13);
		}
		if(ligaLuz == 0){
			sprintf(texto, "LuzCentral - off");
			desenhaTexto(texto,-12,1,-16);
		}else{
			sprintf(texto, "LuzCentral - ON");
			desenhaTexto(texto,-12,1,-16);
		}
	}
	if(active == 1){
		//================================================================= Viewport2
		glEnable(GL_LIGHTING);
		glViewport (0, 0, wScreen, hScreen);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(99.0, wScreen/hScreen, 0.01, 120.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

	}
	if(active == 0){
	//Viewport Demo
		glEnable(GL_LIGHTING);
		glViewport (0, 0, wScreen, hScreen);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(99.0, wScreen/hScreen, 0.1, 120.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(demoCamera[0], demoCamera[1], demoCamera[2], demoFocoVisao[0], demoFocoVisao[1], demoFocoVisao[2], 0, 1, 0);
	}

	iluminacao();
	drawScene();
	glutSwapBuffers();
}


void updateVisao(){
	obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
	obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
	focoPini[0]=obsPini[0];
	focoPini[2]=obsPini[2];
	focoPfin[0]=focoPini[0]-rFoco*cos(aFoco+incH);
	focoPfin[2]=focoPini[2]-rFoco*sin(aFoco+incH);
	focoPini[1]=obsPini[1];
	focoPini[2]=obsPini[2];
	focoDir[0] =focoPfin[0]-focoPini[0];
	focoDir[1] =incV;
	focoDir[2] =focoPfin[2]-focoPini[2];
	glutPostRedisplay();

}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
	switch (key) {
			//--------------------------- Direccao da Lanterna
		case 's':
		case 'S':
			incH=incH-0.05;
			if (incH<-incMaxH ) incH=-incMaxH ;
			updateVisao();
			break;
		case 'd':
		case 'D':
			incH=incH+0.05;
			if (incH>incMaxH ) incH=incMaxH ;
			updateVisao();
			break;
		case 'e':
		case 'E':
			incV=incV+0.05;
			if (incV>incMaxV ) incV=incMaxV ;
			updateVisao();
			break;
		case 'c':
		case 'C':
			incV=incV-0.05;
			if (incV<-incMaxV ) incV=-incMaxV ;
			updateVisao();
			break;
			//--------------------------- Iluminacaoda sala
		case 't':
		case 'T':
			ligaLuz=!ligaLuz;
			glutPostRedisplay();
			break;
			//--------------------------- reset
		case 'r':
		case 'R':
			passoDemo = 0;
			rotacaoB = 600;
			active = 0;
			demoCamera[0] = 25;
			demoCamera[1] = 25;
			demoCamera[2] = 25;
			demoAng = 0.0001;
			demoFocoVisao[0] = 0;
			demoFocoVisao[1] = 0;
			demoFocoVisao[2] = 0;
			volta = 0;
			demoEndX = 0;
			demoEndY = 0;
			demoEndZ = 0;
			contador = 0;
			break;

		case 'l':
		case 'L':
			linear=!linear;
	        if (linear)
	        	glFogi(GL_FOG_MODE, GL_LINEAR);
	        else
			    glFogi(GL_FOG_MODE, GL_EXP2);
			glutPostRedisplay();
			break;
		//--------------------------- Iluminacao
		case '1':
			if (luz1 == 0){
				luz1 = 1;}
			else{
				luz1 = 0;
			}
			glutPostRedisplay();
			break;

		case '2':
			if (luz2 == 0){
				luz2 = 1;}
			else{
				luz2 = 0;
			}
			glutPostRedisplay();
			break;

		case '3':
			if (luz3 == 0){
				luz3 = 1;}
			else{
				luz3 = 0;
			}
			glutPostRedisplay();
			break;

		case '4':
			if (luz4 == 0){
				luz4 = 1;
				}
			else{
				luz4 = 0;
			}
			glutPostRedisplay();
			break;
		case '5':
			if (luz5 == 0){
				luz5 = 1;
				}
			else{
				luz5 = 0;
			}
			glutPostRedisplay();
			break;
			//--------------------------- Escape
		case 27:
			exit(0);
			break;

	}
}

void teclasNotAscii(int key, int x, int y)
{

    GLfloat temp1, temp2;
    if(key == GLUT_KEY_UP && active == 1) {
    	temp1 = obsPini[0]+incVisao*cos(aVisao);
    	temp2 = obsPini[2]-incVisao*sin(aVisao);

    	if(temp1 <=17 && temp1 >=0){
    		obsPini[0]=temp1;
    	}

    	if(temp2 <=17 && temp2 >=0){
    		obsPini[2]=temp2;
    	}

	}
	if(key == GLUT_KEY_DOWN  && active == 1) {
		temp1 = obsPini[0]-incVisao*cos(aVisao);
    	temp2 = obsPini[2]+incVisao*sin(aVisao);

    	if(temp1 <=17 && temp1 >=0){
    		obsPini[0]=temp1;
    	}

    	if(temp2 <=17 && temp2 >=0){
    		obsPini[2]=temp2;
    	}
	}
	if(key == GLUT_KEY_LEFT  && active == 1) {
		aVisao = (aVisao + 0.1) ;
		aFoco=aFoco-0.1;

	}
	if(key == GLUT_KEY_RIGHT && active == 1) {
		aVisao = (aVisao - 0.1) ;
		aFoco=aFoco+0.1;
	}
	updateVisao();
}
/********************************************************
*			CONTROLO DE EVENTOS							*
*														*
********************************************************/
void Timer(int value){

		if(luz1 == 1 && luz2 == 1 && ligaLuz == 0){
			if(passoDemo < 600){
				passoDemo = passoDemo + 0.1f;
			}
		}
		if(luz1 == 0 && luz2 == 0 && ligaLuz == 1){
			if(passoDemo > 0){
				passoDemo = passoDemo - 0.1f;
			}
		}
		contador ++;
		demoAng=demoAng + 0.001;


	//--Luzes------------------------------------------------------------------
	if(active == 0){
		luz1 = 1;
		luz2 = 1;
		luz3 = 1;
		ligaLuz = 0;
	}else{
		luz2 = 0;
	}

	if(obsPini[0] >=10 && obsPini[0] <=12 && obsPini[2] >=3 && obsPini[2] <=5){
		if(luz1 == 1){
			luz1 = 0;
			printf("found!\n");
		}
	}

	if(obsPini[2] >=10 && obsPini[2] <=12 && obsPini[0] >=3 && obsPini[0] <=5){
		if(luz3 == 1){
			luz3 = 0;
			printf("found!\n");
		}
	}

	if(obsPini[0] >=8 && obsPini[0] <=10 && obsPini[2] >=8 && obsPini[2] <=10){
		if(luz1 == 1){
			ligaLuz = 1;
			printf("found!\n");
		}
	}

	//controlo da demo
	if(demoEndX == 1 && demoEndY == 1 && demoEndZ == 1){
		active = 1;
		printf("ACTIVE STATUS = %d\n", active);
	}

	if(volta != 1){
		demoCamera[0] = 25 * cos(demoAng);

	}
	else{
	if (demoCamera[0] > 17){
		demoCamera[0] = demoCamera[0] - 0.01;
		}else {
			demoEndX = 1;
			printf("entrou X \n");
		}
	}
	if(volta != 1){
		demoCamera[1] = 25 * sin(demoAng);
	}else{
		if (demoCamera[1] < 5){
			demoCamera[1] = demoCamera[1] + 0.01;
			demoFocoVisao[1] = demoFocoVisao[1] + 0.01;
		}else {
			demoEndY = 1;
			printf("entrou Y \n");
		}
	}
	if(volta != 1){
		demoCamera[2] = 25 * sin(demoAng);
	}
	else{
		if (demoCamera[2] < 17){
			demoCamera[2] = demoCamera[2] + 0.01;
		}
		else {
			demoEndZ = 1;
			printf("entrou Z \n");
		}
	}

	//DEBUG
	//printf("X:%f - Y:%f - Z:%f \n", demoCamera[0],demoCamera[1],demoCamera[2]);
	//printf("XPF:%f - YPF:%f - ZPF:%f \n", obsPfin[0],obsPfin[1],obsPfin[2]);
	//printf("XPI:%f - YPI:%f - ZPI:%f \n", obsPini[0],obsPini[1],obsPini[2]);

	if(demoCamera[0] < -15){

		if(demoFocoVisao[2]>-45){
			demoFocoVisao[2] = demoFocoVisao[2] - 0.1;
		}
		if(demoFocoVisao[1]>-10){
			demoFocoVisao[1] = demoFocoVisao[1] - 0.1;
		}

	}else {
		if(demoCamera[0] > 15){
			if(demoFocoVisao[2]<0){
				demoFocoVisao[2] = demoFocoVisao[2] + 0.1;
			}
			if(demoFocoVisao[1]<0){
				demoFocoVisao[1] = demoFocoVisao[1] + 0.1;
			}
		}
	}

	if (demoCamera[0] > 24.99999){
		volta = 1;

	}

	//---CALCULO DA POSIÇÃO DOS ALIENS DO GALAXIAN---
	if(contador == 60){
		posAlien = 5;
	}
	if(contador == 120){
		posAlien = -5;
		contador = 0;
	}
	//---CALCULO ROTAÇÃO DOS CUBOS---
	if(angBule < 359){
		angBule=angBule+incBule;}
	else{
		angBule = 0;
	}

	//---CALCULO DA POSIÇÃO DA NAVE DO GALAXIAN---
	if(posNave<150 && flag == 0){
		posNave++;
		if(posNave == 150){
		flag = 1;
		}
	}
	if(posNave>-150 && flag == 1){
		posNave--;
		if(posNave == -150){
		flag = 0;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}
//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize (wScreen, hScreen);
	glutInitWindowPosition (400, 100);
	glutCreateWindow ("{maba}@dei.uc.pt-CG  (left,right,up,down)");

	init();
	glutSpecialFunc(teclasNotAscii);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);
	glutMainLoop();

	return 0;
}

