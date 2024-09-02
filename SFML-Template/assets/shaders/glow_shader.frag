#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;
uniform vec2 resolution;
uniform vec3 glowColor;
uniform float glowStrength;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec4 baseColor = texture2D(texture, uv);

    // Calculate distance from the center of the object
    float distance = length(uv - 0.5);

    // Determine the intensity of the glow based on distance
    float intensity = smoothstep(0.4, 0.5, distance);

    // Apply the glow color
    vec4 glow = vec4(glowColor, 1.0) * intensity * glowStrength;

    // Combine the base color with the glow
    gl_FragColor = baseColor + glow;
}
