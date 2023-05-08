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

	// Non-const version
	Component &getComponentAtIndex(int index);

	// Const version
	const Component &getComponentAtIndex(int index) const;

	void setComponents(Component (&newComponents)[MAX_ITEMS]);
	Component (&getComponents())[MAX_ITEMS];

	void setComponentsCount(int newCount);
	int getComponentCount() const;
	bool addComponent(const Component &component);
	
	String getModel() const;
	void setModel(const String &newModel);
	
	String getDescription() const;
	void setDescription(const String &newDescription);

	bool getConnectionState();
	void setConnectionState(bool newState);

	// Default Guid
	static String DefaultGuid;

private:
	String Id;
	String Name;
	Component Components[MAX_ITEMS];
	String Model;
	String Description;		// Max length 32 characters
	bool isConnected;
	int ComponentCount;
};

#endif // BOARD_H