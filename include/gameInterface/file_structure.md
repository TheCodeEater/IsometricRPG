#File structure for menu widget loading

Each line represents a widget

<widget type> <widget ID> <position x> <position y> <width> <height> <z index> [parameters]

Type: the name of the class of the associted widget
ID: a string idetifying the widget, to be used only by the function that links the event handlers together
Pos x,y width, height: self explanatory
Z index: "layer" in which the object is located. Greater index means the objects will be placed on top of others (determines order of drawing)
[parameters] depending on the object nature, it may require a texture ID or something similar (filename ecc)