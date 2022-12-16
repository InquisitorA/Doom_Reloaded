#include "monsters.h"
#include "texture.h"

using namespace std;

Monster::Monster()
{
    //Initialize the position
    aPosX = 320;
    aPosY = 440;

    //Initialize the velocity
    aVelX = 0;
    aVelY = 0;
    
    dmr = 0;
    dml = 0;
    dmu = 0;
    dmd = 0;
    
    hit = 0;

}

void Monster::renderMonster(int k)
{	
	LTexture gMonster[17];
	
	int i = 0;
	while( i < 17 )
	{
		std::string s = std::to_string(i);
		std::string s1 = "monsters/hellknight" + s + ".bmp";
		bool k = gMonster[i].loadFromFile(s1);
		if( k == false )
		{
			printf( "cannot load monster" );
		}
		i = i + 1;
	}
	
	if( aVelX > 0 )
	{
		if( k == 1 )
		{		
			gMonster[1].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gMonster[2].render( (int)aPosX, (int)aPosY );	
		}
		if( k == 3 )
		{
			gMonster[3].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gMonster[4].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelX < 0 )
	{
		if( k == 1 )
		{
			gMonster[5].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gMonster[6].render( (int)aPosX, (int)aPosY );

		}
		if( k == 3 )
		{
			gMonster[7].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gMonster[8].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelY > 0 )
	{
		if( k == 1 )
		{
			gMonster[9].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gMonster[10].render( (int)aPosX, (int)aPosY );
		}
		if( k == 3 )
		{
			gMonster[11].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gMonster[12].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelY < 0 )
	{
		if( k == 1 )
		{
			gMonster[13].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gMonster[14].render( (int)aPosX, (int)aPosY );
		}
		if( k == 3 )
		{
			gMonster[15].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gMonster[16].render( (int)aPosX, (int)aPosY );
		}
	}
	else
	{
		gMonster[0].render( (int)aPosX, (int)aPosY );
	}
}

void Monster::move( int array[640][480] )
{
    
    //Move the dot left or right
	if( aVelX >= 0 )
    	{
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	}
	if( aVelX <= 0 )
    	{
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	}
	
    //If the dot went too far to the left or right
	if( aPosX < 0 )
	{
		aPosX = 0;
	}
	else if( aPosX > SCREEN_WIDTH - MONSTER_WIDTH )
	{
		aPosX = SCREEN_WIDTH - MONSTER_WIDTH;
	}
	
    //Move the dot up or down
    	if( aVelY >= 0 )
    	{
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 5][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 35][(int)aPosY + 40] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 5][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 35][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	}
	if( aVelY <= 0 )
    	{
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	}
	
    //If the dot went too far up or down
	if( aPosY < 0 )
	{
		aPosY = 0;
	}
	else if( aPosY > SCREEN_HEIGHT - MONSTER_HEIGHT )
	{
		aPosY = SCREEN_HEIGHT - MONSTER_HEIGHT;
	}		
	
} 

void Monster::free( int array[640][480] )
{
	dmr = 0;
	dml = 0;
	dmu = 0;
	dmd = 0;
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 5][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 35][(int)aPosY + 40] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
}
	
void Monster::chase( int x, int y )
{
	if( aPosX > x && dml == 1 )
	{
		aVelX = -MONSTER_VEL;
		aVelY = 0;
	}
	else if( aPosX > x && dml == 0 )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -MONSTER_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = MONSTER_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}
	else if( aPosX < x && dmr == 1 )
	{
		aVelX = MONSTER_VEL;
		aVelY = 0;
	}
	else if( aPosX < x && dmr == 0 )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -MONSTER_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = MONSTER_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}
	else if( aPosX == x )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -MONSTER_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = MONSTER_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}			
}


Demon::Demon()
{
    //Initialize the position
    aPosX = 320;
    aPosY = 0;

    //Initialize the velocity
    aVelX = 0;
    aVelY = 0;
    
    dmr = 0;
    dml = 0;
    dmu = 0;
    dmd = 0;
    
    hit = 0;

}

void Demon::renderDemon(int k)
{	
	LTexture gDemon[17];
	
	int i = 0;
	while( i < 17 )
	{
		std::string s = std::to_string(i);
		std::string s1 = "monsters/helldemon" + s + ".bmp";
		bool k = gDemon[i].loadFromFile(s1);
		if( k == false )
		{
			printf( "cannot load demon" );
		}
		i = i + 1;
	}
	
	if( aVelX > 0 )
	{
		if( k == 1 )
		{		
			gDemon[1].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gDemon[2].render( (int)aPosX, (int)aPosY );	
		}
		if( k == 3 )
		{
			gDemon[3].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gDemon[4].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelX < 0 )
	{
		if( k == 1 )
		{
			gDemon[5].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gDemon[6].render( (int)aPosX, (int)aPosY );

		}
		if( k == 3 )
		{
			gDemon[7].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gDemon[8].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelY > 0 )
	{
		if( k == 1 )
		{
			gDemon[9].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gDemon[10].render( (int)aPosX, (int)aPosY );
		}
		if( k == 3 )
		{
			gDemon[11].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gDemon[12].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelY < 0 )
	{
		if( k == 1 )
		{
			gDemon[13].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gDemon[14].render( (int)aPosX, (int)aPosY );
		}
		if( k == 3 )
		{
			gDemon[15].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gDemon[16].render( (int)aPosX, (int)aPosY );
		}
	}
	else
	{
		gDemon[0].render( (int)aPosX, (int)aPosY );
	}
}

void Demon::move( int array[640][480] )
{
    
    //Move the dot left or right
	if( aVelX >= 0 )
    	{
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	}
	if( aVelX <= 0 )
    	{
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0)
	    {
	    	aPosX += aVelX;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	    {
	    	aPosX += aVelX;
	    }
	}
	
    //If the dot went too far to the left or right
	if( aPosX < 0 )
	{
		aPosX = 0;
	}
	else if( aPosX > SCREEN_WIDTH - DEMON_WIDTH )
	{
		aPosX = SCREEN_WIDTH - DEMON_WIDTH;
	}
	
    //Move the dot up or down
    	if( aVelY >= 0 )
    	{
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 5][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 35][(int)aPosY + 40] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 5][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 35][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	    {
	    	aPosY += aVelY;
	    }
	}
	if( aVelY <= 0 )
    	{
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	    if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	    {
	    	aPosY += aVelY;
	    }
	}
	
    //If the dot went too far up or down
	if( aPosY < 0 )
	{
		aPosY = 0;
	}
	else if( aPosY > SCREEN_HEIGHT - DEMON_HEIGHT )
	{
		aPosY = SCREEN_HEIGHT - DEMON_HEIGHT;
	}		
	
} 

void Demon::free( int array[640][480] )
{
	dmr = 0;
	dml = 0;
	dmu = 0;
	dmd = 0;
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmr = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 0][(int)aPosY + 5] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 0][(int)aPosY + 35] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	{
		dml = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 40] == 1 && array[(int)aPosX + 5][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 35][(int)aPosY + 40] == 0 && array[(int)aPosX + 0][(int)aPosY + 40] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 40][(int)aPosY + 5] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 1 && array[(int)aPosX + 40][(int)aPosY + 35] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 40] == 0 && array[(int)aPosX + 40][(int)aPosY + 40] == 0)
	{
		dmd = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
	if(array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0 && array[(int)aPosX + 0][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 1 && array[(int)aPosX + 5][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 1 && array[(int)aPosX + 35][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
	if(array[(int)aPosX + 0][(int)aPosY + 0] == 0 && array[(int)aPosX + 40][(int)aPosY + 0] == 0)
	{
		dmu = 1;
	}
}
	
void Demon::chase( int x, int y )
{
	if( aPosX > x && dml == 1 )
	{
		aVelX = -DEMON_VEL;
		aVelY = 0;
	}
	else if( aPosX > x && dml == 0 )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -DEMON_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = DEMON_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}
	else if( aPosX < x && dmr == 1 )
	{
		aVelX = DEMON_VEL;
		aVelY = 0;
	}
	else if( aPosX < x && dmr == 0 )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -DEMON_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = DEMON_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}
	else if( aPosX == x )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -DEMON_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = DEMON_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}			
}



