#version 330
 
in vec2 fragTexCoord;
out vec4 outColor;

const int samples = 100;
const float exposure = 0.0034;
const float decay = 0.995;
const float density = 0.84;
const float weight = 6.65;

uniform vec2 lightPosScreenSpace;

// 0 - occlusion, 1 - normal scene 
uniform sampler2DArray tex;

void main(void)
{
	outColor = vec4(0.5,0.5,0.5,0.5);

	vec2 currentTextCoord = fragTexCoord.xy;
	vec2 deltaTextCoord = currentTextCoord - lightPosScreenSpace;
	deltaTextCoord *= 1.0 / float(samples) * density;
 	

	float illuminationDecay = 1.0;

	// Evaluate the summation of shadows from occlusion texture
	for(int i=0; i < samples ; i++)
  	{
		currentTextCoord -= deltaTextCoord; 
		vec4 colorSample  = texture(tex, vec3( clamp(currentTextCoord,0,1), 0 ) );
		colorSample  *= illuminationDecay * weight;
		outColor += colorSample;	
		illuminationDecay *= decay;
 	}

	outColor *= exposure;	
	outColor += texture( tex, vec3(fragTexCoord, 1) );
	outColor *= 0.5;	
}