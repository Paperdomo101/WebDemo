#include <raylib.h>
#include <math.h>

# ifdef PLATFORM_WEB
#    include <emscripten/emscripten.h>
#    define GLSL_VERSION (100)
# else
#    define GLSL_VERSION (330)
# endif

void Load(void);
void Unload(void);
void Update(void);
void Draw(void);

void UpdateDrawFrame(void);
void CalibrateScreen(void);


static int screen_width;
static int screen_height;
static float screen_scale;

static Shader shd_gradient;
static float hue_timer;


int main(void)
{
    Load();
#ifdef PLATFORM_WEB
    bool simulate_infinite_loop = true;
    int frame_rate = GetMonitorRefreshRate(GetCurrentMonitor());
    emscripten_set_main_loop(UpdateDrawFrame, frame_rate, simulate_infinite_loop);
#else
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
    Unload();
    return 0;
}


void Load(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(BASE_WIDTH, BASE_HEIGHT, PROJECT_NAME);

    SetWindowMinSize(BASE_WIDTH, BASE_HEIGHT);

    shd_gradient = LoadShader(0, TextFormat("assets/gradient%d.frag", GLSL_VERSION));

    CalibrateScreen();
}

void Unload(void)
{
    UnloadShader(shd_gradient);

#ifdef PLATFORM_WEB
    emscripten_exit_with_live_runtime();
#endif
    CloseWindow();
}

void Update(void)
{
    if (IsWindowResized())
    {
        CalibrateScreen();
    }

    hue_timer += GetFrameTime() * 40;
}

void Draw(void)
{
    ClearBackground(BLACK);

    BeginShaderMode(shd_gradient);
        Color top    = ColorFromHSV(hue_timer, 1.0, 0.3);
        Color bottom = ColorFromHSV(hue_timer, 0.7, 1.0);

        DrawRectangleGradientV(0, 0, screen_width, screen_height, top, bottom);
    EndShaderMode();

    int text_scale = 10 * screen_scale;
    int text_padding = 10 * screen_scale;

    DrawText(TextFormat("%s v%s", PROJECT_NAME, PROJECT_VERSION), text_padding, text_padding, text_scale, RAYWHITE);

    const char *sup_text = "Sup, World!";
    Vector2 sup_text_size = MeasureTextEx(GetFontDefault(), sup_text, 3 * text_scale, 3 * screen_scale);
    int sup_text_x = screen_width / 2.0 - sup_text_size.x / 2;
    int sup_text_y = screen_height / 2.0 - sup_text_size.y / 2;

    DrawText(sup_text, sup_text_x, sup_text_y, 3 * text_scale, Fade(WHITE, 0.5));

    const char *dimensions_text = TextFormat("%dx%d", screen_width, screen_height);
    Vector2 dimensions_text_size = MeasureTextEx(GetFontDefault(), dimensions_text, text_scale, screen_scale);
    int dimensions_text_x = screen_width - dimensions_text_size.x - text_padding;
    int dimensions_text_y = screen_height - dimensions_text_size.y - text_padding;

    DrawText(dimensions_text, dimensions_text_x, dimensions_text_y, text_scale, Fade(BLACK, 0.3));
}


void CalibrateScreen(void)
{
    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();
    screen_scale = floorf(fminf(screen_width / (float)BASE_WIDTH, screen_height / (float)BASE_HEIGHT));

    SetShaderValue(shd_gradient, GetShaderLocation(shd_gradient, "resolution"), &(Vector2){screen_width, screen_height}, SHADER_UNIFORM_VEC2);
}

void UpdateDrawFrame(void)
{
    Update();

    BeginDrawing();
        Draw();
    EndDrawing();
}
