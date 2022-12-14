#pragma once
namespace Clap
{
    struct Tile
    {
        uint16_t ID = 0;
        //TODO: PACK THESE WITH BIT INFO

        Tile(uint16_t id = 0)
            : ID(id)
        {}
    };

    template <typename T>
    class TileMap
    {
    public:
        TileMap(uint32_t width, uint32_t height, T tile)
            : m_Width(width), m_Height(height)
        {
            m_Map = new T[width * height];
            for(uint32_t i = 0; i < width * height; i++)
            {
                m_Map[i] = T(tile);
            }
        }

        ~TileMap()
        {
            delete[] m_Map;
        }

        bool InBounds(uint32_t x, uint32_t y)
        {
            return (x >= 0 && x < m_Width) && (y >= 0 && y < m_Height);
        }

        T& At(uint32_t x, uint32_t y)
        {
            if(InBounds(x, y))
                return m_Map[y * m_Width + x];
            T t(0);
            return t;
        }

        uint32_t GetWidth()
        {
            return m_Width;
        }

        uint32_t GetHeigth()
        {
            return m_Height;
        }

        static Ref<TileMap> Create(uint32_t width, uint32_t height, T tile)
        {
            return CreateRef<TileMap>(width, height, tile);
        }

    private:
        uint32_t m_Width = 0, m_Height = 0;
        T* m_Map;
    };
}