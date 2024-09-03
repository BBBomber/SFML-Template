#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 resolution;
uniform vec3 glowColor;
uniform float glowStrength;
uniform vec2 shapeCenter; // The center of the shape
uniform float shapeRadius; // The radius of the shape (for circles) or half the smallest dimension (for rectangles)

void main() {
    // Calculate the distance from the center of the shape
    float distance = length((gl_FragCoord.xy - shapeCenter) / shapeRadius);

    // Determine the intensity of the glow based on the distance
    // The first smoothstep defines the outer edge of the glow, the second defines the inner edge.
    float glowEdge = smoothstep(0.5, 0.6, distance);

    // Apply the glow color at the edge
    vec4 glow = vec4(glowColor, glowEdge * glowStrength);

    // Calculate the original shape color
    float shapeIntensity = 1.0 - smoothstep(0.0, 0.5, distance);

    // Combine the glow with the original shape color
    vec4 shapeColor = vec4(1.0, 1.0, 1.0, 1.0) * shapeIntensity;
    gl_FragColor = shapeColor + glow;

    // Ensure the alpha is at maximum
    gl_FragColor.a = 1.0;
}
