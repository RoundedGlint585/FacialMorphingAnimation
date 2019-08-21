#version 330 core
const int layoutCount = 3;// count of expressions
const int coefsCount = layoutCount - 1;//one layout for rest pose
layout (location = 0) in vec3 positions[layoutCount];
layout (location = 2) in vec3 normals[layoutCount];

out vec3 pos;
out vec3 normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float coefs[coefsCount];

void main()
{
    float coefSum = 0.f;
    for (int i = 0; i < coefsCount; i++){
        coefSum += coefs[i];
    }
    float neutralCoef = 1.0f - coefSum;
    clamp(neutralCoef, 0.0f, 1.0f);

    vec3 finalPos = positions[0] * neutralCoef/(coefSum+neutralCoef);

    for (int i = 1; i < layoutCount; i++){
        finalPos = finalPos  + positions[i]*(coefs[i-1]/(coefSum+neutralCoef));
    }


    gl_Position = projection * view * model * vec4(finalPos, 1.0f);

    float coef = coefs[0];


    pos = vec3(model * vec4(finalPos, 1.0));
    normal = (normals[1]);// definetly something wrong here, possible layout bug
}
