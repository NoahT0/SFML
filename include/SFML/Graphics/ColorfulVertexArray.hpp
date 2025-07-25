#pragma once

#include <SFML/Graphics/Export.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>

#include <cstddef>

namespace sf
{
    class RenderTarget;
    // Copy of sf::Vertex but with additional colors
    struct ColorfulVertex
    {
        Vector2f position;          
        Color color{Color::White};
        Vector2f texCoords{}; 
        Color   color2{Color::White};
        Color color3{Color::White};
    };

    // Copy of sf::VertexArray except with ColorfulVertex instead of just Vertex
    class SFML_GRAPHICS_API ColorfulVertexArray : public Drawable
    {
        public:
            ColorfulVertexArray() = default;
            explicit ColorfulVertexArray(PrimitiveType type, std::size_t vertexCount = 0);
            std::size_t getVertexCount() const;
            ColorfulVertex& operator[](std::size_t index);
            void clear();
            void resize(std::size_t vertexCount);
            void append(const ColorfulVertex& vertex);
            void setPrimitiveType(PrimitiveType type);
            PrimitiveType getPrimitiveType() const;
            FloatRect getBounds() const;

        private:
            void draw(RenderTarget& target, RenderStates states) const override;

            std::vector<ColorfulVertex> m_vertices;                             
            PrimitiveType m_primitiveType{PrimitiveType::Points};
    };
};
