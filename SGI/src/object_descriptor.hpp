#ifndef SRC_OBJ_DESCRIPTOR_H_
#define SRC_OBJ_DESCRIPTOR_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "graphic_object.hpp"

using namespace std;

class ObjectDescriptor {
private:
	vector<string> _vertices;
	vector<string> _fileBody;

public:
	ObjectDescriptor();
	virtual ~ObjectDescriptor();

	void store(string name, GraphicObjectType type, vector<Coordinate> coords);
	void persist(void);
};

#endif /* SRC_OBJ_DESCRIPTOR_H_ */
