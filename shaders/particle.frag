#version 450

layout(location = 0) in vec4 fragColor;
layout(location = 0) out vec4 outColor;

void main()
{
    // Coordinates range from 0 to 1.
    // Convert them to -1 to 1.
    vec2 coord = gl_PointCoord * 2.0 - 1.0;

    // Distance from particle center.
    float distanceFromCenter = length(coord);

    // Discard fragments outside the circle.
    if (distanceFromCenter > 1.0)
    {
        discard;
    }

    // Core of the particle.
    float core = 1.0 - smoothstep(
        0.0,
        0.45,
        distanceFromCenter
    );

    // Outer glow.
    float glow = 1.0 - smoothstep(
        0.25,
        1.0,
        distanceFromCenter
    );

    // Combine core and glow.
    float alpha = max(
        core,
        glow * 0.45
    );

    // Slightly brighten the center.
    vec3 color = fragColor.rgb * (1.0 + core * 1.5);

    outColor = vec4(color, alpha * fragColor.a);
}
