//
//  TileMap.hpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include "NormalTile.hpp"
#include "Entity.hpp"
#include "EnemySystem.hpp"
#include "EnemySpawner.hpp"

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
    
    //Accessors
    const sf::Texture* getTileSheet() const;
    const bool TileEmpty(const int x, const int y, const int z) const;
    const bool checktype(const int x, const int y, const int z, const int type) const;
    const int getLayerSize(const int x, const int y, const int layer) const;
    const sf::Vector2i& getMaxSizeGrid() const;
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
