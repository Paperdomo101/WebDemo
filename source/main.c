#include <raylib.h>
#include <math.h>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
    #define GLSL_VERSION (100)
#else
    #define GLSL_VERSION (330)
#endif

static int screen_width, screen_height, screen_scale;
static bool recalculate_screen_resolution;
static Shader shd_gradient;
static float hue_timer;

void Init(void);
void Update(void);
void Draw(void);
void Unload(void);
void UpdateDrawFrame(void);

int main(void)
{
    Init();

#ifdef PLATFORM_WEB
    // (main loop function, fps, simulate infinite loop)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
    Unload();
    return 0;
}

void Init(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(BASE_WIDTH * 2, BASE_HEIGHT * 2, PROJECT_NAME);

    SetWindowMinSize(BASE_WIDTH, BASE_HEIGHT);

    shd_gradient = LoadShader(0, TextFormat("assets/gradient%d.frag", GLSL_VERSION));
    recalculate_screen_resolution = true;
}

void Update(void)
{
    hue_timer += GetFrameTime() * 40;

    if (IsWindowResized())
    {
        recalculate_screen_resolution = true;
    }

    if (recalculate_screen_resolution)
    {
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
        screen_scale = fminf(screen_width / (float)BASE_WIDTH, screen_height / (float)BASE_HEIGHT);
        SetShaderValue(shd_gradient, GetShaderLocation(shd_gradient, "resolution"), &(Vector2){screen_width, screen_height}, SHADER_UNIFORM_VEC2);
    }
}

void Draw(void)
{
    ClearBackground(BLACK);

BeginShaderMode(shd_gradient);

    Color top = ColorFromHSV(hue_timer, 1.0, 0.3);
    Color bottom = ColorFromHSV(hue_timer, 0.7, 1.0);

    DrawRectangleGradientV(0, 0, screen_width, screen_height, top, bottom);

EndShaderMode();

    const char *sup_text = "Sup, World!";
    float sup_text_scale = 30 * screen_scale;
    Vector2 sup_text_size = MeasureTextEx(GetFontDefault(), sup_text, sup_text_scale, 3 * screen_scale);
    int sup_text_x = screen_width / 2.0 - sup_text_size.x / 2;
    int sup_text_y = screen_height / 2.0 - sup_text_size.y / 2;

    DrawText(sup_text, sup_text_x, sup_text_y, sup_text_scale, RAYWHITE);

    int padding = 10 * screen_scale;
    DrawText(TextFormat("%s v%s", PROJECT_NAME, PROJECT_VERSION), padding, padding, 10 * screen_scale, RAYWHITE);

    const char *dimensions_text = TextFormat("%dx%d", screen_width, screen_height);

    Vector2 dimensions_text_size = MeasureTextEx(GetFontDefault(), dimensions_text, 10 * screen_scale, screen_scale);

    int dimensions_text_x = screen_width - dimensions_text_size.x - padding;
    int dimensions_text_y = screen_height - dimensions_text_size.y - padding;

BeginBlendMode(BLEND_MULTIPLIED);

    DrawText(dimensions_text, dimensions_text_x, dimensions_text_y, 10 * screen_scale, Fade(BLACK, 0.4));

EndBlendMode();
}

void Unload(void)
{
    UnloadShader(shd_gradient);

#ifdef PLATFORM_WEB
    emscripten_exit_with_live_runtime();
#endif
    CloseWindow();
}

void UpdateDrawFrame(void)
{
    Update();

    BeginDrawing();
        Draw();
    EndDrawing();
}
