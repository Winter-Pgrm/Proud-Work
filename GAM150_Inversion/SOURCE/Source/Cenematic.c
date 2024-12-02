//------------------------------------------------------------------------------
//
// File Name:	Cenematic.c
// Author(s):	Alex Phillips 
// Project:		Inversion
// Course:		GAM150S17
//
// Copyright © 2017 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AEEngine.h"
#include "Commandlist.h"
#include "Cenematic.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static int isrunning = 1;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static float timerfortransisition(float timers);
static void  Drawthescenes(AEGfxVertexList *MainMenuthisMesh, AEGfxTexture *MainMenuthisTexture, float Talpja);
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
//AEInputCheckTriggered(VK_LBUTTON)
void Text1()
{
	
	//load the image 
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\Stage1.bmp");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	while (isrunning == 1)
	{
		AEInputUpdate();
		timeinrotation = timerfortransisition(timeinrotation);
			if (timeinrotation <= 0.0f)
			{
				isrunning = 0;
				AEGfxTextureUnload(MainMenuNamenewTexture);
				AEGfxMeshFree(MainMenuNamenewMesh);
				//call the next text 
				//free the meshs and things here 
				//apply a trasistion effect 
				Text2();
			}
			else
			{
				if (timeinrotation > 5.0)
				{
					Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, 1.0f);
				}
				else if (timeinrotation > 0.1f && timeinrotation <= 5.0f )
				{
					Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, timeinrotation - 0.05f);

				}

				 if (getinput() == 1)
				{
					isrunning = 0;
					AEGfxTextureUnload(MainMenuNamenewTexture);
					AEGfxMeshFree(MainMenuNamenewMesh);
				}
			}
			
	}
	


}
void Text2()
{
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\Stage3.bmp");
	AEGfxMeshStart();
	isrunning = 1;

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	while (isrunning == 1)
	{
		AEInputUpdate();
		timeinrotation = timerfortransisition(timeinrotation);
		if (timeinrotation <= 0.0f)
		{
			isrunning = 0;
			AEGfxTextureUnload(MainMenuNamenewTexture);
			AEGfxMeshFree(MainMenuNamenewMesh);
			//call the next text 
			//free the meshs and things here 
			//apply a trasistion effect 
			Penguinstage3();
		}
		else
		{
			if (timeinrotation > 5.0)
			{
				Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, 1.0f);
			}
			else if (timeinrotation > 0.1f && timeinrotation <= 5.0f)
			{
				Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, timeinrotation - 0.05f);

			}
			 if (getinput() == 1)
			{
				isrunning = 0;
				AEGfxTextureUnload(MainMenuNamenewTexture);
				AEGfxMeshFree(MainMenuNamenewMesh);
			}
		}

	}
}
void Penguinstage3()
{
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\stagea3.bmp");
	AEGfxMeshStart();
	isrunning = 1;

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	while (isrunning == 1)
	{
		AEInputUpdate();
		timeinrotation = timerfortransisition(timeinrotation);
		if (timeinrotation <= 0.0f)
		{
			isrunning = 0;
			AEGfxTextureUnload(MainMenuNamenewTexture);
			AEGfxMeshFree(MainMenuNamenewMesh);
			//call the next text 
			//free the meshs and things here 
			//apply a trasistion effect 
			Scientistholdspenguin();
		}
		else
		{
			if (timeinrotation > 5.0)
			{
				Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, 1.0f);
			}
			else if (timeinrotation > 0.1f && timeinrotation <= 5.0f)
			{
				Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, timeinrotation - 0.05f);

			}
			 if (getinput() == 1)
			{
				isrunning = 0;
				AEGfxTextureUnload(MainMenuNamenewTexture);
				AEGfxMeshFree(MainMenuNamenewMesh);
			}
		}

	}
}
void Scientistholdspenguin()
{
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\stage3.png");
	AEGfxMeshStart();
	isrunning = 1;

	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	while (isrunning == 1)
	{
		AEInputUpdate();
		timeinrotation = timerfortransisition(timeinrotation);
		if (timeinrotation <= 0.0f)
		{
			isrunning = 0;
			AEGfxTextureUnload(MainMenuNamenewTexture);
			AEGfxMeshFree(MainMenuNamenewMesh);
			//call the next text 
			//free the meshs and things here 
			//apply a trasistion effect 
			
		}
		else
		{
			if (timeinrotation > 5.0)
			{
				Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, 1.0f);
			}
			else if (timeinrotation > 0.1f && timeinrotation <= 5.0f)
			{
				Drawthescenes(MainMenuNamenewMesh, MainMenuNamenewTexture, timeinrotation - .05f);

			}
			 if (getinput() == 1)
			{
				isrunning = 0;
				AEGfxTextureUnload(MainMenuNamenewTexture);
				AEGfxMeshFree(MainMenuNamenewMesh);
			}
		}

	}
}
void Fastesttime()
{
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\letsee.png");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	//timer
	if (timerfortransisition(timeinrotation) <= 0.0f)
	{

		//call the next text 
		//free the meshs and things here 
		//apply a trasistion effect 
	}
}
void Notfastesttime()
{
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\letsee.png");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	//timer
	if (timerfortransisition(timeinrotation) <= 0.0f)
	{

		//call the next text 
		//free the meshs and things here 
		//apply a trasistion effect 
	}
}
void scorescreen()
{
	static  AEGfxVertexList *MainMenuNamenewMesh;
	static AEGfxTexture *MainMenuNamenewTexture;
	MainMenuNamenewTexture = AEGfxTextureLoad("Assets\\letsee.png");
	AEGfxMeshStart();


	AEGfxTriAdd(
		-0.5f, -0.5f, 0x00FF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-0.5f, 0.5f, 0x00F00FFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	MainMenuNamenewMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(MainMenuNamenewMesh, "Failed to create LogoMesh!!");
	float timeinrotation = 8.6f;
	//timer
	if (timerfortransisition(timeinrotation) <= 0.0f)
	{

		//call the next text 
		//free the meshs and things here 
		//apply a trasistion effect 
	}
}


float timerfortransisition(float timers)
{
	float holder = timers;
	holder -= .05f;

	return holder;

}

void Drawthescenes(AEGfxVertexList *MainMenuthisMesh, AEGfxTexture *MainMenuthisTexture, float Talpja)
{
	AESysFrameStart();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetFullTransformWithZOrder(0, 0, 0.0f, 0.0f, 2 * AEGfxGetWinMaxX(), 2 * AEGfxGetWinMaxY());
	AEGfxTextureSet(MainMenuthisTexture, 0,0);
	AEGfxSetTransparency(Talpja);
	AEGfxMeshDraw(MainMenuthisMesh, AE_GFX_MDM_TRIANGLES);
	AESysFrameEnd();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

