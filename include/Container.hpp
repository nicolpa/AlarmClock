#pragma once

#include "Component.hpp"

#define N_MAX_COMPONENTS 10

class Container : public Component
{

public:
    Container(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    virtual ~Container();

    void clear() override;

    /**
     * Get the number of components in this container
     */
    int getComponentsCount();

    /**
     * Return the component at the specified index
     * @param index The index of the component to retreive
     * @return The requested component (return null_ptr if the index is invalid)
     */
    Component* getComponent(uint16_t index);

    /**
     * Get all the container's components
     * @param components The pointer to the components array of this container 
     */
    void getComponents(Component** components);

    /**
     * Add a component to this container
     * @param component The component to be added
     */
    void add(Component* component);

    /**
     * Add a component to this container at a specified index
     * @param component The component to be added
     * @param index The index in the component array to insert this child at
     */
    void add(Component* component, uint16_t index);

    /**
     * Remove the component at a specified index from this container
     * @param index The index of the component to be removed
     */
    void remove(uint16_t index);

    /**
     * Remove the specefic container from this container
     * @param component The component to be removed from this container
     */
    void remove(Component* component);

    /**
     * Remove all the components from this container
     */
    void removeAll();

    /**
     * Draw this container with all its children
     */
    void draw() override;

    virtual bool onClick(uint16_t x, uint16_t y);

    void validate() override;
    void invalidate() override;

protected:
    /**
     * The number of components in this container
     */ 
    uint16_t nComponents = 0;

    /**
     * The array for the components of this container
     */
    Component* components[N_MAX_COMPONENTS];
};