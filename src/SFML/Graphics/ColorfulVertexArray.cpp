#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ColorfulVertexArray.hpp>

#include <cassert>


namespace sf
{


ColorfulVertexArray::ColorfulVertexArray(PrimitiveType type, std::size_t vertexCount) : m_vertices(vertexCount), m_primitiveType(type){}
std::size_t ColorfulVertexArray::getVertexCount() const
{
    return m_vertices.size();
}
ColorfulVertex& ColorfulVertexArray::operator[](std::size_t index)
{
    assert(index < m_vertices.size() && "Index is out of bounds");
    return m_vertices[index];
}

void ColorfulVertexArray::clear()
{
    m_vertices.clear();
}
void ColorfulVertexArray::resize(std::size_t vertexCount)
{
    m_vertices.resize(vertexCount);
}
void ColorfulVertexArray::append(const ColorfulVertex& vertex)
{
    m_vertices.push_back(vertex);
}
void ColorfulVertexArray::setPrimitiveType(PrimitiveType type)
{
    m_primitiveType = type;
}
PrimitiveType ColorfulVertexArray::getPrimitiveType() const
{
    return m_primitiveType;
}
FloatRect ColorfulVertexArray::getBounds() const
{
    if (!m_vertices.empty())
    {
        float left   = m_vertices[0].position.x;
        float top    = m_vertices[0].position.y;
        float right  = m_vertices[0].position.x;
        float bottom = m_vertices[0].position.y;

        for (std::size_t i = 1; i < m_vertices.size(); ++i)
        {
            const Vector2f position = m_vertices[i].position;

            // Update left and right
            if (position.x < left)
                left = position.x;
            else if (position.x > right)
                right = position.x;

            // Update top and bottom
            if (position.y < top)
                top = position.y;
            else if (position.y > bottom)
                bottom = position.y;
        }

        return {{left, top}, {right - left, bottom - top}};
    }

    // Array is empty
    return {};
}

void ColorfulVertexArray::draw(RenderTarget& target, RenderStates states) const
{
    if (!m_vertices.empty())
        target.draw(m_vertices.data(), m_vertices.size(), m_primitiveType, states);
}

};

