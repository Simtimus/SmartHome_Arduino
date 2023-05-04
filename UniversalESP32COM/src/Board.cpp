#include "Board.h"

Board::Board()
    : Id(""), Name(""), Model(""), Description(""), ComponentCount(0)
{ }

Board::Board(String Id, String Name, String Model, String Description)
    : Id(Id), Name(Name), Model(Model), Description(Description), ComponentCount(0)
{ }

String Board::getId() const
{ return Id; }

void Board::setId(const String &newId)
{ Id = newId; }

String Board::getName() const
{ return Name; }

void Board::setName(const String &newName)
{ Name = newName; }

const Component &Board::getComponentAtIndex(int index) const
{
    if (index >= 0 && index < ComponentCount)
    {
        return Components[index];
    }
    // You should handle the case when the index is out of bounds.
    // For this example, we will return the first element.
    return Components[0];
}

void Board::setComponents(Component (&newComponents)[MAX_ITEMS])
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        Components[i] = newComponents[i];
    }
}

Component (&Board::getComponents())[MAX_ITEMS]
{ return Components; }

int Board::getComponentCount() const
{ return ComponentCount; }

bool Board::addComponent(const Component &component)
{
    if (ComponentCount < MAX_ITEMS)
    {
        Components[ComponentCount++] = component;
        return true;
    }
    return false;
}

String Board::getModel() const
{ return Model; }

void Board::setModel(const String &newModel)
{ Model = newModel; }

String Board::getDescription() const
{ return Description; }

void Board::setDescription(const String &newDescription)
{ Description = newDescription; }
