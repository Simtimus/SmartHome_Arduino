#ifndef BOARD_H
#define BOARD_H

// Arduino Libraries
#include <Arduino.h>
// Project Libraries
#include "Component.h"


class Board
{
public:
	Board();
	Board(String Id, String Name, String Model, String Description);

	String getId() const;
	void setId(const String &newId);

	String getName() const;
	void setName(const String &newName);

	const Component &getComponentAtIndex(int index) const;

	void setComponents(Component (&newComponents)[MAX_ITEMS]);
	Component (&getComponents())[MAX_ITEMS];

	int getComponentCount() const;
	bool addComponent(const Component &component);
	
	String getModel() const;
	void setModel(const String &newModel);
	
	String getDescription() const;
	void setDescription(const String &newDescription);

	// Default Guid
	static String DefaultGuid;

private:
	String Id;
	String Name;
	Component Components[MAX_ITEMS];
	String Model;
	String Description;		// Max length 32 characters
	int ComponentCount;
};

#endif // BOARD_H
