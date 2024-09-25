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

// Function to generate noise
float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;

    // Apply the original CRT curvature effect
    uv = uv * 2.0 - 1.0; // Normalize coordinates to -1 to 1
    uv.x *= 1.0 + pow(abs(uv.y), 2.0) * 0.1;
    uv.y *= 1.0 + pow(abs(uv.x), 2.0) * 0.1;
    uv = uv * 0.5 + 0.5; // Re-normalize coordinates back to 0 to 1

    // Fetch the color from the rendered scene using curved UVs
    vec4 sceneColor = texture2D(texture, uv);

    // Apply chromatic aberration with reduced barrel distortion
    float aberration = 0.003;
    vec2 aberrationUV = uv;
    vec4 red = texture2D(texture, aberrationUV + vec2(aberration, 0.0));
    vec4 green = texture2D(texture, aberrationUV);
    vec4 blue = texture2D(texture, aberrationUV - vec2(aberration, 0.0));
    sceneColor = vec4(red.r, green.g, blue.b, 1.0);

    // Apply scanlines
    float scanline = sin(uv.y * resolution.y * 1.5) * 0.04;
    sceneColor.rgb *= 1.0 - scanline;

    // Apply RGB mask (Aperture Grille)
    float grille = mod(gl_FragCoord.x, 3.0);
    sceneColor.r *= 0.9 + 0.1 * step(0.0, grille);
    sceneColor.g *= 0.9 + 0.1 * step(1.0, grille);
    sceneColor.b *= 0.9 + 0.1 * step(2.0, grille);

    // Add subtle flicker
    float flicker = 0.02 * sin(2.0 * 3.1415 * 60.0 * time);
    sceneColor.rgb += flicker;

    // Apply phosphor glow/bloom with reduced intensity
    float glow = smoothstep(0.8, 1.0, sceneColor.rgb);
    sceneColor.rgb += glow * 0.05;

    // Apply static noise
    float noise = (rand(gl_FragCoord.xy + time) - 0.5) * 0.03;
    sceneColor.rgb += noise;

    // Apply vignette effect
    float vignetteStrength = vignette(uv);
    sceneColor.rgb *= mix(1.0, vignetteStrength, 0.3);

    // Clamp the color to prevent overflow
    sceneColor.rgb = clamp(sceneColor.rgb, 0.0, 1.0);

    // Final output color
    gl_FragColor = sceneColor;
}
