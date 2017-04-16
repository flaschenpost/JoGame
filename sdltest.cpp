#include <iostream>
#include <fstream>
#include <SDL/SDL_image.h>
#include <unistd.h>
using namespace std;

uint32_t screenW = 1700;
uint32_t screenH = 900;

int main ( int argc, char *argv[] )
{
  SDL_Rect rcSprite;
  ofstream log;
  log.open("log.txt", ios::out);

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Test", "SDL Test");

  /* create window */
  SDL_Surface* screen = SDL_SetVideoMode(screenW, screenH, 10, 10);
  //
  //Initialize PNG loading
  /* load bitmap to temp surface */
  SDL_Surface* temp = IMG_Load("kopp.png");
  SDL_Surface *sprite = SDL_DisplayFormat(temp);
  /* free the temp surface */
  SDL_FreeSurface(temp);
  log << rcSprite.w << " "<< rcSprite.h << "\n";
  return 1;

  
  uint32_t width = screenW - sprite->w;
  uint32_t height = screenH - sprite->h;

  srand(12643l);

  rcSprite.x = 100;
  rcSprite.y = 100;
  float speedX = 2 + 5 * static_cast<float>(rand()) / static_cast<float> (RAND_MAX);
  float speedY = 1 + 2 * static_cast<float>(rand()) / static_cast<float> (RAND_MAX);

  log << "speedX: " << speedX << "\n";
  log << "speedY: " << speedY << "\n";

  Uint32 lastTime = SDL_GetTicks(); 

    /* draw the sprite */
    SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    usleep(1000000l);

  SDL_Event event;
  int gameover = 0;

  /* message pump */
  while (!gameover)
  {
    Uint32 now = SDL_GetTicks(); 
    Uint32 diff = now - lastTime;
    log << "diff = " << diff << "\n";
    lastTime = now;

    rcSprite.x += speedX * diff / 100;
    rcSprite.y += speedY * diff / 100;

    if(rcSprite.x >= width){
      speedX = -speedX;
      rcSprite.x -= speedX * diff / 10000;
    }

    if(rcSprite.y >= height){
      speedY = -speedY;
      rcSprite.y -= speedY * diff / 10000;
    }
    log << rcSprite.x << " " << rcSprite.y << "\n";
    /* draw the sprite */
    SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

    /* look for an event */

    if (SDL_PollEvent(&event)) {
      /* an event was found */
      switch (event.type) {
        /* close button clicked */
        case SDL_QUIT:
          gameover = 1;
          break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
              gameover = 1;
              break;
          }
          break;
      }
    }

  }

  log.close();
  /* free the background surface */
  SDL_FreeSurface(sprite);

  /* cleanup SDL */
  SDL_Quit();

  return 0;
}
