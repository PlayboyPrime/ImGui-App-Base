#pragma once

namespace tabs
{
	namespace credits
	{
		inline bool state = true;
		void render();
	}

	namespace settings
	{
		void render();
	}

	namespace welcome
	{
		inline bool state = true;
		void render();
	}

#ifdef _DEBUG
	namespace debug
	{
		inline bool about_window = false;
		inline bool debug_log_window = false;
		inline bool demo_window = false;
		inline bool font_selector_window = false;
		inline bool id_stacktool_window = false;
		inline bool metrics_window = false;
		inline bool stacktool_window = false;
		inline bool style_editor_windww = false;
		inline bool user_guide = false;

		inline bool state = true;
		void render();
	}
#endif
}