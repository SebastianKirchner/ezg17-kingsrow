/**
 * This file is a part of a project from http://zompi.pl/light-shafts/
 * (c) 2014 Damian Nowakowski
 */

#version 330
 
/** Texture coords of occlusion image */
in vec2 inoutTexCoord;

/** Output color of the pixel */
out vec4 outColor;

/** Position of the light source on screen */
uniform vec2 lightScreenPos;

/** Array of textures: 0 - occlusion scene, 1 - normal scene */
uniform sampler2DArray tex;

/**
* This is uniform layout storing all needed light shafts parameters.
* Using this layout application will update the uniform.
*/
struct ShaftsParams
{
    int samples;
	float exposure;
	float decay;
	float density;
	float weight;
};

uniform ShaftsParams params;

void main(void)
{
	// Set the basic color
	outColor = vec4(0.5,0.5,0.5,0.5);

	// Get current texture coordinates.
	vec2 textCoo = inoutTexCoord.xy;
		
	// Calculate the vector that is a one step on vector from lightsource to
	// the pixel of image.
	vec2 deltaTextCoord = textCoo - lightScreenPos;
	deltaTextCoord *= 1.0 / 100 * 0.84;//float(params.samples) * params.density;
 	
	// Set up illumination decay factor.
	float illuminationDecay = 1.0;

	// Evaluate the summation of shadows from occlusion texture
	for(int i=0; i < 100 ; i++)
  	{
		// Step sample location along ray.
		textCoo -= deltaTextCoord;

		// Retrieve sample at new location.  
		vec4 colorSample  = texture(tex, vec3( clamp(textCoo,0,1), 1 ) );
			
		// Apply sample attenuation scale/decay factors.
		colorSample  *= illuminationDecay * 6.65;

		// Accumulate combined color.  
		outColor += colorSample;	

		// Update exponential decay factor.
		illuminationDecay *= 0.995;
 	}

	if (inoutTexCoord.x > lightScreenPos.x - 0.01 && inoutTexCoord.x < lightScreenPos.x + 0.01
		&& inoutTexCoord.y > lightScreenPos.y - 0.01 && inoutTexCoord.y < lightScreenPos.y + 0.01)
		outColor = vec4(1, 0, 0, 1);

	// Output final color with a further scale control factor.
	outColor *= 0.0034;
	
	// Get the avarage of color from calculated light scattering and normal scene.	
	outColor += texture( tex, vec3( inoutTexCoord, 1 ) );
	//outColor *= 0.5;

	
}