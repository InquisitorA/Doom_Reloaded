#include "final.h"

#include "texture.h"
#include "timer.h"
#include "monsters.h"
#include "boss.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Surface* floor_surface = NULL;
SDL_Texture* floor_texture = NULL;

SDL_Surface* gSurface = NULL;
SDL_Surface* gOpening = NULL;
SDL_Surface* gMenu = NULL;
SDL_Surface* gMenu1 = NULL;
SDL_Surface* gSettings = NULL;
SDL_Surface* gTexture1 = NULL;
SDL_Surface* gTexture2 = NULL;
SDL_Surface* gTexture3 = NULL;
SDL_Surface* gTexture4 = NULL;
SDL_Surface* gWin = NULL;
SDL_Surface* gLose = NULL;


SDL_Texture* opening = NULL;
SDL_Texture* menu = NULL;
SDL_Texture* menu1 = NULL;
SDL_Texture* settings = NULL;
SDL_Texture* texture1 = NULL;
SDL_Texture* texture2 = NULL;
SDL_Texture* texture3 = NULL;
SDL_Texture* texture4 = NULL;
SDL_Texture* win = NULL;
SDL_Texture* lose = NULL;

Mix_Chunk *gHover = NULL;
Mix_Chunk *gClick = NULL;
Mix_Chunk *gShoot = NULL;
Mix_Music *gMenuMusic = NULL;

class Slayer
{
    public:
		//The dimensions of the dot
		static const int SLAYER_WIDTH = 40;
		static const int SLAYER_HEIGHT = 40;

		//Maximum axis velocity of the dot

		//Initializes the variables
		Slayer();

		//Takes key presses and adjusts the dot's velocity

		//Moves the dot
		void move( int array[640][480] );
		
		void renderSlayer(int k);
		
		int hit;

		//Shows the dot on the screen
		bool alive;
		
		bool win;
		
};

class Bullet
{
    public:
		//The dimensions of the dot
		static const int BULLET_WIDTH = 10;
		static const int BULLET_HEIGHT = 10;

		//Initializes the variables
		Bullet();

		//Takes key presses and adjusts the dot's velocity

		//Moves the dot
		void moveBullet();	
		
		float bPosX, bPosY;

		float bVelX, bVelY;
		
		void renderBullet();
		
		int collisionM( int array[640][480], Monster monster);
		
		int collisionD( int array[640][480], Demon demon);
		
		int collisionB( int array[640][480], Boss boss);
		
		int collisionS( int array[640][480], Slayer slayer);
		
		bool exist;
				
		int array[640][480];		
		
};

int dx, dy;
float mPosX, mPosY;
float mVelX, mVelY;
bool fire;
static const int SLAYER_VEL = 2;
static const int BULLET_VEL = 5;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

SDL_Rect init(int X, int Y, int W, int H)
{
SDL_Rect rect;
rect.x = X;
rect.y = Y;
rect.w = W;
rect.h = H;

return rect;
}

SDL_Rect rect1 = init(135, 70, 380, 98);
SDL_Rect rect2 = init(135, 192, 380, 96);
SDL_Rect rect3 = init(135, 312, 380, 97);
SDL_Rect rect4 = init(43, 368, 88, 70);

void LTexture::render( int x, int y )
{
	//Set rendering space and render to screen	
	SDL_Rect slayer_pos;
	slayer_pos.w = mWidth;	
	slayer_pos.h = mHeight;
	slayer_pos.x = x;
	slayer_pos.y = y;

	//Set clip rendering dimensions
	
	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, NULL, &slayer_pos );
}


bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "DOOM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gSurface = SDL_GetWindowSurface( gWindow );
			if( gSurface == NULL )
			{
				printf( "Surface could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
			{
						printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
						success = false;
			}
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = false;
			}
		}
	}

	return success;
}

bool loadMedia_button1()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture1 = SDL_LoadBMP( "resources/button1.bmp" );
	if( gTexture1 == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

bool loadMedia_button2()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture2 = SDL_LoadBMP( "resources/button2.bmp" );
	if( gTexture2 == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

bool loadMedia_button3()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture3 = SDL_LoadBMP( "resources/button3.bmp" );
	if( gTexture3 == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

bool loadMedia_button4()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture4 = SDL_LoadBMP( "resources/button4.bmp" );
	if( gTexture4 == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

bool loadMedia_settings()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gSettings = SDL_LoadBMP( "resources/settings.bmp" );
	if( gSettings == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	return success;
}

bool loadMedia_opening()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gOpening = SDL_LoadBMP("resources/opening.bmp");
	if(gOpening == NULL)
	{
		printf( "Unable to load image\n", SDL_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia_menu()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gMenu = SDL_LoadBMP("resources/menu.bmp");
	gMenu1 = gMenu;
	if(gMenu == NULL)
	{
		printf( "Unable to load image\n", SDL_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia_win()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gWin = SDL_LoadBMP("resources/win.bmp");
	if(gWin == NULL)
	{
		printf( "Unable to load image\n", SDL_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia_lose()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gLose = SDL_LoadBMP("resources/lose.bmp");
	if(gLose == NULL)
	{
		printf( "Unable to load image\n", SDL_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia_click()
{
	//Loading success flag
	bool success = true;

	//Load sound effects
	gClick = Mix_LoadWAV( "resources/click.wav" );
	if( gClick == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia_shoot()
{
	//Loading success flag
	bool success = true;

	//Load sound effects
	gShoot = Mix_LoadWAV( "resources/shoot.mp3" );
	if( gShoot == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia_menuMusic()
{
	//Loading success flag
	bool success = true;

	//Load music
	gMenuMusic = Mix_LoadMUS( "resources/codex_main.mp3" );
	if( gMenuMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}

void exit()
{
	//Deallocate surface

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	SDL_FreeSurface( gOpening );
	SDL_FreeSurface( gMenu );
	gOpening = NULL;
	gMenu = NULL;
	
	Mix_FreeChunk( gClick );
	Mix_FreeChunk( gShoot );
	gShoot = NULL;
	gClick = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

int handleEvent0(SDL_Event* e)
{
	int var = -1;
	int x,y;
	SDL_GetMouseState(&x, &y);
	if(e->type == SDL_MOUSEBUTTONDOWN)
	{
		var = 0;
		if( 135 < x && x < 503 && 70 < y && y < 166 )
		{
			var = 1;
		}
		//Mouse is right of the button
		else if( 135 < x && x < 503 && 192 < y && y < 266 )
		{
			var = 2;
		}
		//Mouse above the button
		else if(135 < x && x < 503 && 312 < y && y < 408 )
		{
			var = 3;
		}
		else if(32 < x && x < 120 && 370 < y && y < 440)
		{
			var = 8;
		}
	}
	else if(e->type == SDL_MOUSEMOTION)
	{
		var = 4;
		if( 135 < x && x < 503 && 70 < y && y < 166 )
		{
			var = 5;
		}
		//Mouse is right of the button
		else if( 135 < x && x < 503 && 192 < y && y < 266 )
		{
			var = 6;
		}
		//Mouse above the button
		else if(135 < x && x < 503 && 312 < y && y < 408 )
		{
			var = 7;
		}
		else if(32 < x && x < 120 && 370 < y && y < 440)
		{
			var = 9;
		}
	}
	return var;
} 

int handleEvent1(SDL_Event* e)
{
	int var = -1;
	int x,y;
	SDL_GetMouseState(&x, &y);
	if(e->type == SDL_MOUSEBUTTONDOWN)
	{
		var = 0;
		if(32 < x && x < 120 && 370 < y && y < 440)
		{
			var = 1;
		}
	}
	else if(e->type == SDL_MOUSEMOTION)
	{
		var = 2;
		if(32 < x && x < 120 && 370 < y && y < 440)
		{
			var = 3;
		}
	}
	return var;
} 

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

//Scene textures 
Slayer::Slayer()
{
    //Initialize the position
    mPosX = 0;
    mPosY = 240;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    hit = 0;
    
    alive = true;
    
    win = false;

} 

Bullet::Bullet()
{
    //Initialize the position
    bPosX = 0;
    bPosY = 0;

    //Initialize the velocity
    bVelX = 0;
    bVelY = 0;

} 

void Bullet::moveBullet()
{	
	bPosX += bVelX;
	
	if( bPosX < 0 )
	{
		bPosX = 0;
		exist = false;
	}
	else if( bPosX > SCREEN_WIDTH - BULLET_WIDTH )
	{
		bPosX = SCREEN_WIDTH - BULLET_WIDTH;
		exist = false;
	}

	bPosY += bVelY;
			
	if( bPosY < 0 )
	{
		bPosY = 0;
		exist = false;
	}
	else if( bPosY > SCREEN_HEIGHT - BULLET_HEIGHT )
	{
		bPosY = SCREEN_HEIGHT - BULLET_HEIGHT;
		exist = false;
	}	

}

void handleEvent( SDL_Event& e, vector<Bullet>& bul, int k )
{
    //If a key was pressed
    LTexture slayerRf;
    bool trf = slayerRf.loadFromFile("slayer/slayer6.bmp");
    LTexture slayerLf;
    bool tlf = slayerLf.loadFromFile("slayer/slayer12.bmp");
    LTexture slayerUf;
    bool tuf = slayerUf.loadFromFile("slayer/slayer23.bmp");
    LTexture slayerDf;
    bool tdf = slayerDf.loadFromFile("slayer/slayer18.bmp");

    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY -= SLAYER_VEL; mVelX = 0; dx = 0; dy = 1; break;
            case SDLK_s: mVelY += SLAYER_VEL; mVelX = 0; dx = 0; dy = -1; break;
            case SDLK_a: mVelX -= SLAYER_VEL; mVelY = 0; dx = -1; dy = 0; break;
            case SDLK_d: mVelX += SLAYER_VEL; mVelY = 0; dx = 1; dy = 0; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
    	SDL_RenderClear( gRenderer );
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w: mVelY = 0; break;
            case SDLK_s: mVelY = 0; break;
            case SDLK_a: mVelX = 0; break;
            case SDLK_d: mVelX = 0; break;
        }
    }
    if( e.key.keysym.sym == SDLK_f && e.type == SDL_KEYDOWN && k%2 == 0 )
    {
    	bool shootsound = loadMedia_shoot();
    	Mix_PlayChannel( -1, gShoot, 0 );
    	mVelX = 0;
    	mVelY = 0;
    	Bullet newBul;
    	newBul.exist = true;
    	SDL_RenderClear( gRenderer );
    	if( dx == 0 && dy == 0 && fire == true )
    	{
    		slayerRf.render( (int)mPosX, (int)mPosY );
    		newBul.bVelX = BULLET_VEL; 
	    	newBul.bVelY = 0;
	    	newBul.bPosX = mPosX + 40;
    		newBul.bPosY = mPosY + 12;
	    	bul.push_back(newBul);	
    	}
    	if( dx == 1 && dy == 0 && fire == true )
    	{
    		slayerRf.render( (int)mPosX, (int)mPosY );
    		newBul.bVelX = BULLET_VEL; 
	    	newBul.bVelY = 0;
	    	newBul.bPosX = mPosX + 40;
    		newBul.bPosY = mPosY + 12;
	    	bul.push_back(newBul);	
    	}
    	if( dx == -1 && dy == 0 && fire == true )
    	{
    		slayerLf.render( (int)mPosX, (int)mPosY );
    		newBul.bVelX = -BULLET_VEL; 
	    	newBul.bVelY = 0;
	    	newBul.bPosX = mPosX;
    		newBul.bPosY = mPosY + 12;
	    	bul.push_back(newBul);	
    	}
    	if( dx == 0 && dy == 1 && fire == true )
    	{
    		slayerUf.render( (int)mPosX, (int)mPosY );
    		newBul.bVelY = -BULLET_VEL; 
	    	newBul.bVelX = 0;
	    	newBul.bPosX = mPosX + 20;
    		newBul.bPosY = mPosY;
	    	bul.push_back(newBul);	
    	}
    	if( dx == 0 && dy == -1 && fire == true )
    	{
    		slayerDf.render( (int)mPosX, (int)mPosY );
    		newBul.bVelY = BULLET_VEL; 
	    	newBul.bVelX = 0;
	    	newBul.bPosX = mPosX + 10;
    		newBul.bPosY = mPosY + 40;
	    	bul.push_back(newBul);	
    	}
    }
    
    //If a key was released
    
}	 

void Bullet::renderBullet()
{
	LTexture bulTex;
	bool b = bulTex.loadFromFile("slayer/bulletpink.bmp");
	if( b == false )
	{
		printf("unable to load image of bullet");
	}
	else
	{
		bulTex.render( (int)bPosX, (int)bPosY );
	}	
} 
  	
void Slayer::renderSlayer(int k)
{	
	LTexture gSlayer[24];
	
	int i = 0;
	while( i < 24 )
	{
		std::string s = std::to_string(i);
		std::string s1 = "slayer/slayer" + s + ".bmp";
		bool k = gSlayer[i].loadFromFile(s1);
		if( k == false )
		{
			printf( "cannot load slayer" );
		}
		i = i + 1;
	}
	
	if( dx == 0 && dy == 0 )
	{	
		gSlayer[0].render( (int)mPosX, (int)mPosY );		
	}
	
	if( mVelX > 0 )
	{
		if( k == 1 )
		{	
			gSlayer[1].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 2 )
		{
			gSlayer[2].render( (int)mPosX, (int)mPosY );
		}
		if( k == 3 )
		{
			gSlayer[3].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 4 )
		{
			gSlayer[4].render( (int)mPosX, (int)mPosY );	
		}
	}
	else if( mVelX < 0 )
	{
		if( k == 1 )
		{
			gSlayer[7].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 2 )
		{
			gSlayer[8].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 3 )
		{
			gSlayer[9].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 4 )
		{
			gSlayer[10].render( (int)mPosX, (int)mPosY );	
		}
	}
	else if( mVelY > 0 )
	{
		if( k == 1 )
		{
			gSlayer[13].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 2 )
		{
			gSlayer[14].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 3 )
		{
			gSlayer[15].render( (int)mPosX, (int)mPosY );	
		}
		if( k == 4 )
		{
			gSlayer[16].render( (int)mPosX, (int)mPosY );
		}
	}
	else if( mVelY < 0 )
	{
		if( k == 1 )
		{
			gSlayer[19].render( (int)mPosX, (int)mPosY );
		}
		if( k == 2 )
		{

			gSlayer[20].render( (int)mPosX, (int)mPosY );
		}
		if( k == 3 )
		{
			gSlayer[21].render( (int)mPosX, (int)mPosY );
		}
		if( k == 4 )
		{
			gSlayer[22].render( (int)mPosX, (int)mPosY );
		}
	}
	else
	{
		if( dx == 1 && dy == 0 )
		{
			gSlayer[5].render( (int)mPosX, (int)mPosY );
		}
		if( dx == -1 && dy == 0 )
		{
			gSlayer[11].render( (int)mPosX, (int)mPosY );
		}
		if( dx == 0 && dy == 1 )
		{
			gSlayer[23].render( (int)mPosX, (int)mPosY );	
		}
		if( dx == 0 && dy == -1 )
		{
			gSlayer[17].render( (int)mPosX, (int)mPosY );
	
		}
	}
}

void renderPlayer(int k, vector<Bullet>& bul, Slayer slayer)
{
	slayer.renderSlayer(k);	
	for(int i = 0; i < bul.size(); i++)
	{
		if( bul[i].exist == true )
		{
			bul[i].renderBullet();
		}
	}
}

void renderEnemies(int k, Monster monster, Demon demon)
{
	if( monster.hit < 3 )
	{
		monster.renderMonster(k);
	}
	if( demon.hit < 10 )
	{
		demon.renderDemon(k);
	}
}

void renderShooter(int k, int s, vector<Bullet>& ebul, Boss boss)
{
	if( boss.hit < 20 )
	{
		boss.renderBoss(k);
	}	
	if( s%10 == 0 )
	{
		Bullet bullet;
		bullet.exist = true;
		if( boss.aVelX > 0 )
		{
			bullet.bPosX = boss.aPosX + 40;
			bullet.bPosY = boss.aPosY + 20;
			bullet.bVelX = BULLET_VEL;
			bullet.bVelY = 0;
			ebul.push_back(bullet);
		}
		if( boss.aVelX < 0 )
		{
			bullet.bPosX = boss.aPosX;
			bullet.bPosY = boss.aPosY + 20;
			bullet.bVelX = -BULLET_VEL;
			bullet.bVelY = 0;
			ebul.push_back(bullet);
		}
		if( boss.aVelY > 0 )
		{
			bullet.bPosX = boss.aPosX + 20;
			bullet.bPosY = boss.aPosY + 40;
			bullet.bVelY = BULLET_VEL;
			bullet.bVelX = 0;
			ebul.push_back(bullet);
		}
		if( boss.aVelY < 0 )
		{
			bullet.bPosX = boss.aPosX + 20;
			bullet.bPosY = boss.aPosY;
			bullet.bVelY = -BULLET_VEL;
			bullet.bVelX = 0;
			ebul.push_back(bullet);
		}
		
	}		
	for(int i = 0; i < ebul.size(); i++)
	{
		if( ebul[i].exist == true && boss.hit < 20)
		{
			ebul[i].renderBullet();
		}
	}
}		

void Slayer::move( int array[640][480] )
{
    
    //Move the dot left or right
	if( mVelX >= 0 )
    	{
	    if(array[(int)mPosX + 40][(int)mPosY + 0] == 1 && array[(int)mPosX + 40][(int)mPosY + 5] == 0 && array[(int)mPosX + 40][(int)mPosY + 40] == 0)
	    {
	    	mPosX += mVelX;
	    }
	    if(array[(int)mPosX + 40][(int)mPosY + 40] == 1 && array[(int)mPosX + 40][(int)mPosY + 35] == 0 && array[(int)mPosX + 40][(int)mPosY + 0] == 0)
	    {
	    	mPosX += mVelX;
	    }
	    if(array[(int)mPosX + 40][(int)mPosY + 0] == 1 && array[(int)mPosX + 40][(int)mPosY + 5] == 0 && array[(int)mPosX + 40][(int)mPosY + 40] == 1 && array[(int)mPosX + 40][(int)mPosY + 35] == 0)
	    {
	    	mPosX += mVelX;
	    }
	    if(array[(int)mPosX + 40][(int)mPosY + 0] == 0 && array[(int)mPosX + 40][(int)mPosY + 40] == 0)
	    {
	    	mPosX += mVelX;
	    }
	}
	if( mVelX <= 0 )
    	{
	    if(array[(int)mPosX + 0][(int)mPosY + 0] == 1 && array[(int)mPosX + 0][(int)mPosY + 5] == 0 && array[(int)mPosX + 0][(int)mPosY + 40] == 0)
	    {
	    	mPosX += mVelX;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 40] == 1 && array[(int)mPosX + 0][(int)mPosY + 35] == 0 && array[(int)mPosX + 0][(int)mPosY + 0] == 0)
	    {
	    	mPosX += mVelX;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 0] == 1 && array[(int)mPosX + 0][(int)mPosY + 5] == 0 && array[(int)mPosX + 0][(int)mPosY + 40] == 1 && array[(int)mPosX + 0][(int)mPosY + 35] == 0)
	    {
	    	mPosX += mVelX;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 0] == 0 && array[(int)mPosX + 0][(int)mPosY + 40] == 0)
	    {
	    	mPosX += mVelX;
	    }
	}
	
    //If the dot went too far to the left or right
	if( mPosX < 0 )
	{
		mPosX = 0;
	}
	else if( mPosX > SCREEN_WIDTH - SLAYER_WIDTH )
	{
		mPosX = SCREEN_WIDTH - SLAYER_WIDTH;
	}
	
    //Move the dot up or down
    	if( mVelY >= 0 )
    	{
	    if(array[(int)mPosX + 0][(int)mPosY + 40] == 1 && array[(int)mPosX + 5][(int)mPosY + 40] == 0 && array[(int)mPosX + 40][(int)mPosY + 40] == 0)
	    {
	    	mPosY += mVelY;
	    }
	    if(array[(int)mPosX + 40][(int)mPosY + 40] == 1 && array[(int)mPosX + 35][(int)mPosY + 40] == 0 && array[(int)mPosX + 0][(int)mPosY + 40] == 0)
	    {
	    	mPosY += mVelY;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 40] == 1 && array[(int)mPosX + 5][(int)mPosY + 40] == 0 && array[(int)mPosX + 40][(int)mPosY + 40] == 1 && array[(int)mPosX + 35][(int)mPosY + 40] == 0)
	    {
	    	mPosY += mVelY;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 40] == 0 && array[(int)mPosX + 40][(int)mPosY + 40] == 0)
	    {
	    	mPosY += mVelY;
	    }
	}
	if( mVelY <= 0 )
    	{
	    if(array[(int)mPosX + 0][(int)mPosY + 0] == 1 && array[(int)mPosX + 5][(int)mPosY + 0] == 0 && array[(int)mPosX + 40][(int)mPosY + 0] == 0)
	    {
	    	mPosY += mVelY;
	    }
	    if(array[(int)mPosX + 40][(int)mPosY + 0] == 1 && array[(int)mPosX + 35][(int)mPosY + 0] == 0 && array[(int)mPosX + 0][(int)mPosY + 0] == 0)
	    {
	    	mPosY += mVelY;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 0] == 1 && array[(int)mPosX + 5][(int)mPosY + 0] == 0 && array[(int)mPosX + 40][(int)mPosY + 0] == 1 && array[(int)mPosX + 35][(int)mPosY + 0] == 0)
	    {
	    	mPosY += mVelY;
	    }
	    if(array[(int)mPosX + 0][(int)mPosY + 0] == 0 && array[(int)mPosX + 40][(int)mPosY + 0] == 0)
	    {
	    	mPosY += mVelY;
	    }
	}
	
    //If the dot went too far up or down
	if( mPosY < 0 )
	{
		mPosY = 0;
	}
	else if( mPosY > SCREEN_HEIGHT - SLAYER_HEIGHT )
	{
		mPosY = SCREEN_HEIGHT - SLAYER_HEIGHT;
	}		
	
} 

int Bullet::collisionM( int array[640][480], Monster monster )
{
	int p = bPosX;
	int q = bPosY;
	int r = monster.aPosX;
	int s = monster.aPosY;
	if( bVelX != 0 || bVelY != 0 )
	{
		if( array[p][q] == 1 )
		{
			exist = false;
		}
		else if( p > r && p < r + 40 && q > s && q < s + 40 && exist == true )
		{
			monster.hit = monster.hit + 1;
		}
	}
	return monster.hit;
}

int Bullet::collisionD( int array[640][480], Demon demon )
{
	int p = bPosX;
	int q = bPosY;
	int u = demon.aPosX;
	int v = demon.aPosY;
	if( bVelX != 0 || bVelY != 0 )
	{
		if( array[p][q] == 1 )
		{
			exist = false;
		}
		else if( p > u && p < u + 40 && q > v && q < v + 40 && exist == true )
		{
			demon.hit = demon.hit + 1;
		}
	}
	return demon.hit;
}

int Bullet::collisionB( int array[640][480], Boss boss )
{
	int p = bPosX;
	int q = bPosY;
	int x = boss.aPosX;
	int y = boss.aPosY;
	if( bVelX != 0 || bVelY != 0 )
	{
		if( array[p][q] == 1 )
		{
			exist = false;
		}
		else if( p > x && p < x + 40 && q > y && q < y + 40 && exist == true )
		{
			boss.hit = boss.hit + 1;
		}
	}
	return boss.hit;
}	   

int Bullet::collisionS( int array[640][480], Slayer slayer )
{
	int p = bPosX;
	int q = bPosY;
	int x = mPosX;
	int y = mPosY;
	if( bVelX != 0 || bVelY != 0 )
	{
		if( array[p][q] == 1 )
		{
			exist = false;
		}
		else if( p > x && p < x + 40 && q > y && q < y + 40 && exist == true )
		{
			slayer.hit = slayer.hit + 1;
		}
	}
	return slayer.hit;
}

void mazeRender( int random, int mazetyp )
{
	if( true )
	{
		vector<string> textualMaze;
		std::string st = std::to_string(mazetyp);
		std::string st1 = "mazes/maze" + st + ".txt";
		
		ifstream XY(st1);
		string str;
		while (getline(XY, str))
		{
			textualMaze.push_back(str);
		}


		int A4[16][12];
	
		for(int i=0;i<12;i++){
			for(int j=0;j<16;j++){
				if((textualMaze[i][j])=='1'){
				
					A4[j][i] = 1;
				}
			
				else if(textualMaze[i][j]=='0') {
					A4[j][i] = 0;
			
				}
			}
		}
		
		LTexture wall_texture;
		
		std::string s = std::to_string(random);
		std::string s1 = "resources/wall" + s + ".bmp";
		bool randomwall = wall_texture.loadFromFile(s1);
		if( randomwall == false )
		{
			printf( "cannot load wall" );
		}
		
		floor_surface = SDL_LoadBMP("resources/floor.bmp");
		floor_texture = SDL_CreateTextureFromSurface(gRenderer, floor_surface);
		
		for(int i=0;i<16;i++){
			for(int j=0;j<12;j++){
				if((A4[i][j])==1){
					SDL_Rect button_pos;
					button_pos.w = 40;
					button_pos.h = 40;
					button_pos.x = i*40;
					button_pos.y = j*40;
					wall_texture.render( i*40, j*40 );
				}
				if((A4[i][j])==0){
					SDL_Rect button_pos;
					button_pos.w = 40;
					button_pos.h = 40;
					button_pos.x = i*40;
					button_pos.y = j*40;
					SDL_RenderCopy(gRenderer, floor_texture, NULL, &button_pos);
				}
			}
		}
	}
}    				

int main( int argc, char* args[] )
{
	srand((unsigned int)time(NULL));
	int random = (rand()%5) + 1;
	int mazetyp = (rand()%4) + 1;
	//Start up SDL and create window
	if( !init() )
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		vector<string> textMaze;
		std::string st = std::to_string(mazetyp);
		std::string st1 = "mazes/maze" + st + ".txt";
		
		ifstream XY(st1);
		string str;
		while (getline(XY, str))
		{
			textMaze.push_back(str);
		}
		int A[16][12];	
		for(int i=0;i<12;i++){
			for(int j=0;j<16;j++){
				if((textMaze[i][j])=='1'){
				
					A[j][i] = 1;
				}
			
				else if(textMaze[i][j]=='0') {
					A[j][i] = 0;
			
				}
			}
		}
		int B[640][480];
		for(int k1 =0; k1<16;k1++){

			for(int k2 =0; k2<12;k2++){
							
				if(A[k1][k2]==0){
				
					for(int i = 40*k1; i<40*(k1+1);i++){
						for(int j = 40*k2; j<40*(k2+1);j++){
						
							B[i][j] = 0;
						
						}					
					
					}
								
				}
				
				if(A[k1][k2]==1){
				
					for(int i = 40*k1; i<40*(k1+1);i++){
						for(int j = 40*k2; j<40*(k2+1);j++){
						
							B[i][j] = 1;
						
						}					
					
					}				
				
				}						
			
			}
			
		}
		
		
		
		
		
		
		Slayer slayer;
			
		bool quit1 = !loadMedia_opening();

		while(!quit1)
		{
			SDL_Event e1;
				
			while(SDL_PollEvent(&e1) != 0)
			{
				int a = handleEvent0(&e1);
			
				if(e1.type == SDL_QUIT)
				{	
					quit1 = true;
					exit();
				}
				else if(4 > a && a > -1)
				{
					quit1 = true;
				}
				SDL_Texture* opening = SDL_CreateTextureFromSurface(gRenderer, gOpening);
				SDL_RenderCopy(gRenderer, opening, NULL, NULL);
				SDL_RenderPresent(gRenderer);
					
			}
				
		}

		bool quit2 = !loadMedia_menu();
		
		bool quit12 = loadMedia_menuMusic();

		while((!quit2)&&quit1)
		{
			if( Mix_PlayingMusic() == 0 )
			{
				//Play the music
				Mix_PlayMusic( gMenuMusic, -1 );
			}
	
			SDL_Texture* menu = SDL_CreateTextureFromSurface(gRenderer, gMenu);
			SDL_RenderCopy(gRenderer, menu, NULL, NULL);
			SDL_RenderPresent(gRenderer);

			bool quit3 = loadMedia_button1();
					
			bool quit4 = loadMedia_button2();
					
			bool quit5 = loadMedia_button3();
					
			bool quit6 = loadMedia_settings();
					
			bool quit7 = loadMedia_click();
					
			bool quit9 = loadMedia_button4();
			
			bool quit10 = loadMedia_win();
			SDL_Texture* win = SDL_CreateTextureFromSurface(gRenderer, gWin);
							
			bool quit11 = loadMedia_lose();
			SDL_Texture* lose = SDL_CreateTextureFromSurface(gRenderer, gLose);

			while(quit3&&quit4&&quit5)
			{
				SDL_Event e2;
	
				while(SDL_PollEvent(&e2) != 0)
				{
					int b = handleEvent0(&e2);

					if(e2.type == SDL_QUIT)
					{
						quit2 = true;
						quit3 = false;
						exit();
					}
					else if(b == 7)
					{
						SDL_Texture* texture3 = SDL_CreateTextureFromSurface(gRenderer, gTexture3);
						SDL_RenderCopy(gRenderer, texture3, NULL, &rect3);
						SDL_RenderPresent(gRenderer);
									
					}
					else if(b == 6)
					{
						SDL_Texture* texture2 = SDL_CreateTextureFromSurface(gRenderer, gTexture2);
						SDL_RenderCopy(gRenderer, texture2, NULL, &rect2);
						SDL_RenderPresent(gRenderer);
									
					}
					else if(b == 5)
					{
						SDL_Texture* texture1 = SDL_CreateTextureFromSurface(gRenderer, gTexture1);
						SDL_RenderCopy(gRenderer, texture1, NULL, &rect1);
						SDL_RenderPresent(gRenderer);
				
					}
					else if(b == 4)
					{
						SDL_RenderCopy(gRenderer, menu, NULL, NULL);
						SDL_RenderPresent(gRenderer);		
					}
					else if(b == 3)
					{
						Mix_PlayChannel( -1, gClick, 0 );
						quit2 = true;
						quit3 = false;
						exit();		
					}
					else if(b == 2)
					{
						SDL_Texture* settings = SDL_CreateTextureFromSurface(gRenderer, gSettings);
						SDL_RenderCopy(gRenderer, settings, NULL, NULL);
						SDL_RenderPresent(gRenderer);

						Mix_PlayChannel( -1, gClick, 0 );
								
						while(quit6)
						{
									
							SDL_Event e3;
							gMenu = NULL;
									
							
							while(SDL_PollEvent(&e3) != 0)
							{
								int c = handleEvent1(&e3);
										
								if(e3.type == SDL_QUIT)
								{
									quit3 = false;
									quit2 = true;
									quit6 = false;
									exit();
								}
										
								else if(c == 1)
								{	
									Mix_PlayChannel( -1, gClick, 0 );
									quit6 = false;
								}
								else if(c == 3)
								{
									SDL_Texture* texture4 = SDL_CreateTextureFromSurface(gRenderer, gTexture4);
									SDL_RenderCopy(gRenderer, texture4, NULL, &rect4);
									SDL_RenderPresent(gRenderer);
								}
								else if(c == 2)
								{
									SDL_RenderCopy(gRenderer, settings, NULL, NULL);
									SDL_RenderPresent(gRenderer);
								}
							}
						}
						quit6 = true;
						gMenu = gMenu1;
					}
					else if(b == 1)
					{
						//Main loop flag
						bool quit = false;
						//Event handler
						SDL_Event e;

						//The dot that will be moving around on the screen
						Monster monster;
						Boss boss;
						Demon demon;
						vector<Bullet> bul;
						vector<Bullet> ebul;
						int bulNum = 100;
						fire = true;

						//Keeps track of time between steps
						LTimer fpsTimer;
						LTimer capTimer;
						
						int countedFrames = 0;
						fpsTimer.start();

						//While application is running
						while( !quit )
						{
							capTimer.start();
							//Handle events on queue
							while( SDL_PollEvent( &e ) != 0 )
							{
								//User requests quit
								if( e.type == SDL_QUIT )
								{
									quit = true;
									quit3 = false;
									quit1 = false;
								}

								//Handle input for the dot
								handleEvent(e, bul, countedFrames);
								if( bul.size() >= bulNum )
								{
									fire = false;
								}
							}

							//Calculate time step
							monster.free(B);
							monster.chase( mPosX, mPosY );
							monster.move(B);
							
							boss.free(B);
							boss.chase( mPosX, mPosY );
							boss.move(B);
							
							demon.free(B);
							demon.chase( mPosX, mPosY );
							demon.move(B);
							
							slayer.move(B);
							
							for(int k = 0; k < bul.size(); k++)
							{
								bul[k].moveBullet();
								monster.hit = bul[k].collisionM(B, monster);
								boss.hit = bul[k].collisionB(B, boss);
								demon.hit = bul[k].collisionD(B, demon);
							}
							
							int s = ((countedFrames/5)%4) + 1;
							
							SDL_RenderClear( gRenderer );
							
							mazeRender(random, mazetyp);
							
							renderPlayer(s, bul, slayer);
							
							renderEnemies(s, monster, demon);
							
							renderShooter(s, countedFrames, ebul, boss);
							
							for(int k = 0; k < ebul.size(); k++)
							{
								ebul[k].moveBullet();
								slayer.hit = ebul[k].collisionS(B, slayer);
							}
							
							if( monster.hit < 3 )
							{
								if( monster.aPosX >= mPosX && monster.aPosX <= mPosX + 40 && monster.aPosY >= mPosY && monster.aPosY <= mPosY + 40 )
								{	
									slayer.alive = false;
								}
								if( monster.aPosX + 40 >= mPosX && monster.aPosX <= mPosX && monster.aPosY + 40 >= mPosY && monster.aPosY <= mPosY )
								{	
									slayer.alive = false;
								}
							}
							if( demon.hit < 10 )
							{
								if( demon.aPosX >= mPosX && demon.aPosX <= mPosX + 40 && demon.aPosY >= mPosY && demon.aPosY <= mPosY + 40 )
								{	
									slayer.alive = false;
								}
								if( demon.aPosX + 40 >= mPosX && demon.aPosX <= mPosX && demon.aPosY + 40 >= mPosY && demon.aPosY <= mPosY )
								{	
									slayer.alive = false;
								}
							}
							for(int k = 0; k < ebul.size(); k++)
							{
								if( ebul[k].exist == true )
								{
									if( ebul[k].bPosX > mPosX && ebul[k].bPosX < mPosX + 40 && ebul[k].bPosY > mPosY && ebul[k].bPosY < mPosY + 40 )
									{	
										slayer.alive = false;
									}
									if( ebul[k].bPosX + 40 > mPosX && ebul[k].bPosX < mPosX && ebul[k].bPosY + 40 > mPosY && ebul[k].bPosY < mPosY )
									{	
										slayer.alive = false;
									}
								}	
							}
							if( monster.hit >= 3 && demon.hit >= 10 && boss.hit >= 20 && slayer.alive == true )
							{	
								SDL_RenderCopy(gRenderer, win, NULL, NULL);
								SDL_RenderPresent(gRenderer);
								slayer.alive = true;
							}
							if( slayer.alive == false )
							{
								SDL_RenderCopy(gRenderer, lose, NULL, NULL);
								SDL_RenderPresent(gRenderer);
							}
							
							
							SDL_RenderPresent(gRenderer);
							
							++countedFrames;

							//If frame finished early
							int frameTicks = capTimer.getTicks();
							if( frameTicks < 30 )
							{
								//Wait remaining time
								SDL_Delay( 30 - frameTicks );
							}

							//Move for time step		
						}

					}		
				}

			}

		}
		Mix_HaltMusic();

	}
	Mix_HaltMusic();
	exit();
	return 0;
}

