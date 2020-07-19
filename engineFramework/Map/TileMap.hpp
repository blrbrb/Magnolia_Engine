//
//  TileMap.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef TileMap_hpp
#define TileMap_hpp
#include "Tiles_Include.h"
#include "Entity.hpp"
#include "Enemies_Include.h"


class EnemySpawner; 
class Tile;
class NormalTile; 
class Entity;


class TileMap
{
private:
    
    unsigned grid_sizeU;
    float grid_sizeF;
    int gridsizeI; 
    int layers;
    
    xmlDocPtr xml_doc;
    xmlNodePtr node;
    
    void parsemap(xmlDocPtr doc, xmlNodePtr node);
     void parsedoc(char *docname);

    std::string texture_file;
    sf::Vector2i MaxSizeWorldGrid;
    sf::Vector2f MaxSizeWorld_F;
    
    //Defered Render stack thingy
    std::stack<Tile*> renderdefered;
    
   
    
    sf::RectangleShape physicsrect; 
   
    //TileMap vector
    std::vector< std::vector< std::vector< std::vector< Tile* > > > > Map;
    
    sf::Font font; 
    
    sf::Texture tileTextureSheet;
    //Private Functions
    void clear();
  
    //tile culling
    int FromX;
    int ToX;
    int ToY;
    int FromY;
    int layer;
    
    //tile shader culling
    
public:
    
    TileMap(float gridSize, int width, int height, std::string texture_file);
    TileMap(const std::string map_file);
    virtual ~TileMap();
    
    
    //Variables
    bool  lock_layer;
    bool isEntityColliding; 
    
    
    const sf::Texture* getTileSheet() const;
    /// TileEmpty
    /// @brief Return wether or not a particular tile in the four dimensional vector is null
    /// @param x the X-axis of the vector (width in tiles)
    /// @param y the Y-axis of the vector (height in tiles)
    /// @param z the Z-axis of the vector (depth)
    ///@returns const bool wether or not a certian tile is empty
    const bool TileEmpty(const int x, const int y, const int z) const;
    /// checktype
    /// @brief Get the type of a particular tile in the four dimensional vector
    /// @param x the X-axis of the vector (width in tiles)
    /// @param y the Y-axis of the vector (height in tiles)
    /// @param z the Z-axis of the vector (depth)
    /// @param type to check for
    ///@returns wether or not a certian tile is of the same type being checked for
    const bool checktype(const int x, const int y, const int z, const int type) const;
    /// getLayerSize
    /// @brief get how many tiles are placed on the Z-axis (depth) of the tilemap vector in a certian spot.
    /// @param x the X-axis of the vector (width in tiles)
    /// @param y the Y-axisof the vector (height in tiles)
    /// @param layer  of the Z-component
    ///@returns const int how many tiles are placed on the Z-axis in a particular place
    const int getLayerSize(const int x, const int y, const int layer) const;
    /// getMaxSizeGrid
    ///@brief Helper function to find the Maximum size of the map in tiles
    ///@returns the Maximum size of the map in tiles
    const sf::Vector2i& getMaxSizeGrid() const;
    /// getMaxSize
    ///@brief Get the Maximum size (in pixels) of the map
    ///@returns the maximum size of the map
    const sf::Vector2f getMaxSize() const;
   
    
    
    //Functions
    void RemoveTile(const int x, const int y, const int z, const int type);
    void savetofile(const std::string filename);
    void loadfromfile(const std::string filename);
   
    
   
    
    //render functions
    void render(sf::RenderTarget& target, const sf::Vector2i& gridposition, const bool render_collision = false, sf::Shader* shader = NULL,const sf::Vector2f PlayerPosition = sf::Vector2f());
    void DefferedRender(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f PlayerPosition = sf::Vector2f());
    void renderlighttile(sf::RenderTarget& target, sf::Shader* shader = NULL);
   
    //Modifiers
    void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type);
    void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance );
  
    
    //update functions
    void update(Entity* entity, const float& dt);
    void updateWorldBoundsCollision(Entity* entity, const float& dt);
    void updateTiles(Entity* entity, const float& dt, EnemySystem& enemysystem);
    void updateTileCollision(Entity* entity, const float& dt);
    
    
    
};



#endif /* TileMap_hpp */
