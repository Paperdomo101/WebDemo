#version 100
// Smooth gradient shader based on this : https://shader-tutorial.dev/advanced/color-banding-dithering/
precision highp float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform vec2 resolution;

const float NOISE_GRANULARITY = 0.5/255.0;

float random(vec2 coords) {
    return fract(sin(dot(coords.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 coordinates = gl_FragCoord.xy / resolution;

    vec3 fragmentColor = fragColor.rgb;
    fragmentColor.rgb += vec3(mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(coordinates)));

    gl_FragColor = vec4(fragmentColor, fragColor.a);
}
