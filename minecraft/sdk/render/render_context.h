#pragma once

#include <string>
#include <glm/glm.hpp>

namespace semita {
    class font;
    class rectangle;
    class resource_location;
    class texture_ptr;
    class color;
    class hashed_string;
    class text_measure_data;
    class caret_measure_data;
    enum class text_alignment;

    class minecraft_ui_render_ctx {
    public:
        class client_instance* m_client_instance{};
        class screen_context* m_screen_context{};

        virtual ~minecraft_ui_render_ctx();
        virtual int line_length(font& font, const std::string& text, float max_width, bool some_flag) const;
        virtual float text_alpha() const;
        virtual void set_text_alpha(float alpha);
        virtual void draw_debug_text(const rectangle& area, const std::string& text, const color& color, float alpha, text_alignment alignment, const text_measure_data& text_data, const caret_measure_data& caret_data);
        virtual void draw_text(font& font, const rectangle& area, const std::string& text, const color& primary_color, float alpha, text_alignment alignment, const text_measure_data& text_data, const caret_measure_data& caret_data);
        virtual void flush_text(float delta_time);
        virtual void draw_image(const texture_ptr& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2& uv, const glm::vec2& uv_size, int degree);
        virtual void draw_nine_slice(const texture_ptr& texture, const class nineslice_info& info, int degree);
        virtual void flush_images(const color& color, float opacity, const hashed_string& hashed_string);
        virtual void begin_shared_mesh_batch(class component_render_batch& batch);
        virtual void end_shared_mesh_batch(component_render_batch& batch);
        virtual void draw_rectangle(const rectangle& area, const color& color, float alpha, int thickness);
        virtual void fill_rectangle(const rectangle& area, const color& color, float alpha);
        virtual void increase_stencil_ref();
        virtual void decrease_stencil_ref();
        virtual void reset_stencil_ref();
        virtual void fill_rectangle_stencil(const rectangle& area);
        virtual void enable_scissor_test(const rectangle& area);
        virtual void disable_scissor_test();
        virtual void set_clipping_rectangle(const rectangle& area);
        virtual void set_full_clipping_rectangle();
        virtual void save_current_clipping_rectangle();
        virtual void restore_saved_clipping_rectangle();
        virtual rectangle full_clipping_rectangle() const;
        virtual bool update_custom(void* component);
        virtual void render_custom(void* component, int param, rectangle& area);
        virtual void cleanup();
        virtual void remove_persistent_meshes();
        virtual texture_ptr get_texture(texture_ptr result, const resource_location& location, bool force_reload) const;
        virtual texture_ptr zipped_texture() const;
        virtual bool unload_texture(const resource_location& location);
        virtual class ui_texture_info_ptr ui_texture_info(const resource_location& location, bool force_reload) const;
        virtual void touch_texture(const resource_location& location);
        virtual void flush_images_uv_zero_one_base(const color& color, float opacity, const std::string& debug_name, int param);
        virtual bool has_texture(const resource_location& location) const;
        virtual void snap_image_size_to_grid(glm::vec2& size) const;
        virtual void snap_image_position_to_grid(glm::vec2& position) const;
        virtual void notify_image_estimate(unsigned long long estimate);
    };
}
