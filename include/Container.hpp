#pragma once

#include "Component.hpp"
#include "LinkedPointerList.h"

class Container : public Component
{

public:
    Container(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    Container(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Container(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Container(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height);
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

    Component *onClick(uint16_t x, uint16_t y) override;

    void updateLayout() override;

protected:
    LinkedPointerList<Component> *components;
    
};