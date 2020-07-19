//
//  TileMap.cpp
//  engineFramework
//
//  Created by Eli Reynolds on 2/6/20.
//  Copyright © 2020 Eli Reynolds. Apache License .
//


#include "TileMap.hpp"



void TileMap::clear()
{
    //symmetry orgasim
    if(!this->Map.empty())
    {
        for (int x=0; x < this->Map.size(); x++ )
             {
                 for (int y=0; y < this->Map[x].size(); y++ )
                 {
                     for (int z=0; z < this->Map[x][y].size(); z++ )
                     {
                         for (size_t k=0; k < this->Map[x][y][z].size(); k++)
                         {
                               delete this->Map[x][y][z][k];
                               this->Map[x][y][z][k] = NULL;
                         }
                         this->Map[x][y][z].clear();
                     }
                     this->Map[x][y].clear();
                 }
                 this->Map[x].clear();
             }
        this->Map.clear();
        
        std::cout << "Map Local Memory Size: " << " " << this->Map.size();
    }
}





TileMap::TileMap(float gridSize, int width, int height, std::string texture_file) {
    
    
   /*!
     @brief   Default Constructor. Initalizes the tileMap as a 4d Vector of Tiles
    
     @param   float   gridSize    The gridsize for the TileMap
    
     @param   int     width       The width of the TileMap vector
    
     @param   int     height      The height of the TileMap vector
    
     @param   std::string     texture_file        The texturefile to load Tiles From
    
            */
   
    this->grid_sizeF = gridSize;
    this->grid_sizeU = static_cast<unsigned>(gridSize);
    this->gridsizeI = static_cast<int>(gridSize);
    this->lock_layer = false;
    this->MaxSizeWorldGrid.x = width;
    this->MaxSizeWorldGrid.y = height;
    this->layers = 1;
    this->texture_file = texture_file;
    this->MaxSizeWorld_F.x = static_cast<float>(width) * gridSize;
    this->MaxSizeWorld_F.y = static_cast<float>(height) * gridSize;

    //Tile Culling Vars
    
    this->ToX = 0;
    this->FromX = 0;
    this->ToY = 0;
    this->FromY = 0;
    this->layer = 0;

    this->Map.resize(this->MaxSizeWorldGrid.x, std::vector< std::vector< std::vector <Tile* > > >());
    
    for (int x = 0; x < this->MaxSizeWorldGrid.x; x++ )
    {
        
        for (int y = 0; y < this->MaxSizeWorldGrid.y; y++ )
        {
            this->Map[x].resize(this->MaxSizeWorldGrid.y,std::vector< std::vector <Tile*> > ());
  
            for (int z = 0; z < this->layers; z++ )
            {
                
                this->Map[x][y].resize(this->layers, std::vector<Tile*>());
                
            }
            
        }
    
    }
    
    this->tileTextureSheet.loadFromFile(resourcePath() + texture_file);
    
         this->physicsrect.setSize(sf::Vector2f(grid_sizeF,grid_sizeF));
         this->physicsrect.setFillColor(sf::Color::Transparent);
         this->physicsrect.setOutlineColor(sf::Color::Red);
         this->physicsrect.setOutlineThickness(1.f);
    
}



TileMap::TileMap(const std::string map_file)
{
    
      this->ToX = 0;
      this->FromX = 0;
      this->ToY = 0;
      this->FromY = 0;
      this->layer = 0;

    
     this->loadfromfile(map_file);
     
      
     
      
}


TileMap::~TileMap()
{
   
    this->clear();
}

        

//Functions
void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridposition, const bool render_collision, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{
    
   /*!
        @brief   Default render
       
        @param   sf::RenderTarget&     target       The intended render target
       
        @param   const sf::Vector2i&     gridposition     The gridposition.
       
        @param   const bool     render_collision        The boolean value that determines wether or not to render tiles with their respective
                                                        collision boxes
        @param   sf::Shader*      shader      Optional shader to use in the render
       
        @param   const sf::Vector2f       PlayerPosition      Supply this value only if a shader is intended to be rendered onto the tileMap.
       
                */
    
        this->layer = 0;
        
    this->FromX = gridposition.x - 15;
       
           if(this->FromX < 0)
               this->FromX = 0;
           else if (this->FromX > this->MaxSizeWorldGrid.x)
               this->FromX = this->MaxSizeWorldGrid.x;
       
       this->ToX = gridposition.x + 15;
       
           if(this->ToX < 0)
                      this->ToX = 0;
                  else if (this->ToX > this->MaxSizeWorldGrid.x)
                      this->ToX = this->MaxSizeWorldGrid.x;
          
       this->FromY = gridposition.y - 15;
       
           if(this->FromY < 0)
                      this->FromY = 0;
                  else if (this->FromY > this->MaxSizeWorldGrid.x)
                      this->FromY = this->MaxSizeWorldGrid.x;
          
       this->ToY = gridposition.y + 15;
       
           if(this->ToY < 0)
                this->ToY = 0;
           else if (this->ToY > this->MaxSizeWorldGrid.y)
           
               this->ToY = this->MaxSizeWorldGrid.y;

           
    

       for (int x = this->FromX; x < this->ToX; x++ )
       {
           for (int y = this->FromY; y < this->ToY; y++ )
           {
               for (size_t k=0; k < this->Map[x][y][this->layer].size(); k++)
               {
                  
                   this->renderlighttile(target);
                   
                   if(this->Map[x][y][this->layer][k]->gettype() == TileTypes::OBJECT)
                   {
                       this->renderdefered.push(this->Map[x][y][this->layer][k]);
                   }
                   
                   
                //render w/ shader applied
                   if (shader)
                   {
                       
                       this->Map[x][y][this->layer][k]->render(target, shader, PlayerPosition);
                       
                   }
                   else
                   {
                       this->Map[x][y][this->layer][k]->render(target);
                       
                   }
                   
                    
                    //render the collision box
                   if (render_collision)
                   {
                       if (this->Map[x][y][this->layer][k]->getCollision())
                        {
                            this->physicsrect.setPosition(this->Map[x][y][this->layer][k]->getposition());
                            target.draw(this->physicsrect);
                        }
                    
                   }
                   
                 
                   
                   if(this->Map[x][y][this->layer][k]->gettype() == TileTypes::SPAWNER)
                   {
                       this->physicsrect.setPosition(this->Map[x][y][this->layer][k]->getposition());
                       this->physicsrect.setFillColor(sf::Color(50,20,10,100));
                       this->physicsrect.setFillColor(sf::Color::Red);
                       this->physicsrect.setOutlineThickness(1.f);
                       target.draw(this->physicsrect);
                       
                   }
               
               
               
               
               
               
               }
               
               
           }
          
       }
    
}

    



void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool& collision, const short& type )
{
/*!
 @brief  Add a tile to the TileMap

 @param   const int   x   The X-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x]

 @param   const int   y   The Y-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x][y]

 @param   const int   z   The Z-value (relative to the Tilemap vector) to place a tile on e.g. TileMap[x][y][z]

 @param   const sf::IntRect   texture_rect    The texture rectangle from the TileSheet texture to paste.

 @param   const bool&   collision   The boolean value that controlls wether or not a placed tile will have collision.

 @param   const short&   type    The enumerator value representing the type of tile placed.

 @return void


   */
    
    if ( x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0 )
    {
             /*if okay to add tile*/
            //and if the type of tile is NORMAL add normal til
              this->Map[x][y][z].push_back(new NormalTile(type,x, y, this->grid_sizeF , this->tileTextureSheet, texture_rect, collision));
    }
    
    else if (!x || !y || !z)
    {
        throw std::invalid_argument("Invalid Argument : Tile Does Not Exist");
        
    }
    
}
    







void TileMap::RemoveTile(const int x, const int y, const int z, const int type)
{
    
    if ( x < this->MaxSizeWorldGrid.x && x >= 0 && y < this->MaxSizeWorldGrid.y && y >= 0 && z < this->layers && z >= 0 )
       {
           if (!this->Map[x][y][z].empty())
           {
               
               if (this->Map[x][y][z].back()->gettype() == type)
               {
    
                   delete this->Map[x][y][z][this->Map[x][y][z].size() - 1];
                   this->Map[x][y][z].pop_back();
                   std::cout << "Spawner Removed" << std::endl;
                   
               }
               else
               {
                   
                   delete this->Map[x][y][z][this->Map[x][y][z].size() - 1];
                    this->Map[x][y][z].pop_back();
                   std::cout << "TIle Removed" << std::endl;
                   
                   
               }
    
           }
           
       }
    
    
}

const sf::Texture* TileMap::getTileSheet() const
{
    return &this->tileTextureSheet;
}

void TileMap::savetofile(const std::string filename)
{
    
/*!
  @brief  Saves a vector of tiles as a string of integers to a document.
 
  @param   const std::string filename   the name of the file to create and save to.
 
  @discussion
        Maxsize of the Vector:
        Size of the tile grid:
        texture rect value of the tiles at position x, y, z:
        collision value of the tiles at position x, y, z:
        type of the tiles at position x, y, z:
 
  @return void
 
    */
    
    std::ofstream out;
    
       
    out.open(filename);
    
    if (out.is_open())
    {
        out << this->MaxSizeWorldGrid.x << " " << this->MaxSizeWorldGrid.y << "\n"
        << this->gridsizeI << "\n"
        << this->layers << "\n"
        << this->texture_file << "\n";
        
        for (int x=0; x < this->MaxSizeWorldGrid.x; x++ )
        {
            for (int y=0; y < this->MaxSizeWorldGrid.y; y++ )
            {
                for (int z=0; z < this->layers; z++ )
                {
                    if(!this->Map[x][y][z].empty())
                    {
                        for(size_t k=0; k < this->Map[x][y][z].size(); k++)
                        {
                    
                           out << x << " " << y << " " << z << " " << this->Map[x][y][z][k]->asString() << " "; // dont save this last space
                            
                        }
                    }
                    
                }
                
            }
        
        }
    
    }

    else
    {
        std::cout << "ERROR CODE TILEMAP:392 || TILEMAP::SAVETOFILE || COULD NOT SAVE" << std::endl;
        
        throw std::runtime_error("ERROR CODE TILEMAP:392 || TILEMAP::SAVETOFILE || COULD NOT SAVE");
        
    }
    
    out.close();
    

    //exeption handling block
    

}


void TileMap::parsemap(xmlDocPtr doc, xmlNodePtr node)
{
    
    xmlChar* key;
    xmlChar* width;
    xmlChar* height;
    
    node = node->xmlChildrenNode;
    
    while(node != NULL)
    {
        
    if ((!xmlStrcmp(node->name, (const xmlChar *)"map")))
    {
        key = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);


        std::wcout << key << std::endl;
        std::cout << "butthole" << std::endl; 
        
        xmlFree(key);
    }
        
    if ((!xmlStrcmp(node->name, (const xmlChar *)"width")))
    {
        width = xmlGetProp(node, width);
        
        std::cout << width << std::endl;
        
      std::cout << key << std::endl;
      xmlFree(key);
    }
       
     node = node->next;
}
    return;
}



void TileMap::parsedoc(char *docname)
{
    
    
    this->xml_doc = xmlParseFile(docname);
    
    if (this->xml_doc == NULL )
    {
        
    fprintf(stderr,"Document not parsed successfully. \n");
    return;
        
    }
       this->node = xmlDocGetRootElement(this->xml_doc);
    
    if (this->node == NULL)
    {
        
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(this->xml_doc);
        return;
        
    }
    
    if (xmlStrcmp(node->name, (const xmlChar *) "map"))
    {
        fprintf(stderr,"document of the wrong type, root node != map");
        xmlFreeDoc(this->xml_doc);
        return;
    }
    
    this->node = node->xmlChildrenNode;
    
    while (node != NULL)
    {
        if ((!xmlStrcmp(node->name, (const xmlChar *)"storyinfo")))
        {
            this->parsemap(this->xml_doc, this->node);
        }
            this->node = node->next;
    }
    
    
    
    xmlFreeDoc(this->xml_doc);
    return;
    
    
    
    
}

void TileMap::loadfromfile(const std::string filename)
{
   
    

     
  std::ifstream in;
    
    in.open(filename);
    
    if (in.is_open())
   
    {
        sf::Vector2i size;
        int gridsize = 0;
        int layers = 0;
        std::string texture_file = "";
        int x = 0;
        int y = 0;
        int z = 0;
        int textureX = 0;
        int textureY = 0;
        bool collision = false;
        short type = 0;
        
        //Basic Variables
        in >> size.x >> size.y >> gridsize>> layers >> texture_file;
        
        //Tiles 
        
          this->grid_sizeF = static_cast<float>(gridsize);
          this->gridsizeI = gridsize;
          this->MaxSizeWorldGrid.x = size.x;
          this->MaxSizeWorldGrid.y =  size.y;
          this->MaxSizeWorld_F.x = static_cast<float>(size.x) * gridsize;
          this->MaxSizeWorld_F.y = static_cast<float>(size.y) * gridsize;
          this->layers = layers;
          this->texture_file = texture_file;
        
          this->clear();

          this->Map.resize(this->MaxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile* > > > ());
          
          for (int x = 0; x < this->MaxSizeWorldGrid.x; x++ )
          {
              
              for (int y = 0; y < this->MaxSizeWorldGrid.y; y++ )
              {
                  this->Map[x].resize(this->MaxSizeWorldGrid.y,std::vector< std::vector<Tile*> > ());
        
                  for (int z = 0; z < this->layers; z++ )
                  {
                      this->Map[x][y].resize(this->layers, std::vector<Tile*>());
                      
                  }
                  
              }
          
          }
          
        if(!this->tileTextureSheet.loadFromFile(resourcePath() + texture_file))
        {
            std::cout << "ERROR CODE TILEMAP:458 || LOADFROMFILE || Reason: UNABLE_TO_OPEN_FILE" << std::endl;
            
            throw std::runtime_error("ERROR CODE TILEMAP:458 || LOADFROMFILE || Reason: UNABLE_TO_OPEN_FILE");
        }
        while (in >> x >> y >> z >> type)
        {
            if(type == TileTypes::SPAWNER)
            {
                
                int enemy_type= 0;
                int enemyAmount= 0;
                int enemyTimer= 0;
                int enemyMaxDistance= 0;
                
                in >> textureX >> textureY >> enemy_type >> enemyAmount >> enemyTimer >> enemyMaxDistance;
                
                
                this->Map[x][y][z].push_back(new EnemySpawner(x, y, this->grid_sizeF, this->tileTextureSheet,
                                 sf::IntRect(textureX, textureY, 17, 17), enemy_type,
                                 enemyAmount, enemyTimer, enemyMaxDistance));
            }
            
            else
            {
                in >> textureX >> textureY >> collision;
                
                this->Map[x][y][z].push_back(new NormalTile(type, x, y, grid_sizeF, this->tileTextureSheet, sf::IntRect(textureX, textureY, 17, 17), collision));
            }
        }
        
        
    
    }
    else
    {
        std::cout << "ERROR CODE TILEMAP:3 || LOADFROMFILE || COULD NOT LOAD" << std::endl;
        
        throw std::runtime_error("ERROR CODE TILEMAP:3 || LOADFROMFILE || COULD NOT LOAD");
    }
    
    in.close();
}

void TileMap::update(Entity *entity, const float& dt)
{
    
    
    
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
    /*!
     @breif   Get the number of tiles placed on one grid position.
    
     @param   const int   x   The X-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x]
    
     @param   const int   y   The Y-value (relative to the Tilemap vector) to place a tile on. e.g. TileMap[x][y]
    
     @param   const int   z   The Z-value (relative to the Tilemap vector) to place a tile on e.g. TileMap[x][y][z]
    
     @return  const int   The Number Of tiles Placed on a grid.
    
     @return  unsigned    Outside of the Tilemap bounds if the return value from this function is negative.
    */
  
   
    if (x >= 0 && x < static_cast<int>(this->Map.size()))
    {
        if(y >=0 && y < static_cast<int>(this->Map[x].size()))
        {
            if(layer >= 0 && layer < static_cast<int>(this->Map[x][y].size()))
            {
                return static_cast<int>(this->Map[x][y][layer].size());
            }

        }
        
    }
    //Error or Zero tiles
    return -1;
}


void TileMap::DefferedRender(sf::RenderTarget &target, sf::Shader* shader, const sf::Vector2f PlayerPosition)
{
    
   /*!   @brief Renders certian elements of the tilemap behind the main view.
    
        @param  sf::RenderTarget& target   The intended render target.

        @return void    */
    
    while(!this->renderdefered.empty())
    {
        if (shader)
        {
            this->renderdefered.top()->render(target, shader, PlayerPosition);
            this->renderdefered.pop();
        }
        
        
        else {
            this->renderdefered.top()->render(target);
            this->renderdefered.pop(); }
    }
}

const sf::Vector2i &TileMap::getMaxSizeGrid() const
{
    /**
                    @brief Acessor that returns the maximum size of the Tilemap as a vector of two integers. (width x height)
                    @return sf::Vector2i     The maximum size of the tilemap as a vector of two integers
                    @see TileMap::getMaxSize()
     
     */
    return this->MaxSizeWorldGrid;
}




const sf::Vector2f TileMap::getMaxSize() const
{ /**
   @brief Acessor that returnts the maximum size of the TIlemap as a vector of two floating points
   @return sf::Vector2f the maximum size of the tilemap as a vector of two floaing points
    @see Tilemap::getMaxSizeGrid()
   */
    return this->MaxSizeWorld_F;
}

const bool TileMap::TileEmpty(const int x, const int y, const int z) const
{
    
        if (x >= 0 && x < this->MaxSizeWorldGrid.x &&
            y >= 0 && y < this->MaxSizeWorldGrid.y &&
            z >= 0 && z < this->layers)
        {
            
                return this->Map[x][y][z].empty();
           
        }
    
        else if(x < 0 || y < 0 || z < 0)
        {
            return false;
        }
    
        else if (!x || !y || !z)
        {
            throw std::invalid_argument("Invalid Argument: Tile does not exist");
        }
    
}



const bool TileMap::checktype(const int x, const int y, const int z, const int type) const
{
        
    return this->Map[x][y][this->layer].back()->gettype() == type; 
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const int enemytype, const int enemyamount, const int timeToSpawn, const int MaxDistance)
{

    if ( x < this->MaxSizeWorldGrid.x && x >= 0
        && y < this->MaxSizeWorldGrid.y && y >= 0
        && z < this->layers && z >= 0 )
    {
            /*if okay to add tile*/
            this->Map[x][y][z].push_back(new EnemySpawner(x, y, this->grid_sizeF, this->tileTextureSheet, texture_rect, enemytype ,enemyamount, timeToSpawn, MaxDistance));
    }
        
}

void TileMap::updateWorldBoundsCollision(Entity *entity, const float &dt)
{
    //World Bounds
    if(entity->getPosition().x < 0.f )
    {
        entity->setposition(0.f, entity->getPosition().y);
        entity->stopVelocityX();
    }
    else if (entity->getPosition().x + entity->getGlobalBounds().width > this->MaxSizeWorld_F.x)
    {
        entity->setposition(this->MaxSizeWorld_F.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->stopVelocityX();
    }
    if (entity->getPosition().y < 0.f)
    {
        entity->setposition(entity->getPosition().x, 0.f);
        entity->stopVelocityY();
    }
    else if (entity->getPosition().y + entity->getGlobalBounds().height > this->MaxSizeWorld_F.y)
    {
        entity->setposition(entity->getPosition().x, this->MaxSizeWorld_F.y - entity->getGlobalBounds().height);
        entity->stopVelocityY();
    }
    
}

void TileMap::updateTiles(Entity *entity, const float &dt, EnemySystem& enemysystem)
{
    this->layer = 0;
    
    this->FromX = entity->getGridPosition(this->gridsizeI).x -27;
    
        if(this->FromX < 0)
            this->FromX = 0;
        else if (this->FromX > this->MaxSizeWorldGrid.x)
            this->FromX = this->MaxSizeWorldGrid.x;
    
    this->ToX = entity->getGridPosition(this->gridsizeI).x + 27;
    
        if(this->ToX < 0)
                   this->ToX = 0;
               else if (this->ToX > this->MaxSizeWorldGrid.x)
                   this->ToX = this->MaxSizeWorldGrid.x;
       
    this->FromY = entity->getGridPosition(this->gridsizeI).y -27;
    
        if(this->FromY < 0)
                   this->FromY = 0;
               else if (this->FromY > this->MaxSizeWorldGrid.x)
                   this->FromY = this->MaxSizeWorldGrid.x;
       
    this->ToY = entity->getGridPosition(this->gridsizeI).y + 27;
    
        if(this->ToY < 0)
                   this->ToY = 0;
               else if (this->ToY > this->MaxSizeWorldGrid.x)
                   this->ToY = this->MaxSizeWorldGrid.x;
       
    
    
    for (int x= this->FromX; x < this->ToX; x++ )
    {
        for (int y= this->FromY; y < this->ToY; y++ )
        {
            for (size_t k=0; k < this->Map[x][y][this->layer].size(); k++)
            {
                this->Map[x][y][this->layer][k]->update();
                 
                if (this->Map[x][y][this->layer][k]->gettype() == TileTypes::SPAWNER)
                {
                    EnemySpawner* es = dynamic_cast<EnemySpawner*>(this->Map[x][y][this->layer][k]);
                    if (es)
                    {
                        if(!es->getSpawned() && es->getEnemyCounter() < es->getEnemyAmount())
                        {
                            try
                            {
                            enemysystem.SpawnEnemy(BLRB, x*this->grid_sizeF, y*this->grid_sizeF, *es);
                            es->SetSpawned(true);
                            }
                            
                            catch(std::invalid_argument& e)
                            {
                                std::cerr << e.what();
                            }
                            
                            
                        

                        }
                    }
                }
                
            }
        }
    }
            
    
    
}

void TileMap::updateTileCollision(Entity *entity, const float &dt)
{
    
    //Tile Culling
    
    this->layer = 0;
    
    this->FromX = entity->getGridPosition(this->gridsizeI).x -27;
    
        if(this->FromX < 0)
            this->FromX = 0;
        else if (this->FromX > this->MaxSizeWorldGrid.x)
            this->FromX = this->MaxSizeWorldGrid.x;
    
    this->ToX = entity->getGridPosition(this->gridsizeI).x + 27;
    
        if(this->ToX < 0)
                   this->ToX = 0;
               else if (this->ToX > this->MaxSizeWorldGrid.x)
                   this->ToX = this->MaxSizeWorldGrid.x;
       
    this->FromY = entity->getGridPosition(this->gridsizeI).y -27;
    
        if(this->FromY < 0)
                   this->FromY = 0;
               else if (this->FromY > this->MaxSizeWorldGrid.x)
                   this->FromY = this->MaxSizeWorldGrid.x;
       
    this->ToY = entity->getGridPosition(this->gridsizeI).y + 27;
    
        if(this->ToY < 0)
                   this->ToY = 0;
               else if (this->ToY > this->MaxSizeWorldGrid.x)
                   this->ToY = this->MaxSizeWorldGrid.x;
       
    
    
    for (int x= this->FromX; x < this->ToX; x++ )
    {
        for (int y= this->FromY; y < this->ToY; y++ )
        {
            for (size_t k=0; k < this->Map[x][y][this->layer].size(); k++)
            {
              
           sf::FloatRect playerBounds = entity->getGlobalBounds();
           sf::FloatRect wallBounds = this->Map[x][y][this->layer][k]->getGlobalBounds();
           sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

           if (this->Map[x][y][this->layer][k]->getCollision() &&
               this->Map[x][y][this->layer][k]->intersects(nextPositionBounds)
               )
           {
               //Bottom collision
               if (playerBounds.top < wallBounds.top
                   && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                   && playerBounds.left < wallBounds.left + wallBounds.width
                   && playerBounds.left + playerBounds.width > wallBounds.left
                   )
               {
                   entity->stopVelocityY();
                   entity->setposition(playerBounds.left, wallBounds.top - playerBounds.height);
               }

               //Top collision
               else if (playerBounds.top > wallBounds.top
                   && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                   && playerBounds.left < wallBounds.left + wallBounds.width
                   && playerBounds.left + playerBounds.width > wallBounds.left
                   )
               {
                   entity->stopVelocityY();
                   entity->setposition(playerBounds.left, wallBounds.top + wallBounds.height);
               }

               //Right collision
               if (playerBounds.left < wallBounds.left
                   && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                   && playerBounds.top < wallBounds.top + wallBounds.height
                   && playerBounds.top + playerBounds.height > wallBounds.top
                   )
               {
                   entity->stopVelocityX();
                   entity->setposition(wallBounds.left - playerBounds.width, playerBounds.top);
               }

               //Left collision
               else if (playerBounds.left > wallBounds.left
                   && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                   && playerBounds.top < wallBounds.top + wallBounds.height
                   && playerBounds.top + playerBounds.height > wallBounds.top
                   )
               {
                   entity->stopVelocityX();
                   entity->setposition(wallBounds.left + wallBounds.width, playerBounds.top);
               }
            
                
               }
            }
        }
       
    }

    
}




void TileMap::renderlighttile(sf::RenderTarget& target, sf::Shader* shader)
{
    for (int x = this->FromX ; x < this->ToX ; x++ )
             {
                 for (int y = this->FromY; y < this->ToY; y++ )
                 {
                     for (size_t k=0; k < this->Map[x][y][this->layer].size(); k++)
                     {
                         if(this->Map[x][y][this->layer][k]->gettype() == TileTypes::LIGHT)
                         {
                             
                        
                                 this->Map[x][y][this->layer][k]->render(target, shader, this->Map[x][y][this->layer][k]->getCenter());
                             
                             
                         }
                     }
                 }
             }
    
    
}





