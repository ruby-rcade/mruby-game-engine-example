// engine.c
#include <simple2d.h>
#include <mruby.h>
#include <mruby/compile.h>

Window *window;
mrb_state *mrb = NULL;

// This is the C method that will be called when draw_square() is called in Ruby
static mrb_value draw_square(mrb_state *mrb, mrb_value value) {
  mrb_int x;
  mrb_int y;
  mrb_int width;
  mrb_get_args(mrb, "iii", &x, &y, &width);

  S2D_DrawQuad(x, y, 1.0, 0, 0, 1,
               x + width, y, 1.0, 0, 0, 1,
               x + width, y + width, 1.0, 0, 0, 1,
               x, y + width, 1.0, 0, 0, 1);
  return value;
}

// This method defines a Ruby method that will be available to us in game.rb
void setup_game_engine(void) {
  struct RClass *module = mrb_define_module(mrb, "Engine");
  mrb_define_class_method(mrb, module, "draw_square", draw_square, ARGS_REQ(3));
}

// This is the method that loads our game.rb file
void load_game_script(void) {
  FILE *f = fopen("game.rb", "r");
  if (f == NULL) {
    puts("Could not find file: game.rb");
    exit(1);
  }
  mrb_load_file(mrb, f);
  fclose(f);
}

// Called once when key is pressed (key repeat causes this to be called multiple times)
void on_key(const char *key) {
  // printf("on_key: %s\n", key);
  char method[64];
  sprintf(method, "on_key_press(\"%s\")", key);
  mrb_load_string(mrb, method); // call the on_key_press method defined in game.rb
}

// Called each iteration while key is being held down
void key_down(const char *key) {
  // printf("key_down: %s\n", key);
  char method[64];
  sprintf(method, "while_key_down(\"%s\")", key);
  mrb_load_string(mrb, method); // call the while_key_down method defined in game.rb
}

void update() {
  // This is our main game loop. Simple2D calls this method 60 times per second.
  // By enforcing a certain frames per second, we prevent this code from running too fast.

  // puts("--------------------");
  // printf("cursor: %i, %i\n", window->cursor_x, window->cursor_y);
  // printf("frames: %i\n", window->frames);
  // printf("total_ms: %i\n", window->total_ms);
  // printf("loop_ms: %i\n", window->loop_ms);
  // printf("delay_ms: %i\n", window->delay_ms);
  // printf("fps: %f\n", window->fps);
}

void render() {
  // Call the render() method defined in game.rb
  mrb_load_string(mrb, "render()");
}

int main(int argc, char const *argv[]) {
  // Initialize MRuby
  mrb = mrb_open();
  // Define Ruby API
  setup_game_engine();
  // Read game.rb file
  load_game_script();
  
  window = S2D_CreateWindow("Example mruby Game Engine", 800, 600, 60, true, update, render, on_key, key_down);
  S2D_Show(window);
  return 0;
}
