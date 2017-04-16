#include <iostream>
#include <fstream>
#include <SDL/SDL_image.h>
#include <unistd.h>
using namespace std;

#define SCREEN_WIDTH  1800
#define SCREEN_HEIGHT 980
#define SPRITE_SIZE    32

int main ( int argc, char *argv[] )
{
  ofstream log;
  log.open("log.txt", ios::out);

  SDL_Surface *screen, *temp, *sprite, *background;
  SDL_Rect rcSprite, rcOld, rcBackground;
  SDL_Event event;
  Uint8 *keystate;

  int colorkey, gameover;

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Test", "SDL Test");

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* load sprite */
  temp   = IMG_Load("kopp.png");
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  log << rcSprite.w << " "<< rcSprite.h << "\n";

  rcSprite.w = sprite->w;
  rcSprite.h = sprite->h;

  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  /* load background */
  temp  = IMG_Load("back.png");
  background = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  double posX = 100.0;
  double posY = 80.0;

  
  uint32_t width = SCREEN_WIDTH - sprite->w;
  uint32_t height = SCREEN_HEIGHT - sprite->h;

  srand(12643l);

  rcSprite.x = posX;
  rcSprite.y = posY;

  double speedX = 2 + 5 * static_cast<float>(rand()) / static_cast<float> (RAND_MAX);
  double speedY = 1 + 2 * static_cast<float>(rand()) / static_cast<float> (RAND_MAX);

  log << "speedX: " << speedX << "\n";
  log << "speedY: " << speedY << "\n";

  Uint32 lastTime = SDL_GetTicks(); 
  rcBackground.x = 0;
  rcBackground.y = 0;
  rcBackground.w = background->w;
  rcBackground.h = background->h;

  SDL_BlitSurface(background, NULL, screen, &rcBackground);

    /* draw the sprite */
    SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);

  gameover = 0;

  /* message pump */
  while (!gameover)
  {
    Uint32 now = SDL_GetTicks(); 
    Uint32 diff = now - lastTime;

    log << "diff = " << diff << "\n";
    lastTime = now;
    rcOld = rcSprite;

    double deltaX = 0.1 * speedX * diff;
    double deltaY = 0.1 * speedY * diff;

    if(posX + deltaX < width && posX + deltaX > 0){
      posX += deltaX;
      rcOld.w += deltaX;
    }
    else{
      speedX = -speedX;
    }
    if(posY + deltaY < height && posY + deltaY > 0){
      posY += deltaY;
      rcOld.h += deltaY;
    }
    else{
      speedY = -speedY;
    }

    rcSprite.x = posX;
    rcSprite.y = posY;

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
            case SDLK_UP:
              speedY -= 0.5;
              break;
            case SDLK_DOWN:
              speedY += 0.5;
              break;
            case SDLK_RIGHT:
              speedX += 0.5;
              break;
            case SDLK_LEFT:
              speedX -= 0.5;
              break;
            case SDLK_l:
              speedX *= 0.8;
              speedY *= 0.8;
              break;
            case SDLK_s:
              speedX *= 1.2;
              speedY *= 1.2;
              break;

          }
          break;
      }
    }


    /* draw the sprite */
    SDL_BlitSurface(background, NULL, screen, &rcBackground);
    SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

    /* update the screen */
    //  SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_UpdateRect(screen, rcOld.x, rcOld.y, rcSprite.w, rcSprite.h);
  }

  log.close();
  /* free the background surface */
  SDL_FreeSurface(sprite);

  /* cleanup SDL */
  SDL_Quit();

  return 0;
}
