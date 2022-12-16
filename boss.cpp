#include "boss.h"
#include "texture.h"

using namespace std;

Boss::Boss()
{
    //Initialize the position
    aPosX = 600;
    aPosY = 240;

    //Initialize the velocity
    aVelX = 0;
    aVelY = 0;
    
    dmr = 0;
    dml = 0;
    dmu = 0;
    dmd = 0;
    
    hit = 0;

}

void Boss::renderBoss(int k)
{	
	LTexture gBoss[17];
	
	int i = 0;
	while( i < 17 )
	{
		std::string s = std::to_string(i);
		std::string s1 = "monsters/cyberd" + s + ".bmp";
		bool k = gBoss[i].loadFromFile(s1);
		if( k == false )
		{
			printf( "cannot load boss" );
		}
		i = i + 1;
	}
	
	if( aVelX > 0 )
	{
		if( k == 1 )
		{		
			gBoss[1].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gBoss[2].render( (int)aPosX, (int)aPosY );	
		}
		if( k == 3 )
		{
			gBoss[3].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gBoss[4].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelX < 0 )
	{
		if( k == 1 )
		{
			gBoss[5].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gBoss[6].render( (int)aPosX, (int)aPosY );

		}
		if( k == 3 )
		{
			gBoss[7].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gBoss[8].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelY > 0 )
	{
		if( k == 1 )
		{
			gBoss[9].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gBoss[10].render( (int)aPosX, (int)aPosY );
		}
		if( k == 3 )
		{
			gBoss[11].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gBoss[12].render( (int)aPosX, (int)aPosY );
		}
	}
	else if( aVelY < 0 )
	{
		if( k == 1 )
		{
			gBoss[13].render( (int)aPosX, (int)aPosY );
		}
		if( k == 2 )
		{
			gBoss[14].render( (int)aPosX, (int)aPosY );
		}
		if( k == 3 )
		{
			gBoss[15].render( (int)aPosX, (int)aPosY );
		}
		if( k == 4 )
		{
			gBoss[16].render( (int)aPosX, (int)aPosY );
		}
	}
	else
	{
		gBoss[0].render( (int)aPosX, (int)aPosY );
	}
}

void Boss::move( int array[640][480] )
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
	else if( aPosX > SCREEN_WIDTH - BOSS_WIDTH )
	{
		aPosX = SCREEN_WIDTH - BOSS_WIDTH;
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
	else if( aPosY > SCREEN_HEIGHT - BOSS_HEIGHT )
	{
		aPosY = SCREEN_HEIGHT - BOSS_HEIGHT;
	}		
	
} 

void Boss::free( int array[640][480] )
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
	
void Boss::chase( int x, int y )
{
	if( aPosX > x && dml == 1 )
	{
		aVelX = -BOSS_VEL;
		aVelY = 0;
	}
	else if( aPosX > x && dml == 0 )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -BOSS_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = BOSS_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}
	else if( aPosX < x && dmr == 1 )
	{
		aVelX = BOSS_VEL;
		aVelY = 0;
	}
	else if( aPosX < x && dmr == 0 )
	{
		aVelX = 0;
		if( aPosY > y && dmu == 1 )
		{
			aVelY = -BOSS_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = BOSS_VEL;
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
			aVelY = -BOSS_VEL;
		}
		else if( aPosY < y && dmd == 1 )
		{
			aVelY = BOSS_VEL;
		}
		else
		{
			aVelY = 0;
		}
	}			
}
