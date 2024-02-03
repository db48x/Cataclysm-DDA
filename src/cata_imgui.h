#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <array>

class nc_color;
struct item_info_data;

#if defined(WIN32) || defined(TILES)
struct SDL_Renderer;
struct SDL_Window;
#endif

namespace cataimgui
{
struct bounds {
    float x;
    float y;
    float w;
    float h;
};

enum class mbox_btn {
    BT_OK = 0,
    BT_OKCancel = 1,
    BT_YesNoCancel = 2,
    BT_YesNo = 3
};

enum class dialog_result {
    None = 0,
    OKClicked,
    CancelClicked,
    YesClicked,
    NoClicked
};

enum class text_align {
    Left = 0,
    Center = 1,
    Right = 2
};

class client
{
    public:
        client();
        ~client();

        void new_frame();
        void end_frame();
        void process_input( void *input );
#if !(defined(TILES) || defined(WIN32))
        void upload_color_pair( int p, int f, int b );
        void set_alloced_pair_count( short count );
#else
        static struct SDL_Renderer *sdl_renderer;
        static struct SDL_Window *sdl_window;
#endif
};

class window
{
        std::unique_ptr<class window_impl> p_impl;
        bounds cached_bounds;
    protected:
        explicit window( int window_flags = 0 );
    public:
        explicit window( const std::string &id_, int window_flags = 0 );
        virtual ~window();
        void draw_colored_text( std::string const &text, const nc_color &color,
                                text_align alignment = text_align::Left, float max_width = 0.0F, bool *is_selected = nullptr,
                                bool *is_focused = nullptr, bool *is_hovered = nullptr );
        void draw_colored_text( std::string const &text, nc_color &color,
                                text_align alignment = text_align::Left, float max_width = 0.0F, bool *is_selected = nullptr,
                                bool *is_focused = nullptr, bool *is_hovered = nullptr );
        bool action_button( const std::string &action, const std::string &text );
        bool has_button_action();
        std::string get_button_action();
        bool get_is_open() const;
        virtual void draw();
        virtual void on_resized() {}
        bool is_resized();
        size_t get_text_width( const std::string &text );
        size_t str_width_to_pixels( size_t len );
        size_t str_height_to_pixels( size_t len );
        void mark_resized();

    protected:
        bool is_open;
        std::string id;
        int window_flags;
        std::string button_action;
        virtual bounds get_bounds();
        virtual void draw_controls() = 0;
};

#if !(defined(TILES) || defined(WIN32))
void init_pair( int p, int f, int b );
void load_colors();
#endif

}
