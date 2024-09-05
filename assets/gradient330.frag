#version 330
// Smooth gradient shader based on this : https://shader-tutorial.dev/advanced/color-banding-dithering/
precision highp float;

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 resolution;

// Output fragment color
out vec4 finalColor;

const float NOISE_GRANULARITY = 0.5/255.0;

float random(vec2 coords) {
    return fract(sin(dot(coords.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 coordinates = gl_FragCoord.xy / resolution;

    vec3 fragmentColor = fragColor.rgb;
    fragmentColor.rgb += vec3(mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(coordinates)));

    finalColor = vec4(fragmentColor, fragColor.a);
}
