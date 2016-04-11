#include "object_descriptor.hpp"

ObjectDescriptor::ObjectDescriptor() {}
ObjectDescriptor::~ObjectDescriptor() {}

void ObjectDescriptor::store(string name,  GraphicObjectType type, vector<Coordinate> coords) {
	size_t initialVertexPosition = _vertices.size() + 1;
	string object;
	string vertex;

	for(Coordinate coord : coords) {
		vertex = "v " + to_string(coord._x) + ", " + to_string(coord._y) + ", 0.0";
		_vertices.push_back(vertex);
	}

	if(type == GraphicObjectType::point) {
		object = "p " + to_string(initialVertexPosition);
	} else {
		object = "l " + to_string(initialVertexPosition);

		unsigned int position = static_cast<unsigned int>(initialVertexPosition) + 1;
		unsigned int positionsLimit = static_cast<unsigned int>(_vertices.size());

		for(position; position <= positionsLimit; position++) {
			object += ", " + to_string(position);
		}

		if(type == GraphicObjectType::polygon) {
			object += ", " + to_string(initialVertexPosition);
		}
	}

	_fileBody.push_back("o " + name);
	_fileBody.push_back(object);
}

void ObjectDescriptor::persist() {
	ofstream file;
	file.open("export.obj", ofstream::trunc);

	for(string vertex : _vertices) {
		file << vertex << endl;
	}

	for(string declaration : _fileBody) {
		file << declaration << endl;
	}

	file.close();
}