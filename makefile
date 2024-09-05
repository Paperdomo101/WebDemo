# i.e. https://itch-user.itch.io/itch-page
ITCH_USER = "itch-user"
ITCH_PAGE = "itch-page"

PROJECT_NAME 	= "Game"
PROJECT_VERSION = "1.0"
BASE_WIDTH 	=  240
BASE_HEIGHT 	=  160

# Define PROJECT_NAME, PROJECT_VERSION, and resolution variables for use in code
DEFINES = -DPROJECT_NAME=\"$(PROJECT_NAME)\" \
	  -DPROJECT_VERSION=\"$(PROJECT_VERSION)\" \
	  -DBASE_WIDTH=$(BASE_WIDTH) \
	  -DBASE_HEIGHT=$(BASE_HEIGHT)

# Search source folder and subfolders for .c files
CFILES = $(wildcard source/*.c source/*/*.c)

INCLUDES = -Iinclude/
LIBRARIES = -lraylib

# Optimized for size | Warnings for all errors | Link with WASM Raylib | add assets folder to index.data | compatibility flags
WEB_OPT = -Os -Wall -Linclude/web $(LIBRARIES) --shell-file include/web/shell.html --preload-file assets -DPLATFORM_WEB -s USE_GLFW=3 -s GL_ENABLE_GET_PROC_ADDRESS
WEB_OUT = "build/index.html"
WEB_ZIP = "$(PROJECT_NAME)_v$(PROJECT_VERSION)_web.zip"

EMSDK_PATH = /path/to/emsdk

# Use `emrun --list_browsers` for more options
BROWSER = firefox

web_build:
	mkdir -p build && \
	cd $(EMSDK_PATH) && source ./emsdk_env.sh && cd ${PWD} && \
	emcc -o $(WEB_OUT) $(DEFINES) $(CFILES) $(INCLUDES) $(WEB_OPT)

web_run:
	cd $(EMSDK_PATH) && source ./emsdk_env.sh && cd ${PWD} && \
	emrun $(WEB_OUT) --browser $(BROWSER)

web_zip:
	cd build && zip $(WEB_ZIP) index.*

# Build and run in browser
test_web: web_build web_run

# Build and zip for itch.io
release_web: web_build web_zip

# Publish directly to itch.io (you will need to install and login to butler)
publish_web:
	butler push build/$(WEB_ZIP) $(ITCH_USER)/$(ITCH_PAGE):web --userversion $(PROJECT_VERSION)
