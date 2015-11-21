#include "GL.h"

void GL::importShaders() {
	simpleLightShaders = loadShaders("lightingAndTexture.vs", "lightingAndTexture.fs");
	depthShaders = loadShaders("DepthRTT.vertexshader", "DepthRTT.fragmentshader");
	realisticLightShaders = loadShaders("ShadowMapping.vertexshader", "ShadowMapping.fragmentshader");
}

void GL::prepareGL() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}