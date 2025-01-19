#include "../include/renderManager.hpp"
// using namespace std;

RenderManager::~RenderManager()
{
    // map contains vectors of pointers, so we need to delete each vector
    for (auto &element : drawOrder)
    {
        // delete vector associated with the key
        element.second.clear();
    }

    // clear the map
    drawOrder.clear();
}

void RenderManager::reset()
{
    // clear the map
    for (auto &element : drawOrder)
    {
        // delete vector associated with the key
        element.second.clear();
        element.second.shrink_to_fit(); 
    }
                           
    // drawOrder.clear();
   
}

void RenderManager::drawAll()
{
    // iterate through the map
    for (auto &element : drawOrder)
    {

        // iterate through the vector
        for (auto &renderable : element.second)
        {
            
            renderable->draw(rendererPtr);
        }
    }
    
}

void RenderManager::drawLayer(int index)
{
    
    // if the key exists, draw the elements
    if (drawOrder.find(index) != drawOrder.end())
    {
       
        for (auto &renderable : drawOrder[index])
        {
            renderable->draw(rendererPtr);
        }
    }
}