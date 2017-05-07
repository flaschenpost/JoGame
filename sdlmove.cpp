#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <unistd.h>
using namespace std;

#define SCREEN_WIDTH  1800
#define SCREEN_HEIGHT 980
#define SPRITE_SIZE    32

int main ( int argc, char *argv[] )
{
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  ofstream log;
  log.open("log.txt", ios::out);


  SDL_Window *screen = SDL_CreateWindow("JoGame00",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL);

  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);

  SDL_Rect rcSprite, rcOld, rcBackground;
  SDL_Event event;
  Uint8 *keystate;

  int gameover;


  /* load sprite */
  IMG_Init(IMG_INIT_PNG);
  SDL_Surface *temp   = IMG_Load("kopp.png");
  SDL_Texture *sprite = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);

  SDL_QueryTexture(sprite, NULL, NULL, &rcSprite.w, &rcSprite.h);
  log << rcSprite.w << " "<< rcSprite.h << "\n";

  /* setup sprite colorkey and turn on RLE */
  SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0xFF, 0xFF);

  /* load background */
  temp  = IMG_Load("back.png");
  SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);
  IMG_Quit();

  double posX = 100.0;
  double posY = 80.0;

  
  uint32_t width = SCREEN_WIDTH - rcSprite.w;
  uint32_t height = SCREEN_HEIGHT - rcSprite.h;

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
  SDL_QueryTexture(sprite, NULL, NULL, &rcBackground.w, &rcBackground.h);

  SDL_RenderCopy(renderer, background, NULL, NULL);

  /* draw the sprite */
  SDL_RenderCopy(renderer, sprite, NULL, &rcSprite);
  SDL_RenderPresent(renderer);

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
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderCopy(renderer, sprite, NULL, &rcSprite);
    SDL_RenderPresent(renderer);

  }

  log.close();

  /* cleanup SDL */
  SDL_Quit();

  return 0;
}
