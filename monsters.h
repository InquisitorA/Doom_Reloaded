#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Monster
{
    public:
		//The dimensions of the dot
		static const int MONSTER_WIDTH = 40;
		static const int MONSTER_HEIGHT = 40;
		
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		//Maximum axis velocity of the dot
		int array[640][480];
				
		void chase( int x, int y );

		//Initializes the variables
		Monster();

		//Takes key presses and adjusts the dot's velocity

		//Moves the dot
		void move( int array[640][480] );
		
		void free( int array[640][480] );

		//Shows the dot on the screen
		void renderMonster(int countedframes);
		
		float aPosX, aPosY;
		float aVelX, aVelY;

		static const int MONSTER_VEL = 2;
		
		int countedFrames;
		
		int dmr, dml;
		int dmu, dmd;
		
		int hit;
		
};

class Demon
{
    public:
		//The dimensions of the dot
		static const int DEMON_WIDTH = 40;
		static const int DEMON_HEIGHT = 40;
		
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		//Maximum axis velocity of the dot
		int array[640][480];
				
		void chase( int x, int y );

		//Initializes the variables
		Demon();

		//Takes key presses and adjusts the dot's velocity

		//Moves the dot
		void move( int array[640][480] );
		
		void free( int array[640][480] );

		//Shows the dot on the screen
		void renderDemon(int countedframes);
		
		float aPosX, aPosY;
		float aVelX, aVelY;

		static const int DEMON_VEL = 2;
		
		int countedFrames;
		
		int dmr, dml;
		int dmu, dmd;
		
		int hit;
		
};


