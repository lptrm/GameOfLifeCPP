#include "RenderCommand.h"
#include "OpenGLRendererAPI.h"
#include "RendererAPI.h"

RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
