#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 resolution;
uniform float time;
uniform sampler2D texture; // The texture containing the rendered scene

// Function to apply vignette effect
float vignette(vec2 uv) {
    vec2 position = uv * 2.0 - 1.0;
    float radius = length(position);
    return smoothstep(0.8, 0.2, radius);
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;

    // Fetch the color from the rendered scene
    vec4 sceneColor = texture2D(texture, uv);

    // Apply a CRT curvature effect
    uv = uv * 2.0 - 1.0; // Normalize coordinates to -1 to 1
    uv.x *= 1.0 + pow(abs(uv.y), 2.0) * 0.1;
    uv.y *= 1.0 + pow(abs(uv.x), 2.0) * 0.1;
    uv = uv * 0.5 + 0.5; // Re-normalize coordinates back to 0 to 1

    // Fetch the distorted color
    sceneColor = texture2D(texture, uv);

    // Apply chromatic aberration
    float aberration = 0.005;
    vec4 red = texture2D(texture, uv + vec2(aberration, 0.0));
    vec4 green = texture2D(texture, uv);
    vec4 blue = texture2D(texture, uv - vec2(aberration, 0.0));
    sceneColor = vec4(red.r, green.g, blue.b, 1.0);

    // Apply noise/grain effect
    float noise = (fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453) - 0.5) * 0.1;
    sceneColor.rgb += noise;

    // Apply vignette effect
    float vignetteStrength = vignette(uv);
    sceneColor.rgb *= mix(1.0, vignetteStrength, 0.1); // Reduced vignette effect

    // Final output color
    gl_FragColor = sceneColor;
}
