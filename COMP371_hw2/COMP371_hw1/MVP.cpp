#include "MVP.h"

void MVP::generateIDs(GL gl) {
	rDepthmatrixID = glGetUniformLocation(gl.depthShaders, "depthMVP");
	rMvpID = glGetUniformLocation(gl.realisticLightShaders, "MVP");
	rViewID = glGetUniformLocation(gl.realisticLightShaders, "V");
	rModelID = glGetUniformLocation(gl.realisticLightShaders, "M");
	rDepthBiasID = glGetUniformLocation(gl.realisticLightShaders, "DepthBiasMVP");
	rShadowMapID = glGetUniformLocation(gl.realisticLightShaders, "shadowMap");

	lightInvDirID = glGetUniformLocation(gl.realisticLightShaders, "LightInvDirection_worldspace");
	sViewID = glGetUniformLocation(gl.simpleLightShaders, "sView");
	sModelID = glGetUniformLocation(gl.simpleLightShaders, "sModel");
	sProjID = glGetUniformLocation(gl.simpleLightShaders, "sProj");

}