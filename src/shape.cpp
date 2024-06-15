#include "shape.h"

Shape::Shape(const ShapeType shapeType) { setup(shapeType); }

void Shape::Draw(const Shader& shader)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Shape::setup(const ShapeType shapeType)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    switch (shapeType)
    {
    case ShapeType::CUBE:
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        break;
    case ShapeType::PYRAMID:
        glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
        break;
    case ShapeType::CUBOID:
        glBufferData(GL_ARRAY_BUFFER, sizeof(cuboidVertices), cuboidVertices, GL_STATIC_DRAW);
        break;
    }

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);
}
