#include <stdlib.h>
#include <stdio.h>
#include <mruby.h>
#include <mruby/compile.h>
#include "SDL.h"

bool logging = true;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
mrb_state *mrb = NULL;

int x = 0;
int y = 0;

bool setup_sdl();
void cleanup_sdl();
void setup_game_engine();
void load_game_script();
void begin_run_loop();

int main(void)
{
  // Initialize SDL
  if (!setup_sdl()) return 1;

  // Initialize MRuby
  mrb = mrb_open();

  // Define Ruby API
  setup_game_engine();

  // Read game.rb file
  load_game_script();

  // Begin rendering and responding to input
  begin_run_loop();

  // Cleanly close SDL window
  cleanup_sdl();
  return 0;
}

bool setup_sdl(void)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
    return false;
  }

  // Create a window
  window = SDL_CreateWindow(
    "MRuby Game Engine Example", // window title
    0, // x
    0, // y
    640, // width
    480, // height
    0 // SDL_WINDOW_FULLSCREEN or SDL_WINDOW_FULLSCREEN_DESKTOP for single screen
  );

  // Check if window was created successfully
  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return false;
  }

  // Initialize a rendering surface
  screenSurface = SDL_GetWindowSurface(window);
  return true;
}

void cleanup_sdl(void)
{
  if (logging) puts("cleanup_sdl called");
  SDL_DestroyWindow(window);
  SDL_Quit();
}

static mrb_value draw_square(mrb_state *mrb, mrb_value value)
{
  if (logging) puts("draw_square called");
  
  // mrb_int x;
  // mrb_int y;
  // mrb_int width;
  // mrb_get_args(mrb, "iii", &x, &y, &width);
  SDL_Rect rect = {x, y, 100, 100};
  SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
  return value;
}

void setup_game_engine(void)
{
  // if (logging) puts("setup_game_engine called");
  struct RClass *module = mrb_define_module(mrb, "Engine");
  mrb_define_class_method(mrb, module, "draw_square", draw_square, ARGS_REQ(3));
}

void load_game_script(void)
{
  FILE *f = fopen("game.rb", "r");
  if (f == NULL) {
    puts("Could not find file: game.rb");
    exit(1);
  }
  mrb_load_file(mrb, f);
  fclose(f);
}

void begin_run_loop(void)
{
  SDL_Event event;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);

  // Begin run loop
  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
        return;
      }
      switch(event.type) {
        // Single key press events
        case SDL_KEYDOWN:
          // if (event.key.keysym.sym == SDLK_LEFT)  x--; //{ key = "left"; code = "input_received(:left)"; }
          // if (event.key.keysym.sym == SDLK_RIGHT) x++; //{ key = "right"; code = "input_received(:right)"; }
          // if (event.key.keysym.sym == SDLK_UP)    y--; //{ key = "up"; code = "input_received(:up)"; }
          // if (event.key.keysym.sym == SDLK_DOWN)  y++; //{ key = "down"; code = "input_received(:down)"; }
          // printf("Key down: %s\n", key);
          // mrb_load_string(mrb, code);
          break;

        case SDL_KEYUP:
          break;
      }
    }
    
    if (keystates[SDL_SCANCODE_LEFT])  x--; //mrb_load_string(mrb, "input_received(:left)");
    if (keystates[SDL_SCANCODE_RIGHT]) x++; //mrb_load_string(mrb, "input_received(:right)");
    if (keystates[SDL_SCANCODE_UP])    y--; //mrb_load_string(mrb, "input_received(:up)");
    if (keystates[SDL_SCANCODE_DOWN])  y++; //mrb_load_string(mrb, "input_received(:down)");

    // Create white background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    
    // Call render() defined in game.rb
    mrb_load_string(mrb, "render()"); // FIXME: This line is causing errors
  
    SDL_UpdateWindowSurface(window);
  }
}
