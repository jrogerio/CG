#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include <string>

#include "graphic_object.hpp"
#include "point.hpp"
#include "line.hpp"
#include "polygon.hpp"
#include "window.hpp"
#include "object_descriptor.hpp"

//#define PI 3.14159265358979323846
//#define DEG2RAD(DEG) (DEG*PI/180.0)
//#define RAD2DEG(RAD) (DEG*PI/180.0)

using namespace std;

class World {
private:
	vector<GraphicObject> _displayFile;
	Window window;

	void normalizeObjects();
	void normalize(GraphicObject& object);

public:
	World();
	virtual ~World();

	void addPoint(string name, Coordinate coord);
	void addLine(string name, Coordinate begin, Coordinate end);
	void addPolygon(string name, vector<Coordinate> coords);

	Window getWindow();

	void moveWindow(VECTOR step);
	void zoomWindow(int step);
	void rotateWindow(double angle);

	vector<GraphicObject> getObjects();
	GraphicObject& getObjectBy(string name);

	void translateObject(string name, VECTOR deslocation);
	void scaleObject(string name, VECTOR factor);
	void rotateObject(string name, double angle);
	void rotateObject(string name, double angle, Coordinate anchor);

	void exportToObj();
	vector<string> importFromObj(string filePath);
};

#endif /* SRC_WORLD_H_ */
