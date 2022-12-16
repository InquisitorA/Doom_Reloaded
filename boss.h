#include <SDL2/SDL_image.h>

class Boss
{
    public:
		//The dimensions of the dot
		static const int BOSS_WIDTH = 40;
		static const int BOSS_HEIGHT = 40;
		
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		//Maximum axis velocity of the dot
		int array[640][480];
				
		void chase( int x, int y );

		//Initializes the variables
		Boss();

		//Takes key presses and adjusts the dot's velocity

		//Moves the dot
		void move( int array[640][480] );
		
		void free( int array[640][480] );

		//Shows the dot on the screen
		void renderBoss(int countedframes);
		
		float aPosX, aPosY;
		float aVelX, aVelY;

		static const int BOSS_VEL = 1;
		
		int countedFrames;
		
		int dmr, dml;
		int dmu, dmd;
		
		int hit;
		
};

